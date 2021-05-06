#include "my_library.c"

char photo[5];

void init_Photosenor(void){
  pin_Setup('A', 4, 0, 0);
  pin_Setup('A', 3, 0, 0);
  
  (*AT91C_ADCC_MR) = (1 << 9); // set bit 9 for prescale = 2
}

int start_Photosensor(void){
  (*AT91C_ADCC_IER) = (1 << 1);
  (*AT91C_ADCC_CHER) = (1 << 1); //Choose channel 0
  (*AT91C_ADCC_CR) = (1 << 1); //Begins analog-to-digital conversion
  
  while(((*AT91C_ADCC_SR) & 0x1000000) != 0x1000000){} //Wait until DRDY is set
  
  int PH_VALUE = ((*AT91C_ADCC_LCDR) & 0xFFF); //bit 0-11 contains the data, 111111111111 == 0xFFF hex
  
  return PH_VALUE;
}

double toVolt(int reading){
  return ((reading*3.13)/4095); //System voltage: 3.3V, ADC Resolution: 4096 (12-bit)
}

char *getPhotoreading(void){
  sprintf(photo, "%f", toVolt(start_Photosensor()));
  printf("Test printing photosensor voltage: %f \n", toVolt(start_Photosensor()));
  
  return photo;
}

