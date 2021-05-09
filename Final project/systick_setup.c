#include "my_library.c"



void SysTick_Handler(void){
  

  /* Program freezes only when fastMode = 1, resumes when = 0 */
  time+= 1 + (fastMode*59);
 
  
  if((time%1000) == 0)
     time_to_date();

}

void SysTick_Setup(void){
  SysTick_Config(84000-1); //Should be 84M ticks for 1hz but didn't work for some reason. Set ticks to 84k for 1mhz instead. Adapt the blinking interval to the 1mhz clock instead. 
}