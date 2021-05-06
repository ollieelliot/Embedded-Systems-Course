#include "my_library.c"

void delay(int value){
  for (int i = 0; i<value;i++)
    asm("nop"); //Assembly function "No operation", put to sleep
}