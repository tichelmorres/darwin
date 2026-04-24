#define NOB_IMPLEMENTATION
#define NOB_STRIP_PREFIX
#define NOB_WARN_DEPRECATED
#include "nob.h"

int main(int argc, char **argv) {
    NOB_GO_REBUILD_URSELF(argc, argv);

    Cmd cmd = {0};

    cmd_append(&cmd, "gcc");
    cmd_append(&cmd, "-Wall");
    cmd_append(&cmd, "-Wextra");
    cmd_append(&cmd, "-O2");
    cmd_append(&cmd, "-o", "main");
    cmd_append(&cmd, "main.c");
    cmd_append(&cmd, "-lgdi32");
    cmd_append(&cmd, "-luser32");

    if (!cmd_run(&cmd, .dont_reset = true)) return 1;
    return 0;
}
