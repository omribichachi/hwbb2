
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_YEAR '0'
#define CHAR_YEAR '1'

typedef struct Worker
{
	unsigned long int id;
	char* name;
	unsigned long int salary;
	union year {
		unsigned long int yearn;
		char yearc[6];
	} year;
	char type;
} Worker;

typedef struct WorkerList
{
	Worker* data;
	struct WorkerList* next;
} WorkerList;
//A function that creates a new employee that receives a year type mark
Worker* createWorker(char type)
{
	Worker* newWorker = (Worker*)malloc(sizeof(Worker));//create place in memory for new worker
	if (newWorker == NULL)
	{
		printf("malloc worker failure");
	}//malloc worker failure
	else {
		printf("enter id:");
		scanf_s("%d", &newWorker->id);//receive id
		char newname[100];
		printf("enter name:");
		fseek(stdin, 0, SEEK_END);
		gets(newname);//receive name
		int len = strlen(newname);
		newWorker->name = (char*)malloc(sizeof(++len));// sets a new size based on the name input.
		if (newWorker->name == NULL)
		{
			printf("allocation name worker error");
		}//allocation name worker error
		else
		{
			strcpy(newWorker->name, newname);//copy the input, end when \0
			printf("enter salary:");
			scanf_s("%d", &newWorker->salary);//receive salary
			newWorker->type = type;
			switch (type) {//check the type if 1 year will be in letters if 0 year will be in numbers 
			case NUM_YEAR:
				printf("enter year in number: ");
				scanf_s("%d", &newWorker->year.yearn);
				break;
			case CHAR_YEAR:
				printf("enter year in string: ");
				fseek(stdin, 0, SEEK_END);
				gets(newWorker->year.yearc);
				break;
			default:
				printf("WRONG FORMAT!");
				break;
			}
			return newWorker;
		} 

	}
}
Worker* PrintWorker(char type, Worker* worker)
{
	//Prints the employee details other than the year type
	printf("id is: %ld\n", worker->id);
	printf("salary is: %ld \n", worker->salary);
	printf("name is %s\n", worker->name);
	printf("year is: \n");
	switch (type)//check the type if 1 print year in letters if 0 print year in numbers
	{
	case NUM_YEAR:
		printf("%d\n\n", worker->year.yearn);
		break;
	case CHAR_YEAR:
		puts (worker->year.yearc);
		break;
	default:
		printf("WRONG FORMAT!");
		break;
	}
}
WorkerList* addWorker (WorkerList* head, Worker* w) {
	WorkerList* p = head;
	WorkerList* newWorkerlist = (WorkerList*)malloc(sizeof(WorkerList));
	newWorkerlist->data = w;
	if (head == NULL)// case for list is empty
	{
		head = newWorkerlist;
		newWorkerlist->next = NULL;
		return head;
	}
	if (head->next== NULL)//case for 1 item in the list
	{
		if (newWorkerlist->data->salary > head->data->salary)//Checks if the new employee's salary is bigger than the current employee
		{
			newWorkerlist->next = p;
			p->next = NULL;
			head = newWorkerlist;
			return head;
		}
		else {//the new employee salary is not bigger than current employee
			p->next = newWorkerlist;
			return head;
		}
	}
	while (p->next != NULL && p->next->data->salary > newWorkerlist->data->salary)//case for 2 and more employees, looking the right place the worker in the right location
	{
		p = p->next;
	}
	if (p->next != NULL) {// case of addition during the list the right place
		newWorkerlist->next = p->next;
		p->next = newWorkerlist;
	}
	else// add to the end of list
	{
		p->next = newWorkerlist;
		newWorkerlist->next = NULL;
	}
	return head;
}
//int index(WorkerList* head, long unsigned id)
//{
//	WorkerList* p = head;
//	int counter = 1;
//	if (head == NULL)//case list is null
//		return -1;
//	while (p->next != NULL && p->data->id != id)//Search the location employee in the employee list by ID
//	{
//		counter++;
//		p = p->next;
//	}
//	if (p->data != id && p->next == NULL)//case there is no worker with this id
//		return -1;
//	else return counter;//return location if the worker found 
//}


WorkerList* deleteWorstWorker (WorkerList* head)//Keep in mind the list of Workers is arranged so that the first one with the higher salary
{
	WorkerList* p = head;
	WorkerList* ToDelete = head;
	if (head == NULL) {//In a situation when the list is empty
		printf("is empty cant delete");
		return head;
	}
	if (head->next == NULL) {//case for 1 worker in the list
		head = NULL;
		free(p->data->name);
		free(p->data);
		free(p);
		return head;
	}
	ToDelete = ToDelete->next;
	while (ToDelete->next != NULL)//going to the last worker in the list
	{
		p = ToDelete;//Position the pointer one place before the erased part
		ToDelete = ToDelete->next;
	}
	p->next = NULL;//erased the last worker
	free(ToDelete->data->name);//free worker
	free(ToDelete->data);
	free(ToDelete);
	return head;
}
//A function that raises the salary of workers by a certain percent
void update_worker(WorkerList* head, float percent)
{
	WorkerList* p = head;
	if (head == NULL) return;//case list empty
	while (head != NULL)//run allover the list and increse the salary by precent 
	{
		head->data->salary += ((head->data->salary * percent) / 100);
		head = head->next;
	}
	return;
}
//Turns the order of employee locations from last to first
WorkerList* reverse(WorkerList* head)
{
	WorkerList* p1 = head;
	WorkerList* p2 = head;
	WorkerList* p3 = head;
	if (head == NULL || head->next == NULL)//case for empty list and one worker
		return head;
	p2 = p1->next;//pointer to the second worker
	p3 = p2->next;//pointer to the third worker
	p1->next = NULL;//worker 1 becane the last on the list and points to null
	while (p3 != NULL)//p2 worker points to p1 worker and then p1 points on p2, p2 points on p3 and p3 points to the next worker until p3 points null 
	{
		p2->next = p1;
		p1 = p2;
		p2 = p3;
		p3 = p3->next;
	}
	p2->next = p1;
	head = p2;// the worker who was last now is the first
	return head;
}

void freeWorkers(WorkerList* head)
{
	WorkerList* p = head;
	if (head == NULL)//case for null list
		return;
	while (p != NULL)//free all the memory that the list used
	{
		head = head->next;
		p->next = NULL;
		free(p->data->name);
		free(p->data);
		free(p);
		p = head;
	}
	return;
}

int index(WorkerList* head, long int personal_num)
{
	static int location = 1;
	if (head == NULL)
	{
		location = 1;
		return -1; //personal_num does not exist
	}//personal_num does not exist
	if (head->data->id == personal_num) // If the personal_num exist
	{
		int temp = location;
		location = 1;
		return temp;
	}
	location++;
	index(head->next, personal_num); //send the next position
}//index_recursive
void main()
{
	Worker* w;
	WorkerList* list = NULL;
	WorkerList* p = list;
	int temp;
	float precent;
	unsigned long int id;
	int indexx;
	int type1;
	do
	{
		printf("choose one:\n 1 for add item\n 2 for delete item\n 3 for update list\n 4 for print list \n 5 for reverse list\n 6 place of item by id \n 7 for delete list \n 8 for exit\n");
		scanf_s("%d", &temp);
		switch (temp)
		{
		case 1:
			printf("enter 1 for year in letters or 0 tor year in numbers\n");
			scanf_s("%d", &type1);
			if (type1 == 0)
			{
				w = createWorker(NUM_YEAR);
			}
			else if (type1 == 1)
			{
				w = createWorker(CHAR_YEAR);
			}
			else {
				printf("wrong number try again\n"); break;
			}
			list = addWorker(list, w);
			break;
		case 2:
			list = deleteWorstWorker(list);
			break;
		case 3:
			printf("enter precent:");
			scanf_s("%f", &precent);
			update_worker(list,precent);
			break;
		case 4:
			if (list == NULL) {
				printf("list is null\n");
				break;
			}
			else {
				while (p != NULL)
				{
					PrintWorker(p->data->type, p->data);
					p = p->next;
				}
			}
			p = list;
			break;
		case 5:
			list = reverse(list);
			break;
		case 6:
			printf("enter id: ");
			scanf_s("%ld\n", &id);
			indexx = index(list, id);
			printf("%d\n", indexx);
			break;
		case 7:
			freeWorkers(list);
			break;
		case 8:
			break;
		default:
			printf("try again\n");
			break;
		}
	} while (temp!=8);
		


}