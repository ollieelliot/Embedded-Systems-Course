#include "system_sam3x.h"
#include "at91sam3x8.h"

unsigned int readButton();
void setLed();
void SysTick_Handler();
void blinkLed();
void SysTick_Setup();
void PIOD_Handler();

char readLed = 0;
int time = 0;
int toggle_Blink = 0;

void main(void){
  SystemInit();
  SysTick_Setup();
 
 while(1){
   //setLed(readButton());
 }
} 

unsigned int readButton(unsigned int *nButton){
  unsigned int button_Status;
  
  (*AT91C_PMC_PCER) = 1 << 14; //Set the corresponding bit in PMC_PCER to enable the clock in the PIO-Block.
  
  (*AT91C_PIOD_PER) = (1 <<  1); //Set the corresponding bit in PIOD_PER to enable PIO Control, PD1 (Digital Pin 26).
  
  (*AT91C_PIOD_PPUDR) = (1 << 1); //Set the corresponding bit in PIOD_PPUDR to disable the pullup resistor. 
  
  (*AT91C_PIOD_ODR) = (1 << 1); //Set the corresponding bit in PIOD_ODR to disable output, which corresponds to enabling the input pin.  
  
  if (((*AT91C_PIOD_PDSR) & 0x2) == 0x2){ //Mask bit 1 (32 bits) and check if the pin status register at bit 1 is equal to 1, if bit 1 is equal to 1 it means that the button is not pressed down.
    button_Status = 0;
  }
  else{ //Button is pressed down, since bit 1 is equal to 0. 
    button_Status = 1;
    
  }
   
  return button_Status;
}


void setLed(unsigned int nLed){
  
  (*AT91C_PMC_PCER) = 1 << 14; //Set the corresponding bit in PMC_PCER to enable the clock in the PIO-Block.
  
  (*AT91C_PIOD_PER) = (1 <<  3); //Set the corresponding bit in PIOD_PER to enable PIO Control, PD3 (Digital Pin 28).
  
  (*AT91C_PIOD_PPUDR) = (1 << 3); //Set the corresponding bit in PIOD_PPUDR to disable the pullup resistor. 
  
  (*AT91C_PIOD_OER) = (1 << 3); //Set the corresponding bit in PIOD_ODR to disable input, which corresponds to enabling the output pin.  
  
  
  if (nLed == 1){ //Button is pressed down, enable voltage to make led light up.
    (*AT91C_PIOD_SODR) = AT91C_PIO_PD3;
  }
  else{
    (*AT91C_PIOD_CODR) = AT91C_PIO_PD3;
  }
}

void SysTick_Handler(void){

  blinkLed();
}

void SysTick_Setup(void){
  SysTick_Config(84000-1); //Should be 84M ticks for 1hz but didn't work for some reason. Set ticks to 84k for for 1mhz instead. Adapt the blinking interval to the 1mhz clock instead. 
}

void blinkLed(void){
  time++;
  if (readLed == 1 && time%1000 == 0) //When led is on and after every 1000 ticks, turn led off. Our clock is 1mhz, wait for 1000 ticks to get 1hz = 1 second. 1mhz * 1000 = 1hz
    readLed = 0;
    
  else if (readLed == 0 && time%1000 == 0) //When led is off and after every 1000 ticks, turn led on.
    readLed = 1;

  setLed(readLed);
}

void interrupt_Setup(void){
  
}

void PIOD_Handler(void){
  
  /*
  if(*AT91C_PIOD_ISR == 1)
    toggle_Blink = 1;
*/
    
}

  