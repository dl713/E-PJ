#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "GPIO_Wiring.h"

void Exporting(gpio *pgpio, char *pin_num);
void Direction(gpio *pgpio, char *pin_num, char *direction);
void Value_Input(gpio *pgpio, char *pin_num, char *value);
void digitalWrite(char *pin_num, char *value);
void pinMode(char *pin_num, char *str);
void delay_us(int us_time);

void Init_gpio(gpio *pgpio)
{
	memset(pgpio, 0, sizeof(gpio));
	
	pgpio -> Exporting = Exporting;
	pgpio -> Direction = Direction;
	pgpio -> Value_Input = Value_Input;
	pgpio -> digitalWrite = digitalWrite;
	pgpio -> pinMode = pinMode;
	pgpio -> delay_us = delay_us;
}

void Exporting(gpio *pgpio, char *pin_num)
{
	if((pgpio -> fp = fopen("/sys/class/gpio/export","ab")) == NULL){
		printf("Cannot open export file. \n");
		return -1;
	}
	rewind(pgpio -> fp);
	strcpy(pgpio -> set_value, pin_num);
	fwrite(&(pgpio -> set_value), sizeof(char), 3, pgpio -> fp);
	fclose(pgpio -> fp);
}

void Direction(gpio *pgpio, char *pin_num, char *direction)
{
	char buffer[100] = "/sys/class/gpio/gpio";
	strcat(buffer, pin_num);
	strcat(buffer, "/direction");
	if((pgpio -> fp = fopen(buffer, "rb+")) == NULL) {
		printf("Cannot open value file. \n");
		return -1;
	}
	rewind(pgpio -> fp);
	strcpy(pgpio -> set_value, direction);
	fwrite(&(pgpio -> set_value), sizeof(char), 4, pgpio -> fp);
	fclose(pgpio -> fp);
}

void Value_Input(gpio *pgpio, char *pin_num,  char *value)
{
	char buffer1[100] = "/sys/class/gpio/gpio";
	strcat(buffer1, pin_num);
	strcat(buffer1, "/value");
	if((pgpio -> fp = fopen(buffer1, "rb+")) == NULL) {
		printf("Cannot open value file. \n");
		return -1;
	}
	rewind(pgpio -> fp);
	strcpy(pgpio -> set_value, value);
	fwrite(&(pgpio -> set_value), sizeof(char), 2, pgpio -> fp);
	fclose(pgpio -> fp);
}

void pinMode(char *pin_num, char *str)
{
	Exporting(&setup, pin_num);
	Direction(&setup, pin_num, str);
}

void digitalWrite(char *pin_num, char *value)
{
	Value_Input(&setup, pin_num, value);
}

void delay_us(int us_time)
{
	struct timespec tm;
	unsigned long long t_start = 0, t_end = 0;

	clock_gettime(CLOCK_REALTIME, &tm);
	t_start = tm.tv_nsec + tm.tv_sec * 1000000000;
	clock_gettime(CLOCK_REALTIME, &tm);
	t_end = tm.tv_nsec + tm.tv_sec * 1000000000;
	while((t_end - t_start) < (us_time * 1000))
	{
		clock_gettime(CLOCK_REALTIME, &tm);
		t_end = tm.tv_nsec + tm.tv_sec * 1000000000;
	}
}
