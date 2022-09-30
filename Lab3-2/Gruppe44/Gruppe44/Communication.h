#ifndef Communication_H
#define Communication_H



void USART_Init(unsigned int ubrr);
void USART_Transmit( unsigned char data );
unsigned char USART_Receive( void );
#endif
