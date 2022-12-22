/*************************************************/
/* Author : Prasanna */
/* Date   : 20-12-2022 */
/* Filename: UART */
/* Description : UART RECIVE */
/*************************************************/
#include <htc.h>
#define _XTAL_FREQ 20000000
__CONFIG(0x1F7A);

#define RS RD5
#define RW RD6
#define EN RD7

void lcd_cmd (unsigned char cmd);
void lcd_disp (unsigned char data);

void uart_init (void);
void lcd_init ();

void lcd_cmd(unsigned char cmd)
{
	RS = 0;
	RW = 0;
	EN = 1;
	PORTB =cmd;
	__delay_ms(50);
	EN = 0;
	__delay_ms(50);
}
void lcd_disp(unsigned char data)
{
	RS =1;
	RW =0;
	EN =1;
	PORTB =data;
	__delay_ms(50);
	EN =0;
	__delay_ms(50);
}
void uart_init()
{
	TRISC6 = 0;    //LOW 26 PIN RC6/TX/DT
	TRISC7 = 1;    //HIGH 25 PIN RC7/RX/CK
	TXSTA = 0x20;  //b5 TXEN = 1;
	RCSTA = 0x90;  //b7 SPEN = 1;
	SPBRG = 31;    //SPBRG SERIAL PORT BAUD RATE GEN REG (ADD 99H)
	TXIF = 0;
	RCIF = 0;
}
void lcd_init()
{
	TRISB =0x00;   //PORT-B IS USED AS OUTPUT PORT
	TRISD5 =0;     //PORT-D PIN #5 AS OUTPUT PIN
	TRISD6 =0;     //PORT-D PIN #6 AS OUTPUT PIN
	TRISD7 =0;     //PORT-D PIN #7 AS OUTPUT PIN
	__delay_ms(50);
	lcd_cmd(0x38); //INIT 5x8-2 LINE RET HOME
	lcd_cmd(0x0F); //DISP ON ,EN_CUR, EN_BLINK
	lcd_cmd(0x0C); //DISP ON ,EN_CUR, EN_BLINK
	lcd_cmd(0x02); // RET TO HOME
	lcd_cmd(0x06); //CUR++
	lcd_cmd(0x80); //SET DDRAM
	__delay_ms(50);
	lcd_cmd(0x01); //CLEAR DISPLAY
} 
void main()
{
	unsigned char Rdata;
	lcd_init();
	uart_init();
	while(1)
	{
		while(RCIF == 0); //POLL IF RCIF IS EMPTY
		Rdata =RCREG;     //COPY DATA FROM RCREG REGISTER TO RDATA CHAR VARIABLE
		lcd_disp(Rdata);  //DISPLAY RECIVE DATA ON LCD 
	}
}			
	
			
	
	