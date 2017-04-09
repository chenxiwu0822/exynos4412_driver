#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/version.h>

static int tiny4412_open(struct inode *my_indoe, struct file *my_file)
{
        printk("open ok\n");
        return 0;
}

static int tiny4412_release(struct inode *my_indoe, struct file *my_file)
{
        printk("release ok\n");
        return 0;
}

static ssize_t tiny4412_read(struct file *my_file, char __user *buff, size_t cnt, loff_t *loff)
{
        printk("read ok\n");
        return 0;
}

static ssize_t tiny4412_write(struct file *my_file, const char __user *buff, size_t cnt, loff_t *loff)
{
        printk("write ok\n");
        return 0;
}

static struct file_operations tiny4412_fops =
{
        .open    = tiny4412_open,
        .release = tiny4412_release,
        .read    = tiny4412_read,
        .write   = tiny4412_write,
};

static int tiny4412_major;
static struct class *tiny4412_class;

static int __init mod_init(void)
{
        tiny4412_major = register_chrdev(0, "tiny4412_module", &tiny4412_fops);
        printk("tiny4412_major = %d\n", tiny4412_major);
        
        tiny4412_class = class_create(THIS_MODULE, "tiny4412_class");
        if (IS_ERR(tiny4412_class))
        {
                printk(KERN_INFO "create class error\n");
                return -1;
        }
        device_create(tiny4412_class, NULL, MKDEV(tiny4412_major, 0), NULL, "early_device");
      
        printk("mod_init ok\n");
        return 0;
}

static void __exit mod_exit(void)
{
        unregister_chrdev(tiny4412_major, "tiny4412_module");
        printk("mod_exit ok\n");
}

module_init(mod_init);
module_exit(mod_exit);

MODULE_LICENSE("GPL");
