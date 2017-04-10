#include <linux/init.h>
#include <linux/module.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>

#include <asm/io.h>

#include "beep_driver.h"

static volatile unsigned int *GPD0CON = NULL;
static volatile unsigned int *GPD0DAT = NULL;

static int tiny4412_open(struct inode *my_indoe, struct file *my_file)
{
        *GPD0CON &= ~(0xf << 0 * 4);
        *GPD0CON |= (1 << 0 * 4);
        printk(KERN_INFO "open set the gpio to output mode\n");
        return 0;
}

static int tiny4412_release(struct inode *my_indoe, struct file *my_file)
{
        *GPD0DAT &= ~(1 << 0);
        printk(KERN_INFO "release close the beep\n");
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
        case BEEP_ON:
                *GPD0DAT |= (1 << 0);
                printk(KERN_INFO "ioctl open the beep\n");
                break;
                
        case BEEP_OFF:
                *GPD0DAT &= ~(1 << 0);
                printk(KERN_INFO "ioctl close the beep\n");
                break;
                
        default:
                *GPD0DAT &= ~(1 << 0);
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
        .name  = "beep_device",
        .fops  = &tiny4412_fops,
};

static int __init mod_init(void)
{
        misc_register(&misc);

        GPD0CON = ioremap(0x114000A0, 4);
        GPD0DAT = ioremap(0x114000A4, 4);
        
        printk(KERN_INFO "mod_init ok\n");
        return 0;
}

static void __exit mod_exit(void)
{
        misc_deregister(&misc);
        
        iounmap(GPD0CON);
        iounmap(GPD0DAT);
        
        printk(KERN_INFO "mod_exit ok\n");
}

module_init(mod_init);
module_exit(mod_exit);

MODULE_LICENSE("GPL");
