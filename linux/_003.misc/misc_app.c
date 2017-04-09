#include <stdio.h>

int main(int argc, char**argv)
{
        int fd;
        fd = open("/dev/misc_device", 2);
        if(fd<0)
        {
                printf("driver open fail\n");
                return -1;
        }
        
        int data;
        read(fd, &data, 4);
        write(fd, &data, 4);
        close(fd);
        
        return 0;
}
