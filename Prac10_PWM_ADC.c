/*
    Example code written during the Lab Session given only as reference, 
    Please update the function to your own implementation in order to compile.
*/
#include <avr\io.h>
#include "UART.h"

// ADC1, VRef = Vcc, 10 bits
void ADC_Init(){
	ADMUX= (1<<REFS0)| (1<<MUX0);// Vcc, ADC1
	ADCSRA = (1<<ADEN)| (7<<ADPS0); // ADC On, PS=128
	ADCSRB = 0;	
}


uint16_t ADC_read(){
	ADCSRA |= 1<<ADSC; // Start conversion
	while ( ADCSRA&(1<<ADSC) )
		; // Wait for conversion
	return ADC; // Return conversion
}

int main(){
#ifdef PWM_example
  	/* init Timer0 as Fast PWM 				*/ 
   	TCCR2A = (2<<COM2B0)| (3<<WGM20);  /* OC2B non-inverting output, Fast Mode OCRA Top*/
    TCCR2B = (1<<WGM22)|(6<<CS20);  /* Fast Mode OCRA Top, prescaler 256*/
	OCR2A = 142-1;  	/* Set PWM Period */
	OCR2B = OCR2A>>1;  	/* Set PWM 50% */
	DDRH |= (1<<PH6); 	/* Enable output OC2B*/

	while (1)
	{
		switch(UART_getch())
		{
			case 'F':
				OCR2A--;
				break;
			case 'f':
				OCR2A++;
				break;
			case 'P':
				OCR2B++;
				break;
			case 'p':
				OCR2B--;
				break;
		}
	}
#endif

#ifdef ADC_example
	uint16_t value;	
	char str[15];
	
	UART_Ini(207);
	ADC_Init();
	clrscr();
	UART_getch();

	while(1){
		value = ADC_read();
		for(uint8_t i=0;i<value/25;i++)
			UART_putchar('.');
		itoa(value,str,10);
		UART_puts(str);
		UART_puts("\n\r");
	}
#endif
	return 1;
}

