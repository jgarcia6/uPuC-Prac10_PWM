#include <avr/io.h>
#include <avr/interrupt.h>

// F 440Hz, 50%
// OCR0A = 16M/(256*440) = 142-1

void UART0_putchar( unsigned char data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) )
	;
	/* Put data into buffer, sends the data */
	UDR0 = data;
}

char UART0_getchar(void)
{
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) )
	;
	/* Get and return received data from buffer */
	return UDR0;
}

int main( void )
{
	uint16_t porcentaje = 50;
  	/* init Timer0 as Fast PWM 				*/ 
   	TCCR0A = (2<<COM0B0) | (3<<WGM00);  /* Clr OC0B  Fast Mode 	*/
    TCCR0B = (4<<CS00) | (1<<WGM02);  /* prescaler=256			*/
	OCR0A = 142-1; // Timer TOP (Period)
	OCR0B = (OCR0A * porcentaje) / 100; // Set PWM
	sei();

	DDRG |= (1<<PG5);

  	while(1)
	{    
		char data = UART0_getchar();
		UART0_putchar(data);
		switch(data)
		{
		case 'F':
			if (OCR0A>1)
			{
				OCR0A--;
				UART0_putchar('#');
			}
			break;
		case 'f':
			if (OCR0A<255)
			{
				OCR0A++;
				UART0_putchar('=');
			}
			break;
		case 'P':
			if (porcentaje < 100)
			{
				porcentaje++;
				UART0_putchar('>');
			}
			break;
		case 'p':
			if (porcentaje > 0)
			{
				porcentaje--;
				UART0_putchar('<');
			}
			// 
			break;
		}
		OCR0B = (OCR0A * porcentaje) / 100;
  	}

		;  
  return 0;
}
