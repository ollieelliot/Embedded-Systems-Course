#include "my_library.h"

void init_Servo(void){
  (*AT91C_PMC_PCER1) = (1 << 4); //Enable PWM in PMC
  (*AT91C_PIOB_PER) = (1 << 17); //Enable control to pin 62 (Analog In 8)
  
  (*AT91C_PIOB_PDR) = (1 << 17); //Let the peripheral control pin 62
  (*AT91C_PIOB_ABMR) = (1 << 17); //Activate peripheral B
  (*AT91C_PWMC_ENA) = AT91C_PWMC_CHID1;  // (PWMC) PWMC Enable Register
  
  (*AT91C_PWMC_CH1_CMR) = 0x5; //Set pre-scaler to Master_clock/32 = 0101 = 0x5;
  (*AT91C_PWMC_CH1_CPRDR) = 52500; // To calculate period value: (X * CPRD)/MCK = time and then solve for CPRD to get the value, X is 32, MCK is 84M, time is in seconds
  (*AT91C_PWMC_CH1_CDTYR) = 1650; //In microseconds
}

void set_Servo(char x){
  
  if (x == '*' && x != NULL)
    (*AT91C_PWMC_CH1_CDTYUPDR) = 6400; //Turns to 180deg
  else if(x != NULL){
    int key = x - '0';
  (*AT91C_PWMC_CH1_CDTYUPDR) = 1500+(280*key);
  }
  
  /*
  if (get_ServoPos() != 63396)
    printf("%d \n", get_ServoPos());
  */
}
          
unsigned int get_ServoPos(void){
  return(*AT91C_PWMC_CH1_CDTYR);
}