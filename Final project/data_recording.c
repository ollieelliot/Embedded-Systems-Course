#include "my_library.c"

struct stats dailyStats;
struct stats weeklyStats[7];

float sumtot = 0;
int N = 0;
float s = 0;
float avg = 0;
float prevAvg = 0;
int i = 0;

void init_Stats(void){
  
  dailyStats.min = 100;
  dailyStats.max = -100;
}

void recordData(float data){
  if(rec == 1){
    char temp = insertFirst(&list, allocNode(data)); //Returns 0 if no memory, used to check status
    
    dataStats(temp);
    list->timeStamp.minute = get_timestamp().minute;
    list->timeStamp.hour = get_timestamp().hour;
    list->timeStamp.day = get_timestamp().day;
    list->timeStamp.month = get_timestamp().month;
    list->timeStamp.year = get_timestamp().year;
    
    
  }
}

void dataStats(char status){
  
  if(time_elapsed.hour == 23 && time_elapsed.minute == 59 && time_elapsed.second == 59){

    /* Calculate stats for the day*/
    
    if(i > 6)
      i = 0;
    
    
    min(&list);
    max(&list);
    incAvg(&list);
    incVar(&list);
    
    weeklyStats[i].avg = avg;
    weeklyStats[i].var = sqrt(s/N);
    weeklyStats[i].max = dailyStats.max;
    weeklyStats[i].min = dailyStats.min;
    weeklyStats[i].maxTime.minute = dailyStats.maxTime.minute;
    weeklyStats[i].maxTime.hour = dailyStats.maxTime.hour;
    weeklyStats[i].minTime.minute = dailyStats.minTime.minute;
    weeklyStats[i].minTime.hour = dailyStats.minTime.hour;
    weeklyStats[i].date.day = time_elapsed.day;
    weeklyStats[i].date.month = time_elapsed.month;
    weeklyStats[i].date.year = time_elapsed.year;
    
    N = 0;
    s = 0;
    avg = 0;
    prevAvg = 0;
    init_Stats();
    i++;
    
    
    
    freeMemList(&list);
    //printf("New day and freed memory \n");
  }

    
  if(!status){
    /* Calculate current stats*/
    
    min(&list);
    max(&list);
    incAvg(&list);
    incVar(&list);
    
    freeMemList(&list);
    //printf("Freed memory \n");
  }

  
  /*Memory is full after approx. 2 hr 48 min */
  
  
}


void min(DLinkedList **first){
  
  DLinkedList *current = *first;
  float min = 100; //Use startvalue as something very big instead of the first value given by the temperature sensor, because it is always 0, maybe needs more delay to get a better value

  while(current != NULL){
    if (current->sensorData < min && current->sensorData < 240){
      min = current->sensorData;
    }
    if (min <= dailyStats.min){
      dailyStats.min = min;
      dailyStats.minTime.minute = current->timeStamp.minute;
      dailyStats.minTime.hour = current->timeStamp.hour;
  }
  current = current->next; 
 
    
  }
}


void max(DLinkedList **first){
  
  DLinkedList *current = *first;
  float max = -100;

  while(current != NULL){
    if (current->sensorData > max && current->sensorData < 240){
      max = current->sensorData;
    }
    if (max >= dailyStats.max){
      dailyStats.max = max;
      dailyStats.maxTime.minute = current->timeStamp.minute;
      dailyStats.maxTime.hour = current->timeStamp.hour;
    }
    current = current->next; 
  }
  
  
}

/* Incremental average */

void incAvg(DLinkedList **first){
  
  DLinkedList *current = *first;

  while(current != NULL){
    if(current->sensorData < 240){
      N++;
      prevAvg = avg;
      avg += (current->sensorData - avg)/N;
    }
    current = current->next; 
  }
  
}

/* Incremental variance */

void incVar(DLinkedList **first){
  DLinkedList *current = *first;

  while(current != NULL){
    if(current->sensorData < 240)
      s+= (current->sensorData - prevAvg)*(current->sensorData - avg);
    
    current = current->next; 
  }
  
}

void printWeeklyStats(int i){
    printf("Average: %f \n", weeklyStats[i].avg);
    printf("Variance: %f \n",weeklyStats[i].var);
    printf("Max: %f \n",weeklyStats[i].max);
    printf("Min: %f \n",weeklyStats[i].min);
    printf("maxTime min: %d \n",weeklyStats[i].maxTime.minute);
    printf("maxTime hour: %d \n",weeklyStats[i].maxTime.hour);
    printf("minTime min: %d \n",weeklyStats[i].minTime.minute);
    printf("minTime hour: %d \n",weeklyStats[i].minTime.hour);
    printf("Day: %d \n",weeklyStats[i].date.day);
    printf("Month: %d \n",weeklyStats[i].date.month);
    printf("Year: %d \n",weeklyStats[i].date.year);
    
}
struct stats getWeeklyStats(int i){
  return (weeklyStats[i]);
}




  


