
led_sp.bin: start.o led-main.o
	arm-linux-ld -Tled.lds -o led_sp.elf $^
	arm-linux-objcopy -O binary led_sp.elf led.bin
	arm-linux-objdump -D led_sp.elf > led_sp_elf.dis
	
	
%.o : %.S
	arm-linux-gcc -o $@ $< -c

%.o : %.c
	arm-linux-gcc -o $@ $< -c 

clean:
	rm *.o *.elf *.bin *.dis -f
