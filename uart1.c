/*************************************************/
/* Author : Prasanna */
/* Date   : 18-12-2022 */
/* Filename: UART */
/* Description : UART transmitter */
/*************************************************/
#include<htc.h>
#define _XTAL_FREQ 20000000
__CONFIG(0x1F7A);

unsigned char uart_rx(void);
void uart_init (void);
void uart_init()
{
	TRISC6 = 1;      //LOW 25 PIN RC6/TX/CK
	TRISC7 = 0;      //LOW 26 PIN RC7/RX/DTp
	TXSTA  =0x00;    //TX STATUS & CONTROL REG (ADD 98H)
	RCSTA  =0x00;    //RX STATUS & CONTROL REG (ADD 18H)
	SPBRG  =31;      
	SPEN   =1;
	TXEN   =1;
	TXIF   =0;
	RCIF   =0;
}
void uart_tx(unsigned char val)
{
	TXREG  =val;   //TRANSMIT BUFFER 
	while(TXIF == 0);//TRANSMIT BUFFER TXIF = 0;
	TXIF =0;
}
void main()
{
	uart_init();
	uart_tx('S');
	__delay_ms(100);
	uart_tx('L');
	__delay_ms(100);
	uart_tx(' ');
	__delay_ms(100);
	uart_tx('D');
	__delay_ms(100);
	uart_tx('P');
	__delay_ms(100);
	uart_tx('I');
	__delay_ms(100);	
	
	while(1);
	
}	