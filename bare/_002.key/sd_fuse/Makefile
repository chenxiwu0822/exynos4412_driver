

ARCH ?= KKKK

led_sp.bin: start.o led-main.o
	arm-linux-ld -Tled.lds -o led_sp.elf $^
	arm-linux-objcopy -O binary led_sp.elf led.bin
	arm-linux-objdump -D led_sp.elf > led_sp_elf.dis
	echo $(ARCH)
	
	
%.o : %.S
	arm-linux-gcc -o $@ $< -c

%.o : %.c
	arm-linux-gcc -o $@ $< -c 

clear:
	rm *.o *.bak *.elf *.bin *.dis *~ -f
------------------------------------------------------------------------------
SOURCES = $(OBJECTS:.o=.c)

all:
	$(CC) $(CFLAGS)	mkbl2 V310-EVT1-mkbl2.c 	

#---------------------------------------------------------------------------------------
.c.o:
		$(CC) $(CFLAGS) -c $< -o $@

dep:
		gccmakedep	$(SOURCES)

#---------------------------------------------------------------------------------------
clean:
		$(RM)		-rf sd_fdisk *~ *bak
		$(RM)		-rf mkbl2

new:
		$(MAKE)		clean
		$(MAKE)

