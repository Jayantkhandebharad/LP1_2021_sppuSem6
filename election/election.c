// Program to implement election algorithm

#include<stdio.h>
//#include<conio.h>

# define MAX 20

int list[MAX];

int num_proc,max_proc;
int coor_id;

void display()
{
 int i;
 printf("\n\n The list is as follows : \n\n");
 printf("Process : ");
 for(i=1;i<=num_proc;i++)
 {
  printf(" %2d ",i);
 }
 printf("\nALIVE   : ");
 for(i=1;i<=num_proc;i++)
 {
  printf(" %2d ",list[i]);
 }

}

void bully()
{
 int choice = 1;
 int crash,activate;
 int genid;
 int i,flag,gencoor;

 while(choice < 4)
 {
  printf("\n\n Current coordinator : %d",coor_id);
  printf("\n\n 1. Crash a process ");
  printf("\n 2. Activate a process ");
  printf("\n 3. Display");
  printf("\n 4. Exit");
  printf("\n Enter your option : ");
  scanf("%d",&choice);
  switch(choice)
  {
   case 1 :			// Some process crashes
    printf("\n\n Enter a process id to crash : ");
    scanf("%d",&crash);
    list[crash] = 0;
    if(crash == coor_id)
    {
     printf("\n Select a process id that sends a request message : ");
     scanf("%d",&genid);
     printf("\n Sending \"request\" message from P%d to P%d .",genid,coor_id);
   //  getch();
     printf("\n No reply, starting election algorithm. \n");
     while(1)
     {
      flag = 0;
      for(i=genid + 1;i<=num_proc;i++)
      {
       printf("\n Sending \"request\" message from P%d to P%d .",genid,i);
     //  getch();
       if(list[i])
       {
	flag = 1;
	gencoor = i;
       }
      }
      if(flag)
      {
       genid = gencoor;
       printf("\n\n New coordinator seleted : %d",genid);
     //  getch();
      }
      else
       break;
     }
     coor_id = genid;
     printf("\n\n After election algorithm, new coordinator : %d",coor_id);
    }
   break;

   case 2 :
    printf("\n\n Select a process to activate : ");
    scanf("%d",&activate);
    if(list[activate] != 0)
     break;
    list[activate] = 1;
    if(activate == num_proc)
    {
      printf("\n\n New coordinator selected : %d",activate);
      coor_id = activate;
    }
    else
    {
     printf("\n\n Starting election algorithm. ");
     flag = 0;
     for(i=activate + 1;i<=num_proc;i++)
     {
      printf("\n Sending \"request\" message from P%d to P%d .",activate,i);
    //  getch();
      if(list[i])
      {
       flag = 1;
       gencoor = i;
      }
     }
     if(flag)
     {
      printf("\n\n New coordinator seleted : %d",gencoor);
      coor_id = gencoor;
    //  getch();
     }
     else
     {
      printf("\n\n Activated process %d is the new coordinator. ",activate);
      coor_id = activate;
     }
    }
   break;

   case 3 :
   display();
   break;

   case 4 :
   break;

  }
 }
}

void ring()
{
 int choice = 1;
 int crash,activate;
 int genid;
 int i,flag,temp;
 int message[MAX];
 int mid = 0;
 int maxid;

 while(choice < 4)
 {
  printf("\n\n Current coordinator : %d",coor_id);
  printf("\n\n 1. Crash a process ");
  printf("\n 2. Activate a process ");
  printf("\n 3. Display");
  printf("\n 4. Exit");
  printf("\n Enter your option : ");
  scanf("%d",&choice);
  switch(choice)
  {
   case 1 :			// Some process crashes
    printf("\n\n Enter a process id to crash : ");
    scanf("%d",&crash);
    list[crash] = 0;
    if(crash == coor_id)
    {
     printf("\n Select a process id that sends a request message : ");
     scanf("%d",&genid);
     printf("\n Sending \"request\" message from P%d to P%d .",genid,coor_id);
   //  getch();
     printf("\n No reply, starting election algorithm. \n");
     mid = 1;
     message[mid] = genid;

     for(i = (genid + 1) % num_proc;i != genid;i = (i + 1) % num_proc)
     {
      if(list[i])
      {
       printf("\n Sending \"election\" message to P%d .",i);
    //   getch();
       message[++mid] = i;
      }
     }

     temp = 0;
     for(i=1;i<=mid;i++)
     {
      if(message[i] > temp)
      {
       temp = message[i];
       maxid = temp;
      }
     }
     printf("\n\n Loop completed, removing election message.");
     printf("\n\n New co-ordinator selected : %d",maxid);
     for(i = (genid + 1) % num_proc;i != genid;i = (i+1) % num_proc)
     {
      if(list[i])
      {
       printf("\n Coordinator message delivered to : %d",i);
    //   getch();
      }
     }

     coor_id = maxid;
     printf("\n\n After election algorithm, new coordinator : %d",coor_id);
    }
   break;

   case 2 :
    printf("\n\n Select a process to activate : ");
    scanf("%d",&activate);
    if(list[activate] != 0)
     break;
    list[activate] = 1;
    if(activate == num_proc)
    {
      printf("\n\n New coordinator selected : %d",activate);
      coor_id = activate;
    }
    else
    {
     printf("\n\n Starting election after recovery \n");
     for(i = (activate + 1) % num_proc;i!= activate;i = (i+1) % num_proc)
     {
      if(list[i])
      {
       printf("\n Message forwarded to : %d",i);
    //   getch();
       if(i == coor_id)
	break;
      }
     }
     printf("\n\n Sending response from coordinator (%d) to process %d",i,activate);
    }
   break;

   case 3 :
   display();
   break;

   case 4 :
   break;

  }
 }

}

int main()
{
 int i;
 int choice = 1;


 printf("\n\n Enter the number of processes : ");
 scanf("%d",&num_proc);
 for(i=1;i<=num_proc;i++)
 {
  printf("\n\n Process (%d) ",i);
  printf(" Is process active ? (0/1) : ");
  scanf("%d",&list[i]);
 }
 coor_id = num_proc;
 display();
 while(choice < 3)
 {
  printf("\n\n**************************** Choose an algorithm ****************************");
  printf("\n 1. Bully algorithm ");
  printf("\n 2. Ring algorithm ");
  printf("\n 3. Exit ");
  printf("\n\n Enter your choice : ");
  scanf("%d",&choice);
  switch(choice)
  {
   case 1 :
    bully();
    break;

   case 2 :
    ring();
    break;

   case 3 :
   break;
  }
 }
// getch();
 return 0;
}

