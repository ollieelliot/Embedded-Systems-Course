#include "my_library.c"


void SysTick_Handler(void){
  
  static int count = 0;
  
  count+= 1 + (fastMode*59*60*30);
  
  if(count/1000 >= 1){
    time_to_date();
    count = 0;
  }
}

void SysTick_Setup(void){
  SysTick_Config(84000-1); //Should be 84M ticks for 1hz but didn't work for some reason. Set ticks to 84k for 1mhz instead. Adapt the blinking interval to the 1mhz clock instead. 
}

