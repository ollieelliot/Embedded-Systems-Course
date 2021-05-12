#ifndef DATA_REC
#define DATA_REC

extern DLinkedList *list;
extern short rec;
void recordData(float data);
void dataStats(char status);

void min(DLinkedList **first);
void max(DLinkedList **first);
void incAvg(DLinkedList **first);
void incVar(DLinkedList **first);
void init_Stats(void);
void printWeeklyStats(int i);
struct stats getWeeklyStats(int i);

struct stats{
    struct statsDate date;
    struct statsTime minTime;
    struct statsTime maxTime;
    float min;
    float max;
    float avg;
    float var;
    struct stats *prev;
    struct stats *next; 
};


#endif