#include "my_library.c"

char return_menu(char key);
short in_menu = 2;
char key = 0;
char VALID_TIME = 1;
char VALID_DATE = 1;


void main(void){
  
  
  SystemInit();
  printf("Initializing...\n");
  
  SysTick_Setup();
  init_Pins();
  init_Keypad();
  init_Display();
  clear_Display();
  toggleBlinkLed_setup();
  init_Temp();
  start_Temp();
  init_Photosenor();
  init_Servo();
  print_Menu(-2);
  

  
  char date[8];
  char time_char[6];
  

  printf("Initializing completed!\n");
  printf("Running...\n");
  
  //Test stuff
  time_elapsed.second = 55;
  time_elapsed.minute = 59;
  time_elapsed.hour = 23;
  time_elapsed.day = 31;
  time_elapsed.month = 12;
  time_elapsed.year = 2021;
  
  
  
 while(1){
   
   /* Standard setup */
   
   print_Time(65);
   print_Date(10);
   key = read_Keypad(); 
   
   /* Temperature */
   
   if(key == '1' && in_menu != 1){
     
     in_menu = 1;
     clear_Display();
     get_Temperature(128);
     while(key != '*'){
       key = read_Keypad();

       writeDisplayPos("Press '*' to return",72,1);
     }
     /* Return back to main-menu */
   
     return_menu(key);
   }
   
   /*  Toggle fastMode */

   if(key == '5' && in_menu != 1){
     if(fastMode == 0)
       fastMode = 1;
     else
       fastMode = 0;
   }
   
   /*  Setup date */
     
   if(key == '6' && in_menu != 1){
     in_menu = 1;
     clear_Display();
     writeDisplayPos("DATE SETUP",96,0);
     writeDisplayPos("--------------------", 130, 0);
     writeDisplayPos("Press '*' to return", 112,1);
     writeDisplayPos("4. Change date ", 208,0);
     writeDisplayPos("5. Change time ", 248,0);
   
     
     
     while(key != '*'){
       key = read_Keypad();
       
       /* Overwrite previous date */
       
       if((key == '4' && in_menu != 0) || !VALID_DATE){
         in_menu = 0;
         
         clear_Display();
         writeDisplayPos("DATE SETUP",96,0);
         writeDisplayPos("Enter new date: ", 208,0);
         writeDisplayPos("Press '*' to cancel ", 112,1);
         
         strcpy(date, ""); //Reset char array
         int i = 0;
         writeDisplayPos("DDMMYYYY", 224, 0);
         while(i < 8){
            key = read_Keypad();
            
            writeDisplayPos("-", 8+i,1);
            
            if(key != 0 && key != '*' && key != '#'){
              strncat(date, &key, 1); 
              
              /* Code for subscript */
              writeDisplayPos("_", 224+i,0);
              writeDisplayPos(date, 224,0);
              writeDisplayPos(" ", 8+i,1);
              i++;
            }
         }
           
         get_date(date);
         
         VALID_DATE = validDate();
         
         if(VALID_DATE){
           
         /* Restore after use */
         clear_Display();
         writeDisplayPos("DATE SETUP",96,0);
         writeDisplayPos("--------------------", 130, 0);
         writeDisplayPos("Press '*' to return", 112,1);
         writeDisplayPos("4. Change date ", 208,0);
         writeDisplayPos("5. Change time ", 248,0);
       
         in_menu = 1;
         }
         
         else{
           clear_Display();
           writeDisplayPos("Invalid date!", 214,0);
           delay(10000000);
         }
           
       }
       
       /* Overwrite previous time */
       
       if(key == '5' && in_menu != 0 || !VALID_TIME){
         strcpy(time_char, "");
         in_menu = 0;
         
         clear_Display();
         writeDisplayPos("DATE SETUP",96,0);
         writeDisplayPos("Enter new time: ", 248,0);
         
         int i = 0;
         writeDisplayPos("HHMMSS", 8, 1);
         
         while(i < 6){
            key = read_Keypad();
            
            writeDisplayPos("-", 48+i,1);
            
            if(key != 0 && key != '*' && key != '#'){
              strncat(time_char, &key, 1);
              
              writeDisplayPos(time_char, 8, 1);
              writeDisplayPos(" ", 48+i,1);
              i++;
            }
         }
         get_time(time_char);
         
         VALID_TIME = validTime();
         
         if(VALID_TIME){
             
           /* Restore after use */
           clear_Display();
           writeDisplayPos("DATE SETUP",96,0);
           writeDisplayPos("--------------------", 130, 0);
           writeDisplayPos("Press '*' to return", 112,1);
           writeDisplayPos("4. Change date ", 208,0);
           writeDisplayPos("5. Change time ", 248,0);
         
           in_menu = 1;
         }
         
         else{
           clear_Display();
           writeDisplayPos("Invalid time!", 214,0);
           delay(10000000);
         }
       }
     }
     /* Return back to main-menu */
     
     return_menu(key);
   }
 }
}

char return_menu(char key){
    if(key == '*' && in_menu != 2){
       in_menu = 2;
       clear_Display();
       print_Menu(-2);
       return 1;
     }
    return 0;
}