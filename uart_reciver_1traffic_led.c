/*************************************************/
/* Author : Prasanna */
/* Date   : 03-01-2023 */
/* Filename: USART USING TWO CONTROLLER */
/* Description : USART RECEIVE TRAFFIC LED */
/*************************************************/
#include <htc.h>
#define _XTAL_FREQ 20000000
__CONFIG(0x1F7A);

#define RS RB0    //REGISTER SELECT SIGNAL
#define RW RB1    //READ / WRITE SELECT SIGNAL
#define EN RB2    //ENABLE SIGNAL

void lcd_cmd(unsigned char cmd)
{
	RS = 0;
	RW = 0;
	EN = 1;
	PORTD = cmd;
	__delay_ms(25);
	EN = 0;
}

void lcd_data(unsigned char data)
{
	RS = 1;
	RW = 0;
	EN = 1;
	PORTD = data;
	__delay_ms(25);
	EN = 0;
}

void uart_rx_int()
{
	TRISA0= 0;      //FOR TRAFFIC LIGHT INPUT 
	TRISA1= 0;      //FOR TRAFFIC LIGHT INPUT
	TRISA2= 0;      // FOR TRAFFIC LIGHT INPUT
	TRISC7 = 1;     //HIGH 25 PIN -RC7/RX/DT
	RCSTA = 0x90;   //B7 SPEN =1
	SPBRG = 31;
	RCIE = 1;
}

int main()
{
	TRISA0= 0;
	TRISA1= 0;
	TRISA2= 0;
	TRISD = 0;      //PORT-D IS USED AS OUTPUT PORT
	TRISB = 0;      //PORT-B PIN AS OUTPUT PIN
	uart_rx_int();

	unsigned char R,Y,G;  //TRAFFIC LED 
	unsigned char data;
	
	unsigned char data;
	lcd_cmd(0x38);     //INIT 5x8-FONT TYPE ,2 DISPLAY LINE ,8-BITE
	lcd_cmd(0x0C);     //RETURN TO HOME
	lcd_cmd(0x80);     //DDRAM
	
	while(1)
	{
		while(RCIF == 0);
		RA0 = 0;
		data = RCREG;
		lcd_data(data);
		RA0 = 1;
		__delay_ms(500);
		
		while(RCIF == 0);
		RA1 = 0;
		data = RCREG;
		lcd_data(data);
		RA1 = 1;
		__delay_ms(500);
		
		while(RCIF == 0);
		RA2 = 0;
		data = RCREG;
		lcd_data(data);
		RA2 = 1;
		__delay_ms(500);
	
		
		while(RCIF == 0);
		data = RCREG;
		lcd_data(data);
		__delay_ms(500);
		
	}

}		
	
					