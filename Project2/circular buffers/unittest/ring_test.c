/********************************************************************************************************************************
reference: https://myembeddeddiary.wordpress.com/2016/03/28/how-to-write-your-first-cunit-test-program-a-basic-example/
I refered this link instead of the one given in assignment description, since I understood this example better. 
********************************************************************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include "../inc/ring.h"
#include "../inc/diffring.h"
#include <CUnit/Basic.h>
#include <CUnit/Automated.h>
#include <CUnit/CUnit.h>
#include <time.h>
// global variables
ring_t *ptr;
ring_t *randptr;
int randomnumber;

int init_suite(void) { return 0; }
int clean_suite(void) { return 0; }
void testinsert(void);
void testremove(void);
void testentries(void);
void testnull(void);
void testrandom(void);
//Functions Definitions
void testentries(void)
{
	CU_ASSERT(1==entries(ptr));
    int x;
    x= insert(ptr , 't');
    CU_ASSERT(2==entries(ptr));
    //ptr = NULL;
	//CU_ASSERT(0==insert(ptr, 'g'));
}

void testinsert(void)
{
	
	CU_ASSERT(2==insert(ptr, 'v'));
	CU_ASSERT(2==insert(ptr, 's'));
	CU_ASSERT(2==insert(ptr, 'k'));
	CU_ASSERT(1==insert(ptr, 'q'));
	//ptr = NULL;
	//CU_ASSERT(0==insert(ptr, 'g'));
}
void testremove(void)
{
	char *h;
	
	h = (char*)malloc(10);
	CU_ASSERT(2==remove_buf(ptr, h));
	CU_ASSERT(2==remove_buf(ptr, h));
	CU_ASSERT(2==remove_buf(ptr, h));
	CU_ASSERT(1==remove_buf(ptr, h));
	//ptr = NULL;
	//CU_ASSERT(0==remove_buf(ptr, h));
	
}
void testnull(void)
{
	 char *h;
	
	 h = (char*)malloc(10);
     ptr = NULL;
     CU_ASSERT(0==insert(ptr, 'g'));
     CU_ASSERT(0==insert(ptr, 'g'));
	 CU_ASSERT(0==remove_buf(ptr, h));
}
void testrandom(void)
{
	srand(time(0));
	int i;
	randomnumber = rand()%100;
	char *h;
	
	 h = (char*)malloc(10);
	randptr = init(randomnumber);
	printf("\n\rrandomnumber : %d", randomnumber);
	for(i=0;i<(randomnumber-1);i++)
	{
		CU_ASSERT(2==insert(randptr, i));
	}
        CU_ASSERT(1==insert(randptr, i));
    for(i=0;i<(randomnumber-1);i++)
	{
		CU_ASSERT(2==remove_buf(randptr, h));
	}
        CU_ASSERT(1==remove_buf(randptr, h));
    randptr = (ring_t*)realloc(randptr, sizeof(ring_t));
    randomnumber = (rand()%100)*20;
    randptr->Length = randomnumber;
    for(i=0;i<(randomnumber-1);i++)
	{
		CU_ASSERT(2==insert(randptr, i));
	}
        CU_ASSERT(1==insert(randptr, i));
    for(i=0;i<(randomnumber-1);i++)
	{
		CU_ASSERT(2==remove_buf(randptr, h));
	}
        CU_ASSERT(1==remove_buf(randptr, h));

    //free(randptr);
}
int main()
{
	srand(time(0));
    ptr = init(4);
    

	CU_pSuite pSuite1=NULL;
	// Initialize CUnit test registry 
	if (CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();
	// Add suite1 to registry 
	pSuite1 = CU_add_suite("Basic_Test_Suite1", init_suite, clean_suite);
	if (NULL == pSuite1) 
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

// add test1 to suite1 
	if ((NULL == CU_add_test(pSuite1, "\n\n.. Testing insert function..\n\n", testinsert)))
	{
		CU_cleanup_registry();
	return CU_get_error();
	}

//add test 2 to suite1
	if ((NULL == CU_add_test(pSuite1, "\n\nTesting remove_buf function\n\n", testremove)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
//add test 3 to suite1
	if ((NULL == CU_add_test(pSuite1, "\n\nTesting entries function\n\n", testentries)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}	
//add test 4 to suite1
	if ((NULL == CU_add_test(pSuite1, "\n\nTesting for NULL pointer in all functio function\n\n", testnull)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
//add test 4 to suite1
	if ((NULL == CU_add_test(pSuite1, "\n\nRandominzed Testing\n\n", testrandom)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}	
CU_basic_run_tests();// OUTPUT to the screen

CU_cleanup_registry();//Cleaning the Registry
return CU_get_error();
}
//This is test code developed by me to check the basic functionality
/*void main()
{
ring_t *ptr;
ptr = init(13);
int x,y,z;
char *h;
printf("\n\r in main\n" );
h = (char*)malloc(10);
x= insert(ptr, 'v');
x= insert(ptr, 'a');
x= insert(ptr, 'i');
z= entries(ptr);
x= insert(ptr, 's');
x= insert(ptr, 'h');
x= insert(ptr, 'n');
x= insert(ptr, 'a');
x= insert(ptr, 'v');
x= insert(ptr, 'i');
x= insert(ptr, 's');
x= insert(ptr, 'h');
x= insert(ptr, 'r');
printf("\n\r x:%d\n",x );
y= remove_buf(ptr , h);
y= remove_buf(ptr , h);
z= entries(ptr);
x= insert(ptr, 'm');
x= insert(ptr, 'a');
y= remove_buf(ptr , h);
x= insert(ptr, 'a');
x= insert(ptr, 'i');

printf("\n\r y:%d, h:%c\n",y, *h );
z= entries(ptr);
}*/