#include <Adafruit_NeoPixel.h>

#define PIXEL_PIN_Led_RGB         2
#define PIXEL_COUNT_Led_RGB       1
Adafruit_NeoPixel stripRGB(PIXEL_COUNT_Led_RGB, PIXEL_PIN_Led_RGB, NEO_GRB + NEO_KHZ800);
