#ifndef DISPLAY
#define DISPLAY

extern struct date d;

unsigned char read_Status_Display();
void write_Command_2_Display(unsigned char command);
void write_Data_2_Display(unsigned char data);
void init_Display();
void write_Display();
void clear_Display();
void print_Character(char c);
void print_String(char c[]);
void reset_Adress_Pointer();
void writeDisplayPos(char *text, char x , char y);
void print_Menu(int pos);
void print_Time(int pos);
void print_Date(int pos);
void print_TempStats(int i);


#endif

