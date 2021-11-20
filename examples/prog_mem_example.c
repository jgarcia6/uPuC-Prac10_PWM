#include <avr/io.h>
#include <avr/pgmspace.h>
#include "UART.h"

/* Arreglos escritos en Flash */
const char string_1[] PROGMEM = "Primer String";
const char string_2[] PROGMEM = "El Segundo String";
const char string_3[] PROGMEM = "[[[[[[String 3]]]]]]";
const char string_4[] PROGMEM = "String 4";
const char string_5[] PROGMEM = "Ultimo String.";

/* Arreglo (en RAM) de Apuntadores (a Flash) */
PGM_P const string_table[] =
{
	string_1,
	string_2,
	string_3,
	string_4,
	string_5,
};

/* Funcion principal */
int main (void){
	char data;
	uint8_t cnt = 0;
	uint8_t idx=0;
	
	UART_Ini(51);
	DDRB = 1<<PB7;
	PORTB |= 1<<PB7;
	
	data = UART_getch();
	UART_puts("\n\rInicio\n\r");
	while(1){
		UART_puts("\n\rPresiona 1-5\n\r");
		data = UART_getch();
		cnt = 0;
		if(data >= '1' && data <='5'){
			idx = data-'1';
			while( (data = (pgm_read_byte( &string_table[idx][cnt++]))) )
				UART_putchar(data);
		} else {
			UART_puts("x\n\r");
			PORTB ^= 1<<PB7;
		}
	}
	return 1;
}