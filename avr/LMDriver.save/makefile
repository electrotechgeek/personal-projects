TARGET=LMDriver
HWTARGET=atmega169
INCLUDES=-I. -I/usr/avr/include
LIBPATH=-L/usr/avr/lib
CC=avr-gcc
OBJDUMP=avr-objdump
CFLAGS=-mmcu=$(HWTARGET) 
OBJCOPY=avr-objcopy
MAKEFILE=makefile
#DEFINES=-DLTP1157=1
#DEFINES=-DKB_TBC12=1 -DALTFONT=1
DEFINES=-DKB_TBC12=1 \
-DF_CPU=8000000 

#-DHARDCODED_DISPLAY

# -DSTEPDISP


LIBS=$(LIBPATH) -lc
OBJS=main.o displaymux.o cmdproc.o font5x7.o spi.o

#serutil.o

all: clean $(TARGET).hex 

$(TARGET).hex: $(MAKEFILE) $(TARGET).out
	$(OBJCOPY) -j .text -O ihex $(TARGET).out $(TARGET).hex

$(TARGET).out: $(MAKEFILE) $(OBJS)
	$(CC) -o $(TARGET).out $(CFLAGS) -Wl,-Map,$(TARGET).map $(OBJS) $(LIBS)

readfuse: 
	avrdude -P /dev/ttyS0 -p m169 -c stk500v2 -Uhfuse:r:hfuse.txt:i

mmreadfuse: 
	avrdude -p m169 -c mattsmod -Uhfuse:r:hfuse.txt:i

writefuse: 
	avrdude -q -P /dev/ttyS0 -p m169 -c stk500v2 -Uhfuse:w:0xd9:m
	avrdude -q -P /dev/ttyS0 -p m169 -c stk500v2 -Ulfuse:w:0xe2:m
	avrdude -q -P /dev/ttyS0 -p m169 -c stk500v2 -Uefuse:w:0xff:m
#	avrdude -q -P /dev/ttyS0 -p m169 -c stk500v2 -Ulock:w:0xff:m

erase:
	avrdude -q -P /dev/ttyS0 -p m169 -c stk500v2 
boardtest: 
	avrdude -P /dev/ttyS0 -p m169 -c stk500v2

clean:
	rm -f *.o *.out *.map *.hex

upload:
#	avrdude -qq -P /dev/ttyS0 -c stk500v2 -p m169 -U flash:w:$(TARGET).hex
	avrdude -qq -C /etc/avrdude.conf -c usbtiny -p m169 -U flash:w:$(TARGET).hex

# -Wa,-ahls=$<.lst

%.o: %.c
	$(CC) -c -g $(CFLAGS) $(DEFINES) $(INCLUDES) $<
	$(OBJDUMP) -Sh $@ > $<.lst
#	$(CC) -Os -c $(CFLAGS) $(DEFINES) $(INCLUDES) $<
