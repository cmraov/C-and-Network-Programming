#include<stdio.h>
#include<stdlib.h>

struct node
{
 int data;
 struct node *next;
};

struct node *newNode(int data)
{
   struct node *temp;
   temp = (struct node*)malloc(sizeof(struct node));
   temp->data = data;
   temp->next = NULL;
   return temp;
}
void listadd(struct node **head_ref,struct node *temp)
{
   if(*head_ref == NULL)
      *head_ref = temp;
   else
     temp->next = *head_ref;
  *head_ref = temp;

}
void Display(struct node *head_ref)
{
  while(head_ref)
  {
   printf("%d->", head_ref->data);
   head_ref = head_ref->next;
  }
  printf("\n");
}


struct node *ADDLISTS(struct node *head_ref1,struct node *head_ref2,int carry,struct node *prev,struct node *header)
{
  int sum = 0;
  struct node *temp;
  if (head_ref1 == NULL && head_ref2 == NULL)
   {
     if(carry > 0)
     prev->next = newNode(carry);
     return header;
   }
  sum = carry + (head_ref1?head_ref1->data:0)+(head_ref2?head_ref2->data:0);
  carry = (sum>=10)?1:0;
  sum = sum%10;
  temp=newNode(sum);
  if(header == NULL)
     header = temp;
  else
     prev->next = temp;
     prev=temp;
  if(head_ref1!=NULL || head_ref2!=NULL)
    {
       head_ref1=head_ref1?head_ref1->next:NULL;
       head_ref2=head_ref2?head_ref2->next:NULL;
       ADDLISTS(head_ref1,head_ref2,carry,prev,header);
    }
}



main()
{
  struct node *head_ref1 = NULL;
  struct node *head_ref2 = NULL ;
  struct node *head_ref3 = NULL;
  struct node *temp;
  int data,choice,carry = 0;
  while(1)
   {
    printf("1:Add node in list 1\n");
    printf("2:Add node in list 2\n");
    printf("3.Display list 1\n");
    printf("4.Display list 2\n");
    printf("5.Add two numbers in two linked list\n");
    printf("6.Combined list\n");
    printf("Enter your Choice\n");
    scanf("%d",&choice);
    switch(choice)
     {
      case 1:
              printf("Enter the number in a linked list 1\n");
              scanf("%d",&data);
              temp = newNode(data);
              listadd(&head_ref1,temp);
              break;
      case 2:
              printf("Enter the number in a linked list 2\n");
              scanf("%d",&data);
              temp = newNode(data);
              listadd(&head_ref2,temp);
              break;
      case 3: Display(head_ref1);
              break;
      case 4: Display(head_ref2);
              break;
      case 5: head_ref3 = ADDLISTS(head_ref1,head_ref2,carry,NULL,NULL);
              Display(head_ref3);
                     break;
      case 6: Display(head_ref3);
              break;
      default:printf("invalid choice\n");
              exit(0);
     }
   }
}
  
                                                           