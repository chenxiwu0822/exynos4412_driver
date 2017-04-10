#include <linux/init.h>
#include <linux/module.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>

#include <asm/io.h>

#include "led_driver.h"

static volatile unsigned int *GPM4CON = NULL;
static volatile unsigned int *GPM4DAT = NULL;

static int tiny4412_open(struct inode *my_indoe, struct file *my_file)
{
        *GPM4CON &= ~(0xf << 0 * 4);
        *GPM4CON |= (1 << 0 * 4);
        printk(KERN_INFO "open set the gpio to output mode\n");
        return 0;
}

static int tiny4412_release(struct inode *my_indoe, struct file *my_file)
{
        *GPM4DAT |= (1 << 0);
        printk(KERN_INFO "release close the led\n");
        return 0;
}

static ssize_t tiny4412_read(struct file *my_file, char __user *buff, size_t cnt, loff_t *loff)
{
        printk(KERN_INFO "read do nothing\n");
        return 0;
}

static ssize_t tiny4412_write(struct file *my_file, const char __user *buff, size_t cnt, loff_t *loff)
{
        printk(KERN_INFO "write do nothing\n");
        return 0;
}

static int tiny4412_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
        switch(cmd) 
        {
        case LED_ON:
                *GPM4DAT &= ~(1 << 0);
                printk(KERN_INFO "ioctl open the led\n");
                break;
                
        case LED_OFF:
                *GPM4DAT |= (1 << 0);
                printk(KERN_INFO "ioctl close the led\n");
                break;
                
        default:
                *GPM4DAT |= (1 << 0);
                break;
        }

        return 0;
}

static struct file_operations tiny4412_fops =
{
        .open           = tiny4412_open,
        .release        = tiny4412_release,
        .read           = tiny4412_read,
        .write          = tiny4412_write,
        .unlocked_ioctl = tiny4412_ioctl,
};

static struct miscdevice misc =
{
        .minor = 255,
        .name  = "led_device",
        .fops  = &tiny4412_fops,
};

static int __init mod_init(void)
{
        misc_register(&misc);
        
        GPM4CON = ioremap(0x110002E0, 4);
        GPM4DAT = ioremap(0x110002E4, 4);
        
        printk(KERN_INFO "mod_init ok\n");
        return 0;
}

static void __exit mod_exit(void)
{
        misc_deregister(&misc);
        
        iounmap(GPM4CON);
        iounmap(GPM4DAT);
        
        printk(KERN_INFO "mod_exit ok\n");
}

module_init(mod_init);
module_exit(mod_exit);

MODULE_LICENSE("GPL");
