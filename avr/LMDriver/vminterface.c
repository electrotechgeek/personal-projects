#include <vminterface.h>
#include <avr/pgmspace.h>
#include <embedvm2.h>
#include <stddef.h>
#ifdef EMBEDDED
#include <cmdproc.h>
#endif
#include <serutil.h>

unsigned short binOffset;
unsigned char memory[RAM_SIZE];
//unsigned char memory[RAM_SIZE] = {0};
unsigned char eeprom[ROM_SIZE] PROGMEM;
extern unsigned char programControl;

struct embedvm_s vm = {
    0xffff, RAM_SIZE, RAM_SIZE, NULL,
	mem_read, mem_write, call_user // , &rom_read
};

#define UNUSED __attribute__((unused))

void vminterface_init(void)
{
    vm.ip = 0xffff;
    vm.sp = RAM_SIZE;
    vm.sfp = RAM_SIZE;
}

int16_t mem_read(uint16_t addr, bool is16bit)
{
#ifdef VMI_DEBUG
    uart_send_buffered('R');
    uart_send_buffered(':');
    uart_send_hex_byte(addr >> 8);
    uart_send_hex_byte(addr & 0xff);
    uart_send_buffered('\r');
    uart_send_buffered('\n');
#endif // VMI_DEBUG
	if (is16bit)
		return (memory[addr] << 8) | memory[addr+1];
	return memory[addr];
}

void mem_write(uint16_t addr, int16_t value, bool is16bit)
{
#ifdef VMI_DEBUG
    uart_send_buffered('W');
    uart_send_buffered(':');
    uart_send_hex_byte(addr >> 8);
    uart_send_hex_byte(addr & 0xff);
    uart_send_buffered(' ');
    uart_send_hex_byte(value >> 8);
    uart_send_hex_byte(value & 0xff);
    uart_send_buffered('\r');
    uart_send_buffered('\n');
#endif // VMI_DEBUG

	if (is16bit) {
		memory[addr] = value >> 8;
		memory[addr+1] = value;
	} else
		memory[addr] = value;
}

int16_t call_user(uint8_t funcid, uint8_t argc, int16_t *argv)
{
    char tmp = *(char *)argv;

    //uart_send_hex_byte(funcid);

	if (funcid == 0)
    {
        programControl = 0;
        uart_send_buffered('!');
	}

    if (funcid == 1)
    {
#ifdef VMI_DEBUG
        uart_send_buffered('E');
        uart_send_hex_byte(tmp);
        uart_send_buffered('\r');
        uart_send_buffered('\n');
#endif // VMI_DEBUG
        cmd_dataHandler(tmp);
    }
    return 0;
//
//	printf("Called user function %d with %d args:", funcid, argc);
//
//	for (i = 0; i < argc; i++) {
//		printf(" %d", argv[i]);
//		ret += argv[i];
//	}
//
//	printf("\n");
//	fflush(stdout);
//
//	return ret ^ funcid;
    return 0;
}

int8_t rom_read(uint16_t addr)
{
    return pgm_read_byte_near(eeprom + addr);
}
