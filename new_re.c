#include <reg52.h>
// Standard 8052SFR : File
#include <stdio.h> // For printf I/O functions
/* AT89C51ED2SFR */
sfr CKCON = 0x8F;
// Clock Control
/* Timer1 Baudrate (29.4912 MHz x 2 )
 Reload = 256 - [58.9824 MHz / (384x Baud)]
 1200 = 0x80(256-128=128)
 2400 = 0xC0(256-94=192)
 4800 = 0xE0(256-32=224)
 9600 = 0xF0(256-16=240)
 19200 = 0xF8(256-8=248)
 38400 = 0xFC(256-4=252)
*/
sbit scl = P2^1;
// I2C SCL Signal
sbit sda = P2^1;
// I2C SDA Signal
/* Pototype Section */
void ds1307_write_byte(unsigned char,unsigned
char); // Setup RTC
unsigned char ds1307_read_byte(unsigned char);
// Read RTC
void i2c_send_byte(unsigned char);
// Write Byte I2C
unsigned char i2c_get_byte(void);
// Read Byte I2C
void delay_i2c(void);
// Short Delay For I2C Bus Interface
void delay(unsigned long);
// Delay Time Function(1..4294967295)
/*--------------------------------------------
The main C function. Program execution Here
---------------------------------------------*/
void main (void)
{
 unsigned char j;
unsigned char last_second;
 CKCON = 0x01;
// Initial X2 Mode (58.9824 MHz)

/* Initial MCS51Serial Port */
 TMOD &= 0x0F;
// Reset old Timer1 Mode Config
 TMOD |= 0x20;
// Update Timer1 = 8 Bit Auto Reload
 SCON = 0x50;
// Serial Port Mode 1 (N,8,1)
 ES = 0;
// Disable Serial Interupt
ET1 = 0;
// Disable Timer1 Interrupt
 PCON &= 0x7F;
// SMOD1 = 0 (Disable Double Baudrate)
 TH1 = 0xF0;
// Setup Timer1 Baudrate 9600BPS / 58.9824 MHz
 TL1 = 0xF0;
 TR1 = 1;
// Start Timer1 Generate Baudrate
 TI = 1;
// Set TI to send First char of UART
 scl = 1;
// Makesure I2C Stop Condition
 sda = 1;
ds1307_write_byte(7,0x80);
// Disable Square Wave Output
 ds1307_write_byte(2,0);
// Set Hour = 00
 ds1307_write_byte(1,0);
// Set Minute = 00
ds1307_write_byte(0,0);
// Start RTC Clock + Set Second = 00

printf("Hello This is ET-BASE51V3.0(ED2)\n"); // Display Start Menu
printf("Demo Test RTC:DS1307PollingRead\n");
printf("HR:MN:SC\n");
delay(100);
while(1)
 {
 printf("\r");
// Restart Print
 j = ds1307_read_byte(2);
// Get Hour
 printf("%02BX",j);
 printf(":");
 j = ds1307_read_byte(1);
// Get Minute
 printf("%02BX",j);
 printf(":");
  j = ds1307_read_byte(0);
// Get Second
 last_second = j;
// Save Second Reference
 printf("%02BX",j);
 do
// Repeat Get Second until Second Change
 {
 j = ds1307_read_byte(0);
// Get Second
 }
 while(last_second == j);
// Repeat if Second Not Change
}
}
/*******************************/
/* Write Data 1-Byte to DS1307 */
/*******************************/
void ds1307_write_byte(unsigned char
ds1307_address,unsigned char ds1307_data)
{
 sda = 0;
// I2C Start Condition
 scl = 0;
 delay_i2c();
 i2c_send_byte(0xD0);
// Send ID Code DS1307,Write (1101000+0)
 sda = 1;
// Release SDA
 scl = 1;
// Start ACK Clock
 delay_i2c();
 while(sda) {}
 scl = 0;
// End ACK Clock
 delay_i2c();
 i2c_send_byte(ds1307_address);
// Send DS1307 Address
sda = 1;
// Release SDA
 scl = 1;
// Start ACK Clock
 delay_i2c();
 while(sda) {}
 scl = 0;
// End ACK Clock
 delay_i2c();
 i2c_send_byte(ds1307_data);
// Send DS1307 Data
 sda = 1;
// Release SDA
 scl = 1;
// Start ACK Clock
 delay_i2c();
 while(sda) {}
 scl = 0;
// End ACK Clock
 delay_i2c();
 sda = 0;
// Stop Bit(End of Data)
 scl = 1;
// I2C Stop
							//Condition
delay_i2c();
sda = 1;
return;
}
/********************************/
/* Read Data 1-Byte From DS1307 */
/********************************/
unsigned char ds1307_read_byte(unsigned char
ds1307_address)
{
 unsigned char ds1307_data;
// Dummy Byte
 sda = 0;
// I2C Stat condition
 scl = 0;
 delay_i2c();
 i2c_send_byte(0xD0);
// Send ID Code DS1307,Write (1101000+0)
 sda = 1;
// Release SDA
 scl = 1;
// Start ACK Clock
 delay_i2c();
 while(sda) {}
 scl = 0;
// End ACK Clock
 delay_i2c();
 i2c_send_byte(ds1307_address);
// Send DS1307 Address
 sda = 1;
// Release SDA
 scl = 1;
// Start ACK Clock
delay_i2c();
 while(sda) {}
 scl = 0;
// End ACK Clock
 delay_i2c();
 scl = 1;
// I2C Stop
 					//Condition
delay_i2c();
 sda = 1;
 // New Start For Read //
 sda = 0;
// I2C Stat
//condition
 scl = 0;
 delay_i2c();
 i2c_send_byte(0xD1);
// Send ID Code DS1307,Read (1101000+1)
sda = 1;
// Release SDA
 scl = 1;
// Start ACK Clock
 delay_i2c();
 while(sda) {}
 scl = 0;
// End ACK Clock
 delay_i2c();

 ds1307_data = i2c_get_byte();
//
Read 1-Byte From DS1307
 sda = 1;
// Send Stop Bit (End of Read Data)
 scl = 1;
// Start Stop Bit Clock
 delay_i2c();
 scl = 0;
// End Stop Bit Clock
 delay_i2c();
 scl = 1;
// I2C Stop
//Condition
 delay_i2c();
 sda = 1;
 return ds1307_data;
}
/******************************/
/* Send Data 8 Bit to I2C Bus */
/******************************/
void i2c_send_byte(unsigned char i)
{
 char j;
// Bit Counter Send
 for(j = 0;j < 8;j++)
// 8-Bit Counter Send Data
 {
 if((i & 0x80) == 0x80)
// Send MSB First
 {sda = 1;}
// Send Data = 1
 else
 {sda = 0;}
// Send Data = 0
 scl = 1;
// Release SDA
 delay_i2c();
 scl = 0;
// Next Bit Send
 delay_i2c();
 i <<= 1;
// Shift Data For Send (MSB <- LSB)
 }
 return;
}
/*******************************/
/* Get Data 8 Bit From I2C Bus */
/*******************************/
unsigned char i2c_get_byte(void)
{
unsigned char i;
// Result Byte Buffer
char j;
// Bit Counter Read Data
for(j = 0; j < 8; j++)
// 8-Bit Counter Read Data
{
 i <<= 1;
// Shift Result
Save (MSB <- LSB)
 sda = 1;
// Release Data
 scl = 1;
// Strobe Read SDA
 delay_i2c();
 if(sda == 1)
 {
 i |= 0x01;
// Save Bit Data = 1
}
 else
 {
 i &= 0xFE;
// Save Bit Data = 0
}
 scl = 0;
// Next Bit Read
 delay_i2c();
}
 return i;
}
/**************************************/
/* Delay For I2C Bus Device Interface */
/**************************************/
void delay_i2c(void)
{
 unsigned char i;
 i = 100;
// Delay Counter
 while(i > 0) {i--;}
// Loop Decrease Counter
 return;
}
/*******************************************/
/* Long Delay Time Function(1..4294967295) */
/*******************************************/
void delay(unsigned long i)
{
 while(i > 0) {i--;}
// Loop Decrease Counter
 return;
}


