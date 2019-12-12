	
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//header /////////////////////////////////////////////////////////

/* Struct for list nodes */
struct lst_node_s {
int data;
struct lst_node_s* next;
};
typedef struct lst_node_s Lst_Node_s;
Lst_Node_s *root_list = NULL;
Lst_Node_s *iter= NULL;
Lst_Node_s *temp_lst= NULL;

/* Struct for task nodes */
struct tsk_node_s {
int task_num; //starting from 0
int task_type; // insert:0, delete:1, search:2
int value;
struct tsk_node_s *next;
};
typedef struct tsk_node_s Tsk_Node_s;
Tsk_Node_s *root_tsk = NULL;
Tsk_Node_s *final= NULL;
Tsk_Node_s *temp_tsk= NULL;


/* List operations */
int Insert(int value);
int Search(int value); 
int Delete(int value);

/* Task queue functions */
void Task_queue(int n); //generate n random tasks for the task queue
void Task_enqueue( int task_num, int task_type, int value); //insert a new task into task queue
int Task_dequeue(int* task_num_p, int* task_type_p, int* value_p); //take a task from task queue

/////////////////////////////////////////

void Task_queue(int n){

	int randomValue[n];
	int randomTaskType[n];
	int taskNumber[n];
		
	//assigning a random number to the task type and value	
	srand(time(NULL));
	for (int i = 0; i <n; ++i)
	{
		
		randomTaskType [i]=rand()%3;
		randomValue [i]=rand()%21;
		taskNumber [i]=i;
	}	

	for (int i = 0; i <n; i++){
	 Task_enqueue(taskNumber [i], randomTaskType [i],randomValue [i]); 	
	}
		
	 
	 for (int i = 0; i <n; i++){
	Task_dequeue(&taskNumber [i], &randomTaskType [i],&randomValue [i]); 	
	}		
	
}

void Task_enqueue( int task_num, int task_type, int value){
	// firstly control root , than not change root pointer 
	if (root_tsk == NULL ){
		root_tsk=(Tsk_Node_s *)malloc(sizeof(Tsk_Node_s));
		root_tsk->task_type=task_type;
		root_tsk->value=value;
		root_tsk->task_num=task_num;
		final=root_tsk;
	}
	else
	{
			
		final->next = (Tsk_Node_s *)malloc(sizeof(Tsk_Node_s));
		final->next->task_type=task_type;
		final->next->value=value;
		final->next->task_num=task_num;
		final=final->next;
		final->next=NULL;
	}	
}

int Task_dequeue(int* task_num_p, int* task_type_p, int* value_p){
	if(root_tsk == NULL)
	{	
		return -1;
	}
	
	// task type is checked
	if (*task_type_p == 0)
	{
		printf("task %d - insert %d  :",*task_num_p,*value_p);	
		Insert(*value_p);		
	
	}
	else if(*task_type_p == 1)
	{
		printf("task %d - delete %d  :",*task_num_p,*value_p);	
		Delete(*value_p);
		
	}
	else
	{
		printf("task %d - search %d  :",*task_num_p,*value_p);
		Search(*value_p);
	}
	//After making dequeue delete the task
	temp_tsk=root_tsk;
	root_tsk= root_tsk->next;
	free(temp_tsk);
	return  0;
}

int  Insert( int value){

	if (root_list == NULL) //list is empty
	{
		root_list=(Lst_Node_s *)malloc(sizeof(Lst_Node_s));
		root_list->next=NULL;
		root_list->data=value;
		printf (" %d is inserted \n" ,value);

	}
	else if(root_list->data > value )// If the value is smaller than the root	
	{  
		temp_lst=(Lst_Node_s *)malloc(sizeof(Lst_Node_s));
		temp_lst->data =value;
		temp_lst->next=root_list ;
		root_list =temp_lst;
		printf (" %d is inserted \n" ,value);

	}
	else if (root_list->data == value )// If the value is  the same  root cannot be inserted
	{
		printf (" %d cannot be inserted \n" ,value);
	}
	else
	{
		iter =root_list;
		
			while ( iter-> next !=NULL && iter->next->data <= value ){ //the value is somewhere in the middle of the list

			
				if(iter->next-> data == value ){ //i
					printf(" %d cannot be inserted \n" ,value );
				}
				iter=iter->next;
			}
			if(iter->data != value){
				temp_lst= (Lst_Node_s *)malloc(sizeof(Lst_Node_s));
				temp_lst->next =iter->next;
				iter->next=temp_lst;
				temp_lst->data =value;
	        	printf (" %d is inserted \n" ,value);
            }
	return 0;
	}
}

int Delete(int value )
{
	if(root_list == NULL) //cannot delete if the list is empty
	{ 
		printf (" %d cannot be deleted  \n" , value);		
	}
	else if(root_list->data == value)// changed root_list
	{ 
		temp_lst=root_list;
		root_list=root_list->next;
		free(temp_lst);
		
		printf (" %d deleted \n" , value);
	}
	else
	{	

		iter=root_list;

		while(iter->next != NULL && iter->next -> data != value)
		{
			iter=iter->next;
		}
		if(iter->next == NULL)
		{
			printf (" %d  cannot be deleted \n" , value);

		}
		else
		{

		temp_lst= iter->next;
		iter->next= iter->next->next;
		free(temp_lst);
		printf (" %d  deleted  \n" , value);
    		}
    }
    return 0;				
}


int Search(int value)
{		
	iter=root_list;

	while(iter != NULL) {

		if(iter->data == value )
		{
			printf( " %d is found   \n" , value);
			return 0;
		}

	iter=iter->next;
}
	printf("%d is not found  \n" , value);	
	return 0;
}

/////////////////////////

int main(int argc, char* argv[]){
   
	int number = atoi(argv[1]);

	Task_queue(number);

	printf( " Final list \n" );

	iter =root_list;
	
	while(iter!=NULL )
	{
		printf("%d " , iter->data);
		iter= iter->next;
	}

}

