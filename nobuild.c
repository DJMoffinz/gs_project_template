#define NOBUILD_IMPLEMENTATION
#include "./nobuild.h"
#include "./source/main.h"

//#define PROJ_NAME "App"
#define PROJ_NAME PROJECT_NAME

#define BUILD_DIR "bin"

#define OUT_PATH PATH(BUILD_DIR, PROJ_NAME)

// compiler to use
#ifndef _WIN32
#    define CC "cc"
#    define EXT
#else
#    if defined(__GNUC__)
#       define CC "gcc"
#    elif defined(__clang__)
#       define CC "clang"
#    elif defined(_MSC_VER)
#       define CC "cl.exe"
#    endif
#    define OSLIBS "opengl32.lib", "kernel32.lib", "user32.lib", \
                   "shell32.lib", "vcruntime.lib", "msvcrt.lib", "gdi32.lib", "Winmm.lib", "Advapi32.lib" //wow imagine having to include all these, couldn't be windows users
#    define EXT ".exe"
#endif

#ifndef _MSC_VER // build flags for all common compilers except MSVC (hopefully, not tested)
#    define f "-"
#    define CFLAGS f "std=gnu99", f "w", f "ldl", f "lGL", f "lX11", f "pthread", f "lXi", f "lm"
#    define REL_FLAGS f "O3"
#    define DBG_FLAGS f "g", f "O0"
#    define OUTPUT f "o", OUT_PATH
#else            // build flags for MSVC
#    define f "/"
#    define CFLAGS f "EHsc", f "link", f "SUBSYSTEM:CONSOLE", f "NODEFAULTLIB:msvcrt.lib", f "NODEFAULTLIB:LIBCMT", OSLIBS
#    define REL_FLAGS f "MP", f "FS", f "Ox", f "W0"
#    define DBG_FLAGS f "w", f "MP", "-Zi", f "DEBUG:FULL"
#    define OUTPUT f "Fe", OUT_PATH
#endif

// Include directories
#define INCLUDE f "I", PATH(".", "third_party", "include")

// Source files
// TODO: figure out how to make wildcards work in path macros
#define SOURCES PATH(".","source","main.c")

void clean_build_dir(void)
{
    INFO("Cleaning build directory...");
    RM(BUILD_DIR); // Remove the 'bin' directory if it exists
    MKDIRS(BUILD_DIR); // Create the 'bin' directory
}

//TODO: figure out how to use the array making function properly so this function works.
//I also tried using the JOIN macro, but the CMD macro seems to really hate args with spaces
Cstr_Array debug_or_release_flags(int argc, char **argv)
{
     if (argc>1) {
            if (strcmp(argv[1], "release") == 0) {
                INFO("Building release...");
                return cstr_array_make(REL_FLAGS, NULL);
            } else if (strcmp(argv[1], "debug") == 0) {
                INFO("Bulding debug...");
                return cstr_array_make(DBG_FLAGS, NULL);
            } else {
                PANIC("Unrecognised build type specification, \"release\" and \"debug\" are valid specifications.");
            };
    }
    WARN("Build type not specified, defaulting to release...");
    return cstr_array_make(REL_FLAGS, NULL);
}

int main(int argc, char **argv)
{
    GO_REBUILD_URSELF(argc, argv); // Rebuild if the build script changes


    clean_build_dir();
    //Cstr_Array flags = debug_or_release_flags(argc, argv);

    INFO("Building project...");
    CMD(CC,
        //*flags.elems,
        REL_FLAGS,
        INCLUDE,
        SOURCES,
        CFLAGS,
        OUTPUT EXT  // Output file path with file extension added
    );

    return 0;
}
