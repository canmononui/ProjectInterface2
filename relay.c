//Relay
#include<reg52.h>
#include<stdio.h>
#include <intrins.h>
sbit relay = P3^6;
sbit relay1 = P3^7;
void main()
{

relay = 0;
relay1 = 0;

}