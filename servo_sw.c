//LDR To Servo
#include<reg51.h>
#include<stdio.h>
#include <intrins.h>
sbit sw=P3^0; // LDR Output
sbit servo=P2^0; //Servo Output
void Delay_servo(unsigned int us);
void Servo_clockwise(void);
void Servo_anticlockwise(void);
void main()
{
  //Servo_anticlockwise();
  servo=0;
  while(1)
  {
  	if(sw==)
 	{
		Servo_clockwise();
	}
	else
 	{
		Servo_anticlockwise();
	}
  }
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
	void Servo_clockwise(void)
	{
 	//Turn to 0 degree
    servo = 1;
    Delay_servo(50);
    servo = 0;
	}

	void Servo_anticlockwise(void)
	{
 	//Turn to 180 degree
    servo=1;
    Delay_servo(110);
    servo=0;
	}
	
