#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

typedef struct _gpio
{
	FILE *fp;
	char set_value[10];
	
	void (*Exporting)(struct _gpio*, char *pin_num);
	void (*Direction)(struct _gpio*, char *pin_num, char *direction);
	void (*Value_Input)(struct _gpio*, char *pin_num, char *value);

	void (*digitalWrite)(char *pin_num, char* value);
	void (*pinMode)(char *pin_num, char *str);
	void (*delay_us)(int us_time);
}gpio;

gpio setup;
void Init_gpio(gpio *pgpio);

