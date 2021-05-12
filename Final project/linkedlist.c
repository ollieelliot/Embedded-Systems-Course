#include <math.h>
#include "my_library.c"


DLinkedList *allocNode(float data){
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


char insertFirst(DLinkedList **first, DLinkedList *nodeIn){
                 
  //Check for null, if there is memory available
  if(nodeIn != NULL){
      //printf("Reached start of insertFirst\n");
      DLinkedList *temp;
      temp = *first;
      
      /*
      if (isMember(first, nodeIn) == 0)
      {
          printf("A node with this address already exist");
      }
      */

      if(temp == NULL){ //If the list is empty
          nodeIn->prev = NULL; 
          nodeIn->next = NULL; 
          (*first) = nodeIn; 
      
          
      }
      
      else{ 
          nodeIn->prev = NULL; 
          nodeIn->next = (*first); 
          (*first)->prev = nodeIn; 
          (*first) = nodeIn; 
          
          //printf("Inserted %lf at start\n", nodeIn->sensorData);
      }
  }
  else{
    //printf("No memory left \n");
    return 0;
  }
  return 1;

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

            if (nodeIn == temp) 
            {
                status = 0;
                break;
            }
            else{
                status = 1;
            }
            temp = temp->next;
        }
    }
    return status; //Status = 0 if node is in list, Status = 1 if not, Status = 2 if list is empty.
}

void printList(DLinkedList **first){ //Prints the list from the beginning

    if(*first == NULL){ //If the list is empty
        printf("Nothing to print, empty list!\n");
    }
    else{
        DLinkedList *temp;
        temp = *first;

        while(temp != NULL){
          
          /*
            printf("***Printing the data in list: %lf\n", temp->sensorData);
            printf("***Minute: %d\n", temp->timeStamp.minute);
            printf("***Hour: %d\n", temp->timeStamp.hour);
            printf("***Day: %d\n", temp->timeStamp.day);
            printf("***Month: %d\n", temp->timeStamp.month);
            printf("***Year: %d\n", temp->timeStamp.year);
            printf("-------------------\n");
          */
          
            temp = temp->next;
        }
    }
}


DLinkedList *removeNode(DLinkedList **first, DLinkedList *nodeIn){
    DLinkedList *temp;
    temp = *first;
    if(isMember(first, nodeIn)==0){
        
        if (temp == nodeIn && temp->next != NULL) //If it is the first node and there exist at least one node after it
        {
            *first = (*first)->next;
            temp = NULL;
            (*first)->prev = NULL;            
        }

        if ((*first)->prev == NULL && (*first)->next==NULL){//If it is the only node in the list, reset everything
            *first = NULL;
            
        } 

        if ((*first) != NULL && nodeIn->next == NULL)//If it is the last node
                {
                    nodeIn->prev->next = NULL;           
                }

        if (temp!= NULL && nodeIn != NULL && nodeIn->next != NULL && nodeIn->prev != NULL){//If the node is not the first, last or the only node.
            while(temp != nodeIn){//Find the node we want to remove
                temp = temp->next;
                }
            
            temp->prev->next = temp->next; //The node before temp should point to the node after temp and the other way around as well, both for prev and next.
            temp->next->prev = temp->prev; 
           
            }
    }
    else{
        printf("Can't remove! Node doesn't exist or list is empty.\n");
        }
    return nodeIn;
}

/*
DLinkedList *readSensor(){

    //!= null
    double rand_Data = (double)rand()/(double)(RAND_MAX);
    
    insertFirst(&first, allocNode(rand_Data));
    //printf("Random-generated sensor data: %lf\n", rand_Data);

    return allocNode(rand_Data);
}
*/

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