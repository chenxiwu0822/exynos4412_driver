#include <common.h>
#include <command.h>

int do_hello(cmd_tbl_t* cmdtp, int flag, int argc, char * const argv[])
{
        printf("hello world!\n");
}

U_BOOT_CMD
(
        hello,                  // <命令的名称>,
        1,                      // <最大参数个数>,
        1,                      // <重复次数>,
        do_hello,               // <命令底层执行的回调函数>,
        "print hello world",    // <说明命令的功能>,
        "detail"                // <说明命令的详细用法>
);
