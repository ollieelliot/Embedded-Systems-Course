#include "my_library.c"

char readLed = 0;
int time_led = 0;
int toggle_Blink = 0;

void setLed(unsigned int nLed, unsigned int pinID){//Only for pins on controller D
  
  (*AT91C_PMC_PCER) = (1 << 14); //Set the corresponding bit in PMC_PCER to enable the clock in the PIO-Block. PIOD-block has id 14
  
  //Writing to pin 26 (bit 1)
  
  (*AT91C_PIOD_PER) = (1 <<  pinID); //Set the corresponding bit in PIOD_PER to enable PIO Control, PD3 (Digital Pin 28).
  (*AT91C_PIOD_PPUDR) = (1 << pinID); //Set the corresponding bit in PIOD_PPUDR to disable the pullup resistor. 
  (*AT91C_PIOD_OER) = (1 << pinID); //Set the corresponding bit in PIOD_ODR to enable output, which corresponds to disabling input.  
  
  if (nLed == 1){ //Button is pressed down, enable voltage to make led light up.
    (*AT91C_PIOD_SODR) = (1 <<  pinID);
  }
  else{
    (*AT91C_PIOD_CODR) = (1 <<  pinID);
  }
}



void blinkLed(void){
  
  if (toggle_Blink == 1){
    time_led++;
  
    if (readLed == 1 && time_led%1000 == 0) //When led is on and after every 1000 ticks, turn led off. Our clock is 1mhz, wait for 1000 ticks to get 1hz = 1 second. 1mhz * 1000 = 1hz
      readLed = 0;
      
    else if (readLed == 0 && time_led%1000 == 0) //When led is off and after every 1000 ticks, turn led on.
      readLed = 1;

    setLed(readLed, 3);
  }
  else
    setLed(0, 3);
  
}


void toggleBlinkLed_setup(void){ //Setup the interrupt
  
  //Writing to pin 26 (bit 1), since our button is connected to this pin
  (*AT91C_PIOD_AIMER) = 1 << 1; //Additional Interrupt Modes Enable
  (*AT91C_PIOD_IFER) = 1 << 1;  // Enable the input glitch filter to pin
  (*AT91C_PIOD_DIFSR) = 1 << 1; //Debouncing filtering selection
  (*AT91C_PIOD_SCDR) = (unsigned int) 255; //Set debouncing value to 255 
  (*AT91C_PIOD_ISR); //Clear old events detected
  
   NVIC_ClearPendingIRQ(PIOD_IRQn); //Clear pending interrupts
   NVIC_SetPriority(PIOD_IRQn, 1);
   NVIC_EnableIRQ(PIOD_IRQn);
  (*AT91C_PIOD_PER) = (1 <<  1); //Enable PIO (taken from HW 1 tips document, is this necessary?) 
  (*AT91C_PIOD_IER) = (1 << 1); //Enable input change interrupt to pin 26, interrupts everytime there is a change on pin 26
   
  
}


void PIOD_Handler(void){
  
  if (((*AT91C_PIOD_ISR) & 0x2) == 0x2){ //Use the PIO Controller Interrupt Status Register to check if the button has been registered as pressed down
   
    if (toggle_Blink == 0) //Basic toggle on/off logic
      toggle_Blink = 1;
  
    else if (toggle_Blink == 1)       
      toggle_Blink = 0;
  }
  
}
