#include "my_library.c"

uint64_t time = 0;

char char_array[10000];
char char_array2[10000];
short fastMode = 0;
short RESET_TIME_DISPLAY = 0;

/* Days per month */
int mday[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

struct date currentDate;
struct date time_elapsed;





struct date time_to_date(void){
  
  
   /* Check for new year */ 
  if(time_elapsed.month == 12 && time_elapsed.day == mday[time_elapsed.month-1] && time_elapsed.hour == 23 && time_elapsed.minute == 59 && time_elapsed.second == 59){
    time_elapsed.day = 0;
    time_elapsed.month = 0;
    time_elapsed.year++;
    time_elapsed.month++;
    //printf("Newyear: %d \n", time_elapsed.year);
  }
  
   /* Check for new month */ 
  if(time_elapsed.day == mday[time_elapsed.month-1] && time_elapsed.hour == 23 && time_elapsed.minute == 59 && time_elapsed.second == 59){
    time_elapsed.day = 0;
    time_elapsed.month++;
    //printf("Month: %d \n", time_elapsed.month);
  }
    
  /* Check if a minute has passed */
  if(time_elapsed.second >= 59){
      time_elapsed.second = 0;
      RESET_TIME_DISPLAY = 1;
      time_elapsed.minute++;
  }
    else
      time_elapsed.second++;
  
  /* Check if an hour has passed*/
  
  if(time_elapsed.minute > 59){
    time_elapsed.minute = 0;
    //printf("New hour \n");
    time_elapsed.hour++;
  }
  
  /* Check for new day */
  
  if(time_elapsed.hour > 23){
    time_elapsed.hour = 0;
    time_elapsed.day++;
  }
  /*
  printf("Day: %d \n", time_elapsed.day);
  printf("Month: %d \n", time_elapsed.month);
  printf("Year: %d \n", time_elapsed.year);
  printf("Days of month: %d \n", mday[time_elapsed.month-1]);  
  */
  
    return time_elapsed;
}


/* Convert unsigned int to char in order to print*/
    
char *uint_to_char(uint64_t num){
    sprintf(char_array, "%llu", num);
    return char_array;
}

char *int_to_char(int num){
    sprintf(char_array2, "%d", num);
    return char_array2;
}

int string_to_int(char num[]){
    return atoi(num);
}

struct date get_date(char input[]){
    
    int date;

    date = string_to_int(input);

    time_elapsed.day = date/1000000;
    time_elapsed.month = (date/10000)%100;
    time_elapsed.year = date%10000;
    
    return time_elapsed;
    
}

struct date get_time(char input[]){
    
    int t;

    t = string_to_int(input);

    time_elapsed.second = t%100;
    time_elapsed.minute = (t/100)%100;
    time_elapsed.hour = t/10000;
    
    
    return time_elapsed;
    
}






  