TARGET=blink
HWTARGET=attiny45
INCLUDES=-I. -I/usr/lib/avr/include/avr
LIBPATH=-L/usr/avr/lib
CC=avr-gcc
OBJDUMP=avr-objdump
CFLAGS=-mmcu=$(HWTARGET) -O3
OBJCOPY=avr-objcopy
MAKEFILE=makefile
DEFINES=-DF_CPU=1000000 

LIBS=$(LIBPATH) -lc
OBJS=blink.o 


all: clean $(TARGET).hex

$(TARGET).hex: $(MAKEFILE) $(TARGET).out
	$(OBJCOPY) -j .text -O ihex $(TARGET).out $(TARGET).hex

$(TARGET).out: $(MAKEFILE) $(OBJS)
	$(CC) -o $(TARGET).out $(CFLAGS) -Wl,-Map,$(TARGET).map $(OBJS) $(LIBS)

writefuse: 
#	avrdude -qq -C /etc/avrdude.conf -c usbtiny -p m169 -Ulfuse:w:0xe2:m
#	avrdude -qq -C /etc/avrdude.conf -c usbtiny -p m169 -Ulfuse:w:0xc2:m
#	avrdude -qq -C /etc/avrdude.conf -c usbtiny -p m169 -Uhfuse:w:0xd9:m

erase:
	avrdude -q -P /dev/ttyS0 -p m169 -c stk500v2 
boardtest: 
	avrdude -P /dev/ttyS0 -p m169 -c stk500v2

clean:
	rm -f *.o *.out *.map *.hex

upload:
	avrdude -qq -C /etc/avrdude.conf -c usbtiny -p attiny45 -U flash:w:$(TARGET).hex

%.o: %.c
	$(CC) -c -g $(CFLAGS) $(DEFINES) $(INCLUDES) $<
	$(OBJDUMP) -Sh $@ > $<.lst
#	$(CC) -Os -c $(CFLAGS) $(DEFINES) $(INCLUDES) $<
