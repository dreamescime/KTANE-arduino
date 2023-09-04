#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <U8g2lib.h>

#define Adresse_esclave           59 //numéro d'adresse esclave de ce module (ne pas mettre 2 identiques)

#define PIXEL_PIN_Led_RGB         2
#define PIXEL_COUNT_Led_RGB       1
Adafruit_NeoPixel stripRGB(PIXEL_COUNT_Led_RGB, PIXEL_PIN_Led_RGB, NEO_GRB + NEO_KHZ800);


#define BP_1          3
#define BP_2          4
#define BP_3          5
#define BP_4          6

U8G2_ST7920_128X64_1_SW_SPI u8g2(U8G2_R0, /* clock=*/ 13, /* data=*/ 11, /* CS=*/ 10, /* reset=*/ 8);
/* PIN CONNECTIONS: 
 * 
 * BLK        GND
 * BLA        3.3V
 * PSB        GND
 * E (SCK)    13
 * RW (MOSI)  11
 * RS (CS)    10
 * 
 * VCC        5V
 * GND        GND
 * 
*/

bool reussite = false;
byte ligne = 0;
byte colonne[7] = {0, 1, 2, 3, 4, 5, 6};
byte ordre_symbole[4];
byte ordre = 0;

const unsigned char 101_ [] PROGMEM = { // '101-Copyright', 32x32px
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xc0, 0x00, 0x00, 0x0e, 0x38, 0x00, 
	0x00, 0x10, 0x06, 0x00, 0x00, 0x20, 0x03, 0x00, 0x00, 0x41, 0xe1, 0x80, 0x00, 0x87, 0x38, 0x80, 
	0x00, 0x8c, 0x18, 0xc0, 0x01, 0x9c, 0x10, 0x40, 0x01, 0x18, 0x00, 0x40, 0x01, 0x18, 0x00, 0x40, 
	0x01, 0x18, 0x00, 0x40, 0x01, 0x18, 0x00, 0x40, 0x01, 0x1c, 0x10, 0x40, 0x00, 0x8c, 0x18, 0xc0, 
	0x00, 0x87, 0x38, 0x80, 0x00, 0x43, 0xf1, 0x00, 0x00, 0x20, 0x03, 0x00, 0x00, 0x10, 0x06, 0x00, 
	0x00, 0x0e, 0x38, 0x00, 0x00, 0x01, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const unsigned char 102_ [] PROGMEM = { // '102-EtoileNoir', 32x32px
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x01, 0x80, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x03, 0xc0, 0x00, 
	0x00, 0x03, 0xc0, 0x00, 0x00, 0x07, 0xc0, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x7f, 0xfe, 0x00, 
	0x00, 0x3f, 0xfc, 0x00, 0x00, 0x0f, 0xf0, 0x00, 0x00, 0x0f, 0xf0, 0x00, 0x00, 0x0f, 0xf0, 0x00, 
	0x00, 0x1f, 0xf0, 0x00, 0x00, 0x1e, 0x78, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x30, 0x08, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const unsigned char 103_ [] PROGMEM = { // '103-EtoileBlanche', 32x32px
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 
	0x00, 0x00, 0x80, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x00, 0x40, 0x00, 
	0x00, 0x02, 0x00, 0x00, 0x00, 0xfe, 0x3f, 0x80, 0x00, 0x80, 0x01, 0x80, 0x00, 0x20, 0x02, 0x00, 
	0x00, 0x10, 0x04, 0x00, 0x00, 0x08, 0x10, 0x00, 0x00, 0x08, 0x10, 0x00, 0x00, 0x08, 0x08, 0x00, 
	0x00, 0x09, 0xc8, 0x00, 0x00, 0x12, 0x20, 0x00, 0x00, 0x18, 0x1c, 0x00, 0x00, 0x10, 0x04, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const unsigned char 104_ [] PROGMEM = { // '104-Smiley', 32x32px
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0xc0, 0x00, 
	0x00, 0x04, 0x80, 0xc0, 0x03, 0x80, 0x00, 0xc0, 0x03, 0x00, 0x00, 0xc0, 0x03, 0x00, 0x01, 0xc0, 
	0x03, 0x00, 0x01, 0x80, 0x03, 0x80, 0x07, 0x80, 0x01, 0xf1, 0xff, 0x00, 0x00, 0xff, 0xfc, 0x00, 
	0x00, 0x1f, 0xc0, 0x00, 0x00, 0x06, 0xc0, 0x00, 0x00, 0x04, 0x40, 0x00, 0x00, 0x07, 0xc0, 0x00, 
	0x00, 0x03, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const unsigned char 105_ [] PROGMEM = { // '105-DoubleK', 32x32px
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x03, 0xc7, 0xf1, 0xe0, 0x03, 0xe1, 0xc3, 0xe0, 0x00, 0x31, 0xc2, 0x00, 0x00, 0x11, 0xc6, 0x00, 
	0x00, 0x11, 0xc4, 0x00, 0x00, 0x19, 0xc4, 0x00, 0x00, 0x09, 0xcc, 0x00, 0x00, 0x0d, 0xd8, 0x00, 
	0x00, 0x07, 0xf8, 0x00, 0x00, 0x1d, 0xdc, 0x00, 0x00, 0x19, 0xce, 0x00, 0x00, 0x39, 0xc6, 0x00, 
	0x00, 0x71, 0xc7, 0x00, 0x00, 0x61, 0xc3, 0x80, 0x00, 0xe1, 0xc3, 0x80, 0x03, 0xc3, 0xe1, 0xe0, 
	0x03, 0xc3, 0xf0, 0xf0, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x30, 
	0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const unsigned char 106_ [] PROGMEM = { // '106-Omega', 32x32px
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x1c, 0x38, 0x00, 0x00, 0x70, 0x1c, 0x00, 0x00, 0xe0, 0x0e, 0x00, 0x00, 0xc0, 0x07, 0x00, 
	0x01, 0xc0, 0x07, 0x00, 0x01, 0xc0, 0x03, 0x00, 0x01, 0xc0, 0x03, 0x00, 0x01, 0xc0, 0x03, 0x00, 
	0x01, 0xc0, 0x03, 0x00, 0x00, 0xc0, 0x07, 0x00, 0x00, 0xe0, 0x0e, 0x00, 0x00, 0x70, 0x1c, 0x00, 
	0x00, 0x1c, 0x38, 0x00, 0x00, 0x04, 0x40, 0x00, 0x01, 0x84, 0x41, 0x00, 0x01, 0xfc, 0x7f, 0x00, 
	0x01, 0xfc, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const unsigned char 107_ [] PROGMEM = { // '107-SquidGame', 32x32px
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x1f, 0xff, 0xe0, 0x07, 0x0f, 0xff, 0xc0, 
	0x07, 0x0e, 0x03, 0x80, 0x07, 0x07, 0x03, 0x80, 0x07, 0x03, 0x07, 0x00, 0x07, 0x03, 0x87, 0x00, 
	0x07, 0x01, 0xce, 0x00, 0x07, 0xff, 0xce, 0x00, 0x07, 0xff, 0xfc, 0x00, 0x07, 0xff, 0xfc, 0x00, 
	0x07, 0x03, 0xff, 0x00, 0x07, 0x07, 0x33, 0x80, 0x07, 0x0e, 0x31, 0xc0, 0x07, 0x1c, 0x30, 0xc0, 
	0x07, 0x1c, 0x30, 0xe0, 0x07, 0x18, 0x30, 0xe0, 0x07, 0x18, 0x30, 0x60, 0x07, 0x38, 0x30, 0x60, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const unsigned char 108_ [] PROGMEM = { // '108-Cul', 32x32px
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 
	0x00, 0x07, 0xf0, 0x00, 0x00, 0x0e, 0x18, 0x00, 0x00, 0x08, 0x08, 0x00, 0x00, 0x01, 0xc0, 0x00, 
	0x00, 0x01, 0xc0, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x03, 0x01, 0x80, 0x40, 0x07, 0x01, 0x00, 0xe0, 
	0x06, 0x00, 0x00, 0x70, 0x0e, 0x00, 0x00, 0x30, 0x0e, 0x00, 0x00, 0x38, 0x0c, 0x00, 0x00, 0x38, 
	0x1c, 0x00, 0x00, 0x18, 0x1c, 0x00, 0x00, 0x18, 0x1c, 0x00, 0x00, 0x1c, 0x1c, 0x00, 0x00, 0x1c, 
	0x1c, 0x00, 0x00, 0x1c, 0x1c, 0x03, 0xe0, 0x1c, 0x1c, 0x0f, 0xf0, 0x18, 0x1e, 0x3f, 0xfc, 0x78, 
	0x0f, 0xfc, 0x1f, 0xf8, 0x07, 0xf0, 0x07, 0xf0, 0x03, 0xc0, 0x03, 0xe0, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const unsigned char 109_ [] PROGMEM = { // '109-Hvirgule', 32x32px
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x02, 0x00, 
	0x00, 0x3e, 0x0e, 0x00, 0x00, 0x26, 0x1e, 0x00, 0x00, 0x07, 0x1c, 0x00, 0x00, 0x03, 0x38, 0x00, 
	0x00, 0x03, 0x70, 0x00, 0x00, 0x07, 0xe0, 0x00, 0x00, 0x07, 0xe0, 0x00, 0x00, 0x0f, 0x60, 0x00, 
	0x00, 0x1e, 0x60, 0x00, 0x00, 0x1c, 0x60, 0x00, 0x00, 0x38, 0x60, 0x00, 0x00, 0x78, 0x3e, 0x00, 
	0x00, 0x60, 0x1c, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x1c, 0x00, 
	0x00, 0x00, 0xf8, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const unsigned char 110_ [] PROGMEM = { // '110-Six', 32x32px
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0x00, 0x00, 0x0f, 0xfe, 0x00, 
	0x00, 0x1c, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x31, 0xe0, 0x00, 0x00, 0x37, 0xf8, 0x00, 
	0x00, 0x7e, 0x3c, 0x00, 0x00, 0x78, 0x0e, 0x00, 0x00, 0x70, 0x0e, 0x00, 0x00, 0x70, 0x07, 0x00, 
	0x00, 0x70, 0x07, 0x00, 0x00, 0x70, 0x07, 0x00, 0x00, 0x70, 0x07, 0x00, 0x00, 0x70, 0x07, 0x00, 
	0x00, 0x30, 0x0e, 0x00, 0x00, 0x38, 0x0e, 0x00, 0x00, 0x1e, 0x3c, 0x00, 0x00, 0x0f, 0xf8, 0x00, 
	0x00, 0x01, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const unsigned char 111_ [] PROGMEM = { // '111-Nalenvers', 32x32px
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 
	0x00, 0x0e, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x0c, 0x06, 0x00, 
	0x00, 0x0c, 0x1c, 0x00, 0x00, 0x0c, 0x7c, 0x00, 0x00, 0x1d, 0xfc, 0x00, 0x00, 0x1f, 0x98, 0x00, 
	0x00, 0x1e, 0x18, 0x00, 0x00, 0x38, 0x38, 0x00, 0x00, 0x20, 0x30, 0x00, 0x00, 0x00, 0x30, 0x00, 
	0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x1c, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const unsigned char 112_ [] PROGMEM = { // '112-AT', 32x32px
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x03, 0xc0, 0x00, 
	0x00, 0x03, 0xe0, 0x00, 0x00, 0x07, 0xe0, 0x00, 0x00, 0x06, 0x70, 0x00, 0x00, 0x0e, 0x70, 0x00, 
	0x00, 0x0c, 0x38, 0x00, 0x00, 0x1c, 0x38, 0x00, 0x00, 0x18, 0x1c, 0x00, 0x00, 0x38, 0x1c, 0x00, 
	0x00, 0x3f, 0xfe, 0x00, 0x00, 0x7f, 0xfe, 0x00, 0x00, 0xe1, 0x87, 0x00, 0x00, 0xe1, 0x83, 0x00, 
	0x01, 0xc1, 0x83, 0x80, 0x01, 0xc1, 0x81, 0x80, 0x03, 0x81, 0x81, 0xc0, 0x03, 0x81, 0x80, 0xc0, 
	0x03, 0x01, 0x80, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const unsigned char 113_ [] PROGMEM = { // '113-AdansE', 32x32px
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x1c, 0x00, 0x00, 0x3f, 0xfe, 0x00, 0x00, 0x61, 0xc7, 0x00, 
	0x00, 0x61, 0x83, 0x00, 0x00, 0x01, 0x83, 0x00, 0x00, 0x07, 0xff, 0x00, 0x00, 0x39, 0x80, 0x00, 
	0x00, 0x61, 0x80, 0x00, 0x00, 0xe1, 0x80, 0x00, 0x00, 0xc1, 0x80, 0x00, 0x00, 0xe1, 0xc1, 0x00, 
	0x00, 0x7e, 0xff, 0x00, 0x00, 0x38, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const unsigned char 114_ [] PROGMEM = { // '114-Troisfondu', 32x32px
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x80, 0x00, 0x00, 0x71, 0xe0, 0x00, 0x00, 0x60, 0x60, 0x00, 
	0x00, 0x60, 0x70, 0x00, 0x00, 0x60, 0x70, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x60, 0x00, 
	0x00, 0x01, 0xc0, 0x00, 0x00, 0x07, 0x80, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x70, 0x00, 
	0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x38, 0x00, 
	0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x06, 0x00, 
	0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const unsigned char 115_ [] PROGMEM = { // '115-E2points', 32x32px
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x06, 0x30, 0x00, 
	0x00, 0x06, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x3f, 0xf0, 0x00, 0x00, 0x30, 0x38, 0x00, 0x00, 0x30, 0x1c, 0x00, 0x00, 0x30, 0x0e, 0x00, 
	0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x01, 0xff, 0x00, 
	0x00, 0x03, 0xff, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x06, 0x00, 
	0x00, 0x30, 0x0e, 0x00, 0x00, 0x30, 0x0c, 0x00, 0x00, 0x30, 0x18, 0x00, 0x00, 0x38, 0x70, 0x00, 
	0x00, 0x1f, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const unsigned char 116_ [] PROGMEM = { // '116-Nchapeau', 32x32px
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x30, 0x00, 
	0x00, 0x06, 0x30, 0x00, 0x00, 0x02, 0x30, 0x00, 0x00, 0x01, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x7e, 0x1f, 0x80, 0x00, 0x38, 0x0e, 0x00, 0x00, 0x38, 0x0e, 0x00, 
	0x00, 0x38, 0x1e, 0x00, 0x00, 0x38, 0x3e, 0x00, 0x00, 0x38, 0x2e, 0x00, 0x00, 0x38, 0x6e, 0x00, 
	0x00, 0x38, 0xce, 0x00, 0x00, 0x39, 0x8e, 0x00, 0x00, 0x3b, 0x0e, 0x00, 0x00, 0x3e, 0x0e, 0x00, 
	0x00, 0x3e, 0x0e, 0x00, 0x00, 0x3c, 0x0e, 0x00, 0x00, 0x38, 0x0e, 0x00, 0x00, 0x38, 0x0e, 0x00, 
	0x00, 0x7e, 0x1f, 0x80, 0x00, 0x7e, 0x1f, 0x80, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x03, 0x00, 
	0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const unsigned char 117_ [] PROGMEM = { // '117-3Serprent', 32x32px
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x38, 0x00, 0x00, 0x06, 0x20, 0x00, 0x00, 0x02, 0x60, 0x00, 
	0x00, 0x03, 0x40, 0x00, 0x00, 0x01, 0xc0, 0x00, 0x00, 0x0f, 0xf0, 0x00, 0x00, 0x0f, 0xf8, 0x00, 
	0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0xf0, 0x00, 
	0x00, 0x03, 0xe0, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x1c, 0x00, 
	0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x0f, 0xf0, 0x00, 0x00, 0x1f, 0xe0, 0x00, 
	0x00, 0x18, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x18, 0x60, 0x00, 0x00, 0x0f, 0xf0, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const unsigned char 118_ [] PROGMEM = { // '118-Pointdinterogation', 32x32px
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 
	0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x01, 0xc0, 0x00, 
	0x00, 0x03, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 
	0x00, 0x0e, 0x08, 0x00, 0x00, 0x06, 0x1c, 0x00, 0x00, 0x07, 0x18, 0x00, 0x00, 0x01, 0xf8, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const unsigned char 119_ [] PROGMEM = { // '119-Paragraph', 32x32px
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x07, 0xfc, 0x00, 
	0x00, 0x0f, 0xd8, 0x00, 0x00, 0x0f, 0xd8, 0x00, 0x00, 0x0f, 0xd8, 0x00, 0x00, 0x1f, 0xd8, 0x00, 
	0x00, 0x0f, 0xd8, 0x00, 0x00, 0x0f, 0xd8, 0x00, 0x00, 0x0f, 0xd8, 0x00, 0x00, 0x03, 0xd8, 0x00, 
	0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x18, 0x00, 
	0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x18, 0x00, 
	0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const unsigned char 120_ [] PROGMEM = { // '120-Cdroit', 32x32px
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xf8, 0x00, 0x00, 0x0f, 0xfe, 0x00, 
	0x00, 0x1c, 0x06, 0x00, 0x00, 0x38, 0x02, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 
	0x00, 0x60, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0xe0, 0xe0, 0x00, 0x00, 0xe0, 0xe0, 0x00, 
	0x00, 0xe0, 0xe0, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 
	0x00, 0x38, 0x00, 0x00, 0x00, 0x3c, 0x06, 0x00, 0x00, 0x1f, 0x1e, 0x00, 0x00, 0x07, 0xfc, 0x00, 
	0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const unsigned char 121_ [] PROGMEM = { // '121-Cgauche', 32x32px
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xc0, 0x00, 0x00, 0x7f, 0xf0, 0x00, 
	0x00, 0xe0, 0x78, 0x00, 0x00, 0x80, 0x1c, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x0e, 0x00, 
	0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x0e, 0x0e, 0x00, 0x00, 0x0e, 0x0e, 0x00, 
	0x00, 0x0e, 0x0e, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x0c, 0x00, 
	0x00, 0x00, 0x1c, 0x00, 0x00, 0xc0, 0x38, 0x00, 0x00, 0xf9, 0xf0, 0x00, 0x00, 0x7f, 0xe0, 0x00, 
	0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const unsigned char 122_ [] PROGMEM = { // '122-Fourche', 32x32px
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x07, 0xe0, 0x00, 0x00, 0xc1, 0xc1, 0x80, 0x00, 0xc1, 0xc1, 0x80, 0x00, 0xc1, 0xc1, 0x80, 
	0x00, 0xc1, 0xc1, 0x80, 0x00, 0xc1, 0xc3, 0x80, 0x00, 0xc1, 0xc3, 0x80, 0x00, 0xe1, 0xc3, 0x80, 
	0x00, 0xe1, 0xc3, 0x00, 0x00, 0x61, 0xc3, 0x00, 0x00, 0x31, 0xc6, 0x00, 0x00, 0x0f, 0xf8, 0x00, 
	0x00, 0x01, 0xc0, 0x00, 0x00, 0x01, 0xc0, 0x00, 0x00, 0x01, 0xc0, 0x00, 0x00, 0x01, 0xc0, 0x00, 
	0x00, 0x07, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const unsigned char 123_ [] PROGMEM = { // '123-Infogramme', 32x32px
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x0f, 0x00, 0x00, 0x00, 0x1c, 0x3c, 0x00, 0x00, 0x30, 0x66, 0x00, 0x00, 0x70, 0xc7, 0x00, 
	0x00, 0xe1, 0xc3, 0x00, 0x00, 0xe1, 0xc3, 0x80, 0x00, 0xe1, 0xc3, 0x80, 0x00, 0xc1, 0xc3, 0x80, 
	0x00, 0xc1, 0xc3, 0x80, 0x00, 0xc1, 0xc3, 0x80, 0x00, 0xe1, 0xc3, 0x80, 0x00, 0xe1, 0xc3, 0x80, 
	0x00, 0x61, 0xe7, 0x00, 0x00, 0x70, 0xe7, 0x00, 0x00, 0x38, 0x7e, 0x00, 0x00, 0x1c, 0x7c, 0xc0, 
	0x00, 0x07, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const unsigned char 124_ [] PROGMEM = { // '124-CroixLorraine', 32x32px
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x10, 0x00, 0x00, 0x06, 0x3c, 0x00, 0x00, 0x0f, 0x3c, 0x00, 0x00, 0x0f, 0xf8, 0x00, 
	0x00, 0x0f, 0xf8, 0x00, 0x00, 0x03, 0xf8, 0x00, 0x00, 0x01, 0xfe, 0x00, 0x00, 0x01, 0xff, 0x00, 
	0x00, 0x73, 0xdf, 0x00, 0x00, 0xff, 0xc6, 0x00, 0x00, 0xff, 0x80, 0x00, 0x00, 0x7f, 0x80, 0x00, 
	0x00, 0x1f, 0xe0, 0x00, 0x00, 0x1f, 0xf0, 0x00, 0x00, 0x1f, 0xf0, 0x00, 0x00, 0x3c, 0xf0, 0x00, 
	0x00, 0x3c, 0x20, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const unsigned char 125_ [] PROGMEM = { // '125-Balon', 32x32px
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xf0, 0x00, 0x00, 0x1f, 0xfc, 0x00, 0x00, 0x38, 0x1e, 0x00, 
	0x00, 0x70, 0x0e, 0x00, 0x00, 0xe0, 0x07, 0x00, 0x00, 0xe0, 0x03, 0x00, 0x00, 0xe0, 0x03, 0x80, 
	0x00, 0xc0, 0x03, 0x80, 0x00, 0xc0, 0x03, 0x80, 0x00, 0xc0, 0x03, 0x80, 0x00, 0xc0, 0x03, 0x80, 
	0x00, 0xe0, 0x03, 0x80, 0x00, 0xe0, 0x03, 0x00, 0x00, 0xe0, 0x07, 0x00, 0x00, 0x70, 0x0e, 0x00, 
	0x00, 0x38, 0x1e, 0x00, 0x00, 0x1f, 0xfc, 0x00, 0x00, 0x0f, 0xf0, 0x00, 0x00, 0x01, 0xc0, 0x00, 
	0x00, 0x01, 0xc0, 0x00, 0x00, 0x01, 0xc0, 0x00, 0x00, 0x01, 0xc0, 0x00, 0x00, 0x01, 0xc0, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const unsigned char 126_ [] PROGMEM = { // '126-Ytete', 32x32px
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x3e, 0x40, 0x00, 0x00, 0x33, 0xc0, 0x00, 0x00, 0x33, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 
	0x00, 0x0d, 0x80, 0x00, 0x00, 0x09, 0x80, 0x00, 0x00, 0x01, 0xc0, 0x00, 0x00, 0x03, 0xc0, 0x00, 
	0x00, 0x03, 0x40, 0x00, 0x00, 0x07, 0x60, 0x00, 0x00, 0x06, 0x20, 0x00, 0x00, 0x0e, 0x30, 0x00, 
	0x00, 0x0c, 0x30, 0x00, 0x00, 0x1c, 0x11, 0x80, 0x00, 0x18, 0x19, 0x80, 0x00, 0x30, 0x0f, 0x80, 
	0x00, 0x30, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const unsigned char 127_ [] PROGMEM = { // '127-BT', 32x32px
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x3f, 0xc0, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0xff, 0xf0, 0x00, 
	0x00, 0xff, 0xf0, 0x00, 0x00, 0xcf, 0x30, 0x00, 0x00, 0x8f, 0x30, 0x00, 0x00, 0x0f, 0x00, 0x00, 
	0x00, 0x0f, 0xfc, 0x00, 0x00, 0x0f, 0xff, 0x00, 0x00, 0x0f, 0x07, 0x80, 0x00, 0x0f, 0x07, 0x80, 
	0x00, 0x0f, 0x03, 0x80, 0x00, 0x0f, 0x03, 0x80, 0x00, 0x0f, 0x03, 0x80, 0x00, 0x0f, 0x07, 0x80, 
	0x00, 0x0f, 0x1f, 0x00, 0x00, 0x3f, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const char symbole[6][7] = {
{125, 112, 126, 111, 107, 109, 121},
{115, 125, 121, 123, 103, 109, 118},
{101, 108, 123, 105, 114, 126, 103},
{110, 119, 127, 107, 105, 118, 104},
{122, 104, 127, 120, 119, 117, 102},
{110, 115, 124, 113, 122, 116, 106}};

byte symbole_1 = 0;

void initialisation() {
  randomSeed(millis());
      for (int h = 0; h < 500; h++) { //mellange la premiere ligne
        int i = random(0, 7); 
        int j = random(0, 7);
        int swap = colonne[i];
        colonne[i] = colonne[j];
        colonne[j] = swap;}
  ligne = random(0, 6);

  //afficher les symboles 
  /*en premier : symbole[ligne][colonne[0]]
  
  
  
  */
	ordre = 1;
	for (int j = 0; j < 7; j++) {
		for (int i = 0; i < 4; i++) {
			if (symbole[ligne][j] == symbole[ligne][colonne[i]]) { ordre_symbole[i] = ordre; ordre ++;}
		}
	}
	Serial.println("les symboles sont : ");
	Serial.print(symbole[ligne][colonne[0]]); Serial.print("    ");
	Serial.print(symbole[ligne][colonne[1]]); Serial.print("    ");
	Serial.print(symbole[ligne][colonne[2]]); Serial.print("    ");
	Serial.print(symbole[ligne][colonne[3]]); Serial.println("");
	
	Serial.print("l'ordre est :");
	Serial.print(ordre_symbole[0]); Serial.print("    ");
	Serial.print(ordre_symbole[1]); Serial.print("    ");
	Serial.print(ordre_symbole[2]); Serial.print("    ");
	Serial.print(ordre_symbole[3]); Serial.println("");

	dessine(symbole[ligne][colonne[0]],  1, 20);
	dessine(symbole[ligne][colonne[1]], 33, 20);
	dessine(symbole[ligne][colonne[2]], 65, 20);
	dessine(symbole[ligne][colonne[3]], 97, 20);
}

void dessine(byte val, int x, int y) {
	if (val == 101) u8g2.drawXBM(x, y, 32, 32, 101_);
	if (val == 102) u8g2.drawXBM(x, y, 32, 32, 102_);
	if (val == 103) u8g2.drawXBM(x, y, 32, 32, 103_);
	if (val == 104) u8g2.drawXBM(x, y, 32, 32, 104_);
	if (val == 105) u8g2.drawXBM(x, y, 32, 32, 105_);
	if (val == 106) u8g2.drawXBM(x, y, 32, 32, 106_);
	if (val == 107) u8g2.drawXBM(x, y, 32, 32, 107_);
	if (val == 108) u8g2.drawXBM(x, y, 32, 32, 108_);
	if (val == 109) u8g2.drawXBM(x, y, 32, 32, 109_);
	if (val == 110) u8g2.drawXBM(x, y, 32, 32, 110_);
	if (val == 111) u8g2.drawXBM(x, y, 32, 32, 111_);
	if (val == 112) u8g2.drawXBM(x, y, 32, 32, 112_);
	if (val == 113) u8g2.drawXBM(x, y, 32, 32, 113_);
	if (val == 114) u8g2.drawXBM(x, y, 32, 32, 114_);
	if (val == 115) u8g2.drawXBM(x, y, 32, 32, 115_);
	if (val == 116) u8g2.drawXBM(x, y, 32, 32, 116_);
	if (val == 117) u8g2.drawXBM(x, y, 32, 32, 117_);
	if (val == 118) u8g2.drawXBM(x, y, 32, 32, 118_);
	if (val == 119) u8g2.drawXBM(x, y, 32, 32, 119_);
	if (val == 120) u8g2.drawXBM(x, y, 32, 32, 120_);
	if (val == 121) u8g2.drawXBM(x, y, 32, 32, 121_);
	if (val == 122) u8g2.drawXBM(x, y, 32, 32, 122_);
	if (val == 123) u8g2.drawXBM(x, y, 32, 32, 123_);
	if (val == 124) u8g2.drawXBM(x, y, 32, 32, 124_);
	if (val == 125) u8g2.drawXBM(x, y, 32, 32, 125_);
	if (val == 126) u8g2.drawXBM(x, y, 32, 32, 126_);
	if (val == 127) u8g2.drawXBM(x, y, 32, 32, 127_);
}

void get_Symboles(){
    int flag = 0;
    reussite = false;
    for(int i = 0; i < 4; i++){
        flag = 0;
        while (flag == 0){
            bouton_appuye = BP_Appuye();
            if (bouton_appuye == ordre_symbole[i]){
                flag = 1;
            }
            if (bouton_appuye != ordre_symbole[i]  &&  bouton_appuye != 0){
                return;
            }
        }
    }
    reussite = true;
}

int BP_Appuye() { //fonction qui donne une valeur pour le BP appuyé
    int nombre_appuye = 0;
    kval = 0;
    if (digitalRead(BP_1) == LOW) {
        kval = 1;
        nombre_appuye++;}
    if (digitalRead(BP_2) == LOW) {
        kval = 2;
        nombre_appuye++;}
    if (digitalRead(BP_3) == LOW) {
        kval = 3;
        nombre_appuye++;}
    if (digitalRead(BP_4) == LOW) {
        kval = 4;
        nombre_appuye++;}
    if (nombre_appuye > 1){ //si plusieurs BP sont appuyé, on renvoie 26 (erreur)
        return 5;}
        else if (kval_old == kval) { //si BP identique au précédent resultat, on renvois 0
            return 0;}
            else{kval_old = kval; // sinon on renvoie la valeur du BP appuyé
                return kval;}
}

void setup() {
  Wire.begin(Adresse_esclave);
  stripRGB.begin();
  stripRGB.show();
  initialisation();
}

void loop() {
	if (
}
