#define NOBUILD_IMPLEMENTATION
#include "./nobuild.h"
#include "./source/main.h"
//#include <libgen.h>
//#define IMCWD basename(GETCWD())

//#define PROJ_NAME "App"
#define PROJ_NAME PROJECT_NAME

#define BUILD_DIR "bin"

//properties users should change
#ifndef WIN32 // *NIX build flags

#define CC "cc"
#define CFLAGS "-std=gnu99", "-w", "-ldl", "-lGL", "-lX11", "-pthread", "-lXi", "-lm"
#define REL_FLAGS "-O3"
#define OUTPUT "-o", PATH(BUILD_DIR, PROJ_NAME)

#else         // Winblows build flags

#define CC "cl.exe"
#define CFLAGS "/EHsc", "/link", "/SUBSYSTEM:CONSOLE", "/NODEFAULTLIB:msvcrt.lib", "/NODEFAULTLIB:LIBCMT" \ //actual flags
               "opengl32.lib", "kernel32.lib", "user32.lib", \                                              //manually linked os libraries
               "shell32.lib", "vcruntime.lib", "msvcrt.lib", "gdi32.lib", "Winmm.lib", "Advapi32.lib"       //more os libraries kekw, imagine using windows
#define REL_FLAGS "/MP", "/FS", "/Ox", "/W0"
#define DBG_FLAGS "/w", "/MP", "-Zi", "/DEBUG:FULL"
#define OUTPUT "/Fe", PATH(BUILD_DIR, PROJ_NAME ".exe")

#endif

// Include directories
#define INCLUDE "-I", PATH(".", "third_party", "include")

// Source files
// TODO: figure out how to make wildcards work in path macros, this also means i'll need to be able to pass arrays to the CMD macro
#define SOURCES PATH(".","source","main.c") //i will say that being able to pass wildcarded file paths to msvc is one thing windows did right

void clean_build_dir(void)
{
    INFO("Cleaning build directory...");
    RM(BUILD_DIR); // Remove the 'bin' directory if it exists
    MKDIRS(BUILD_DIR); // Create the 'bin' directory
}

void build_project(void)
{
    INFO("Building project...");

    CMD(CC,
        REL_FLAGS,
        INCLUDE,    // Include paths
        SOURCES,    // Source file
        //sources.elems;
        CFLAGS,     // Compiler flags
        OUTPUT      // Output file path
    );
}

int main(int argc, char **argv)
{
    GO_REBUILD_URSELF(argc, argv); // Rebuild if the build script changes

    clean_build_dir();
    build_project();

    return 0;
}
