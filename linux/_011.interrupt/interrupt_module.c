#include <linux/init.h>
#include <linux/module.h>

#include <linux/gpio.h>
#include <mach/gpio.h>
#include <plat/gpio-cfg.h>

#include <linux/interrupt.h>
#include <linux/irq.h>

static int irq;

static irqreturn_t key_handler(int irq, void *dev)
{
        if(!gpio_get_value(EXYNOS4_GPX3(2)))
        {
                printk("Button press\n");
        }else
        {
                printk("Button loosen\n");
        }
        return IRQ_NONE;
}

static int __init mod_init(void)
{
        int ret = -1;
        gpio_free(EXYNOS4_GPX3(2));
        gpio_request(EXYNOS4_GPX3(2), "key1");
        s3c_gpio_cfgpin(EXYNOS4_GPX3(2), S3C_GPIO_INPUT);
        irq = gpio_to_irq(EXYNOS4_GPX3(2));
        ret = request_irq(irq, key_handler, IRQ_TYPE_EDGE_BOTH, "key", NULL);
        if(ret != 0)
        {
                printk("request the %d interrupt fail\n", irq);
        }
        printk(KERN_INFO "mod_init ok\n");
        return 0;
}

static void __exit mod_exit(void)
{
        free_irq(irq, NULL);
        gpio_free(EXYNOS4_GPX3(2));
        printk(KERN_INFO "mod_exit ok\n");
}

module_init(mod_init);
module_exit(mod_exit);

MODULE_LICENSE("GPL");
