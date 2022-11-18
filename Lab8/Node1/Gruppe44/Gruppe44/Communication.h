#ifndef Communication_H
#define Communication_H

// Functions taken from ATmega datasheet, page 172-174

void USART_Init(unsigned int ubrr);
void USART_Transmit( unsigned char data );
unsigned char USART_Receive( void );
#endif
