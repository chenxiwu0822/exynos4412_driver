#include <linux/init.h>
#include <linux/module.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>

static int tiny4412_open(struct inode *my_indoe, struct file *my_file)
{
        printk(KERN_INFO "misc open ok\n");
        return 0;
}

static int tiny4412_release(struct inode *my_indoe, struct file *my_file)
{
        printk(KERN_INFO "misc release ok\n");
        return 0;
}

static ssize_t tiny4412_read(struct file *my_file, char __user *buff, size_t cnt, loff_t *loff)
{
        printk(KERN_INFO "misc read ok\n");
        return 0;
}

static ssize_t tiny4412_write(struct file *my_file, const char __user *buff, size_t cnt, loff_t *loff)
{
        printk(KERN_INFO "misc write ok\n");
        return 0;
}

static struct file_operations tiny4412_fops =
{
        .open    = tiny4412_open,
        .release = tiny4412_release,
        .read    = tiny4412_read,
        .write   = tiny4412_write,
};

static struct miscdevice misc =
{
        .minor   = 255,
        .name    = "misc_device",
        .fops    = &tiny4412_fops,
};

static int __init mod_init(void)
{
        misc_register(&misc);
        printk(KERN_INFO "mod_init ok\n");
        return 0;
}

static void __exit mod_exit(void)
{
        misc_deregister(&misc);
        printk(KERN_INFO "mod_exit ok\n");
}

module_init(mod_init);
module_exit(mod_exit);

MODULE_LICENSE("GPL");
