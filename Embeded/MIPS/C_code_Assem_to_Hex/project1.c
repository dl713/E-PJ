#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct mips{
	char label[20];
	char instr[20];
	char op1[20];
	char op2[20];
	char op3[20];
	int encoding;
};

#define MAX_NUM 50

int reg(char *ch_in)
{
	int i;
	char *reg_array[32] = {"$0", "$1", "$2", "$3", "$4", "$5", "$6", "$7", "$8", "$9",
				"$10", "$11", "$12", "$13", "$14", "$15", "$16", "$17", "$18", "$19",
				"$20", "$21", "$22", "$23", "$24", "$25", "$26", "$27", "$28", "$29",
				"$30", "$31"};
	char *reg_name[32] = {"$zero", "$at", "$v0", "$v1", "$a0", "$a1", "$a2", "$a3", "$t0", "$t1",
				"$t2", "$t3", "$t4", "$t5", "$t6", "$t7", "$s0", "$s1", "$s2", "$s3",
				"$s4", "$s5", "$s6", "$s7", "$t8", "$t9", "$k0", "$k1", "$gp", "$sp",
				"$fp", "$ra"};

	for(i=0; i<32; i++)	
	{
		if(strcmp(ch_in, reg_array[i])==0) break;
		else if(strcmp(ch_in, reg_name[i])==0) break;
	}

	return i;
}

int typeA(int operation, char *rd, char *rs, char *rt)
{
	int rdi, rsi, rti;
	
	rdi = reg(rd);
	rsi = reg(rs);
	rti = reg(rt);

	return ((operation)|(rsi<<21)|(rti<<16)|(rdi<<11));

}

unsigned int typeB(unsigned int operation, char *rt, char *rs, int im)
{
	int rti, rsi;

	rti = reg(rt);
	rsi = reg(rs);

	if(im<0) im = (im & 0x0000ffff);

	return ((operation)|(rsi<<21)|(rti<<16)|im);
}

unsigned int typeC(unsigned int operation, char *rt, char *rs)
{
	int rti, rsi, i, j;
	char rss[2][10];
	char *endpt;
	int num;																		

	rti = reg(rt);

	for(i=0; (rs[i]!='(')&&(rs[i]!=' '); i++) rss[0][i] = rs[i];
	rss[0][i] = '\0';
	
	for(; (rs[i]=='(')||(rs[i]==' '); i++);

	for(j=0; (rs[i]!=')')&&(rs[i]!='\0'); i++)
	{
		rss[1][j] = rs[i];
		j++;
	}
	rss[1][j] = '\0';
	
	rsi = reg(rss[1]);

	if(rss[0][1]=='x') num = (int)(strtol(rss[0], &endpt, 16));
	else num = atoi(rss[0]);
	
	if(num<0) num = (num & 0x0000ffff);

	return ((operation)|(rsi<<21)|(rti<<16)|(num));
}

unsigned int typeD(unsigned int operation, char *rs, char *rt, int im)
{
	int rsi, rti;

	rsi = reg(rs);
	rti = reg(rt);

	if(im<0) im = (im & 0x0000ffff);

	return ((operation)|(rsi<<21)|(rti<<16)|im);
}

unsigned int typeE(unsigned int operation, int im)
{
	if(im<0) im = (im & 0x04ffffff);
	
	return ((operation)|im);
}

int lab(char *labels, struct mips *arr, int max_line)
{
	int i;

	for(i=0; i<max_line; i++) if(strcmp(labels, arr[i].label)==0) break;

	return i;
}

int op(char *inst)
{
	int i;

	char operation[10][5] = {"add", "sub", "and", "or", "slt", "lw", "sw", "beq", "addi", "j"};
	
	for(i=0; i<10; i++) if(strcmp(inst, operation[i])==0) break;

	return i;
}

int inputc(char line[MAX_NUM], struct mips *arr, int a)
{
	int j, b;

	if((int)strcspn(line,":")!=(int)strlen(line))
	{
		for(j=0; (line[j]!=':')&&(line[j]!=' '); j++)
		{
			arr[a].label[j] = line[j];
		}
		arr[a].label[j] = '\0';
		
		for(; (line[j]==' ')||(line[j]==':'); j++);

		for(b=0; line[j]!=' '; b++)
		{
			arr[a].instr[b] = line[j];
			j++;
		}
		arr[a].instr[b] = '\0';

		for(; line[j]==' '; j++);
		
		for(b=0; (line[j]!=' ')&&(line[j]!=',')&&(line[j]!='\0'); b++)
		{
			arr[a].op1[b] = line[j];
			j++;
		}
		arr[a].op1[b] = '\0';

		if(line[j]=='\0')
		{
			arr[a].op2[0] = '\0';
			arr[a].op3[0] = '\0';
			return 0;
		}


		for(; (line[j]==' ')||(line[j]==','); j++);

		if((op(arr[a].instr)==5)||(op(arr[a].instr)==6))
		{
			for(b=0; line[j]!='\0'; b++)
			{
				arr[a].op2[b] = line[j];
				j++;
			}
		}

		else
		{
			for(b=0; (line[j]!=' ')&&(line[j]!=',')&&(line[j]!='\0'); b++)
			{
				arr[a].op2[b] = line[j];
				j++;
			}
		}
		arr[a].op2[b] = '\0';

		if(line[j]=='\0')
		{
			arr[a].op3[0] = '\0';
			return 0;
		}

		for(; (line[j]==' ')||(line[j]==','); j++);


		for(b=0; (line[j]!=' ')&&(line[j]!=',')&&(line[j]!='\0'); b++)
		{
			arr[a].op3[b] = line[j];
			j++;
		}
		arr[a].op3[b] = '\0';
	}

	else
	{
		arr[a].label[0] = '\0';
		for(j=0; line[j]==' '; j++);
		
		for(b=0; line[j]!=' '; b++)
		{
			arr[a].instr[b] = line[j];
			j++;
		}
		arr[a].instr[b] = '\0';

		for(; line[j]==' '; j++);

		for(b=0; (line[j]!=' ')&&(line[j]!=',')&&(line[j]!='\0'); b++)
		{
			arr[a].op1[b] = line[j];
			j++;
		}
		arr[a].op1[b] = '\0';

		if(line[j]=='\0')
		{
			arr[a].op2[0] = '\0';
			arr[a].op3[0] = '\0';
			return 0;
		}

		for(; (line[j]==' ')||(line[j]==','); j++);
		
		if((op(arr[a].instr)==5)||(op(arr[a].instr)==6))
		{
			for(b=0; line[j]!='\0'; b++)
			{
				arr[a].op2[b] = line[j];
				j++;
			}
		}

		else
		{
			for(b=0; (line[j]!=' ')&&(line[j]!=',')&&(line[j]!='\0'); b++)
			{
				arr[a].op2[b] = line[j];
				j++;
			}
		}

		arr[a].op2[b] = '\0';
		
		if(line[j]=='\0')
		{
			arr[a].op3[0] = '\0';
			return 0;
		}

		for(; (line[j]==' ')||(line[j]==','); j++);


		for(b=0; (line[j]!=' ')&&(line[j]!=',')&&(line[j]!='\0'); b++)
		{
			arr[a].op3[b] = line[j];
			j++;
		}
		arr[a].op3[b] = '\0';
	}

	return 0;
}

int main(int argc, char *argv[])
{	
	FILE *fp_in=fopen(argv[1], "r");
	FILE *fp_out=fopen(argv[2], "w");

	int i=0, max_line, instruct;
	char line[MAX_NUM][MAX_NUM], *result;

	while(1)
	{
		result = fgets(line[i], MAX_NUM, fp_in);
		if(result==NULL)break;
		line[i][strlen(line[i])-1] = '\0';
		i++;
	}
	max_line = i;

	struct mips arr[MAX_NUM];

	for(i=0; i<max_line; i++) inputc(line[i], arr, i);

	for(i=0; i<max_line; i++)
	{
		instruct = op(arr[i].instr);
	
		switch(instruct)
		{
			case 0:	arr[i].encoding = typeA(0x00000020, arr[i].op1, arr[i].op2, arr[i].op3); break;					//add
			case 1: arr[i].encoding = typeA(0x00000022, arr[i].op1, arr[i].op2, arr[i].op3); break;					//sub
			case 2: arr[i].encoding = typeA(0x00000024, arr[i].op1, arr[i].op2, arr[i].op3); break;					//and
			case 3: arr[i].encoding = typeA(0x00000025, arr[i].op1, arr[i].op2, arr[i].op3); break;					//or
			case 4: arr[i].encoding = typeA(0x0000002A, arr[i].op1, arr[i].op2, arr[i].op3); break;					//slt
			case 5: arr[i].encoding = typeC(0x8c000000, arr[i].op1, arr[i].op2); break;						//lw
			case 6: arr[i].encoding = typeC(0xac000000, arr[i].op1, arr[i].op2); break;						//sw
			case 7: arr[i].encoding = typeD(0x10000000, arr[i].op1, arr[i].op2, (lab(arr[i].op3, arr, max_line)-i-1)); break;	//beq
			case 8: arr[i].encoding = typeB(0x20000000, arr[i].op1, arr[i].op2, atoi(arr[i].op3)); break;				//addi
			case 9: arr[i].encoding = typeE(0x08000000, lab(arr[i].op1, arr, max_line)); break;					//j
		}
	}

	for(i=0; i<max_line; i++) fprintf(fp_out, "%08x\n", arr[i].encoding);

	return 0;
}
