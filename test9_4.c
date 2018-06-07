#include<reg51.h>
#include <stdio.h> // For printf I/O functions

#define ldata P1
sfr CKCON = 0x8F; // Clock Control
sbit r1	= P0^0;	  //keypad row1
sbit r2	= P0^1;	  //keypad row2
sbit r3	= P0^2;	  //keypad row3
sbit r4	= P0^3;	  //keypad row4
sbit c1	= P0^4;	  //keypad col1
sbit c2	= P0^5;	  //keypad col2
sbit c3	= P0^6;	  //keypad col3

sbit relay1=P3^0;   //Relay Switch1 Output
sbit relay2=P3^1;   //Relay Switch2	Output
//sbit swtop=P3^6;    //check sw top
//sbit swtun=P3^7;    //check sw under
sbit ldr1=P3^2; 	//Optical Sensor)
sbit ldr2=P3^4; 	//Optical Sensor)
sbit rs=P3^5;   	// LCD reset 
sbit en=P3^3;
//rw(read/write control) connect to GND
void open_curtain();
void close_curtain();
void stop_curtain();
void Tdelay();     // functions initializaion
void delay2(unsigned int);
void lcdcmd(char cvalue,int a);
void lcd_data(unsigned char );
void lcd_display1(unsigned char *c );
void lcd_display2(unsigned char *c );
void lcd_display3(char *dvalue, char A);
void delay_time();

void main()
	{	int i,j,a,b,c,d/*,z,x,v*/;
		char buffer[10],buffer1[10],buffer2[10];
		//int time=0,time1=0,time2=0;
		int count=0xC0;

;
		lcdcmd(0x38,0);		 //2 lines 5x7 matrix
		lcdcmd(0x0C,0);      //display on , cursor blinking
		lcdcmd(0x01,0);		 //clear screen
		lcdcmd(0x06,0);		 //increment cursor

		lcd_display1("Welcome to");
		lcd_display2("Smart Curtain");
		delay2(1500);		 //delay show on LCD 
		lcdcmd(0x01,0);		 //clear screen
		
		lcd_display1("Pls enter mode");
		lcd_display2("Mode 1, 2, 3");

		while(1)
		{
		r1 = 0; r2 = r3 = r4 =1;
		if(c1==0)
		{
		lcdcmd(0x01,0);
		delay2(32);
		while(1)
		{
		lcd_display1("Mode1 (Auto)");
		lcd_display2("<1kLu=O >1kLu=C");
		while(1)
				{
				if(ldr1==0 && ldr2==0){open_curtain();} //Night (LDR LED OFF)
				if(ldr1==1 && ldr2==1){close_curtain();}//Day (LDR LED ON)
				if(ldr1==1 && ldr2==0){stop_curtain();} //Curtain Stop
				if(ldr1==0 && ldr2==1){stop_curtain();} //Curtain Stop
					r1 = 0; r2 = r3 = r4 =1;
					if(c1==0){break;}
					if(c2==0){break;}	
					if(c3==0){break;}
				}
			break;
		}
		stop_curtain();
		lcdcmd(0x01,0);
		}
		
		if(c2==0)
		{
		int n=0;
		int timekey[10]=0;
		lcdcmd(0x01,0);
		delay2(32);
		while(1)	 //Edit in loop while(1)
		{
		lcd_display1("Mode2 (On Time)");
		delay2(1500);		 //delay show on LCD 
		lcdcmd(0x01,0);
		lcd_display1("Enter Time");
//********************************************************		
		while(1)
		{
			r1 = 0; r2 = r3 = r4 =1;
			if(c1==0)
			{
			lcd_display3("1",count);
			delay2(500);
			count++;
			n++;
			timekey[n]=1;
			}
			if(c2==0)
			{
			lcd_display3("2",count);
			delay2(500);
			count++;
			n++;
			timekey[n]=2;
			}
	
			if(c3==0)
			{
			lcd_display3("3",count);
			delay2(500);
			count++;
			n++;
			timekey[n]=3;
			}
			r1 = r3 = r4 =1; r2=0;
			if(c1==0)
			{
			lcd_display3("4",count);
			delay2(500);
			count++;
			n++;
			timekey[n]=4;
			}
			if(c2==0)
			{
			lcd_display3("5",count);
			delay2(500);
			count++;
			n++;
			timekey[n]=5;
			}
	
			if(c3==0)
			{
			lcd_display3("6",count);
			delay2(500);
			count++;
			n++;
			timekey[n]=6;
			}
			r1 = r2 = r4 =1; r3=0;
			if(c1==0)
			{
			lcd_display3("7",count);
			delay2(500);
			count++;
			n++;
			timekey[n]=7;
			}
			if(c2==0)
			{
			lcd_display3("8",count);
			delay2(500);
			count++;
			n++;
			timekey[n]=8;
			}
	
			if(c3==0)
			{
			lcd_display3("9",count);
			delay2(500);
			count++;
			n++;
			timekey[n]=9;
			}	   
			r1 = r2 = r3 =1; r4=0;
			if(c2==0)
			{
			lcd_display3("0",count);
			delay2(500);
			count++;
			n++;
			timekey[n]=0;
			}
			if(n==6){break;}
		}
//*********************************************************		

		i=(timekey[1]*10)+timekey[2];
		j=(timekey[3]*10)+timekey[4];
		a=(timekey[5]*10)+timekey[6];
		

	for(b=i;b<=23;b++)
		{
			for(c=j;c<=59;c++)
			{
				for(d=a;d<=59;d++)
				{				
			sprintf(buffer,"%d",b);
			sprintf(buffer1,"%d",c);
			sprintf(buffer2,"%d",d);

			lcd_display2(buffer);	   //HR
			lcd_display3(":",0xC2);
			lcd_display3(buffer1,0xC3);	//MM
			lcd_display3(":",0xC5);
			lcd_display3(buffer2,0xC6);	
			delay2(1000);
			lcdcmd(0x01,0);
			lcd_display1("Mode2 (On Time)");
			if(d==59){a=0;}
//**************************************************************			
			
//*******************************************************************
			//if(c3==0){close_curtain();} //check enter key #
			r1 = 0; r2 = r3 = r4 =1;
					if(c1==0){break;}
					if(c2==0){break;}	
					if(c3==0){break;}
				}
			if(c==59){j=0;}
			r1 = 0; r2 = r3 = r4 =1;
					if(c1==0){break;}
					if(c2==0){break;}	
					if(c3==0){break;}
			}
			if(b==23){i=0;}
			r1 = 0; r2 = r3 = r4 =1;
					if(c1==0){break;}
					if(c2==0){break;}	
					if(c3==0){break;}
		}
			r1 = 0; r2 = r3 = r4 =1;
					if(c1==0){break;}
					if(c2==0){break;}	
					if(c3==0){break;}
		stop_curtain();
		lcdcmd(0x01,0);
		}
		}
		
			
		if(c3==0)
		{
		lcdcmd(0x01,0);
		delay2(32);
		while(1)
			{ 	
				lcd_display1("Mode3 (EnterKey)");
				lcd_display2("*=O 0=S #=C");
					while(1)
					{
					/*if(sw==0)
					{
					stop_curtain();
					}	*/
				
					r4 = 0; r1 = r2 = r3 =1;
					if(c1==0){open_curtain();} //check enter key *
					if(c3==0){close_curtain();} //check enter key #
					if(c2==0){stop_curtain();} //check enter number 0
					r1 = 0; r2 = r3 = r4 =1;
					if(c1==0){break;}
					if(c2==0){break;}	
					if(c3==0){break;}
					}
				break;
			}
			stop_curtain();
			lcdcmd(0x01,0);
		}
	}
}


void lcd_display1(unsigned char *dvalue)
	{
	int x;
	lcdcmd(0x80,0);
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
void lcd_display3(char *dvalue, char A)
	{
	int x;
	lcdcmd(A,0);
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

void delay2(unsigned int ms)  // providing some delay
{
unsigned int i,j;
for(i=0;i<ms;i++)
for(j=0;j<120;j++);
}

void lcdcmd(char cvalue,int a ) // LCD in command mode opearaion
	{
	ldata=cvalue;
	rs=a;
	en=1;
	Tdelay();
	en=0;
	}
void lcdcmd1(int cvalue,int a ) // LCD in command mode opearaion
	{
	ldata=cvalue;
	rs=a;
	en=1;
	Tdelay();
	en=0;
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
