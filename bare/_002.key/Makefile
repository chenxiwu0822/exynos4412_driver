
key_sp.bin: start.o key-main.o
	arm-linux-ld -Tkey.lds -o key_sp.elf $^
	arm-linux-objcopy -O binary key_sp.elf file_ok.bin
	arm-linux-objdump -D key_sp.elf > key_sp_elf.dis
	
%.o : %.S
	arm-linux-gcc -o $@ $< -c

%.o : %.c
	arm-linux-gcc -o $@ $< -c 

clean:
	rm *.o *.elf *.bin *.dis -f
