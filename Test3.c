//LDR To Servo
#include<reg51.h>
sbit LDR=P1^4; // LDR Output
sbit servo=P3^5; //Servo Output
void timer(unsigned int msec);
void Servo_clockwise(void);
void Servo_anticlockwise(void);
void main()
{
  //Servo_anticlockwise();
  //servo=0;
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

	void Servo_anticlockwise(void)
	{
 	unsigned int i;
	servo=0;
	//anticlockwise direction
		for(i=0;i<1;i++)
		{
			servo=1;
			timer(20);
			servo=0;
			timer(380);
		}
	}
