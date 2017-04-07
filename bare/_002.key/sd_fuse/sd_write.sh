#
# Copyright (C) 2011 Samsung Electronics Co., Ltd.
#              http://www.samsung.com/
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License version 2 as
# published by the Free Software Foundation.
#modify by zth
#
####################################

if [ -z $2 ]  #检查传入的第三个参数长度是否为 0
then
    echo "传参数顺序: ./脚本.h  <SD卡设备>  <要烧录的文件>"
    exit 0
fi

if [ -b $1 ]   #检查第二个参数是否是块设备
then
    echo "$1 SD卡设备正常！"
else
    echo "$1 SD卡设备错误！"
    exit 0   #退出脚本
fi


if [ -e $2 ]   #检查第三个参数(就是要烧录的文件是否存在)
then
    echo "$2 文件存在！ "
else
    echo "$2 文件不存在！"
    exit 0    #退出脚本
fi


BDEV_NAME=`basename $1`   #变量赋值--块设备名称
BDEV_SIZE=`cat /sys/block/${BDEV_NAME}/size`  


if [ ${BDEV_SIZE} -le 0 ]; then
	echo "Error: NO media found in card reader."
	exit 1
fi


if [ ${BDEV_SIZE} -gt 32000000 ]; then	echo "Error: Block device size (${BDEV_SIZE}) is too large"
	exit 1
fi


E4412_UBOOT=$2 #将要烧录文件赋值给变量E4412_UBOOT
MKBL2=./mkbl2  #需要当前路径下有一个mkbl2文件


if [ ! -f ${E4412_UBOOT} ]; then  #检测文件是否是普通文件，非目录和设备文件
	echo "$2 文件非普通文件！请检查文件是否正确！"
	exit -1  #退出脚本文件
fi

if [ ! -f ${MKBL2} ]; then       #检测文件是否是普通文件，非目录和设备文件
	echo "当前目录下缺少 mkbl2 文件！"
	exit -1 #退出脚本文件
fi

${MKBL2} ${E4412_UBOOT} bl2.bin 14336    #14K 通过mkbl2文件烧录程序 地址是14336


####################################
# fusing images

signed_bl1_position=1
bl2_position=17
uboot_position=49
tzsw_position=705

#<BL1 fusing>
echo "---------------------------------------"
echo "BL1 fusing"

#烧录命令
dd iflag=dsync oflag=dsync if=./E4412_N.bl1.bin of=$1 seek=$signed_bl1_position

#<BL2 fusing>
echo "---------------------------------------"
echo "BL2 fusing"
#烧录命令
dd iflag=dsync oflag=dsync if=./bl2.bin of=$1 seek=$bl2_position

sync


#输出信息
echo "---------------------------------------"
echo "程序烧录成功！"
echo "请拔出SD卡，放入开发板运行！！"
