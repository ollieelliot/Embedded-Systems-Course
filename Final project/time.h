#ifndef TIME
#define TIME


extern char char_seconds[2];
extern int fastMode;
extern struct date time_elapsed;
extern short RESET_TIME_DISPLAY;


struct date{
  short second: 6;    /* Seconds: 0-59 */
  short minute: 6;    /* Minutes: 0-59 */
  short hour: 5;      /* Hours: 0-23 (24-hour clock system) */
  short day: 5;       /* The day of the month: 1-31 (Depending on leapyear) */
  short month: 4;     /* Month: 0-11 */
  short year: 11;      /* Years since date assigned by user */
};

struct timestamp{
  short minute: 6;    /* Minutes: 0-59 */
  short hour: 5;      /* Hours: 0-23 (24-hour clock system) */
  short day: 5;       /* The day of the month: 1-31 (Depending on leapyear) */
  short month: 4;     /* Month: 0-11 */
  short year: 11;      /* Years since date assigned by user */
};

struct statsDate{   
  short day: 5;       
  short month: 4;     
  short year: 11;
};

struct statsTime{   
  short minute: 6;
  short hour: 5; 
};

char *uint_to_char(uint64_t tick);
struct date time_to_date(void);
char *int_to_char(int num);
void set_date(char input[]);
void set_time(char input[]);
int string_to_int(char num[]);
char validDate(void);
char validTime(void);
struct date get_timestamp(void);
char *float_to_char(float num);


#endif