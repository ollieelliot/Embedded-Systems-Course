#include "my_library.c"

int column_clear[] = {256, 512, 128}; //First only Col 1 is cleared, then only Col 2 is cleared and then Col 3.
int rows[] = {32, 4, 8, 16}; //Row 1, Row 2, Row 3, Row 4 = Bit 5, Bit 2, Bit 3, Bit 4 in PIOC
char key_pressed = 0;
  

char keys[4][3] = {{'1', '2', '3'},   //Array with the keys [rows][cols]
                    {'4','5','6'}, 
                    {'7','8','9'}, 
                    {'*', '0', '#'}};


void init_Keypad(void){
  
  //Set the corresponding bit in PIOC_ODR to enable input to databus
  (*AT91C_PIOC_ODR) = 956;
  
  //Disable pull-up resistor for all pins
  (*AT91C_PIOC_PPUDR) = 956;
  
  (*AT91C_PIOD_PER) = (1 << 2);       //Enable control to OE KEY BUS, pin 27
  (*AT91C_PIOD_OER) = (1 << 2);       //Set output to pin 27;
  
  
}

char read_Keypad(void){ 
    
  (*AT91C_PIOD_CODR) = (1 << 2);      //Clear OE KEY BUS (Active low) to enable, pin 27
  
  (*AT91C_PIOC_OER) = 896;            //Set all columns as output...bit 7,8,9, 1110000000 = 0x380 = 896
  (*AT91C_PIOC_SODR) = 896;           //Set all columns to HIGH

  char KEY_VALUE = 0;
  
  for (int i = 0; i < 3; i++){        //Loop columns
    (*AT91C_PIOC_CODR) = column_clear[i];       //Clear the n:th column
    
    for (int j = 0; j < 4; j++){      //Loop rows
      if (((*AT91C_PIOC_PDSR) & rows[j]) == 0){ //Mask the row and check if the bit for that row is zero
        
          KEY_VALUE = keys[j][i];                   //Store the key that has been pressed
      }
    }
    (*AT91C_PIOC_SODR) = 896; //Set all columns to HIGH again
  }
  
  (*AT91C_PIOC_ODR) = 896;            //Set all columns as input
  (*AT91C_PIOD_SODR) = (1 << 2);      //Set OE KEY BUS (Active low) to disable, pin 27
  
  
  /* Code to debounce keyboard to only register one value per press */
  
  if(KEY_VALUE == 0){
    key_pressed = 0;
  }
  
  if (key_pressed != KEY_VALUE){
        key_pressed = KEY_VALUE;
        return KEY_VALUE;
      }
  else
    return 0;
  
}

