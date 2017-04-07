.text
.globl _start
_start:
        ldr sp, =0x02060000   // 设置栈                  
        bl main               // 调用main函数
halt_loop:
        b halt_loop