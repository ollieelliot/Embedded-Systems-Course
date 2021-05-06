#ifndef TIME
#define TIME

extern uint64_t time;
extern char char_seconds[2];
extern short fastMode;
extern struct date time_elapsed;
extern short RESET_TIME_DISPLAY;


struct date{
  int second;    /* Seconds: 0-59 */
  int minute;    /* Minutes: 0-59 */
  int hour;      /* Hours: 0-23 (24-hour clock system) */
  int day;       /* The day of the month: 1-31 (Depending on leapyear) */
  int month;     /* Month: 0-11 */
  int year;      /* Years since date assigned by user */
};

char *uint_to_char(uint64_t tick);
struct date time_to_date(void);
char *int_to_char(int num);
struct date get_date(char input[]);
struct date get_time(char input[]);
int string_to_int(char num[]);


#endif