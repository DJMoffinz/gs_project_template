#define NOB_IMPLEMENTATION
#include "nob.h"

#define PROJ_NAME "App"

#define SRC_DIR "source/"
#define BUILD_DIR "bin/"
#define THIRDPARTY_DIR "third_party/include/"

int main(int argc, char **argv)
{
    NOB_GO_REBUILD_URSELF(argc, argv);

    Nob_Cmd cmd = {0};

    if (!nob_mkdir_if_not_exists(BUILD_DIR)) return 1;

    nob_cc(&cmd);
#if !defined(_MSC_VER) //linux or mingw
    nob_cmd_append(&cmd, "-O3");
    nob_cmd_append(&cmd, "-I", THIRDPARTY_DIR);
    nob_cc_inputs(&cmd, SRC_DIR "main.c");
    nob_cmd_append(&cmd, "-std=gnu99", "-w");
#   if !defined(__MINGW32__)
    nob_cmd_append(&cmd, "-ldl", "-lGL", "-lX11", "-pthread", "-lXi");
    if (setenv("MESA_GL_VERSION_OVERRIDE", "3.3", 1)) return 1; //fail if setting this variable fails for any reason
#   else
    nob_cmd_append(&cmd, "-lopengl32", "-lkernel32", "-luser32", "-lshell32", "-lgdi32", "-lWinmm", "-lAdvapi32");
#   endif
    nob_cmd_append(&cmd, "-lm");
#else //msvc
#define DBG_FLAGS "/w", "/MP", "-Zi", "/DEBUG:FULL"
#define REL_FLAGS "/MP", "/FS", "/Ox", "/W0"
    nob_cmd_append(&cmd, DBG_FLAGS);
    nob_cmd_append(&cmd, "/I", THIRDPARTY_DIR);
    nob_cc_inputs(&cmd, SRC_DIR "*.c");
    nob_cmd_append(&cmd, "/EHsc", "/link", "/SUBSYSTEM:CONSOLE", "/NODEFAULTLIB:msvcrt.lib", "/NODEFAULTLIB:LIBCMT",
    "opengl32.lib", "kernel32.lib", "user32.lib",
    "shell32.lib", "vcruntime.lib", "msvcrt.lib", "gdi32.lib", "Winmm.lib", "Advapi32.lib");

#endif
    nob_cc_output(&cmd, BUILD_DIR PROJ_NAME);
    if (!nob_cmd_run(&cmd)) return 1;
    nob_cmd_append(&cmd, "./" BUILD_DIR PROJ_NAME);
    if (!nob_cmd_run(&cmd)) return 1;
    return 0;
}
