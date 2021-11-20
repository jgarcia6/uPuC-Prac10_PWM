#ifndef _ADC_H
#define _ADC_H

#include <inttypes.h>

/* Esta función inicializa para 8 bits de resolución y habilita el ADC del microcontrolador de
   forma genérica. Encontrar el desplazamiento (offset) de la medición y almacenarla. */
void ADC_Ini ( void );

/* Está función lo que realiza es una lectura del ADC usando el canal correcto y retornando el
   valor de 8 bits acorde a la aplicación (ver Figura 2), compensando el desplazamiento de la medición. */
uint8_t ADC_Read( uint8_t channel );

/* Esta función utiliza ADC_Read() y en base a las últimas muestras determina si ha detectado
   algún movimiento. */
uint8_t motion_Detected( void );

#endif