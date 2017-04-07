#define GPM4CON (*(volatile unsigned int *)0x110002E0)
#define GPM4DAT (*(volatile unsigned int *)0x110002E4)

int main(void)
{
        GPM4CON &= ~(0xf << 0 * 4);     // 清除寄存器
        GPM4CON |= (1 << 0 * 4);        // 输出模式
        while(1)
        {
                GPM4DAT &= ~(1 << 0);   // 点亮第一个灯 
        }
        return 0;
}
