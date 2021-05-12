#ifndef LINKED_LIST
#define LINKED_LIST

typedef struct DLinkedList {
    char sensorData;
    struct timestamp timeStamp;
    struct DLinkedList *prev;
    struct DLinkedList *next; 
    }DLinkedList;


char insertFirst();
DLinkedList *allocNode(float data);
void printList();
int isMember();
DLinkedList *removeNode();
DLinkedList *readSensor();
void sortAscending();
void freeMemList();

#endif