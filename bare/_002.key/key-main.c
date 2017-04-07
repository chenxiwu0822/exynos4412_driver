/* 1、LED灯接口配置寄存器 */
#define GPM4CON (*(volatile unsigned int *)0x110002E0)
#define GPM4DAT (*(volatile unsigned int *)0x110002E4)

/* 2、按键接口配置寄存器 */
#define GPX3CON (*(volatile unsigned int *)0x11000C60)
#define GPX3DAT (*(volatile unsigned int *)0x11000C64)

/* 3、蜂鸣器接口配置*/
#define GPD0CON (*(volatile unsigned int *)0x114000A0)
#define GPD0DAT (*(volatile unsigned int *)0x114000A4)

int main(void)
{
        /* 1、设置GPM4CON为输出模式 */
        GPM4CON &= ~((0xf << 3 * 4) | (0xf << 2 * 4) | (0xf << 1 * 4) | (0xf << 0 * 4));
        GPM4CON |=  ((1  << 3 * 4) | (1  << 2 * 4) | (1  << 1 * 4) | (1  << 0 * 4));

        /* 2、设置按键接口管脚为输入模式
         * key1 ---> GPX3_2
         * key2 ---> GPX3_3
         * key3 ---> GPX3_4
         * key4 ---> GPX3_5
         */
        GPX3CON &= ~((0xf << 2 * 4) | (0xf << 3 * 4) | (0xf << 4 * 4) | (0xf << 5 * 4));
        
        /* 3. 设置蜂鸣器为输出模式 */
        GPD0CON &= ~(0xf << 0 * 4);
        GPD0CON |=  (1   << 0 * 4);
    
        /* 4、根据key来控制led灯 */
        while(1) 
        {
                if(!(GPX3DAT & (1 << 2)))       // 判断按键1是否按下，如果按下进入if语句
                {  
                        GPM4DAT &= ~(1 << 0);   // 点亮第一个灯
                        GPD0DAT |= (1 << 0);    // 开蜂鸣器
                }

                else if(!(GPX3DAT & (1 << 3)))  // 判断按键2是否按下，如果按下进入if语句
                {
                        GPM4DAT &= ~(1 << 1);   // 点亮第二个灯
                GPD0DAT |= (1 << 0);            // 开蜂鸣器
                }

                else if(!(GPX3DAT & (1 << 4)))  // 判断按键3是否按下，如果按下进入if语句
                {
                        GPM4DAT &= ~(1 << 2);   // 点亮第三个灯
                        GPD0DAT |= (1 << 0);    // 开蜂鸣器
                }

                else if(!(GPX3DAT & (1 << 5)))  // 判断按键4是否按下，如果按下进入if语句
                { 
                        GPM4DAT &= ~(1 << 3);   // 点亮第四个灯
                        GPD0DAT |= (1 << 0);    // 开蜂鸣器
                }

                else
                {
                        // 如果没有按键按下全灭
                        GPM4DAT |= (1 << 3) | (1 << 2) | (1 << 1) | (1 << 0);
                        GPD0DAT &=~(1 << 0);    // 关蜂鸣器
                }
        }
        return 0;
}

