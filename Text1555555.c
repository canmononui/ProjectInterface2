#include<reg51.h>
sbit relay1=P3^6;
sbit swtop = P3^1;

void main()
	{
	while(1)
	{
		
	  if(swtop==0)
		{   
		relay1=1;
		}
		else
		{
		relay1=0;
		}
	}
	}