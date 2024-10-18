#define NOBUILD_IMPLEMENTATION
#include "./nobuild.h"
#include "./source/main.h"
//#include <libgen.h>
//#define IMCWD basename(GETCWD())

//#define PROJ_NAME "App"
#define PROJ_NAME PROJECT_NAME

#define BUILD_DIR "bin"

// compiler to use
#ifndef _WIN32
#    define CC "cc"
#else
#    if defined(__GNUC__)
#       define CC "gcc"
#    elif defined(__clang__)
#       define CC "clang"
#    elif defined(_MSC_VER)
#       define CC "cl.exe"
#    endif
#endif

//properties users can change
#ifndef _MSC_VER // build flags for all common compilers except MSVC (hopefully, not tested)
#    define f "-"
#    define CFLAGS f "std=gnu99", f "w", f "ldl", f "lGL", f "lX11", f "pthread", f "lXi", f "lm"
#    define REL_FLAGS f "O3"
#    define DBG_FLAGS f "O0", f "g"
#    define OUTPUT f "o", PATH(BUILD_DIR, PROJ_NAME)
#else         // build flags for MSVC
#    define f "/"
#    define CFLAGS f "EHsc", f "link", f "SUBSYSTEM:CONSOLE", f "NODEFAULTLIB:msvcrt.lib", f "NODEFAULTLIB:LIBCMT" \ //actual flags
                   "opengl32.lib", "kernel32.lib", "user32.lib", \                                                   //manually linked os libraries
                   "shell32.lib", "vcruntime.lib", "msvcrt.lib", "gdi32.lib", "Winmm.lib", "Advapi32.lib"            //more os libraries kekw, imagine using windows
#    define REL_FLAGS f "MP", f "FS", f "Ox", f "W0"
#    define DBG_FLAGS f "w", f "MP", "-Zi", f "DEBUG:FULL"
#    define OUTPUT f "Fe", PATH(BUILD_DIR, PROJ_NAME ".exe")
#endif

// Include directories
#define INCLUDE f "I", PATH(".", "third_party", "include")

// Source files
// TODO: figure out how to make wildcards work in path macros, this also probably means i'll need to be able to pass arrays to the CMD macro
#define SOURCES PATH(".","source","main.c") //i will say that being able to pass wildcarded file paths to msvc is one thing windows did right

void clean_build_dir(void)
{
    INFO("Cleaning build directory...");
    RM(BUILD_DIR); // Remove the 'bin' directory if it exists
    MKDIRS(BUILD_DIR); // Create the 'bin' directory
}

//TODO: this doesnt work cause you cant use macros when the silly thing is compiled, so it defaults to release no matter what argument you pass to it
int main(int argc, char **argv)
{
    GO_REBUILD_URSELF(argc, argv); // Rebuild if the build script changes

    if (argc>0) {
            if (strcmp(argv[1], "release") == 0) {
                INFO("Building release...");
                #define FLAGS REL_FLAGS
            } else if (strcmp(argv[1], "debug") == 0) {
                INFO("Bulding debug...");
                #define FLAGS DBG_FLAGS
            } else {
                PANIC("Unrecognised build type specification, \"release\" and \"debug\" are valid specifications.");
            };
    } else {
        WARN("Build type not specified, defaulting to release...");
        #define FLAGS REL_FLAGS
    };

    clean_build_dir();
    INFO("Building project...");

    CMD(CC,
        FLAGS,
        INCLUDE,    // Include paths
        SOURCES,    // Source file
        //sources.elems;
        CFLAGS,     // Compiler flags
        OUTPUT      // Output file path
    );

    return 0;
}
