#include <linux/init.h>
#include <linux/module.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>

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

static struct miscdevice misc =
{
        .minor   = 255,
        .name    = "tiny4412_hello",
        .fops    = &tiny4412_fops,
};

static int __init hello_init(void)
{
        /* 注册杂项字符设备 */
        misc_register(&misc);
        printk("hello_init ok\n");
        return 0;
}

static void __exit hello_exit(void)
{
        /* 注销 */
        misc_deregister(&misc);
        printk("hello_exit ok\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
