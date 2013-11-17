dd if=/dev/urandom of=zeros.bin count=65536 bs=1
avr32-objcopy -I binary -O ihex zeros.bin zeros_temp.hex
sed '/:10[01].*/d' zeros_temp.hex > zeros.hex
