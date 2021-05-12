#include "my_library.c"

char char_array[10000];
char char_array2[10000];
char char_array3[10000];


short RESET_TIME_DISPLAY = 0;

/* Days per month */
int mday[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

struct date currentDate;
struct date time_elapsed;

short currentDay = 0;
short currentMonth = 0;
short currentYear = 0;

short currentSecond = 0;
short currentMinute = 0;
short currentHour = 0;

/* Check currentDate and if valid input, store it in time_elapsed */

char validDate(void){
  
  printf("Current day: %d \n", currentDay);
  
  if(currentMonth > 12)
    return 0;
  
  if(currentDay > mday[currentMonth-1])
    return 0;
  
  else{
    time_elapsed.day = currentDay;
    time_elapsed.month = currentMonth;
    time_elapsed.year = currentYear;
  }
  
  return 1;
}

char validTime(void){
  
  if(currentHour > 24)
    return 0;
  
  if(currentMinute > 59)
    return 0;
  
  if(currentSecond > 59)
    return 0;
  
  else{
    time_elapsed.hour = currentHour;
    time_elapsed.minute = currentMinute;
    time_elapsed.second = currentSecond;
  }
  return 1;

}


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
    time_elapsed.day = 1;
    time_elapsed.month++;
    //printf("Month: %d \n", time_elapsed.month);
  }
    
  /* Check if a minute has passed */
  if(time_elapsed.second >= 59){
      RESET_TIME_DISPLAY = 1;
      recordData(get_Temperature());
      time_elapsed.second = 0;
      time_elapsed.minute++;
  }
    else
      time_elapsed.second++;
  
  /* Check if an hour has passed*/
  
  if(time_elapsed.minute > 59){
    time_elapsed.minute = 0;
    time_elapsed.hour++;
  }
  
  /* Check for new day */
  
  if(time_elapsed.hour > 23){
    time_elapsed.hour = 1;
    time_elapsed.day++;
  }
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

char *float_to_char(float num){
    sprintf(char_array3, "%f", num);
    return char_array3;
}

int string_to_int(char num[]){
    return atoi(num);
}

void set_date(char input[]){
    
    int date;
    
    date = string_to_int(input);
    
    printf("date: %d \n", date);

    currentDay = date/1000000;
    currentMonth = (date/10000)%100;
    currentYear = date%10000;
    


    
}

void set_time(char input[]){
    
    int t;

    t = string_to_int(input);

    currentSecond = t%100;
    currentMinute = (t/100)%100;
    currentHour = t/10000;

    
}

struct date get_timestamp(void){
  return time_elapsed;
}






  