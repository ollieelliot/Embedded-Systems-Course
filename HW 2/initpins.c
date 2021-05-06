#include "my_library.h"

void pin_Setup(char block, int bit, int in_out, int pullup){//0 for input 1 for output; 0 = disable pullup, 1 = enable pullup
  if(block == 'C' || block == 'c'){
    (*AT91C_PIOC_PER) = (1 << bit);
    
    if(in_out == 0)
      (*AT91C_PIOC_ODR) = (1 << bit);
    
    else if(in_out == 1)
      (*AT91C_PIOC_OER) = (1 << bit);
    
    if(pullup == 0)
      (*AT91C_PIOC_PPUDR) = (1 << bit);
    
    if(pullup == 1)
      (*AT91C_PIOC_PPUER) = (1 << bit);
  }
  
  if(block == 'D' || block == 'd'){
     (*AT91C_PIOD_PER) = (1 << bit);
     
    if(in_out == 0)
      (*AT91C_PIOD_ODR) = (1 << bit);
    
    else if(in_out == 1)
      (*AT91C_PIOD_OER) = (1 << bit);
    
    if(pullup == 0)
      (*AT91C_PIOD_PPUDR) = (1 << bit);
    
    if(pullup == 1)
      (*AT91C_PIOD_PPUER) = (1 << bit);
  }
  
  if(block == 'B' || block == 'b'){
     (*AT91C_PIOB_PER) = (1 << bit);
    
    if(in_out == 0)
      (*AT91C_PIOB_ODR) = (1 << bit);
    
    else if(in_out == 1)
      (*AT91C_PIOB_OER) = (1 << bit);
    
    if(pullup == 0)
      (*AT91C_PIOB_PPUDR) = (1 << bit);
    
    if(pullup == 1)
      (*AT91C_PIOB_PPUER) = (1 << bit);
  }
  
  if(block == 'A' || block == 'a'){
   (*AT91C_PIOA_PER) = (1 << bit);
    
    if(in_out == 0)
      (*AT91C_PIOA_ODR) = (1 << bit);
    
    else if(in_out == 1)
      (*AT91C_PIOA_OER) = (1 << bit);
    
    if(pullup == 0)
      (*AT91C_PIOA_PPUDR) = (1 << bit);
    
    if(pullup == 1)
      (*AT91C_PIOA_PPUER) = (1 << bit);
  }
}

void init_Pins(void){
  //Set the corresponding bit in PMC_PCER to enable the clock in the PIO-Block.
  (*AT91C_PMC_PCER) = (1 << 13);  //PIOC-block has id 13
  (*AT91C_PMC_PCER) = (1 << 14);   //PIOD-block has id 14
  (*AT91C_PMC_PCER) = (1 << 12);   //PIOB-block has id 12
  (*AT91C_PMC_PCER1) = (1 << 5);   //PIOA-block 
  (*AT91C_PMC_PCER) = (1 << 27);   //Enable Timer Counter 1
  
   //Enable pin control to display pins
  (*AT91C_PIOC_PER) = 1032192; // bit 14 (C/D = Command/Data), 15 (CE = Chip select) and  16 (Read display), 17 write display (WR), 18 font select (FS), 19 display mode (RV)
                               //11111100000000000000 = 1032192
  
  (*AT91C_PIOC_PPUDR) = 1032192; //Disable pull up for C/D, CE, RD, WR, FS, RV
  
  pin_Setup('D', 0, 1, 0);
  
  (*AT91C_PIOC_OER) = 258048;//111111000000000000 = 258048 //Enable output bit 12-17
  
   //Enable pin control to databus
  (*AT91C_PIOC_PER) = 13308;     //Set bits 2,3,4,5,6,7,8,9, 12 (output enable), 13 (dir)
                                 //in controller C to enable pio control, 11001111111100 = 13308
  (*AT91C_PIOC_PPUDR) = 13308;  //Disable pull up for above 
  
  (*AT91C_PIOC_SODR) = (1 << 12);   //Set bit 12 (output enable in 74Chip, Active Low)
  
}