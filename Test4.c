// automatic rail gate controlling system 
#include<reg51.h>
sbit servo=P3^5; // servo motor control signal pin
sbit ldr=P1^4;
sbit led=P3^0;
void open_gate(void);
//void close_gate(void);
//void timer(unsigned int msec);
void main()
{
 open_gate(); 		
		/*while(1)
		{
		if(ldr == 1)
		  {
		   
		  }
		else
		  {

 		  }
		}*/
}
 void timer(unsigned int msec)     // Function for timer
{
unsigned int i;
for(i=0;i<msec;i++)
{
TMOD=0x20;         // Mode2
TH1=0xD1;
TL1=0xFF;

TR1=1;
while(TF1==0);
TF1=0;
TR1=0;
}
}

void open_gate(void)
{
 unsigned int i;
 servo=0;
 //anticlockwise direction
		
		for(i=0;i<1;i++)
		{
			servo=1;
			timer(97);
			servo=0;
			timer(212);
		}	
}
/* void close_gate(void)
{
 unsigned int i;
 servo=0;
 //clockwise direction
		for(i=0;i<1;i++)
		{
			servo=1;
			timer(60);
			servo=0;
			timer(340);
		}  
} */