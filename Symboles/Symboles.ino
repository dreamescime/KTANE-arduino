#include <Adafruit_NeoPixel.h>

#define PIXEL_PIN_Led_RGB         2
#define PIXEL_COUNT_Led_RGB       1
Adafruit_NeoPixel stripRGB(PIXEL_COUNT_Led_RGB, PIXEL_PIN_Led_RGB, NEO_GRB + NEO_KHZ800);


#define BP_1          3
#define BP_2          4
#define BP_3          5
#define BP_4          6

U8G2_ST7920_128X64_1_SW_SPI u8g2(U8G2_R0, /* clock=*/ 13, /* data=*/ 11, /* CS=*/ 10, /* reset=*/ 8);

byte ligne = 0;
byte colonne[7] = {0, 1, 2, 3, 4, 5, 6};
const byte symbole[6][7] = {
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
  */en premier : symbole[ligne][colonne[1]]
}
