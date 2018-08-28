#include <stdio.h>
#include <wiringPi.h>
#include <sys/time.h>

int main(int argc, char * argv[])
{
	unsigned int delay_cnt = 0;
	wiringPiSetup();
	pinMode(30,OUTPUT);
	while(1)
	{
		if((delay_cnt >= 100) && (delay_cnt < 200))
		{
			digitalWrite(06,HIGH);
			delay_cnt++;
			printf("high : %d\n",delay_cnt);
		}
		else if((delay_cnt < 100))
		{
			digitalWrite(06,LOW);
			delay_cnt++;
			printf("low : %d\n",delay_cnt);
		}
		else
		{
			delay_cnt = 0;
			printf("reset : %d\n",delay_cnt);
		}
	}
	return 0;
}
