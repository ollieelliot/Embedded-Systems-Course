#ifndef LED
#define LED

extern char readLed;
extern int time_led;
extern int toggle_Blink;

//DEFINE REGISTERS
#define AT91C_PIOD_AIMER (AT91_CAST(AT91_REG *) 0x400E14B0)
#define AT91C_PIOD_DIFSR (AT91_CAST(AT91_REG *) 0x400E1484)
#define AT91C_PIOD_SCDR (AT91_CAST(AT91_REG *) 0x400E148C)

#define AT91C_PIOC_AIMER (AT91_CAST(AT91_REG *) 0x400E12B0)
#define AT91C_PIOC_DIFSR (AT91_CAST(AT91_REG *) 0x400E1284)
#define AT91C_PIOC_SCDR (AT91_CAST(AT91_REG *) 0x400E128C)

void setLed();
void SysTick_Handler();
void blinkLed();
void SysTick_Setup();
void PIOD_Handler();
void toggleBlinkLed_setup();

#endif


