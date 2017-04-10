#include <linux/init.h>
#include <linux/module.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>

#include <asm/io.h>

#include <linux/gpio.h>
#include <mach/gpio.h>
#include <plat/gpio-cfg.h>

#include "led_driver.h"

static int tiny4412_open(struct inode *my_indoe, struct file *my_file)
{
        printk(KERN_INFO "open do nothing\n");
        return 0;
}

static int tiny4412_release(struct inode *my_indoe, struct file *my_file)
{
        gpio_set_value(EXYNOS4X12_GPM4(0), 1);
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
                gpio_set_value(EXYNOS4X12_GPM4(0), 0);
                printk(KERN_INFO "ioctl open the led\n");
                break;
                
        case LED_OFF:
                gpio_set_value(EXYNOS4X12_GPM4(0), 1);
                printk(KERN_INFO "ioctl close the led\n");
                break;
        default:
                gpio_set_value(EXYNOS4X12_GPM4(0), 1);
                printk(KERN_INFO "ioctl close the led\n");
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
        int ret;
        gpio_free(EXYNOS4X12_GPM4(0));
        ret = gpio_request(EXYNOS4X12_GPM4(0), "led");
        if (ret) 
        {
                printk(KERN_INFO "gpio_request fail");
                return ret;
        }
        s3c_gpio_cfgpin(EXYNOS4X12_GPM4(0), S3C_GPIO_OUTPUT);
        gpio_set_value(EXYNOS4X12_GPM4(0), 1);
        misc_register(&misc);
        printk(KERN_INFO "mod_init ok\n");
        return 0;
}

static void __exit mod_exit(void)
{
        gpio_free(EXYNOS4X12_GPM4(0));
        misc_deregister(&misc);
        printk(KERN_INFO "mod_exit ok\n");
}

module_init(mod_init);
module_exit(mod_exit);

MODULE_LICENSE("GPL");
