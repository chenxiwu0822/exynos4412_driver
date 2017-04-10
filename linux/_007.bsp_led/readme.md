# 使用 Linux 标准 GPIO 库函数实现 LED 驱动

由于在使用 GPM4_0 的时候老是报 gpio_request failinsmod 资源被占用的错误，这里我们使用的是 GPB_5 引脚直接外接一个 LED 灯(低电平点亮).