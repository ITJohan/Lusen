// SysTick
#define STK_BASE		0xE000E010
#define STK_CTRL		((volatile unsigned int*) (STK_BASE))
#define STK_LOAD		((volatile unsigned int*) (STK_BASE+0x4))
#define STK_VAL			((volatile unsigned int*) (STK_BASE+0x8))

// GPIO
typedef struct {
	unsigned int	moder;
	unsigned short	otyper;
	unsigned short	otReserved;
	unsigned int	ospeedr;
	unsigned int	pupdr;
	unsigned char	idrLow;
	unsigned char	idrHigh;
	unsigned short	idrReserved;
	unsigned char	odrLow;
	unsigned char	odrHigh;
	unsigned short	odrReserved;
} GPIO;
#define GPIO_D 				((volatile GPIO*) 0x40020c00)		// Keypad
#define GPIO_E				((volatile GPIO*) 0x40021000)		// Display

/* Definiera bitar för de olika bitarna i styrregistret */
#define B_RS			0x01
#define B_RW			0x02
#define B_SELECT		0x04
#define B_CS1			0x08
#define B_CS2			0x10
#define B_RST			0x20
#define B_E				0x40

// Definition av kommandon till display, sänds via dataregister.
#define LCD_ON 			0x3F // Display on
#define LCD_OFF 		0x3E // Display off
#define LCD_SET_ADD 	0x40 // Set horizontal coordinate
#define LCD_SET_PAGE 	0xB8 // Set vertical coordinate
#define LCD_DISP_START 	0xC0 // Start address
#define LCD_BUSY 		0x80 // Read busy status

#define SIZE			2