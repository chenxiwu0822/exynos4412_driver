#include <stdio.h>
#include <sys/ioctl.h>

#include "leds_driver.h"

int main(int argc, char**argv)
{
        int fd;
        fd = open("/dev/led_device", 2);
        if(fd < 0)
        {
                printf("driver open fail\n");
                return -1;
        }
        
        int data;
        read(fd, &data, 4);
        write(fd, &data, 4);
        
        ioctl(fd, LED_ON, 0);
        sleep(1);
        ioctl(fd, LED_ON, 1);
        sleep(1);
        ioctl(fd, LED_ON, 2);
        sleep(1);
        ioctl(fd, LED_ON, 3);
        sleep(1);
        ioctl(fd, LED_OFF, 3);
        sleep(1);
        ioctl(fd, LED_OFF, 2);
        sleep(1);
        ioctl(fd, LED_OFF, 1);
        sleep(1);
        ioctl(fd, LED_OFF, 0);
        sleep(1);
        
        close(fd);
        
        return 0;
}
