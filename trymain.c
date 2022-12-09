#include "pss.h"
#include <stdlib.h>
#include <stdio.h>

struct Info* Init_an_Info(int t,int id,int *gids_arr,int size_of_gids_arr){
    
    struct Info* mpla= (struct Info*) calloc(sizeof(struct Info));
    
    mpla->iId = id;
    mpla->itm = t;
    int j;
    
    for ( j = 0; j < size_of_gids_arr ; j ++){
        /*if j < MG else break; */
        
        mpla->igp[j] = gids_arr[j];
    }
    
    mpla->iprev = NULL;
    mpla->inext = NULL;
    return mpla;
}

struct Subscription *Give( int i ){
    struct Subscription *new = (struct Subscription *) malloc(sizeof(struct Subscription));

    new->sId =  i;
    new->snext = NULL;

    return new; 
}
int main(){
	
	/*
	initialize(); 
		TEST for Single Link List Functions

	struct SubInfo *head;
	head = NULL;

	struct SubInfo *n;
	n = (struct SubInfo *)malloc(sizeof(struct SubInfo));
	n->sId = 4;
	n->stm = 7;
	n->snext = NULL;
	SL_Insert(&head , n);

	struct SubInfo  *b;
	b = (struct SubInfo *)malloc(sizeof(struct SubInfo));
	b->sId = 5;
	b->stm = 15;
	b->snext = NULL;
	
	struct SubInfo *d;
	d = (struct SubInfo *)malloc(sizeof(struct SubInfo));
	d->sId = 7;
	d->stm = 5;
	d->snext = NULL;
	
	struct SubInfo *g;
	g = (struct SubInfo *)malloc(sizeof(struct SubInfo));
	g->sId = 9;
	g->stm = 16;
	g->snext = NULL;
	
	SL_Insert(&head , g);
	SL_Insert(&head , b);
	SL_Insert(&head , d);
	SL_Print(head);

	printf("**********");
	SL_Delete(&head , 5);
	SL_Print(head);
	printf("**********");
	SL_Delete(&head , 16);
	SL_Print(head);
	printf("**********");
	SL_Delete(&head , 7);
	SL_Print(head);
	printf("**********");

	SL_Delete(&head , 5);
	SL_Print(head);
	printf("**********");

	
*/

	/*	TEST fos Double Linked List Functions 
	struct Info *head, *f1;

	struct Info *AlexGamiesai[5];
	int i;
	for (i= 0 ; i < 5 ; i++) AlexGamiesai[i] = NULL;
	
	int ar[5] = {1,2,3,45,4};

	for ( i = 0 ; i < 5; i++){
		f1 = Init_an_Info( i*3*2*5 , 1071 , ar , 5);
		DL_Insert(&AlexGamiesai[i],f1);
		f1 = Init_an_Info( i*3*2 , 1071 , ar , 5);
		DL_Insert(&AlexGamiesai[i],f1);
		f1 = Init_an_Info( i*3 , 1071 , ar , 5);
		DL_Insert(&AlexGamiesai[i],f1);
	}
	for ( i = 0 ; i< 5 ; i++){
	printf("Alex tou %d\n",i);
	DL_Print(AlexGamiesai[i]);
	printf("\n");

	}		
*/
	struct Info *head, *f1;

	f1 = (struct Info *) malloc(sizeof(struct Info));
	f1 -> itm = 7;
	f1->iId = 1054;

	int ar[5] = {1,2,3,45,4};
	int i;
	while ( i < 5 ){
		f1->igp[i] = ar[i];
		i++;
	}

	f1 -> iprev = NULL;
	f1 -> inext = NULL;


	head = NULL;

	/*int a[5] ={6,7,4,3,2} ;
	*ar = 5;
	printf("%d",*ar);

	int i = 0;
	while ( i < 5 ){
		printf("%d",*ar);
		i++;
		ar++;
	}
	*/
	f1 = Init_an_Info( 7 , 1051 , ar , 5);

	

	DL_Insert(&head,f1);
	DL_Print(head);

	struct Info *f2 = Init_an_Info( 17 , 1071 , ar , 5);
	DL_Insert(&head,f2);

	struct Info *f3 = Init_an_Info( 5 , 1031 , ar , 5);

	DL_Insert(&head,f3);

	DL_Print(head);

	printf("*********\n");

	DL_Delete( &head , 10 );
	DL_Print(head);
	printf("*********\n");

	DL_Delete(&head , 7);
	DL_Print(head);	
	printf("%d" , DL_LookUp(&head , 7));



	/* TEST FOR SINGLE LINKED LIST NOT SORTED 

	struct Subscription *head = NULL;
	struct Subscription *f;
	f = Give(1);
	L_Insert(&head , f);
	L_Print(head);
	printf("\n");
	f = Give(5);
	L_Insert(&head , f);
	L_Print(head);
	printf("\n");
	
	f = Give(7);
	L_Insert(&head , f);
	L_Print(head);
	printf("\n");
	
	f = Give(8);
	L_Insert(&head , f);

	L_Print(head);
	printf("\n");

	L_Delete(&head , 5 );
	L_Print(head);
	printf("\n");

	L_Delete(&head , 1 );
	L_Print(head);
	printf("\n");

	L_Delete(&head , 8 );
	L_Print(head);
	printf("\n");
	
	L_Delete(&head , 7 );
	L_Print(head);
	printf("\n");

	printf("%d",L_LookUp(&head , 8));

	*/

	initialize();
	Group_Print();
	return 0;
}