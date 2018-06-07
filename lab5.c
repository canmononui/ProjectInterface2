//lab5
#include<reg51.h>
sbit r1	= P0^0;	  //keypad row1
sbit r2	= P0^1;	  //keypad row2
sbit r3	= P0^2;	  //keypad row3
sbit r4	= P0^3;	  //keypad row4
sbit c1	= P0^4;	  //keypad col1
sbit c2	= P0^5;	  //keypad col2
sbit c3	= P0^6;	  //keypad col3

sfr ldata=0x90;
sbit rs=P3^5;   // LCD reset 
sbit en=P3^3;

void Tdelay();     // functions initializaion
void delay(unsigned int);
void lcdcmd(char,int a);
void lcd_data(unsigned char );
void lcd_display1(unsigned char *c ,char A);
void lcd_display2(unsigned char *c );

void ds1307_write_byte(unsigned char,unsigned char); // Setup RTC
unsigned char ds1307_read_byte(unsigned char); // Read RTC
void i2c_send_byte(unsigned char); // Write Byte I2C
unsigned char i2c_get_byte(void); // Read Byte I2C
void delay_i2c(void); // Short Delay For I2C Bus Interface
void delay(unsigned long); // Delay Time Function(1..4294967295)

void main()
	{
	char count=0x80;
		int lcd=0,lcd1 =0;
		lcdcmd(0x38,0);		 //2 lines 5x7 matrix
		lcdcmd(0x0C,0);      //display on , cursor blinking
		lcdcmd(0x01,0);		 //clear screen
		lcdcmd(0x06,0);
		while(1)
		{
		r1 = 0; r2 = r3 = r4 =1;
		if(c1==0)
		{
		lcd_display1("1",count);
		count++;
		delay(32);
		}
		if(c2==0)
		{
		lcd_display1("2",count);
		count++;
		delay(32);
		}

		if(c3==0)
		{
		lcd_display1("3",count);
		count++;
		delay(32);
		}
		r1 = r3 = r4 =1; r2=0;
		if(c1==0)
		{
		lcd_display1("4",count);
		count++;
		delay(32);
		}
		if(c2==0)
		{
		lcd_display1("5",count);
		count++;
		delay(32);
		}

		if(c3==0)
		{
		lcd_display1("6",count);
		count++;
		delay(32);
		}
		r1 = r2 = r4 =1; r3=0;
		if(c1==0)
		{
		lcd_display1("7",count);
		count++;
		delay(32);
		}
		if(c2==0)
		{
		lcd_display1("8",count);
		count++;
		delay(32);
		}

		if(c3==0)
		{
		lcd_display1("9",count);
		count++;
		delay(32);
		}
		r1 = r2 = r3 =1; r4=0;
		if(c1==0)
		{
		lcd_display1("*",count);
		count++;
		delay(32);
		}
		if(c2==0)
		{
		lcd_display1("0",count);
		count++;
		delay(32);
		}

		if(c3==0)
		{
		lcd_display1("#",count);
		count++;
		delay(32);
		}
		

		}

	}

void lcd_display1(char *dvalue, char A)
	{
	int x;
	lcdcmd(A,0);
	for(x=0;dvalue[x]!=0;x++)
	{
		lcdcmd(dvalue[x],1);
	}
	}
void lcd_display2(unsigned char *dvalue)
	{
	int x;
	lcdcmd(0xC0,0);
	for(x=0;dvalue[x]!=0;x++)
	{
		lcdcmd(dvalue[x],1);
	}
	}
void Tdelay()  // providing some delay
{
unsigned int j;
for(j=0;j<1275;j++);
}

void delay(unsigned int ms)  // providing some delay
{
unsigned int i,j;
for(i=0;i<ms;i++)
for(j=0;j<400;j++);
}

void lcdcmd(char cvalue,int a ) // LCD in command mode opearaion
	{
	ldata=cvalue;
	rs=a;
	//rw=0;
	en=1;
	Tdelay();
	en=0;
	}
