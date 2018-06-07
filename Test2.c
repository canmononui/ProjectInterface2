//Servo
#include<reg51.h>
sbit servo=P3^5;
void open_gate(void);
void close_gate(void);
void timer(unsigned int msec);
void main()
{
 unsigned int i;
 servo=0;
//clockwise direction
		for(i=0;i<1;i++)
		{
			servo=1;
			timer(50);
			servo=0;
			timer(340);
		}
}