#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<pthread.h>
struct node
{
  int data;
  struct node *next;
};
void fill_list(int *);
void empty_list(int *);
//void show_list();
void delete(struct node *,int *value);
pthread_mutex_t list_mutex;
struct node *head = NULL;

unsigned int threads_fill_done;
sem_t done_filling_list;
sem_t filling_list;
main()
{
  int i;
  pthread_mutex_init(&list_mutex,NULL);
  int res = sem_init(&done_filling_list,0,0);
  if (res < 0)
   {
      perror("Semaphore initialization failed");
      exit(0);
   }
   sem_init(&filling_list,0,1);
   threads_fill_done = 0;

   pthread_t threads[11];
   int params[5] = {0,1,2,3,4};

   for (i=0; i<5; i++)
    {
     pthread_create(&threads[i],NULL,(void *)fill_list,(void*)&params[i]);
    }
   for (i=5;i<10;i++)
    {
     pthread_create(&threads[i],NULL,(void *)empty_list,(void*)&params[i-5]);
    }
 for (i=5;i<10;i++)
     pthread_join(threads[i],NULL);

    pthread_mutex_destroy(&list_mutex);
    sem_destroy(&filling_list);
    sem_destroy(&done_filling_list);
    printf("All threads completed.List:\n");
}
void insert(struct node *head,int value)
{
  struct node *temp;
  struct node *q;
  q = head;
  temp = (struct node*)malloc(sizeof(struct node));
  temp->data = value;
  temp->next = NULL;
  if(head == NULL)
    head = temp;
 else
   {
    for(;q->next;q++);
     q->next = temp;
   }
}

void fill_list(int *value)
{
  int i;
  pthread_mutex_lock(&list_mutex);
  printf("Thread is inserting number %d in list\n",*value);
  insert(head,*value);
   pthread_mutex_unlock(&list_mutex);

  sem_wait(&filling_list);
  if (threads_fill_done == 4)
  {
    printf("Filling done\n");
    for(i=0;i<5;i++)
    sem_post(&done_filling_list);
  }
  else
  {
   threads_fill_done++;
   sem_post(&filling_list);
  }

}

void delete(struct node *head,int *value)
{
 struct node *temp,*prev;
 if(head == NULL)
   return;
 for(prev=head;prev->next->data!=*value;prev=prev->next);
   temp=prev->next;
    prev->next= temp->next;
  free(temp);
}

void empty_list(int *value)
{
 printf("Thread is waiting for semaphore to be released\n");
 sem_wait(&done_filling_list);
 pthread_mutex_lock(&list_mutex);
 printf("Thread is removing number %d from list\n",*value);
 delete(head,*value);
 pthread_mutex_unlock(&list_mutex);
}
                                                                                 
