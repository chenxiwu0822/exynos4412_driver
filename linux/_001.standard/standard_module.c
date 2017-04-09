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
static int tiny4412_minor;
static dev_t tiny4412_devno;

struct cdev * standard_device;
static struct class  * tiny4412_class;

static int __init mod_init(void)
{
        int ret;
        ret = alloc_chrdev_region(&tiny4412_devno, tiny4412_minor, 1, "standard_device");
        tiny4412_major = MAJOR(tiny4412_devno);
        if (ret < 0) 
        {
                printk(KERN_ERR "cannot get tiny4412_major %d \n", tiny4412_major);
                return -1;
        }
        
        standard_device = cdev_alloc();
        if (standard_device != NULL) 
        {
                cdev_init(standard_device, &tiny4412_fops);
                standard_device->owner = THIS_MODULE;
                if (cdev_add(standard_device, tiny4412_devno, 1) != 0) 
                {
                        printk(KERN_ERR "add cdev error!\n");
                        goto error;
                }
        }
        else
        {
                printk(KERN_ERR "cdev_alloc error!\n");
                return -1;
        }

        tiny4412_class = class_create(THIS_MODULE, "tiny4412_class");
        if (IS_ERR(tiny4412_class))
        {
                printk(KERN_INFO "create class error\n");
                return -1;
        }
        device_create(tiny4412_class, NULL, tiny4412_devno, NULL, "standard_device");
        
        printk("mod_init ok\n");
        return 0;

error:
        unregister_chrdev_region(tiny4412_devno, 1);
        return ret;
}

static void __exit mod_exit(void)
{
        unregister_chrdev(tiny4412_major, "tiny4412_module");
        printk("mod_exit ok\n");
}

module_init(mod_init);
module_exit(mod_exit);

MODULE_LICENSE("GPL");
