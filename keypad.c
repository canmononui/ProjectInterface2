//Smart Curtain Project
//LDR Contro Motor
#include<reg51.h>
sfr ROW=0x80;      // assigning  Port1 to read ROW
sfr COL=0xA0;      // assigning Port2 to COLUM
sfr ldata=0x90;

//Set Port
sbit ldr1=P1^0; 		//Optical Sensor)
sbit ldr2=P1^1; 		//Optical Sensor)
sbit relay1=P1^2;   //Relay Switch1 Output
sbit relay2=P1^3;   //Relay Switch2	Output

sbit rs=P3^0;	   //LCD
sbit rw=P3^1;	   //LCD
sbit en=P3^2;	   //LCD
unsigned char dat[4][3]={'0','1','2','3','4','5','6','7','8','9','A','B'}

void open_curtain(void);
void close_curtain(void);
void stop_curtain(void);
void lcdcmd(unsigned char value);
void msdelay(unsigned int value);
oid printstring(unsigned char ch[]);
void main()
{
	lcdcmd(0x38);
  	lcdcmd(0x0F);
  	lcdcmd(0x06);
  	lcdcmd(0x01);
  	LCDclear();
  	lcdcmd(0x80);
  while(1)
	printstring("userID:");
	lcdcmd(0x87);

}
void lcdcmd(unsigned char value)
{
 lcdready();
 ldata=value;
 rs=0;
 rw=0;
 en=1;
 msdelay(10);
 en=0;
 }
void msdelay(unsigned int value)
{
 unsigned int i,j;
 for(i=0;i<value;i++)
 for(j=0;j<100;j++);
 }

void printstring(unsigned char ch[])
{
 unsigned int i;
 for(i=0;ch[i]!='\0';i++)
 lcddata(ch[i]);
 }

void open_curtain(void)  //motor on anticlockwise
{
			relay1=1;    
			relay2=0;	
}
void close_curtain(void)  //motor on clockwise
{
			relay1=0;
			relay2=1;	
}
void stop_curtain(void)	 //motor off
{
			relay1=1;	 //relay led off
			relay2=1;	 //relay led off			 
}	 	 