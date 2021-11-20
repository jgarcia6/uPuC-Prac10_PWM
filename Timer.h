#ifndef _TIMER_H
#define _TIMER_H

#include <inttypes.h>

/* Función para inicializar el Timer0 y generar */
/* la temporización de 1 Sec. */
void Timer0_Ini ( void );

/* Función para verificar bandera del segundo */
uint8_t Timer0_SecFlag ( void );

/* Funcion que genera una frecuencia con ancho modulable sobre OC2B */
void Timer2_Gen_Tone(uint16_t tone, uint8_t volume)

#endif /* _TIMER0_H */