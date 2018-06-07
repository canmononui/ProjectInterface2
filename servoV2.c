#include<reg52.h>
#include<stdio.h>
#include <intrins.h>

sbit motor_pin = P3^5;
void Delay(unsigned int);
void Delay_servo(unsigned int);
void main()
{
  motor_pin = 0;

  do
  {
    //Turn to 0 degree
    motor_pin = 0;
    Delay_servo(1000);
    motor_pin = 1;

    /*Delay(1000);

    //Turn to 90 degree
    motor_pin=1;
    Delay_servo(82);
    motor_pin=0;

    Delay(1000);

    //Turn to 180 degree
    motor_pin=1;
    Delay_servo(110);
    motor_pin=0;

    Delay(1000);*/
  }while(1);
}

void Delay_servo(unsigned int msec)
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