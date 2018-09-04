#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	int op_num = 0;
	int count_op = 0;
	int stack_cnt = 0;
	int pop_cnt = 0;
	char oper[20] = { 0, };
	int queue_stack[1000] = { 0, };
	int result[1000] = { 0, };
	int result_cnt = 0;
	char *ptr = oper;

	scanf("%d", &op_num); // Choose how many operations you will insert.


	while (count_op != op_num)
	{
		scanf("%s", ptr);
		if (strcmp(ptr, "push") == 0) // if you insert 'push', you can insert one character data.
		{
			scanf("%s", ptr);
			queue_stack[stack_cnt] = atoi(ptr);
			stack_cnt++;
		}
		else if(strcmp(ptr, "size") == 0) // if you insert 'size', you can get the size of queue stack.
		{
			result[result_cnt] = stack_cnt;
			result_cnt++;
		}
		else if (strcmp(ptr, "empty") == 0) // if you insert 'empty', you can check the empty state of queue stack.
		{
			if (stack_cnt == 0)
			{
				result[result_cnt] = 1;
				result_cnt++;
			}
			else
			{
				result[result_cnt] = 0;
				result_cnt++;
			}
		}
		else if (strcmp(ptr, "pop") == 0) // if you insert 'pop', you can erase the first data.
		{
			if (queue_stack[0] == 0)
				result[result_cnt] = -1;
			else
				result[result_cnt] = queue_stack[pop_cnt];
			while (queue_stack[pop_cnt] != 0)
			{
				queue_stack[pop_cnt] = queue_stack[pop_cnt + 1];
				pop_cnt++;
			}
			stack_cnt = pop_cnt;
			pop_cnt = 0;
			result_cnt++;
		}
		else if (strcmp(ptr, "front") == 0) // if you insert 'front', you can get the first data.
		{
			result[result_cnt] = queue_stack[0];
			result_cnt++;
		}
		else if (strcmp(ptr, "back") == 0) // if you insert 'back', you can get the last data.
		{
			result[result_cnt] = queue_stack[stack_cnt - 1];
			result_cnt++;
		}
		ptr = oper;
		count_op++;
	}

	printf("\n\n\n");

	for(int i = 0; i < result_cnt; i++) // print all the queue stack.
	{
		printf("%d\n", result[i]);
	}
	return 0; 
}
