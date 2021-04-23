#include "system_sam3x.h"
#include "at91sam3x8.h"
#include <stdio.h>

//DEFINE REGISTERS
#define AT91C_PIOD_AIMER (AT91_CAST(AT91_REG *) 0x400E14B0)
#define AT91C_PIOD_DIFSR (AT91_CAST(AT91_REG *) 0x400E1484)
#define AT91C_PIOD_SCDR (AT91_CAST(AT91_REG *) 0x400E148C)

#define AT91C_PIOC_AIMER (AT91_CAST(AT91_REG *) 0x400E12B0)
#define AT91C_PIOC_DIFSR (AT91_CAST(AT91_REG *) 0x400E1284)
#define AT91C_PIOC_SCDR (AT91_CAST(AT91_REG *) 0x400E128C)

char readLed = 0;
int time = 0;
int toggle_Blink = 0;
int temp_Flag = 0;
char photo[5];

char keys[4][3] = {{'1', '2', '3'},   //Array with the keys [rows][cols]
                    {'4','5','6'}, 
                    {'7','8','9'}, 
                    {'*', '0', '#'}};

unsigned int readButton();
void setLed();
void SysTick_Handler();
void blinkLed();
void SysTick_Setup();
void PIOD_Handler();
void PIOC_Handler();
void toggleBlinkLed_setup();
void init_Keypad();
char read_Keypad();
void Keypad_Interrupt_setup();
void delay();
unsigned char read_Status_Display();
void write_Command_2_Display(unsigned char command);
void write_Data_2_Display(unsigned char data);
void init_Display();
void write_Display();
void init_Pins();
void clear_Display();
void print_Character(char c);
void print_String(char c[]);
void reset_Adress_Pointer();
void pin_Setup(char block, int bit, int in_out, int pullup);
void start_Temp();
void init_Temp();
void init_Photosenor();
int start_Photosensor();
double toVolt(int reading);

void main(void){
  printf("Initializing...\n");
  
  SystemInit();
  SysTick_Setup();
  init_Pins();
  init_Keypad();
  init_Display();
  clear_Display();
  write_Display();
  toggleBlinkLed_setup();
  init_Temp();
  start_Temp();
  init_Photosenor();
 
  
  
  
  printf("Initializing completed!\n");
  printf("Running...\n");
  
 while(1){
   read_Keypad();
   
   
   sprintf(photo, "%f", toVolt(start_Photosensor()));
   printf("Test printing photosensor voltage: %f \n", toVolt(start_Photosensor()));
   
   clear_Display();
   print_String("Photo resistor voltage: ");
   print_String(photo);
   delay(100000);
   
   
   //Temperature
   
   /*
   if (temp_Flag == 1){
     delay(100000);
     temp_Flag = 0;
     unsigned int RA = (*AT91C_TC0_RA);
     unsigned int RB =(*AT91C_TC0_RB);
     
     unsigned int time_diff = RB - RA;
     printf("RB - RA: %d\n", time_diff);
     float temp = time_diff/(42. * 5.) - 273.15;
     char temperature[5];
     sprintf(temperature, "%f", temp);
     
     printf("Temperature: %f\n", temp);
     
     //Test print to display
     
     clear_Display();
     print_String("Temperature: ");
     print_String(temperature);
     
       start_Temp();
   }
   */
   
   
   
   //setLed(readButton(), 3); //To turn on the led while pressing down the button
   
 }
} 

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
  /*
  (*AT91C_PIOD_PER) = (1 << 0); //Enable reset, bit 0 pin 25  
  (*AT91C_PIOD_PPUDR) = (1 << 0);
  (*AT91C_PIOD_OER) = (1 << 0); //enable output to reset display (pin 25 in arduino)
  */
  
  (*AT91C_PIOC_OER) = 258048;//111111000000000000 = 258048 //Enable output bit 12-17
  
   //Enable pin control to databus
  (*AT91C_PIOC_PER) = 13308;     //Set bits 2,3,4,5,6,7,8,9, 12 (output enable), 13 (dir)
                                 //in controller C to enable pio control, 11001111111100 = 13308
  (*AT91C_PIOC_PPUDR) = 13308;  //Disable pull up for above 
  
  (*AT91C_PIOC_SODR) = (1 << 12);   //Set bit 12 (output enable in 74Chip, Active Low)
  
}

unsigned int readButton(unsigned int *nButton){
  unsigned int button_Status;
  
  (*AT91C_PMC_PCER) = 1 << 14; //Set the corresponding bit in PMC_PCER to enable the clock in the PIO-Block. PIOD-block has id 14
  
  //Writing to pin 26 (bit 1)
  pin_Setup('D', 1, 0, 0);
  /*
  (*AT91C_PIOD_PER) = (1 <<  1); //Set the corresponding bit in PIOD_PER to enable PIO Control, PD1 (Digital Pin 26).
  (*AT91C_PIOD_PPUDR) = (1 << 1); //Set the corresponding bit in PIOD_PPUDR to disable the pullup resistor. 
  (*AT91C_PIOD_ODR) = (1 << 1); //Set the corresponding bit in PIOD_ODR to disable output, which corresponds to enabling the input pin.  
  */

  if (((*AT91C_PIOD_PDSR) & 0x2) == 0x2){ //Mask bit 1 (32 bits) and check if the pin status register at bit 1 is equal to 1, if bit 1 is equal to 1 it means that the button is not pressed down.
    button_Status = 0;
  }
  else{ //Button is pressed down, since bit 1 is equal to 0. 
    button_Status = 1;
    
  }
  return button_Status;
}


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


void SysTick_Handler(void){

  blinkLed(); //Execute blinkLed() with the systick
}


void SysTick_Setup(void){
  SysTick_Config(84000-1); //Should be 84M ticks for 1hz but didn't work for some reason. Set ticks to 84k for 1mhz instead. Adapt the blinking interval to the 1mhz clock instead. 
}


void blinkLed(void){
  
  if (toggle_Blink == 1){
    time++;
  
    if (readLed == 1 && time%1000 == 0) //When led is on and after every 1000 ticks, turn led off. Our clock is 1mhz, wait for 1000 ticks to get 1hz = 1 second. 1mhz * 1000 = 1hz
      readLed = 0;
      
    else if (readLed == 0 && time%1000 == 0) //When led is off and after every 1000 ticks, turn led on.
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


void init_Keypad(void){
  
  //Set the corresponding bit in PIOC_ODR to enable input to databus
  (*AT91C_PIOC_ODR) = 956;
  
  //Disable pull-up resistor for all pins
  (*AT91C_PIOC_PPUDR) = 956;
  
}


char read_Keypad(void){ 
    int column_clear[] = {256, 512, 128}; //First only Col 1 is cleared, then only Col 2 is cleared and then Col 3.
    int rows[] = {32, 4, 8, 16}; //Row 1, Row 2, Row 3, Row 4 = Bit 5, Bit 2, Bit 3, Bit 4 in PIOC
    
    (*AT91C_PIOD_PER) = (1 << 2);       //Enable control to OE KEY BUS, pin 27
    (*AT91C_PIOD_OER) = (1 << 2);       //Set output to pin 27;
    (*AT91C_PIOD_CODR) = (1 << 2);      //Clear OE KEY BUS (Active low) to enable, pin 27
    
    (*AT91C_PIOC_OER) = 896;            //Set all columns as output...bit 7,8,9, 1110000000 = 0x380 = 896
    (*AT91C_PIOC_SODR) = 896;           //Set all columns to HIGH
    
    char value = NULL;
    
    for (int i = 0; i < 3; i++){        //Loop columns
      (*AT91C_PIOC_CODR) = column_clear[i];       //Clear the n:th column
      
      for (int j = 0; j < 4; j++){      //Loop rows
        if (((*AT91C_PIOC_PDSR) & rows[j]) == 0){ //Mask the row and check if the bit for that row is zero
          //printf("reached if");
          setLed(1, 6);                         //Turn on LED on pin 29 on the arduino (Controller D), to test the keys
          value = keys[j][i];                   //Store the key that has been pressed
        }
      }
      
      (*AT91C_PIOC_SODR) = 896; //Set all columns to HIGH again
    }
    (*AT91C_PIOC_ODR) = 896;            //Set all columns as input
    (*AT91C_PIOD_SODR) = (1 << 2);      //Set OE KEY BUS (Active low) to disable, pin 27
    
    //Print to Terminal I/O
    if(value != NULL){
      printf("Key pressed: %c \n", value);
      //Display print test
      
      //print_Character(value);
    }
    /*
    if(value == '*'){
      printf("Display cleared\n");
      clear_Display();
      print_String("Keypad test: ");
    }
    */
      
    
    setLed(0, 6);       //Turn off LED on pin 29 on the arduino (Controller D), to test the keys
    return value;
  
}


void delay(int value){
  for (int i = 0; i<value;i++)
    asm("nop"); //Assembly function "No operation", put to sleep
}


unsigned char read_Status_Display(void){
  unsigned char temp = 0;
  
  //PMC is already enabled from init_Pins to the C-block
                                 
  //Set the corresponding bit in PIOC_ODR to enable input to databus
  (*AT91C_PIOC_ODR) = 1020;     //Bits 2,3,4,5,6,7,8,9 is set with 1111111100 = 0x3FC = 1020
  
  (*AT91C_PIOC_SODR) = (1 << 13);   //Set bit 13 (dir) as input
  (*AT91C_PIOC_CODR) = (1 << 12);   //Clear bit 12 (output enable in 74Chip, Active Low)
  (*AT91C_PIOC_SODR) = (1 << 14);   //Set bit 14 (C/D), Command/Data
  (*AT91C_PIOC_CODR) = (1 << 15);   //Clear chip select, bit 15 (CE)
  (*AT91C_PIOC_CODR) = (1 << 16);   //Clear bit 16 (RD), Read Display
  
  //Call delay function
  delay(100); 
  
  //Read databus pins and store in temp
  temp = (*AT91C_PIOC_PDSR) & 0x3FC; 
 
  (*AT91C_PIOC_SODR) = (1 << 12);    //Disable output on 74Chip (Active Low), set bit 12
  (*AT91C_PIOC_CODR) = (1 << 13);    //Clear dir to set as output to 74Chip, 1 = Input, 0 = Output
  (*AT91C_PIOC_SODR) = (1 << 15);   //Set CE (chip select display)
  (*AT91C_PIOC_SODR) = (1 << 16);   //Set RD (read display)
  
  return temp;
    
}

void write_Command_2_Display(unsigned char command){
  while((read_Status_Display() & 0xC) != 0xC){//Bit 0 and 1 must be = 0 and Bit 1 and 2 must be = 1
    //Wait for status to be ok so we can write
  }
  
  //Clear databus
  (*AT91C_PIOC_CODR) = 1020;
  
  //Set command to databus 
  (*AT91C_PIOC_SODR) = ((unsigned int) command << 2);//command & 1020; //Set command to our databus
  
  (*AT91C_PIOC_CODR) = (1 << 13);   //Clear dir to set as output to 74Chip, 1 = Input, 0 = Output
  (*AT91C_PIOC_CODR) = (1 << 12);   //clear output enable to activate output
  
  (*AT91C_PIOC_OER)  = 1020;        //Set databus as output(2-9)
  
  (*AT91C_PIOC_SODR) = (1 << 14);   //Set C/D signal = 1 = Command (bit 14)
  (*AT91C_PIOC_CODR) = (1 << 15);   //Clear chip select display (CE), bit 15
  (*AT91C_PIOC_CODR) = (1 << 17);   //clear write display (WR), bit 17

  delay(100);
  
  (*AT91C_PIOC_SODR) = (1 << 15);   //Set CE
  (*AT91C_PIOC_SODR) = (1 << 17);   //Set WR
  (*AT91C_PIOC_SODR) = (1 << 12);   //Disable output on 74Chip (Active Low)
  
  (*AT91C_PIOC_ODR)  = 1020;        //Make databus as input
  
}


void write_Data_2_Display(unsigned char data){
  while((read_Status_Display() & 0xC) != 0xC){ //Two lowest bits needs to be 1 
    //Wait for status to be ok so we can write
  }
  
  //Clear databus
  (*AT91C_PIOC_CODR) = 1020;
  
  //Set command to databus 
  (*AT91C_PIOC_SODR) = ((unsigned int) data << 2); //data & 1020; //Set command to our databus
  
  (*AT91C_PIOC_CODR) = (1 << 13);   //Clear dir to set as output to 74Chip, 1 = Input, 0 = Output
  (*AT91C_PIOC_CODR) = (1 << 12);   //clear output enable to activate output
  
  (*AT91C_PIOC_OER)  = 1020;        //set databus as output
  
  (*AT91C_PIOC_CODR) = (1 << 14);   //Set C/D signal = 1 = Command (bit 14)
  (*AT91C_PIOC_CODR) = (1 << 15);   //Clear chip select display (CE), bit 15
  (*AT91C_PIOC_CODR) = (1 << 17);   //clear write display (WR), bit 17
  
  delay(100);
  
  (*AT91C_PIOC_SODR) = (1 << 15);   //Set CE
  (*AT91C_PIOC_SODR) = (1 << 17);   //Set WR
  (*AT91C_PIOC_SODR) = (1 << 12);   //Disable output on 74Chip (Active Low)
  
  (*AT91C_PIOC_ODR)  = 1020;        //Make databus as input
}


void init_Display(void){
  
  //Clear reset display, pin 25 on arduino, bit 0 in controller D
  (*AT91C_PIOD_CODR) = (1 << 0);
  //Call delay function
  delay(100);
  //Set reset display
  (*AT91C_PIOD_SODR) = (1 << 0);
  
  write_Data_2_Display(0x00);
  write_Data_2_Display(0x00);
  write_Command_2_Display(0x40);  //Set text home address
  
  write_Data_2_Display(0x00);
  write_Data_2_Display(0x40);
  write_Command_2_Display(0x42); //Set graphic home address
  
  write_Data_2_Display(0x28);
  write_Data_2_Display(0x00);
  write_Command_2_Display(0x41); // Set text area
    
  write_Data_2_Display(0x28);
  write_Data_2_Display(0x00);
  write_Command_2_Display(0x43); // Set graphic area
  write_Command_2_Display(0x80); // text mode
  write_Command_2_Display(0x94); // Text on graphic off
}


void clear_Display(void){            //Clears the display by printing lots of spaces
    reset_Adress_Pointer();     //Set address pointer to beginning before printing spaces
    for(int i = 0; i<640; i++){ //640 = 0x280
        write_Data_2_Display(0x00); //Character 'Space'
        write_Command_2_Display(0xC0);
    }
    reset_Adress_Pointer();     //Set address pointer to beginning when done
}


void print_Character(char c){
  
  //In the default ASCII table the first character 
  //which is space, begins on 0x20. So we need to subtract by 0x20
  //to get our desired character.
  write_Data_2_Display(c - 0x20);
  write_Command_2_Display(0xC0);
}


void print_String(char c[]){            //Print a string by printing every character one by one
  
  for(int i = 0; c[i] != '\0'; i++){    //Loop till a null character (end of string, \0)
    print_Character(c[i]);
    
  }
}


void reset_Adress_Pointer(void){ //Resets the address pointer to the top-left cointer
  write_Data_2_Display(0x00);    //0x00 is top-left corner
  write_Command_2_Display(0x24); //Command for setting the address pointer
  
}


void write_Display(void){       
  
  //Test printing a character to the display
  write_Data_2_Display(0x00);
  write_Data_2_Display(0x00);
  write_Command_2_Display(0x24);
  
  //Testing the keypad with the display
  //print_String("Keypad test: ");

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
  (*AT91C_PIOB_ODR) = (1 << 25); //Disable when done sending pulse, prevent collision with temp pin
 
  (*AT91C_TC0_CCR) = 4;
  (*AT91C_TC0_SR);
  (*AT91C_TC0_IER) = 64; //Enable interrupt for LDRBS, bit 6, 64 dec
  
  //Start pulse
  (*AT91C_PIOB_OER) = (1 << 25);
  (*AT91C_PIOB_CODR) = (1 <<  25);
  delay(15);
  (*AT91C_PIOB_SODR) = (1 <<  25);
  (*AT91C_PIOB_ODR) = (1 << 25); //Disable when done sending pulse, prevent collision with temp pin
  
}

void TC0_Handler(void){
  (*AT91C_TC0_IDR) = 64; //Disable interrupt for LDRBS, bit 6, 64 dec
  temp_Flag = 1;
}

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









  