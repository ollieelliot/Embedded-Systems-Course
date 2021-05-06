#ifndef KEYPAD
#define KEYPAD

extern char keys[4][3];

void init_Keypad();
char read_Keypad();
void Keypad_Interrupt_setup();

#endif


