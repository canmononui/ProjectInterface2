// scl >> 2.1
#include<reg51.h>

void nop(void);

#define delay_us nop(); //generates 1 microsecond
#define LCD P1
//sfr ldata=0x90;
sbit RS=P3^5; //connect p3.0 to rs pin of lcd
sbit EN=P3^3; //connect p3.2 to en pin of lcd

sbit r1	= P0^0;	  //keypad row1
sbit r2	= P0^1;	  //keypad row2
sbit r3	= P0^2;	  //keypad row3
sbit r4	= P0^3;	  //keypad row4
sbit c1	= P0^4;	  //keypad col1
sbit c2	= P0^5;	  //keypad col2
sbit c3	= P0^6;	  //keypad col3

sbit SCK=P2^1; //serial clock pin
//sbit SDA=P2^0; //serial data pin
//sbit op = P2^2;
 
#define SCKHIGH  SCK=1;
#define SCKLOW   SCK=0;
//#define SDAHIGH  SDA=1;
//#define SDALOW   SDA=0;

void lcd_data_string(unsigned char *str);
void integer_lcd(int);
void init_lcd(void);
void cmd_lcd(unsigned char);
void write_lcd(unsigned char);
void display_lcd(unsigned char *);
void delay_ms(unsigned int);
void lcd_data_string(unsigned char *str);

void start(void);
void stop(void);
void send_byte(void);
unsigned char receive_byte(void);
void write_i2c(unsigned char,unsigned char,unsigned char);
unsigned char read_i2c(unsigned char,unsigned char);

//clock[]={seconds,minutes,hours,day_of_week,date,month,year};
unsigned char clock[]={0x00,0x31,0x23,0x02,0x24,0x12,0x12};
//unsigned char *s[]={"SUN","MON","TUE","WED","THU","FRI","SAT"};
unsigned char slave_ack,add=0,c,k,x,y;
unsigned int num;
unsigned char str,value1,value2,hr,min,sec,onhr,onmin,offhr,offmin=0;

void disp_time();
void disp_time_date();
void disp_setime();
void disp_setalrmon();
void disp_setalrmoff();
void disp_alrmon();
void disp_alrmoff();
void lcdint(unsigned int m);
void delay_50m ();
void delay_1sec();

void init_serial()	  // Initialize serial port
{
	TMOD=0x20;        // Mode=2
	TH1=0xfd;	  	  // 9600 baud
	SCON=0x50;        // Serial mode=1 ,8-Bit data,1 Stop bit ,1 Start bit  , Receiving on
	TR1=1;	          // Start timer
}

void transmit_data(unsigned char str)		// Function to transmit data through serial port
{
	SBUF=str;		                // Store data in sbuf
	while(TI==0);	                        // Wait till data transmit
	TI=0;			  
}

void receive_data()  interrupt 4	 // Function to recieve data serialy from RS232 into microcontroller
 {
	 str=SBUF;                       // Read sbuf
	 RI=0;
 	 transmit_data(str);             // Transmit to HyperTerminal
 }

            // Real Time Clock Mode

void main(void)

{
	IE=0x90;
	P0=0;
	init_lcd();
	init_serial();		 // Initialize serial port

            while(add<=6)   //update real time clock
                        {
                        write_i2c(0xd0,add,clock[add]);
                        add++;
                        }
add=0;
            while(1)
            {
                 disp_time_date();
							
								x=((read_i2c(0xd0,0x02)/16)*10)+(read_i2c(0xd0,0x02)%16);			//reading & converting Hrs into integers
								y=((read_i2c(0xd0,0x01)/16)*10)+(read_i2c(0xd0,0x01)%16);			//reading & converting Mins into integers
								if(x==23 && y==32)
									{
										op=1;
									}
									else if(x==23 && y==33)
									{
										op=0;
									}
									r1 = 0; r2 = r3 = r4 =1;
									while(c1==0)
									{
										cmd_lcd(0x01);
										cmd_lcd(0x02);
										lcd_data_string("Enter Hours");
										while(RI==0);
										value1=SBUF;
										cmd_lcd(0xC0);
										write_lcd(value1);
										RI=0;
										while(RI==0);
										value2=SBUF;
										write_lcd(value2);
										RI=0;
										clock[2]=((value1-0x30)*16)+(value2-0x30);
										delay_ms(200);
									}
									while(c2==0)
									{
										cmd_lcd(0x01);
										cmd_lcd(0x02);
										lcd_data_string("Enter Minutes");
										while(RI==0);
										value1=SBUF;
										cmd_lcd(0xC0);
										write_lcd(value1);
										RI=0;
										while(RI==0);
										value2=SBUF;
										write_lcd(value2);
										RI=0;
										clock[1]=((value1-0x30)*16)+(value2-0x30);
										delay_ms(200);
									}
									while(c3==3)
									{
										cmd_lcd(0x01);
										cmd_lcd(0x02);
										lcd_data_string("Enter Seconds");
										while(RI==0);
										value1=SBUF;
										cmd_lcd(0xC0);
										write_lcd(value1);
										RI=0;
										while(RI==0);
										value2=SBUF;
										write_lcd(value2);
										RI=0;
										clock[0]=((value1-0x30)*16)+(value2-0x30);
										delay_ms(200);
									}
									r1 = r2 = r3 = 0;r4 =1;
									while(c3==3)
									{
										cmd_lcd(0x01);
										cmd_lcd(0x02);
										lcd_data_string("New Time Updating");
										while(add<=6)   //update real time clock
                        {
                        write_i2c(0xd0,add,clock[add]);
                        add++;
                        }
										cmd_lcd(0xC0);
										lcd_data_string("................");
										add=0;
										str='z';
									}
            }
}                

//starts i2c, if both SCK & SDA are idle

void start(void)
{ 
            if(SCK==0) //check SCK. if SCK busy, return else SCK idle
                        return;
      
SCKLOW  //clock low   
delay_us
}          

//stops i2c, releasing the bus
void stop(void)
{        
SCKHIGH //clock high
delay_us
}

//transmits one byte of data to i2c bus

void send_byte(void)
{
                        SCKHIGH   //clock high
                        delay_us
                        SCKLOW   //clock low
                        delay_us
SCKHIGH  //send clock for acknowledge
delay_us
slave_ack=SDA; //read data pin for acknowledge
SCKLOW  //clock low
delay_us
}      

//receives one byte of data from i2c bus
unsigned char receive_byte(void)
{
                        SCKHIGH //clock high
                        delay_us
                        SCKLOW  //clock low
                        delay_us
SCKHIGH //clock high
delay_us
SCKLOW //clock low
delay_us
}

//writes one byte of data(c) to slave device(device_id) at given address(location)

void write_i2c(unsigned char device_id,unsigned char location,unsigned char c)
{
            do
            {
                        start();      //starts i2c bus
                        send_byte(device_id); //select slave device
                        if(slave_ack==1)  //if acknowledge not received, stop i2c bus
                                    stop();
            }while(slave_ack==1); //loop until acknowledge is received
send_byte(location); //send address location
send_byte(c); //send data to i2c bus
stop(); //stop i2c bus
delay_ms(4);
}
//reads one byte of data(c) from slave device(device_id) at given address(location)

unsigned char read_i2c(unsigned char device_id,unsigned char location)
{
unsigned char c;
            do
            {
                        start();   //starts i2c bus  
                        send_byte(device_id); //select slave device
                        if(slave_ack==1) //if acknowledge not received, stop i2c bus
                                    stop();
            }while(slave_ack==1); //loop until acknowledge is received
send_byte(location);  //send address location     
stop(); //stop i2c bus
start(); //starts i2c bus  
send_byte(device_id+1); //select slave device in read mode
c=receive_byte(1); //receive data from i2c bus
stop(); //stop i2c bus
return c;
}      

//initialize lcd

void init_lcd(void)
{                           
delay_ms(10); //delay 10 milliseconds
cmd_lcd(0x0e); //lcd on, cursor on
delay_ms(10);
cmd_lcd(0x38); //8 bit initialize, 5x7 character font, 16x2 display
delay_ms(10);
cmd_lcd(0x06); //right shift cursor automatically after each character is displayed
delay_ms(10);
cmd_lcd(0x01); //clear lcd
delay_ms(10);
cmd_lcd (0x80);
}

//transmit command or instruction to lcd
void cmd_lcd(unsigned char c)
{
EN=1;
RS=0; //clear register select pin
LCD=c; //load 8 bit data
EN=0; //clear enable pin
delay_ms(2); //delay 2 milliseconds
}

//transmit a character to be displayed on lcd
void write_lcd(unsigned char c)
{
EN=1; //set enable pin
RS=1; //set register select pin
LCD=c;  //load 8 bit data
EN=0; //clear enable pin
delay_ms(2); //delay 2 milliseconds
}

//transmit a string to be displayed on lcd
void display_lcd(unsigned char *s)
{
while(*s)
write_lcd(*s++);
}

//generates delay in milli seconds
void delay_ms(unsigned int i)
{
unsigned int j;
            while(i-->0)
            {
                        for(j=0;j<500;j++)
                        {
                                    ;
                        }
            }
}
void disp_time_date()
{
												c=read_i2c(0xd0,0x02);//read hours register and display on LCD
                        write_lcd((c/16)+48);
                        write_lcd((c%16)+48);
                        write_lcd(':');
                 
                        c=read_i2c(0xd0,0x01);//read minutes register and display on LCD
                        write_lcd((c/16)+48);
                        write_lcd((c%16)+48);
                        write_lcd(':');
                   
                        delay_ms(10);
                        c=read_i2c(0xd0,0x00);//read seconds register and display on LCD
                        write_lcd((c/16)+48);
                        write_lcd((c%16)+48);
                        write_lcd(' ');
                 
                        display_lcd(s[read_i2c(0xd0,0x03)]);//read day register and display
                     
                        cmd_lcd(0xc0);
                        c=read_i2c(0xd0,0x04);//read date register and display on LCD
                        write_lcd((c/16)+48);
                        write_lcd((c%16)+48);
                        write_lcd('/');
                       
                        c=read_i2c(0xd0,0x05);//read month register and display on LCD
                        write_lcd((c/16)+48);
                        write_lcd((c%16)+48);
                        write_lcd('/');
                  
                        write_lcd('2');
                        write_lcd('0');
                        c=read_i2c(0xd0,0x06);//read year register and display on LCD
                        write_lcd((c/16)+48);
                        write_lcd((c%16)+48);
                        delay_ms(100);
                        cmd_lcd(0x01); 
}
void lcd_data_string(unsigned char *str)  // Function to send string to LCD
{
int i=0;
while(str[i]!='\0')
{
  write_lcd(str[i]);
  i++;
  delay_ms(20);
}
return;
}