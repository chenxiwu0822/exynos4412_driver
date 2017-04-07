.text
.globl _start                   // 汇编总是从 _start 开始执行
_start:                         // 相当于 C 里面的 main 函数
        ldr sp, =0x02060000     // 设置栈                  
        bl main                 // 调用 main 函数
halt_loop:
        b halt_loop
