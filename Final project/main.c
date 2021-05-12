#include "my_library.c"


char return_menu(char key);
short in_menu = 2;
char key = 0;
char VALID_TIME = 1;
char VALID_DATE = 1;
short rec = 0;

int fastMode = 0;

DLinkedList *list = NULL; //Initilize the list


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
  init_Stats();
  print_Menu(-2);
  
  
  char date[8];
  char time_char[6];


  printf("Initializing completed!\n");
  printf("Running...\n");
  
  //Test stuff
  time_elapsed.second = 0;
  time_elapsed.minute = 0;
  time_elapsed.hour = 23;
  time_elapsed.day = 1;
  time_elapsed.month = 1;
  time_elapsed.year = 2021;
  
  
 while(1){
   
   /* Standard setup */
   
   print_Time(65);
   print_Date(10);
   key = read_Keypad(); 
   
   /* Temperature stats */
   
   if(key == '1' && in_menu != 1){
     int page = 0;
     //printList(&list);
     in_menu = 1;
     clear_Display();
     while(key != '*'){
       key = read_Keypad();
       print_TempStats(page);
       
       writeDisplayPos("[6] Next -->",250,1);
       writeDisplayPos("<-- Prev [4]",226,1);
       
       if(key == '6'){
         clear_Display();
         page++;
         if(page > 6)
           page = 0;
         print_TempStats(page);
         writeDisplayPos("[6] Next -->",250,1);
         writeDisplayPos("<-- Prev [4]",226,1);
       }
       
       if(key == '4'){
         clear_Display();
         page--;
         if(page < 0)
           page = 6;
         print_TempStats(page);
         writeDisplayPos("[6] Next -->",250,1);
         writeDisplayPos("<-- Prev [4]",226,1);
       }
       
       
       
       
       writeDisplayPos("Press '*' to return",112,1);
     }
     /* Return back to main-menu */
   
     return_menu(key);
   }
   
    /* Toggle recording of temperature data */
   
    if(key == '4' && in_menu != 1){
      if(rec == 0)
       rec = 1;
      else
       rec = 0;
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
              
              /* Code for text position marker */
              writeDisplayPos("_", 224+i,0);
              writeDisplayPos(date, 224,0);
              writeDisplayPos(" ", 8+i,1);
              i++;
            }
            if(key == '*'){
              break;
            }
         }
         
         if(i == 8){
           set_date(date);
           
           VALID_DATE = validDate();
           
           printf("Valid date: %d", VALID_DATE);
           
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
           
       }
       
       /* Overwrite previous time */
       
       if(key == '5' && in_menu != 0 || !VALID_TIME){
         strcpy(time_char, "");
         in_menu = 0;
         
         clear_Display();
         writeDisplayPos("DATE SETUP",96,0);
         writeDisplayPos("Enter new time: ", 248,0);
         writeDisplayPos("Press '*' to cancel ", 112,1);
         
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
            
            if(key == '*'){
              break;
            }
         }
         
         if(i == 6){
           set_time(time_char);
           
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