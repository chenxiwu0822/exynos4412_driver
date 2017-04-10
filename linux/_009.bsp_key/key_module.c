#include <linux/init.h>
#include <linux/module.h>
#include <linux/miscdevice.h>
#include <linux/uaccess.h>
#include <linux/fs.h>

#include <asm/io.h>

#include <linux/gpio.h>
#include <mach/gpio.h>
#include <plat/gpio-cfg.h>

static int tiny4412_open(struct inode *my_indoe, struct file *my_file)
{
        printk(KERN_INFO "open do nothing\n");
        return 0;
}

static int tiny4412_release(struct inode *my_indoe, struct file *my_file)
{
        printk(KERN_INFO "release do nothing\n");
        return 0;
}

static ssize_t tiny4412_read(struct file *my_file, char __user *buff, size_t cnt, loff_t *loff)
{
        int key = 0;
        if(!gpio_get_value(EXYNOS4_GPX3(2))) 
        {  
                key = 0x01;
        }
        else if(!gpio_get_value(EXYNOS4_GPX3(3))) 
        {
                key = 0x02;   
        }
        else if(!gpio_get_value(EXYNOS4_GPX3(4))) 
        {
                key = 0x03;   
        }
        else if(!gpio_get_value(EXYNOS4_GPX3(5))) 
        {
                key = 0x04;   
        }
        copy_to_user(buff, &key, 4);
        return 0;
}

static ssize_t tiny4412_write(struct file *my_file, const char __user *buff, size_t cnt, loff_t *loff)
{
        printk(KERN_INFO "write do nothing\n");
        return 0;
}

static int tiny4412_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
        printk(KERN_INFO "ioctl do nothing\n");
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
        .name  = "key_device",
        .fops  = &tiny4412_fops,
};

static int __init mod_init(void)
{
        gpio_free(EXYNOS4_GPX3(2));
        gpio_free(EXYNOS4_GPX3(3));
        gpio_free(EXYNOS4_GPX3(4));
        gpio_free(EXYNOS4_GPX3(5));
        
        gpio_request(EXYNOS4_GPX3(2), "key1");
        gpio_request(EXYNOS4_GPX3(3), "key2");
        gpio_request(EXYNOS4_GPX3(4), "key3");
        gpio_request(EXYNOS4_GPX3(5), "key4");
        
        s3c_gpio_cfgpin(EXYNOS4_GPX3(2), S3C_GPIO_INPUT);
        s3c_gpio_cfgpin(EXYNOS4_GPX3(3), S3C_GPIO_INPUT);
        s3c_gpio_cfgpin(EXYNOS4_GPX3(4), S3C_GPIO_INPUT);
        s3c_gpio_cfgpin(EXYNOS4_GPX3(5), S3C_GPIO_INPUT);
        
        misc_register(&misc);
        printk(KERN_INFO "mod_init ok\n");
        return 0;
}

static void __exit mod_exit(void)
{
        misc_deregister(&misc);
        
        gpio_free(EXYNOS4_GPX3(2));
        gpio_free(EXYNOS4_GPX3(3));
        gpio_free(EXYNOS4_GPX3(4));
        gpio_free(EXYNOS4_GPX3(5));
        
        printk(KERN_INFO "mod_exit ok\n");
}

module_init(mod_init);
module_exit(mod_exit);

MODULE_LICENSE("GPL");
