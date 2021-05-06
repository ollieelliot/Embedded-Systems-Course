#include "my_library.c"

unsigned int readButton(unsigned int *nButton){
  unsigned int button_Status;
  
  (*AT91C_PMC_PCER) = 1 << 14; //Set the corresponding bit in PMC_PCER to enable the clock in the PIO-Block. PIOD-block has id 14
  
  //Writing to pin 26 (bit 1)
  pin_Setup('D', 1, 0, 0);

  if (((*AT91C_PIOD_PDSR) & 0x2) == 0x2){ //Mask bit 1 (32 bits) and check if the pin status register at bit 1 is equal to 1, if bit 1 is equal to 1 it means that the button is not pressed down.
    button_Status = 0;
  }
  else{ //Button is pressed down, since bit 1 is equal to 0. 
    button_Status = 1;
    
  }
  return button_Status;
}
