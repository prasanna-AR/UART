/**********************************************************/
/* Author : Prasanna */
/* Date   : 15-01-2023 */
/* Filename: USART USING GSM MODULE*/
/* Description :USING GSM MODULE TO SENDING SMS TO PHONE */
/*********************************************************/
#include<htc.h>
#define _XTAL_FREQ 20000000
__CONFIG(0x1F7A);

#define PTR RC2       //FOR PIR SENSOR OUTPUT

#define RS RD5        //FOR LCD RS PIN
#define RW RD6       //FOR LCD RW PIN
#define EN RD7		//FOR LCD EN PIN

void lcd_cmd(unsigned char cmd);  
void lcd_disp(unsigned char data);
unsigned uart_rx(void);           
void uart_tx(unsigned char val);
void uart_init (void);
void uart_init();

char AT[]="AT\r\n";                //FOR GSM AT COMMEND
char sms_mode[]="AT+CMGF=1\r\n";    //FOR GSM SMS_MODE SET
char phone_number[]="AT+CMGS=\"6369557722\"\r\n";//FOR SMS WHICH NUMBER TO SEND A MESSAGE
char sms_mess[]="HI PRASANNA\x1A\r\n";  //FOR MESSAGE WHAT WE NEED PRINT AND CTRL+Z
char call[]="ATD6369557722;\r\n";      //FOR CALL


void lcd_cmd(unsigned char cmd)
{
	RS=0;
	RW=0;
	EN=1;
	PORTB=cmd;
	__delay_ms(50);
	EN=0;
	__delay_ms(50);
}	
void lcd_disp(unsigned char data)
{
	RS =1;
	RW =0;
	EN =1;
	PORTD =data;
	__delay_ms(50);
	EN =0;
	__delay_ms(50);
}


void lcd_init()
{
	TRISB =0;       // FOR LCD 
	TRISD =0;       //FOR LCD RS,RW,EN PIN
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
void uart_init()
{
	TRISC6 = 0;    //LOW 26 PIN RC6/TX/CK
	TRISC7 = 1;    //HIGH 25 PIN RC7/RX/DT
	TXSTA  = 0x20;  //TX STATUS & CONTROL REG.(ADD 98H)
	RCSTA  = 0x90;  //RX STATUS & CONTROL REG.(ADD 18H)
	SPBRG  = 31;    //BAUD RATE VALUE
	TXIF  = 0;      
	RCIF  = 0;
}
void uart_tx(unsigned char val)
{
	TXREG  =val;     //TRANSMIT BUFFER 
	while(TXIF == 0);//TRANSMIT BUFFER TXIF = 0;
	TXIF =0;
}
unsigned uart_rx(void)
{
	while(RCIF == 0);//POLL IF RCIF IS EMPTY
	RCIF = 0;        
	return RCREG;
}	

void uart_print(unsigned char *str)
{
	while(*str)
	{
		uart_tx(*str++);
	}	
		
}
int main()
{
	TRISC2 = 1;
	TRISC3 =0;
	lcd_init();
	uart_init();
	
	{
		if(RC2 == 1)
		{
		     RC3 = 1;
		     __delay_ms(100);
		      uart_print(AT);
		      __delay_ms(500);
		      
		      uart_print(call);
		      __delay_ms(500);
		      
		  }
		
	     else
	     {  
		   RC3 = 0;
		   __delay_ms(100);
			uart_print(AT);    
			__delay_ms(500);
		
			uart_print(sms_mode);
			__delay_ms(500);
		
			uart_print(phone_number);
			__delay_ms(500);
		
			uart_print(sms_mess);
			__delay_ms(500);
			
	     }
	     
		  while(1); 
	}	     
}	    
	