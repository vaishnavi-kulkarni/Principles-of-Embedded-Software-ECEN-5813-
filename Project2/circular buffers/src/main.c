#include <stdlib.h>
#include <stdio.h>
#include "../inc/ring.h"
#include "../inc/main.h"


void main()
{
	removed_data = (char *)malloc(20);

	while(1)
	{	
	break_var = 1;
	breakflag =1;
	printf("\n\r Enter 1.initiliazation 2.Insert 3.Remove 4.Entries 5.Resize 6.Quit\n\r" );
	scanf("%d", &switch_var);
	switch(switch_var)
	{
		case 1:
		//Init
		printf("\n\r Enter number of circular buffers you want to create(betwen 0 to 100)\n\r" );
    	scanf("%d", &max);
		while(break_var!=0&&breakflag!=0)
		{
			printf("\n\rEnter the buffer number(0 to %d) to initilize that buffer\n\r", max);
			scanf("%d", &i);
			printf("\n\rPlease enter size of the %dth  buffer\n\r", i);
			scanf("%d", &buff_size);
			ptr[i] = init(buff_size);
			if(ptr[i]==NULL)
				breakflag=0;
			printf("\n\rPlease enter 0 if you want to end the initiliazation process or 1 to continue\n\r");
			scanf("%d",&break_var);
		}
		break_var = 1;
		breakflag=1;
		break;
		case 2:
		//For insert operation
		while(break_var!=0&&breakflag!=0)
		{
	    	printf("\n\rPlease enter buffer number (0 to %d) in which you want to insert data \n\r", max);
			scanf("%d",&buff_num);	
			printf("\n\rPlease enter data\n\r");
			scanf("%c", &data);
			if(data == '\n')
				scanf("%c", &data);

			x = insert(ptr[buff_num], data);
			if(x!=2)
				breakflag=0;
			printf("\n\rPlease enter 0 if you want to end the insertion process or 1 to continue\n\r");
			scanf("%d",&break_var);

		}
	    break_var=1;
	    breakflag=1;
		break;
		case 3: 
		//For remove operation
		while(break_var!=0&&breakflag!=0)
		{
		    printf("\n\rPlease enter the the buffer number (0 to %d) from which you want to remove data \n\r", max);
			scanf("%d",&buff_num);
            x = remove_buf(ptr[buff_num],removed_data);
            	if(x!=2)
				breakflag=0;
			printf("\n\rPlease enter 0 if you want to end the removal process or 1 to continue\n\r");
			scanf("%d",&break_var);

		}
    	break_var=1;
    	breakflag=1;
		break;
		case 4:
		while(break_var!=0&&breakflag!=0)
		{
		    printf("\n\rPlease enter the the buffer number (0 to %d) for which you wish to know the number of elements present inside the buffer \n\r", max);
			scanf("%d",&buff_num);
            x = entries(ptr[buff_num]);
           
            if (x==1)
            	printf("\n\rBuffer is empty\n\r");
             if(x!=2)
				breakflag=0;
			printf("\n\rPlease enter 0 if you want to end the this process or 1 to continue\n\r");
			scanf("%d",&break_var);

		}
		break_var =1;
		breakflag=1;
		break;
		case 5:
		//Resizing
		while(break_var!=0)
		{
		    printf("\n\rPlease enter the the buffer number (0 to %d) which you want to resize \n\r", max);
			scanf("%d",&buff_num);
			printf("\n\r Enter length\n\r");
			scanf("%d", &l);
			ptr[buff_num] = realloc(ptr[buff_num], sizeof(ring_t));
			ptr[buff_num]->Length = l;
			printf("\n\rPlease enter 0 if you want to end the this process or 1 to continue\n\r");
			scanf("%d",&break_var);

		}
		break_var =1;	
		break;
		case 6:
		exit(0);
		break;
	}
	}

}