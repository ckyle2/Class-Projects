#include<stdio.h>
#include<stdlib.h>
//Chase Kyle
struct node
{
        int data, processed;
        struct node *prev, *next;
};

int count = 0;
int first = 0;
int reversed = 0;
int processTime = 0;
int nodesProcessed = 0;
int clookFlag = 0;
struct node* head = NULL;

//creates a node to be added to doubly-linked list
struct node* createNode(int data) 
{
        struct node *ptr = (struct node *)malloc(sizeof (struct node));
        ptr->data = data;
	ptr->processed = 0;
        ptr->prev = NULL;
        ptr->next = NULL;
        return (ptr);
}

//insert a node into the doubly-linked list
void insertNode(int data) 
{
	struct node *temp, *ptr = createNode(data);

        if (head == NULL) 
	{
                head = ptr;
		count++;
                return;
        } 
	else 
	{
                temp = head; 
		while(temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = ptr; 
		ptr->prev = temp;
		count++;
        }
}

//print out the current doubly-linked list
void displayList(struct node *ptr)
{
	printf("Current Process Requests: \n");
	int i = 0;
	while (ptr) 
	{
                printf("%d ", ptr->data);
                ptr = ptr->next;
                i++;
        }
	printf("\n");
}

//delete the entire list
void deleteList(struct node** head_ref)
{
	struct node* current = *head_ref;
	struct node* next; 
	int i = 0;
	while(i < count)
	{
		next = current->next;
		free(current);
		current = next;
		i++;
	}
	*head_ref = NULL;
	printf("List deleted.\n");
	count = 0;
	nodesProcessed = 0;
	processTime = 0;
	reversed = 0;
	clookFlag = 0;
}

//generate random numbers to be inserted into the doubly-linked list
void generateCylinders()
{
	int i, num;
	for(i = 0; i < 20; i++)
	{
		num = rand()%1000;
		insertNode(num);
		if(i == 0)
			first = num;
	}
	return;
}

//sort the list in ascending order
void sortList()
{
	struct node *ptr1, *ptr2;
	int i,j,temp;
	ptr1 = head;
	ptr2 = head;
	
	for(i = 0; i < count; i++)
	{
		temp = ptr1->data;
		for(j = 0; j < i; j++)
			ptr2 = ptr2->next;
		for(j = i; j > 0 && ptr2->prev->data > temp; j--)
		{	
			ptr2->data = ptr2->prev->data;
			ptr2 = ptr2->prev;	
		}
		ptr2->data = temp;
		ptr2 = head;
		ptr1 = ptr1->next;
		
	}
}

//reset all flags
void resetFlags()
{
	struct node *temp = head;
	while(temp != NULL)
	{
		temp->processed = 0;
		temp = temp->next;
	}
	nodesProcessed = 0;
	processTime = 0;
	reversed = 0;
	clookFlag = 0;
	return;
}

/*implementation of shortest search time first algorithm
  goal is to find which cylinder is closest to the one being processed currently
  */
void sstf()
{
	struct node *left, *right, *temp = head;
	int leftDif, rightDif, leftDone, rightDone;
	while(temp->next != NULL)
	{
		if(temp->data == first)
		{
			break;
		}
		temp = temp->next;
	}
	
	while(leftDone != 1 || rightDone != 1)
	{
		temp->processed = 1;
		nodesProcessed++;

		left = temp->prev;
		right = temp->next;

		if(left == NULL)
			leftDone = 1;
		else if (left != NULL)
		{
			while(left->processed == 1 && leftDone != 1)
			{
				if(left->prev == NULL)
				{
					leftDone = 1;
					break;
				}
				left = left->prev;
			}
		}
		if(leftDone != 1)
		{
			leftDif = abs(left->data - temp->data);
		}
		else if (leftDone == 1)
		{
			leftDif = 1000;
		}
	
		if(right == NULL)
			rightDone = 1;
		else if (right != NULL)
		{
			while(right->processed == 1)
			{
				if(right->next == NULL)
				{
					rightDone = 1;
					break;
				}
				right = right->next;
			}
		}
		if(rightDone != 1)
		{
			rightDif = abs(right->data - temp->data);
		}
		else if(rightDone == 1)
		{
			rightDif = 1000;
		}
		if(leftDif == 1000 && rightDif == 1000)
			break;

		if(leftDif <= rightDif)
		{
			processTime+= leftDif;
			temp = left;
		}
		else
		{
			processTime+= rightDif;
			temp = right;
		}
		
	}
	printf("Nodes Processed: %d\n", nodesProcessed);
	return;	
}
//used in scan function, scans left side of disc from current position
void scanLeft(struct node *start)
{
	int distance;
	struct node *left;
	left = start->prev;
	while(left->prev != NULL)
	{
		if(left->prev->processed == 1)
		{
			left->processed = 1;
			nodesProcessed++;
			return;
		}
		distance = left->next->data - left->data;
		processTime += distance;
		left->processed = 1;
		left = left->prev;
		nodesProcessed++;
	}
	if(reversed == 0 && clookFlag == 0)
	{
		distance = left->next->data;
		processTime += distance;
		left->processed = 1;
		nodesProcessed++;
	}
	else
	{
		distance = left->next->data - left->data;
		processTime += distance;
		left->processed = 1;
		nodesProcessed++;
	}
	
	return;
}
//used in scan function, scans right side of disc from current position
void scanRight(struct node *start)
{
	int distance;
	struct node *right;
	right = start->next;
	while(right->next != NULL)
	{
		if(right->next->processed == 1)
		{
			right->processed = 1;
			nodesProcessed++;
			return;
		}
		distance = right->data - right->prev->data;
		processTime += distance;
		right->processed = 1;
		right = right->next;
		nodesProcessed++;
	}
	if(reversed == 0 && clookFlag == 0)
	{
		distance = 999 - right->prev->data;
		processTime += distance;
		right->processed = 1;
		nodesProcessed++;
	}
	else
	{
		distance = right->data - right->prev->data;
		processTime += distance;
		right->processed = 1;
		nodesProcessed++;
	}
	
	return;
}
//scans the disc from current position down to beginning of disc, then backtracks and scans up to hit all cylinders missed when scanning down the list
void scan()
{
	struct node *temp = head;
	int distance;
	while(temp->next != NULL)
	{
		if(temp->data == first)
		{
			break;
		}
		temp = temp->next;
	}
	
	temp->processed = 1;
	nodesProcessed++;

	if(temp->data < 500)
	{
		scanLeft(temp);
		reversed = 1;
		temp = temp->next;
		distance = temp->data;
		processTime += distance;
		temp->processed = 1;
		nodesProcessed++;
		scanRight(temp);
	}
	else
	{
		scanRight(temp);
		reversed = 1;
		temp = temp->prev;
		distance = 999 - temp->data;
		processTime += distance;
		temp->processed = 1;
		nodesProcessed++;
		scanLeft(temp);
	}
	reversed = 0;
	printf("Nodes Processed: %d\n", nodesProcessed);
	return;	
	
}
//enhanced version of c-scan algorithm. scans down until last cylinder is hit, then jumps to end of disc and scans down to hit any cylinders missed when scanning down originally.
void clook()
{
	struct node *rightMost, *temp = head;
	int distance;
	clookFlag++;
	while(temp->next != NULL)
	{
		if(temp->data == first)
		{
			break;
		}
		temp = temp->next;
	}
	rightMost = temp;
	while(rightMost->next != NULL)
	{
		rightMost = rightMost->next;
	}

	temp->processed = 1;
	nodesProcessed++;

	if(temp->data < 500)
	{
		scanLeft(temp);
		temp = rightMost;
		temp->processed = 1;
		nodesProcessed++;
		scanLeft(temp);
	}
	else
	{
		scanRight(temp);
		temp = head;
		temp->processed = 1;
		nodesProcessed++;
		scanRight(temp);
	}
	printf("Nodes Processed: %d\n", nodesProcessed);
	return;	
		
}
int main() 
{	
	int i;
	for(i = 0; i < 5; i++)
	{	
		generateCylinders(head);
		displayList(head);
		sortList();
		printf("Shortest Seek Time First Scheduling:\n");
		sstf();
		printf("Process Time For SSTF: %d\n", processTime);
		resetFlags();
		printf("Scan Scheduling:\n");
		scan();
		printf("Process Time For Scan: %d\n", processTime);
		resetFlags();
		printf("C-Look Scheduling:\n");
		clook();
		printf("Process Time For C-Look: %d\n", processTime);
		deleteList(&head);
	}
        printf("\n");
        return 0;
}
