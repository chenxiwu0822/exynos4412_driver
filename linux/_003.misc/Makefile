obj-m += hello_modu.o

KERNEL = /home/wangbing/workspace/exynos4412/source/linux-3.5
ROOTFS = /home/wangbing/workspace/exynos4412/rootfs

all:
	make -C $(KERNEL) M=`pwd` modules
	arm-linux-gcc hello_app.c -o app
	rm -rf $(ROOTFS)/test/*
	cp *.ko $(ROOTFS)/test
	cp app $(ROOTFS)/test
clean:
	make -C $(KERNEL) M=`pwd` modules clean
	rm -rf $(ROOTFS)/test/*
	rm -f app
