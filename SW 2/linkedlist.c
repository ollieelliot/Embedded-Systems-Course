#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "my_library.c"

typedef struct DLinkedList {
    double sensorData;
    struct date timeStamp;
    struct DLinkedList *prev;
    struct DLinkedList *next; 
    }DLinkedList;


DLinkedList *first = NULL; //Initilize the list


DLinkedList *allocNode(double data){
    DLinkedList *temp;
    temp = (DLinkedList*)malloc(sizeof(DLinkedList)); //Allocate memory for the node
    
    //printf("Input data: %lf\n", data);
    if (temp != NULL) //If there is memory available
    {
        //printf("Reached if in allocNode\n");
        temp->sensorData = data; //Temp points to sensordata and sets the sensordata to data.
        //printf("The data in allocNode: %lf\n", temp->sensorData);
    }
    //printf("Reached end of allocNode\n");
    return temp;
    
}

void insertFirst(DLinkedList **first, DLinkedList *nodeIn
                 
  //Check for null
  if(*nodeIn != NULL){
      //printf("Reached start of insertFirst\n");
      DLinkedList *temp;
      temp = *first;
      
      if (isMember(first, nodeIn) == 0)
      {
          printf("A node with this address already exist");
      }

      if(temp == NULL){ //If the list is empty
          nodeIn->prev = NULL; //Point the new node prev to NULL
          nodeIn->next = NULL; //Point the new node next to NULL
          (*first) = nodeIn; // Point first to the new node.
      
          //printf("Reached if in insertFirst\n");
          //printf("Inserted %lf at start and list was empty before\n", nodeIn->sensorData);
          
      }
      
      else{ 
          nodeIn->prev = NULL; //New node is first and will have previous point to null
          nodeIn->next = (*first); //nodeIn next points to the "old first"
          (*first)->prev = nodeIn; //the old "first previous" points to the new node
          (*first) = nodeIn; //Updates the first node to the new node
          
           //printf("Inserted %lf at start\n", nodeIn->sensorData);
      }
  }

}

int isMember(DLinkedList **first, DLinkedList *nodeIn){
    int status = 1;
    if(*first == NULL){ //If the list is empty
        printf("List is empty! Can't use isMember\n");
        
    }
    else{
        DLinkedList *temp;
        temp = *first;
        while (temp != NULL){
            //printf("Iterating through while in isMember, temp: %lf\n", temp->sensorData);
            //printf("nodeIn: %lf\n", nodeIn->sensorData);
            if (nodeIn == temp) //Check if 
            {
                //printf("Pointer address of nodeIn: %p, pointer address of current: %p\n", nodeIn, temp);
                //printf("Reached if in isMember, status = 0\n");
                status = 0;
                break;
            }
            else{
                //printf("Reached else in isMember, status = 1\n");
                //printf("Pointer address of duplicate nodeIn: %p, pointer address of current: %p\n", nodeIn, temp);
                status = 1;
            }
            temp = temp->next;
        }
    }
    //printf("Status: %d\n", status);
    return status; //Status = 0 if node is in list, Status = 1 if not, Status = 2 if list is empty.
}

void printList(DLinkedList **first){ //Prints the list from the beginning

    if(*first == NULL){ //If the list is empty
        printf("Nothing to print, empty list!\n");
    }
    else{
        //printf("Reached else in printList\n");
        DLinkedList *temp;
        temp = *first;

        while(temp != NULL){
            //printf("Should print temp\n");
            printf("***Printing the data in list: %lf\n", temp->sensorData);
            temp = temp->next;
        }
    }
}

DLinkedList *removeNode(DLinkedList **first, DLinkedList *nodeIn){
    //printf("Reached start of removeNode\n");
    DLinkedList *temp;
    temp = *first;
    if(isMember(first, nodeIn)==0){
        //printf("Reached inside of if in removeNode\n");
        
        if (temp == nodeIn && temp->next != NULL) //If it is the first node and there exist at least one node after it
        {
            *first = (*first)->next;
            temp = NULL;
            (*first)->prev = NULL;
            //printf("Removed %lf since it was a member and was first node\n", nodeIn->sensorData);
        }

        if ((*first)->prev == NULL && (*first)->next==NULL){//If it is the only node in the list, reset everything
            *first = NULL;
            //printf("Removed %lf since it was a member and was the only node\n", nodeIn->sensorData);
        } 

        if ((*first) != NULL && nodeIn->next == NULL)//If it is the last node
                {
                    //printf("Removed %lf since it was a member and was last node\n", nodeIn->sensorData);
                    nodeIn->prev->next = NULL;
                    
                }

        if (temp!= NULL && nodeIn != NULL && nodeIn->next != NULL && nodeIn->prev != NULL){//If the node is not the first, last or the only node.
            while(temp != nodeIn){//Find the node we want to remove
                //printf("Reached inside of while in removeNode\n");
                temp = temp->next;
                }
            
            temp->prev->next = temp->next; //The node before temp should point to the node after temp and the other way around as well, both for prev and next.
            temp->next->prev = temp->prev; 
            //printf("Removed %lf since it was a member\n", nodeIn->sensorData);    
                    
                
            }
        //printf("Reached end of if in removeNode\n");
    }
    else{
        printf("Can't remove! Node doesn't exist or list is empty.\n");
        }
    return nodeIn;
}

DLinkedList *readSensor(){

    //!= null
    double rand_Data = (double)rand()/(double)(RAND_MAX);
    
    insertFirst(&first, allocNode(rand_Data));
    //printf("Random-generated sensor data: %lf\n", rand_Data);

    return allocNode(rand_Data);
}

void sortAscending(DLinkedList **first){
    DLinkedList *current, *index;
    current = *first;
    double temp;

    if(*first == NULL){ //If the list is empty
        printf("Nothing to sort.\n");   
    }
    else{
        while (current != NULL)
        {
            index = current->next;
            while (index != NULL){
                //printf("Inside while in sortAscending\n");

                //Swap nodes, not data
                if(current->sensorData > index->sensorData){ //If the current data is bigger than the next data, switch places
                    //printf("Current max sensordata: %lf and next sensordata: %lf\n", current->sensorData, current->next->sensorData);
                    temp = current->sensorData; //Store the current data in temp
                    current->sensorData = index->sensorData; //Store the next data into the current data, simply swapping the values.
                    index->sensorData = temp; //Store the current data in the next data, simply swapping the values.
                }
                index = index->next;
            }
            current = current->next;
        }
    }
    //printf("Reached end of sortAscending\n");
}

void freeMemList(DLinkedList **first){//Frees every node in the current list, won't delete nodes that arent connected to the list.
    if(*first == NULL){ //If the list is empty
        printf("Nothing to free, empty list!\n");
    }
    else{
       
        DLinkedList *temp;
        
        while(*first != NULL){
            //printf("Reached while in freeMem\n ");
            temp = *first;
            *first = (*first)->next;
            //printf("#####Freeing the node: %lf\n", temp->sensorData);
            free(temp);
        }
    }

}