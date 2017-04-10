#include <stdio.h>
#include <sys/ioctl.h>

#include "beep_driver.h"

int main(int argc, char**argv)
{
        int fd, i;
        fd = open("/dev/beep_device", 2);
        if(fd < 0)
        {
                printf("driver open fail\n");
                return -1;
        }
        
        int data;
        read(fd, &data, 4);
        write(fd, &data, 4);
        
        for(i = 0; i < 5; i++)
        {
                ioctl(fd, BEEP_ON);
                sleep(1);
                ioctl(fd, BEEP_OFF);
                sleep(1);
        }
        
        close(fd);
        
        return 0;
}
