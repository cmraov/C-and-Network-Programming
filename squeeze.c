#include<stdio.h>
#include<stdlib.h>
main()
{
  int i,j=0;
 /* char a[20];*/
    char a[20] = "hello world";
// printf("Enter a string\n");
// gets(a);
  for (i=j=0;a[i]!='\0';i++)
  {
     if(a[i]!='o')
        a[j++]=a[i];
  }
  a[j]='\0';
  printf ("sqeeze string = %s\n",a);
}
~
