#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>

struct thread_data
{
	int num;
	int fibSeq[100];
	char* msg;
};
void GenerateSequence(void*);
int fib(int);

int main()
{
	pthread_t thread0, thread1, thread2, thread3;
	int i, k;
	int nums[4];
	struct thread_data array[4];
	//takes four integers from input to calculate fibonacci sequences
	printf("Please insert four integers seperated by spaces to be evaluated: ");
	scanf("%d %d %d %d", &nums[0], &nums[1], &nums[2], &nums[3]);
	
	//insert string associated with number to show if pthread_join functioned properly.
	array[0].msg = "Chase";
	array[0].num = nums[0];
	array[1].msg = "Kyle";
	array[1].num = nums[1];
	array[2].msg = "CPSC";
	array[2].num = nums[2];
	array[3].msg = "ESU";
	array[3].num = nums[3];
	
	//creates threads to calculate all four fibonacci sequences at same time
	pthread_create(&thread0, 0, (void*) &GenerateSequence, (void *) &array[0]);
	pthread_create(&thread1, 0, (void*) &GenerateSequence, (void *) &array[1]);
	pthread_create(&thread2, 0, (void*) &GenerateSequence, (void *) &array[2]);
	pthread_create(&thread3, 0, (void*) &GenerateSequence, (void *) &array[3]);

	//joins the threads together to make sure they return how we want them to
	pthread_join(thread0, NULL);
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	pthread_join(thread3, NULL);

	//outputs name and fib sequence for each thread
	for(i=0; i<4; i++)
	{
		printf(array[i].msg);
		for(k=0; k < array[i].num; k++)
		{
			printf(" %d", array[i].fibSeq[k]);
		}
		printf("\n");
	}
	
	return 0;
}
//calculate fibonacci sequence of a number
int fib(int x)
{
	if (x==0)
	{
		return 0;
	}
	if (x==1)
	{
		return 1;
	}
	else
	{
		return fib(x-1) + fib(x-2);
	}
}

void GenerateSequence(void *threadarg)
{
	int i;
	struct thread_data *my_data;
	my_data = (struct thread_data *) threadarg;
	for(i=0;i <= my_data->num; i++)
	{
		my_data->fibSeq[i] = fib(i);
	}
	pthread_exit(0);
}


