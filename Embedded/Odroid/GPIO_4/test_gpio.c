#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "GPIO_Wiring.h"

#define BAUD ((float)1/9600)

void printB()
{
	digitalWrite("21", "1");
	usleep(BAUD);
	digitalWrite("21", "0");
	usleep(BAUD);
	digitalWrite("21", "0");
	usleep(BAUD);
	digitalWrite("21", "1");
	usleep(BAUD);
	digitalWrite("21", "0");
	usleep(BAUD);
	digitalWrite("21", "0");
	usleep(BAUD);
	digitalWrite("21", "0");
	usleep(BAUD);
	digitalWrite("21", "0");
	usleep(BAUD);
	digitalWrite("21", "1");
	usleep(BAUD);
	digitalWrite("21", "0");
	usleep(BAUD);
	digitalWrite("21", "1");
}

int main()
{
	Init_gpio(&setup);
	pinMode("21","out");
	digitalWrite("21", "1");
	while(1)
	{
		usleep(500000);
		printB();
		usleep(500000);
	}
	return 0;
}
