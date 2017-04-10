#include <linux/init.h>
#include <linux/module.h>
#include <linux/miscdevice.h>
#include <linux/uaccess.h>
#include <linux/fs.h>

#include <asm/io.h>

static volatile unsigned int *GPX3CON = NULL;
static volatile unsigned int *GPX3DAT = NULL;

static int tiny4412_open(struct inode *my_indoe, struct file *my_file)
{
        /* key1 -> GPX3_2   key2 -> GPX3_3   key3 -> GPX3_4   key4 -> GPX3_5 */
        *GPX3CON &= ~((0xf << 2 * 4) | (0xf << 3 * 4) | (0xf << 4 * 4) | (0xf << 5 * 4));
        printk(KERN_INFO "open set the gpio to input mode\n");
        return 0;
}

static int tiny4412_release(struct inode *my_indoe, struct file *my_file)
{
        printk(KERN_INFO "close do nothing\n");
        return 0;
}

static ssize_t tiny4412_read(struct file *my_file, char __user *buff, size_t cnt, loff_t *loff)
{
        int key = 0;
        if(!(*GPX3DAT & (1 << 2))) 
        {  
                key = 0x01;
        }
        else if(!(*GPX3DAT & (1 << 3))) 
        {
                key = 0x02;   
        }
        else if(!(*GPX3DAT & (1 << 4))) 
        {
                key = 0x03;   
        }
        else if(!(*GPX3DAT & (1 << 5))) 
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
        misc_register(&misc);
        
        GPX3CON = ioremap(0x11000C60, 4);
        GPX3DAT = ioremap(0x11000C64, 4);
        
        printk(KERN_INFO "mod_init ok\n");
        return 0;
}

static void __exit mod_exit(void)
{
        misc_deregister(&misc);
        
        iounmap(GPX3CON);
        iounmap(GPX3DAT);
        
        printk(KERN_INFO "mod_exit ok\n");
}

module_init(mod_init);
module_exit(mod_exit);

MODULE_LICENSE("GPL");
