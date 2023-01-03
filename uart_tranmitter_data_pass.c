/* Author : Prasanna */
/* Date   : 02-01-2023 */
/* Filename: USART USING TWO CONTROLLER */
/* Description : USART TRANMITTER DATA PASS */
/*************************************************/
#include<htc.h>
#define _XTAL_FREQ 20000000
__CONFIG(0x1F7A);

void uart_init()
{
	
	TRISC6 = 0;      //LOW 25 PIN RC6/TX/CK
	TXSTA  =0x20;    //TX STATUS & CONTROL REG (ADD 98H)
	TXEN = 1;
	SPEN = 1;
	SPBRG  =31;      
	TXIF   =0;
}
void uart_tx(unsigned char val)
{
	TXREG  = val;   //TRANSMIT BUFFER 
	while(TXIF == 0);//TRANSMIT BUFFER TXIF = 0;
	TXIF =0;
}
void main()
{
	uart_init();
	uart_tx('R');
	__delay_ms(100);
	uart_tx('G');
	__delay_ms(100);
	uart_tx('Y');
	__delay_ms(100);

	while(1);

	
}		