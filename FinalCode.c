//Smart Curtain Project
//LDR Contro Motor
#include<reg51.h>

//Set Port
sbit ldr1=P1^0; 		//Optical Sensor)
sbit ldr2=P1^1; 		//Optical Sensor)
sbit relay1=P1^2;   //Relay Switch1 Output
sbit relay2=P1^3;   //Relay Switch2	Output

void open_curtain(void);
void close_curtain(void);
void stop_curtain(void);
void main()
{
	while(1)
    {
		if(ldr1==0 && ldr2==0) //Night (LDR LED OFF)
		{
			open_curtain();
		}
		if(ldr1==1 && ldr2==1) //Day (LDR LED ON)
		{
			close_curtain();
		}
		else //Curtain Stop
		{
		    stop_curtain(); 
		}
	}
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