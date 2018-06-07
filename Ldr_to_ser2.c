//LDR To Servo
#include<reg51.h>
#include<stdio.h>
#include <intrins.h>
sbit LDR=P1^4; // LDR Output
sbit servo=P3^5; //Servo Output
void Delay_servo(unsigned int us);
void Servo_clockwise(void);
void Servo_anticlockwise(void);
void main()
{
  //Servo_anticlockwise();
  P0 = 0xff;
  servo=0;
  while(1)
  {
  	if(LDR==1)
 	{
		Servo_clockwise();
	}
	else
 	{
		Servo_anticlockwise();
	}
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
    servo=0;
    Delay_servo(50);
    servo=1;
	}
	
 	void Delay_servo(unsigned int us)
	{
  		while(us--)
  		{
    	_nop_();
  		}
	}