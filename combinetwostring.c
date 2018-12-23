#include<stdio.h>
#include<stdlib.h>
#include<string.h>
main()
{
  char str1[] = "abcd";
  char str2[] = "efghijk";
  char str3[100];
  int i = 0,j=0;
  while(str1[i]!='\0' || str2[i] !='\0')
   {
     if(str1[i]!='\0' && str2[i] !='\0')
       {
        str3[j] =str1[i];
        str3[++j] = str2[i];
       }
      if(str1[i]!='\0' && str2[i] =='\0')
        str3[j] =str1[i];
      else
        str3[j] =str2[i];
    i++;
    j++;
   }
  printf("Combined string is %s\n",str3);
}
