#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct DLinkedList {
    double sensorData;
    struct DLinkedList *prev;
    struct DLinkedList *next; 
    }DLinkedList;

void insertFirst();
DLinkedList *allocNode();
void printList();
int isMember();
DLinkedList *removeNode();
DLinkedList *readSensor();
void sortAscending();
void freeMemList();
DLinkedList *first = NULL; //Initilize the first node


int main(){

    //Create some nodes for testing
    DLinkedList *node1 = allocNode(2.0);
    DLinkedList *node2 = allocNode(4.0);
    DLinkedList *node3 = allocNode(-10.0);
    DLinkedList *node4 = allocNode(358.0);

    DLinkedList *node_test1 = allocNode(5.0);
    DLinkedList *node_test2 = allocNode(259.0);
    
    srand(time(0)); // Use the current time as seed to generate new seeds

    printf("Reached beginning of main\n");

    printf("------------First insertion--------------------------------\n");
    insertFirst(&first, node1);
    printf("------------More insertion(s)--------------------------------\n");
    insertFirst(&first, node2);
    insertFirst(&first, node3);
    insertFirst(&first, node4);
    
    printf("------------isMember test--------------------------------\n");
    printf("Is node %lf a member? %d \n",node_test1->sensorData, isMember(&first, node_test1));
    printf("Is node %lf a member? %d \n",node_test2->sensorData, isMember(&first, node_test2));
    printf("Is node %lf a member? %d \n",node1->sensorData, isMember(&first, node1));
    printf("Is node %lf a member? %d \n",node2->sensorData, isMember(&first, node2));
    printf("Is node %lf a member? %d \n",node3->sensorData, isMember(&first, node3));
    printf("Is node %lf a member? %d \n",node4->sensorData, isMember(&first, node4));

    printf("------------Print the current list--------------------------------\n");
    printList(&first);
    
    printf("---------------- Removing all nodes, in a different order than inserted: --------------------------------\n");
    removeNode(&first, node2);
    removeNode(&first, node3);
    removeNode(&first, node1);  
    removeNode(&first, node4); 
    
    printf("------------Removing previously removed node--------------------------------\n");
    removeNode(&first, node1);

    
    printf("------------Removing non-existing node--------------------------------\n");
    DLinkedList *test_node3 = allocNode(24.0);
    removeNode(&first, test_node3);

    
    printf("---------------- Insertion after removing all nodes: --------------------------------\n");
    insertFirst(&first, node1);
    insertFirst(&first, node3);
    
    printf("---------------- Print the list after inserting new nodes: --------------------------------\n");
    printList(&first);

    printf("---------------- Insertion and removing of the same node, nodes from previous insert are still active: --------------------------------\n");
    insertFirst(&first, node4);
    removeNode(&first, node4);

    
    printf("---------------- Print the list after removing all nodes: --------------------------------\n");
    removeNode(&first, node1);
    removeNode(&first, node3);
    printList(&first);

    
    printf("---------------- Sensor data insertion: --------------------------------\n");
    DLinkedList *data1 = readSensor();
    
    printf("---------------- Printing the pointer to the node we just inserted: --------------------------------\n");
    printf("Printing value of pointer: %lf\n", data1->sensorData);

    printf("---------------- More sensor data insertion: --------------------------------\n");
    
    DLinkedList *data2 = readSensor();
    DLinkedList *data3 = readSensor();
    DLinkedList *data4 = readSensor();
    DLinkedList *data5 = readSensor();
    DLinkedList *data6 = readSensor();

    printf("---------------- Print the list after sensor data insertion: --------------------------------\n");
    printList(&first);
    printf("The value of first node is: %lf\n", first->sensorData);
    
    printf("---------------- Print the list after ascending order: --------------------------------\n");
    sortAscending(&first);
    printList(&first);
    printf("The value of first node is: %lf\n", first->sensorData);

    printf("---------------- Free the memory: --------------------------------\n");
    freeMemList(&first);

    printf("---------------- Attempt to print the list after freeing the memory: --------------------------------\n");
   
    printList(&first);

    printf("Reached end of main\n");

}

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

void insertFirst(DLinkedList **first, DLinkedList *nodeIn){
    //Check for null
    
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
        printf("Inserted %lf at start and list was empty before\n", nodeIn->sensorData);
        
    }
    
    else{ 
        nodeIn->prev = NULL; //New node is first and will have previous point to null
        nodeIn->next = (*first); //nodeIn next points to the "old first"
        (*first)->prev = nodeIn; //the old "first previous" points to the new node
        (*first) = nodeIn; //Updates the first node to the new node
        
         printf("Inserted %lf at start\n", nodeIn->sensorData);
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
            printf("Removed %lf since it was a member and was first node\n", nodeIn->sensorData);
        }

        if ((*first)->prev == NULL && (*first)->next==NULL){//If it is the only node in the list, reset everything
            *first = NULL;
            printf("Removed %lf since it was a member and was the only node\n", nodeIn->sensorData);
        } 

        if ((*first) != NULL && nodeIn->next == NULL)//If it is the last node
                {
                    printf("Removed %lf since it was a member and was last node\n", nodeIn->sensorData);
                    nodeIn->prev->next = NULL;
                    
                }

        if (temp!= NULL && nodeIn != NULL && nodeIn->next != NULL && nodeIn->prev != NULL){//If the node is not the first, last or the only node.
            while(temp != nodeIn){//Find the node we want to remove
                //printf("Reached inside of while in removeNode\n");
                temp = temp->next;
                }
            
            temp->prev->next = temp->next; //The node before temp should point to the node after temp and the other way around as well, both for prev and next.
            temp->next->prev = temp->prev; 
            printf("Removed %lf since it was a member\n", nodeIn->sensorData);    
                    
                
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
    printf("Random-generated sensor data: %lf\n", rand_Data);

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
            printf("Reached while in freeMem\n ");
            temp = *first;
            *first = (*first)->next;
            printf("#####Freeing the node: %lf\n", temp->sensorData);
            free(temp);
        }
    }

}