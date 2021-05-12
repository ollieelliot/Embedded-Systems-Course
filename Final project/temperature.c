#include "my_library.c"

int temp_Flag = 0;

void TC0_Handler(void){
  (*AT91C_TC0_IDR) = 64; //Disable interrupt for LDRBS, bit 6, 64 dec
  temp_Flag = 1;
}

void init_Temp(void){
  (*AT91C_TC0_CMR) = 0; //Select Timer_Clock1 as TCLK1
  (*AT91C_TC0_CCR) = 5; // 101 = 5 dec, enable the clock and enable software trigger, counter is reset and the clock is started 
  (*AT91C_TC0_CMR) = 393216;// 1100000000000000000 = 393216 dec
  (*AT91C_PIOB_PER) = (1 << 25); //Enable pin 2 (id 25)
  NVIC_EnableIRQ(TC0_IRQn); //Enable NVIC interrupt for Timer counter 0 
  
}

void start_Temp(void){
  
  //Reset pulse
  (*AT91C_PIOB_OER) = (1 << 25);
  (*AT91C_PIOB_CODR) = (1 <<  25);
  delay(25);
  (*AT91C_PIOB_SODR) = (1 <<  25);
  (*AT91C_PIOB_ODR) = (1 << 25); 
 
  (*AT91C_TC0_CCR) = 4;
  (*AT91C_TC0_SR);
  (*AT91C_TC0_IER) = 64; //Enable interrupt for LDRBS, bit 6, 64 dec
  
  //Start pulse
  (*AT91C_PIOB_OER) = (1 << 25);
  (*AT91C_PIOB_CODR) = (1 <<  25);
  delay(15);
  (*AT91C_PIOB_SODR) = (1 <<  25);
  (*AT91C_PIOB_ODR) = (1 << 25); 
  
}

float get_Temperature(void){
  
    if (temp_Flag == 1){
     
     temp_Flag = 0;
     unsigned int RA = (*AT91C_TC0_RA);
     unsigned int RB =(*AT91C_TC0_RB);
     
     unsigned int time_diff = RB - RA;
     
     delay(10);
     float temp = time_diff/(42. * 5.) - 273.15;
     
     start_Temp();
     return temp;
   }
   return 0;
}
