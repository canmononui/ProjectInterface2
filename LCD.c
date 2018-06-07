#include<reg51.h> 
#define LCD P1
sbit RS=P3^5; 
sbit EN=P3^3;//Data to display
void lcd_display(unsigned char *c );
void delay()  
 {   
   int k;   
   for(k=0;k<=1000;k++); 
  } 
void lcd(char a,short int b)       //Subroutine for command and data transmission 
  {   
   LCD=a;                             //Placing byte in D0-D7 lines of LCD
   RS=b;                              //0 for command and 1 for data
   EN=1;   
   delay();   
   EN=0; 
  }
void main()
{
   lcd_display("Welcome to");
   lcd(0x38,0);                      //Initializing LCD
   lcd(0x0f,0);   
   lcd(0x01,0);  
   lcd(0x02,0); 
   lcd(0x83,0);   
   //while(1);
 }
void lcd_display(unsigned char *dvalue)
{
	unsigned int x;
	for(x=0;dvalue[x]!=0;x++)	//dvalue[x]!=0
	{
	lcd(dvalue[x],1);
	}
	while(1);
}