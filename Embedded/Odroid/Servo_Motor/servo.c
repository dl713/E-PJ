#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include "gp.h"

int main(void)
{
	pinMode("30","out");
	while(1){
		digitalWrite("30","1");
		//sleep(1);
		usleep(2000);
		digitalWrite("30","0");
		//sleep(1);
		usleep(18000);
	}
	return 0;
}
