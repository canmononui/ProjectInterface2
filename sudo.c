//loop check curtain distance
//สมมุติใช้เวลาทั้งหมด 30 วินาที	

void open_curtain(void);
void delay_count(unsigned int count);
void main()
{

	int count=0;

}

void open_curtain(void)  //motor on anticlockwise
{
	relay1=1;    
	relay2=0;	
}

void delay_count(unsigned int count);
{
	while(count>0&&count<30)
		{
		count++;
		}
}


	
