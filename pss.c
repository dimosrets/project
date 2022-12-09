/***************************************************************
 *
 * file: pss.h
 *
 * @Author  Nikolaos Vasilikopoulos (nvasilik@csd.uoc.gr)
 * @Version 20-10-2020
 *
 * @e-mail       hy240-list@csd.uoc.gr
 *
 * @brief   Implementation of the "pss.h" header file for the Public Subscribe System,
 * function definitions
 *
 *
 ***************************************************************
 */
#include <stdio.h>
#include <stdlib.h>

#include "pss.h"



/* Array of Groups */
struct Group *G[MG];

/* Subscribers list */
struct SubInfo *S;

/*
Bhma 1: 
    create functions:
        //mallon oxi create a list of subscribers -> SL_Create
        OK-insert in a list of subscribers -> SL_Insert
        delete from a list of  subscribers -> SL_Delete
        search in a list of subscribers -> SL_LookUp
        OK-print the list of subscribers -> SL_Print
 
struct SubInfo SL_Create(void){
    struct SubInfo *s = (struct SubInfo *)malloc(sizeof(struct SubInfo));
    return s;
}
*/
void DL_Print(struct Info* head);
/* FUNCTIONS FOR SIMPLE LINK LIST SubInfo */
void SL_Insert(struct SubInfo **head , struct SubInfo *new){
    struct SubInfo *cur;
    if ( *head == NULL || (*head)->stm >= new->stm ){
        new->snext = *head;
        *head = new;
    }
    else{
        cur = *head;
        while( cur ->snext != NULL && cur->snext->stm < new->stm){
            cur = cur->snext;
        }
        new->snext = cur->snext;
        cur->snext = new;
    }
}

int SL_LookUP(struct SubInfo **head , int t){
    struct SubInfo *cur = *head;

    while(cur != NULL){
        if ( cur->sId == t ) return 1;
        cur = cur->snext;
    }
    return 0;
}
void SL_Delete( struct SubInfo **head , int t){
    struct SubInfo *temp = *head , *prev;

    if ( temp != NULL && temp->sId == t ){
        *head = temp->snext;
        free(temp);
        return;
    }

    while( temp != NULL && temp->sId != t){
        prev = temp;
        temp = temp->snext;
    }

    if ( temp == NULL){
        return;
    }

    prev->snext = temp->snext;
    free(temp);

}
void SL_Print( struct SubInfo *head){
    struct SubInfo *tmp = head;
    while( tmp != NULL){
        printf("    SUBSCRIBER :\n");
        printf("id : %d\n",tmp->sId );
        printf("stm : %d\n",tmp->stm );
        int i;
        for ( i = 0 ; i < MG ; i++){
            if ( tmp->sgp[i] != NULL){
                printf("Pos = %d \n",i);
                DL_Print((tmp->sgp[i]));
            }
        }
        tmp = tmp->snext;
    }
}

/* FUNCTIONS FOR DOUBLE LINK LIST Info */


int DL_Insert(struct Info** head, struct Info* new)
{
    struct Info* cur;
    /*if list is empty*/
    if (*head == NULL){
      *head = new;  
        return 1;
    } /*if the new must be the first element*/
    else if ((*head)->itm >= new->itm) {
        new->inext = *head;
        new->inext->iprev = new;
        *head = new;
        return 0;
    }
    else {
        cur = *head;
 
        while (cur->inext != NULL && cur->inext->itm < new->itm)
            cur = cur->inext;
 
        /* Make the appropriate links */
        new->inext = cur->inext;
 
        if (cur->inext != NULL)
            new->inext->iprev = new;
 
        cur->inext = new;
        new->iprev = cur;
        return 1;
    }
}
int DL_LookUp(struct Info **head , int t){
    struct Info * cur = *head;
    while ( cur != NULL){
        if ( cur->iId == t ) return 1;
        cur = cur->inext;
    }
    return 0;
}
void DL_Delete(struct Info** head, int t)
{
    struct Info *temp = *head, *prev;
  
    if (temp != NULL && temp->itm == t) {
        *head = temp->inext; 
        free(temp); 
        return;
    }
  
    while (temp != NULL && temp->itm != t) {
        prev = temp;
        temp = temp->inext;
    }
  
    if (temp == NULL)
        return;
  
    prev->inext = temp->inext;
  
}

void DL_Print(struct Info* head)
{
    while (head != NULL) {
        printf("Id : %d\n",head->iId);
        printf("Itm : %d\n", head->itm);
        printf("Array: ");
        int i;
        for ( i = 0; i < MG ; i++){
            printf("%d ",head->igp[i]);
        }
        printf("\n");
        head = head->inext;
    }
}

struct Info *DL_Find_Last( struct Info *head){
    if ( head == NULL) return NULL;
    struct Info *cur = head;

    
    while ( cur->inext != NULL ) cur=cur->inext;
    
    return cur;
    
}

/* BHMA 4 SINGLE LINK LIST */
void L_Insert( struct Subscription **head , struct Subscription *new ){
    struct Subscription *cur;
    

    if ( *head == NULL){
        new->snext = *head;
        *head = new;
        return;
    }
    cur = *head;
    while ( cur->snext != NULL) cur = cur->snext;
    
    cur->snext = new;

   


}

void L_Delete( struct Subscription **head , int id ){
    struct Subscription *temp = *head , *prev;

    if ( temp != NULL && temp->sId == id ){
        *head = temp->snext;
        free(temp);
        return;
    }

    while( temp != NULL && temp->sId != id){
        prev = temp;
        temp = temp->snext;
    }

    if ( temp == NULL){
        return;
    }

    prev->snext = temp->snext;
    free(temp);
}

void L_Print( struct Subscription *head){
    struct Subscription *cur = head;

    while ( cur!= NULL){
        printf("%d ",cur->sId);
        cur = cur->snext;
    }
}

int L_LookUp(struct Subscription **head , int id){
    struct Subscription *cur = *head;

    while(cur != NULL){
        if ( cur->sId == id ) return 1;
        cur = cur->snext;
    }
    return 0;
}

/**
 * @brief Optional function to initialize itm structures that
 *        need initialization
 *
 * @return 0 on success
 *         1 on failure
 */

int initialize(void){
    int i;
    
    for ( i = 0 ; i < MG ; i++){
        G[i] = (struct Group *) malloc(sizeof(struct Group));
        G[i]->gId = i;
        G[i]->ggsub = NULL;
        G[i]->gfirst = NULL;
        G[i]->glast = NULL;    
    }

    S = NULL;

    return EXIT_SUCCESS;
}

/**
 * @brief Free resources
 *
 * @return 0 on success
 *         1 on failure
 */
int free_all(void){
    return EXIT_SUCCESS;
}
void Insert_In_Group_An_Info(int pos , struct Info *el){
    
    DL_Insert(&(G[pos]->gfirst), el);
/*
    if (DL_Insert(&(G[pos]->gfirst), el) == 1 ){
        G[pos]->glast = el;    
    }
*/
    /* I NEED TO FIND THE LAST ELEMENT */
    G[pos]->glast = DL_Find_Last(G[pos]->gfirst);
    /*
    printf("CHECK THE LAST ");
    DL_Print(G[pos]->glast);
    printf("\n");
    */
}
void Print_Subs(){
    SL_Print(S);
}
void Group_Print(){
    int i;
    printf("##########################\n");
    printf("######PRINTS GROUPS#######\n");
    printf("##########################\n");

    for ( i = 0 ; i < MG ; i++){
        printf("\n\n##########################\n");
        printf("Group id: %d\n",G[i]->gId);
        printf("    Info: \n");
        DL_Print(G[i]->gfirst);
        printf("    Last element\n");
        DL_Print(G[i]->glast);
        printf("\n  Subscribers: \n");
        L_Print(G[i]->ggsub);
    }
}
void DL_Print_iID( struct Info *h ){
        printf("<");
    
    while( h!= NULL){
        printf("%d, ",h->iId);
        h = h->inext;
    }
    printf(">");
    /*
    printf("\n");
    */

}

/**
 * @brief Insert info
 *
 * @param iTM Timestamp of arrival
 * @param iId Identifier of information
 * @param gids_arr Pointer to array containing the gids of the Event.
 * @param size_of_gids_arr Size of gids_arr including -1
 * @return 0 on success
 *          1 on failure
 */
int Insert_Info(int iTM,int iId,int* gids_arr,int size_of_gids_arr){
    int c_g,c_arr,j;

    for ( j = 0 ; j < MG; j++){
        if ( DL_LookUp(&G[j]->gfirst, iId ) == 1 ) return EXIT_FAILURE;
    }
    for ( c_arr = 0 ; c_arr < size_of_gids_arr-1 ; c_arr++){
        /*printf("%d\n", c_arr);*/
        /*
        elenxeis G[gid_arr[c_arr]]->gfirst == NULL77 :
                tmp = G[gid_arr[c_arr]]->gfirst
                G->ggsub->sgp[gid_arr[c_arr]] != tmp : ubdate;
                int boolean;
                G[gid_arr[c_arr]]->gfirst == NULL :
                    boolean = 1;
                else :
                    boolean = 0
        */
        int check;
        if (G[gids_arr[c_arr]]->gfirst == NULL ){
                check = 1;
            /*            
            if ( G->ggsub->sgp[gid_arr[c_arr]] !=G[gid_arr[c_arr]]->gfirst ){
            }
            else{
                check = 0;
            }
            */
        }
        struct Info *new;
        new = (struct Info *) malloc(sizeof(struct Info));
        new->iId = iId;
        new->itm = iTM;
        
        for ( j = 0 ; j < MG ; j++){
            new->igp[j] = 0;
        }
        
        for ( j = 0; j < size_of_gids_arr-1 ; j ++){
            /*if j < MG else break; */
            if ( gids_arr[j] < 0 || gids_arr[j] > 63 ) return EXIT_FAILURE;
        
            new->igp[gids_arr[j]] = 1;
        }

        new->iprev = NULL;
        new->inext = NULL;
        
        Insert_In_Group_An_Info(gids_arr[c_arr], new );
        /*
        na vriskoume pios malakas einai sybscriber sto group poy valame pliroforia
        kai na tin allazoume 
        an boolean == 1: 
            S->sgp[gids_arr[c_arr]] = gfirst
        */
        if ( check == 1){
            struct Subscription *sub = G[gids_arr[c_arr]]->ggsub;
            while ( sub != NULL){
                struct SubInfo *cur = S;
                while ( cur->sId != sub->sId) {
                    cur = cur->snext;
                }
                cur->sgp[gids_arr[c_arr]] = G[gids_arr[c_arr]]-> gfirst;
                sub = sub->snext;
            }
        }
        
    }

    for ( j = 0 ; j< size_of_gids_arr-1 ; j++){
        /*i should make a sort function for an array */
        printf("\tGROUPID = <%d>,INFOLIST = ",gids_arr[j]);
        DL_Print_iID(G[gids_arr[j]]->gfirst);
        printf("\n");
    }
    
    return EXIT_SUCCESS;
}

void Print_SubInfo_Id(struct SubInfo *s){
    while ( s != NULL){
        printf("%d ",s->sId);
        s= s->snext;
    }
}

void Print_Group_Subs_Id(){
    int i;
    for ( i = 0 ;i<MG ; i++){
        printf("\nGROUPID = <%d>, SUBLIST = ",G[i]->gId);
        printf("<");
        L_Print(G[i]->ggsub);
        printf(">");
    }
    printf("\n");
}

/**
 * @brief Subsriber Registration
 *
 * @param sTM Timestamp of arrival
 * @param sId Identifier of subscriber
 * @param gids_arr Pointer to array containing the gids of the Event.
 * @param size_of_gids_arr Size of gids_arr including -1
 * @return 0 on success
 *          1 on failure
 */
int Subscriber_Registration(int sTM,int sId,int* gids_arr,int size_of_gids_arr){

    int i;
    for (i = 0 ; i < MG ; i++){
        if ( L_LookUp( &G[i]->ggsub , sId) == 1){
            return EXIT_FAILURE;
        }
    }

    struct SubInfo *new;
    new = (struct SubInfo *) malloc(sizeof(struct SubInfo));
    new->sId = sId;
    new->stm = sTM;

    
    for ( i = 0 ; i< MG ;i++){
        new->sgp[i]= (struct Info *) 1;
    }

    for ( i = 0 ; i< size_of_gids_arr-1 ; i++){
        if ( gids_arr[i] < 0 || gids_arr[i] > 63 ) return EXIT_FAILURE;

        new->sgp[gids_arr[i]] =  G[ gids_arr[i]]->gfirst;/*G[ gids_arr[i]]->gfirst;*/
    }
    new->snext = NULL;
    /*for ( i = 0 ; i < MG; i++) DL_Print(new->sgp[i]);*/
    /*printf("Created SubInfo\n");   printf("Insert SubInfo\n");*/
    SL_Insert(&S , new);

    for ( i = 0 ; i< size_of_gids_arr-1 ; i++){
        /*printf("Create %d Subscription\n",i);*/
        struct Subscription *n = (struct Subscription*) malloc(sizeof(struct Subscription));
        n->sId = sId;
        n->snext = NULL;
        if ( L_LookUp(&G[gids_arr[i]]->ggsub , sId)){
            continue;
        }
        L_Insert(&G[gids_arr[i]]->ggsub , n );
    } 

    /*
    print for S event
    */
    printf("SUBSCRIBERLIST = ");
    printf("<");
    Print_SubInfo_Id(S);
    printf(">");
    printf("\n");
    for ( i = 0 ; i < size_of_gids_arr-1 ; i++){
        printf("\n\tGROUPID = <%d>, SUBLIST = ",G[gids_arr[i]]->gId);
        printf("<");
        L_Print(G[gids_arr[i]]->ggsub);
        printf(">");
    }
    printf("\n");
 
    /*
    Print_Group_Subs_Id();
*/
    return EXIT_SUCCESS;
}
/**
 * @brief Consume Information for subscriber
 *
 * @param sId Subscriber identifier
 * @return 0 on success
 *          1 on failure
 */
int Consume(int sId){
    int i;

    if ( SL_LookUP(&S , sId ) == 0) return EXIT_FAILURE;
    struct SubInfo *cur = S;

    while ( cur->sId != sId ) cur = cur->snext;
    /*
    SL_Print(cur);
    sostos sub
    */

/*
    for (i = 0 ; i < MG ; i++){
        /*DL_Print(cur->sgp[i] );
        if ( cur->sgp[i] != (struct Info *)1){
            
            /*DL_Print_iID(cur->sgp[i]); printf("\n");*/
            
            /*DL_Print_iID(cur->sgp[i]);
        }
    }
    */

    for ( i = 0 ; i < MG ; i++){
    if ( cur->sgp[i] == NULL || cur->sgp[i] == (struct Info *)1 ){
        if ( L_LookUp( &G[i]->ggsub , sId) == 1 ){
            printf("GROUPID = <%d>, INFOLIST = <> , NEWSGP = <>\n",i);
        }


    }
    else{
        if ( L_LookUp( &G[i]->ggsub , sId) == 1 ){
            printf("GROUPID = <%d>, INFOLIST = ",i);
            
         
            
                DL_Print_iID(cur->sgp[i]);
                cur->sgp[i] = G[i]->glast;

            
            
                printf(", NEWSGP = <%d>\n",cur->sgp[i]->iId);
        }
        else{
                printf("\n");  
            }        
            
        }
    }
        
        
    printf("\n");
    return EXIT_SUCCESS;
}
/**
 * @brief Delete subscriber
 *
 * @param sId Subscriber identifier
 * @return 0 on success
 *          1 on failure
 */
int Delete_Subscriber(int sId){
    /*Delete from the SubsList*/
    SL_Delete(&S , sId);
    int i;
    for (i = 0 ; i < MG ; i++){
        if ( L_LookUp(&G[i]->ggsub , sId) == 1 ){
            L_Delete(&G[i]->ggsub , sId);
        }
    }
    printf("SUBSCRIBERLIST = ");
    printf("<");
    Print_SubInfo_Id(S);
    printf(">");
    printf("\n");
    for( i = 0 ; i < MG ; i++){
        printf("GROUPID = <%d> ",G[i]->gId);
        printf(", SUBLIST = < ");
        L_Print(G[i]->ggsub);
        printf(">");
        printf("\n");
    }
    return EXIT_SUCCESS;
}

int NumberOfSubs( struct SubInfo *s){
    int count = 0;
    while (s!= NULL){
        count++;
        s = s->snext;
    }

    return count;
}

int NumberOfGroups(){
    int i,count;
    for (i = 0 ; i < MG ; i++){
        if ( !(G[i]->ggsub == NULL && G[i]->gfirst == NULL)){
                count++;
        }
    }
    return count;
}

void Print_Subscribers_Id( struct Subscription *s){
    while ( s != NULL){
        printf("%d ",s->sId);
        s = s->snext;
    }
    
}

void WhichGroups( struct SubInfo *s){
    int i;
    for ( i = 0 ; i < MG ; i++){
        if ( s->sgp[i] != (struct Info *) 1){
            printf("%d ",i);
        }
    }
}
/**
 * @brief Print itm Structures of the system
 *
 * @return 0 on success
 *          1 on failure
 */
int Print_all(void){
    /*GROUPID = {}, INFOLIST = iId1 , iId2 .., SUBLIST = iId1 , iId2...  */
    int i;
    for( i = 0 ; i < MG ; i++){
        printf("GROUPID = <%d>, INFOLIST = ",G[i]->gId);
        DL_Print_iID(G[i]->gfirst);
        printf(" SUBLIST = <");
        L_Print(G[i]->ggsub);
        printf(">\n");


    }
    /*SUBSCRIBERLIST = sId1... */
    printf("SUBSCRIBERLIST = <");
    Print_SubInfo_Id(S);
    printf(">\n");
    /*SUBSCRIBERID = sId1 , GROUPLIST = gId1,gId2... */
    /*...*/
    /*SUBSCRIBERID = sId1 , GROUPLIST = gId1,gId2... */
    struct SubInfo *tmp = S;
    while ( tmp != NULL){
        printf("SUBSCRIBERID = <%d> , GROUPLIST = <",tmp->sId);
        WhichGroups(tmp);
        printf(">\n");
        tmp = tmp->snext;    
    }
    printf("\n");
    /*NO_GROUPS = <.> NO_SUBSCRIBERS = <.> */
    printf("NO_GROUPS = <63>, NO_SUBSCRIBERS = <%d>\n",NumberOfSubs(S));
    /*,NumberOfGroups()*/
    return EXIT_SUCCESS;
}
