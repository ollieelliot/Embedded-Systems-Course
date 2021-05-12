#include "my_library.c"

struct date d;

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
  delay(15); 
  
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

  delay(15);
  
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
  
  delay(15);
  
  (*AT91C_PIOC_SODR) = (1 << 15);   //Set CE
  (*AT91C_PIOC_SODR) = (1 << 17);   //Set WR
  (*AT91C_PIOC_SODR) = (1 << 12);   //Disable output on 74Chip (Active Low)
  
  (*AT91C_PIOC_ODR)  = 1020;        //Make databus as input
}


void init_Display(void){
  
  //Clear reset display, pin 25 on arduino, bit 0 in controller D
  (*AT91C_PIOD_CODR) = (1 << 0);
  //Call delay function
  delay(15);
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


void clear_Display(void){        //Clears the display by printing lots of spaces
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

void writeDisplayPos(char *text, char x , char y){
  write_Data_2_Display(x);
  write_Data_2_Display(y);
  write_Command_2_Display(0x24);//Set address pointer

  print_String(text);   //Prints text
}

void print_Menu(int pos){
  
  writeDisplayPos("MENU",100 + pos,0);
  writeDisplayPos("--------------------", 132 + pos, 0);
  writeDisplayPos("|  1.Temperature stats |", 170 + pos,0);
  writeDisplayPos("|  2.                  |", 210 + pos,0);
  writeDisplayPos("|  3.                  |", 250 + pos,0);
  writeDisplayPos("|  4.Toggle record     |", 34 + pos, 1);
  writeDisplayPos("|  5.Toggle fastMode   |", 74 + pos, 1);
  writeDisplayPos("|  6.Setup date        |", 114 + pos, 1);
  
}

void print_Time(int pos){
  
   //writeDisplayPos("Time: ", 0 + pos, 0);
  if(RESET_TIME_DISPLAY == 1){
    RESET_TIME_DISPLAY = 0;
    clear_Display();
    print_Menu(-2);
  }
     
   writeDisplayPos(uint_to_char(time_elapsed.hour), 6 + pos, 0);
   writeDisplayPos(":", 8 + pos, 0);
   writeDisplayPos(uint_to_char(time_elapsed.minute), 9 + pos, 0);
   writeDisplayPos(":", 11 + pos, 0);
   writeDisplayPos(uint_to_char(time_elapsed.second), 12 + pos, 0);
}

void print_Date(int pos){

  
   //writeDisplayPos("Time: ", 0 + pos, 0);
   writeDisplayPos(uint_to_char(time_elapsed.day), 99 + pos, 0);
   writeDisplayPos("/", 101 + pos, 0);
   writeDisplayPos(uint_to_char(time_elapsed.month), 103 + pos, 0);
   writeDisplayPos("/", 104 + pos, 0);
   writeDisplayPos(uint_to_char(time_elapsed.year), 105 + pos, 0);
}

void print_TempStats(int i){
   
   int doffset = 4;
   writeDisplayPos("Recorded: ", 54 - doffset, 0);
   writeDisplayPos(uint_to_char(getWeeklyStats(i).date.day), 56 + doffset, 0);
   writeDisplayPos("/", 58 + doffset, 0);
   writeDisplayPos(uint_to_char(getWeeklyStats(i).date.month), 60 + doffset, 0);
   writeDisplayPos("/", 61 + doffset, 0);
   writeDisplayPos(uint_to_char(getWeeklyStats(i).date.year), 62 + doffset, 0);
   
   writeDisplayPos("Average: ", 128, 0);
   writeDisplayPos(float_to_char(getWeeklyStats(i).avg), 138, 0);
   writeDisplayPos(" C", 146, 0);
   
   writeDisplayPos("Variance: ", 168, 0);
   writeDisplayPos(float_to_char(getWeeklyStats(i).var), 178, 0);
   writeDisplayPos(" C", 186, 0);
   
   writeDisplayPos("Max: ", 208, 0);
   writeDisplayPos(float_to_char(getWeeklyStats(i).max), 218, 0);
   writeDisplayPos(" C", 226, 0);
   
   writeDisplayPos("[", 231, 0);
   writeDisplayPos(uint_to_char(getWeeklyStats(i).maxTime.hour), 232, 0);
   writeDisplayPos(":", 234, 0);
   writeDisplayPos(uint_to_char(getWeeklyStats(i).maxTime.minute), 235, 0);
   writeDisplayPos("]", 237, 0);
   
   writeDisplayPos("Min: ", 248, 0);
   writeDisplayPos(float_to_char(getWeeklyStats(i).min), 2, 1);
   writeDisplayPos(" C", 10, 1);
   
   writeDisplayPos("[", 15, 1);
   writeDisplayPos(uint_to_char(getWeeklyStats(i).minTime.hour), 16, 1);
   writeDisplayPos(":", 18, 1);
   writeDisplayPos(uint_to_char(getWeeklyStats(i).minTime.minute), 19, 1);
   writeDisplayPos("]", 21, 1);
   
   

}


