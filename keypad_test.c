 //----- reading the char/number from the keyboard----//
#include<reg51.h>
#define ROW P1      // assigning  Port1 to ROW
#define COL P2       // assigning port2 to COL
void msdelay(unsigned int value);
void sertx(unsigned char );
unsigned char dat[4][3]={'0','1','2','3',    // keypad read data
                          '4','5','6','7',
                           '8','9','A','B'};
void main()
{
 unsigned char colloc,rowloc; // initializing column and row locations
 TMOD=0x20;               // timer -2 mode-2
 TH1=0xFD;                 // preset FD 
 SCON=0x50;              // serial control reg. 9600 baudrate
 TR1=1;                      // timer-1 start
 COL=0xFF;               // make column pins input
 while(1)
 {
   do
   {
    ROW=0x00;      // write "00000000" to ROW   
       colloc=COL;  // read column input
    colloc&=0x0F;  // hide higher nibble
    }while(colloc!=0x0f); //check whether any change in column pins
    do
    {
     do
     {
      msdelay(20);
      colloc=COL;
      colloc&=0x0F;
      }while(colloc==0x0F);
      msdelay(20);                  // check column after 20ms
      colloc=COL;                  // it is for accuracy if there is any random spike it can ignore
      colloc&=0x0F;
      }while(colloc==0x0F);
    while(1)
    {
     ROW=0xFE;         // write "1111_1110" on to ROW
     colloc=COL;
     colloc&=0x0F;
     if(colloc!=0x0F)  // if there is a change in column/button pressed
     {  
      rowloc=0;           
       break;
      }
      ROW=0xFD;  // writing "1111_1101" onto the ROW
      colloc=COL;
      colloc&=0x0F;
      if(colloc!=0x0F)  // if there is a change in column/button pressed
       {
        rowloc=1;
        break;
        }
      ROW=0xFB;   // writing "1111_1011" onto the ROW 
      colloc=COL;
      colloc&=0x0F;
      if(colloc!=0x0F)  // if button pressed / change in column
       {
        rowloc=2;
        break;
        }
      ROW=0xF7;     // writing "1111_0111" onto ROW
      colloc=COL;
      colloc&=0x0F;
      if(colloc!=0x0F)  // if button pressed/change in column
      {
       rowloc=3;
       break;
       }
       }
   if(colloc==0x0E)
   sertx( dat[rowloc][0]);
   if(colloc==0x0D)
   sertx(dat[rowloc][1]);
   if(colloc==0x0B)
   sertx(dat[rowloc][2]);
   if(colloc==0x07)
    sertx(dat[rowloc][3]);
    } 
  }
void sertx(unsigned char x)
{
 SBUF=x;
 while(TI==0);
 TI=0;
 }
void msdelay(unsigned int value)
{
 unsigned int i,j;
 for(j=0;j<value;j++)
 for(i=0;i<100;i++) ;
  }