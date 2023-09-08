#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <U8g2lib.h>

#define Num_Module 26

#define PIXEL_PIN_Led_RGB         2
#define PIXEL_COUNT_Led_RGB       1
Adafruit_NeoPixel stripRGB(PIXEL_COUNT_Led_RGB, PIXEL_PIN_Led_RGB, NEO_GRB + NEO_KHZ800);

#define BP_1          3

uint8_t Recep[5];
byte Numero_de_serie = 0;
byte Nb_Batteries = 0;
byte Port = 0;
byte Nb_Erreur = 0;
byte Indicateur = 0;
uint8_t Strike = 0;
uint8_t Module_fini = 0;

void setup() {
	Wire.begin(Num_Module);                // join i2c bus with address ...
	Wire.onRequest(requestEvent); // register event
	Wire.onReceive(receiveEvent); // register event
	Serial.begin(9600);
	Serial.println("\n Module Jeu de Mot KTANE");
	u8g2.begin();
}

void loop() {

}

void requestEvent() {
  Wire.write(Strike);
  Wire.write(Module_fini);
  Strike = 0;
}

void receiveEvent(int howMany) {
  for (int i = 0; i = 5; i++) {
    int c = Wire.read();
    Recep[i] = c;
  }
  Numero_de_serie = Recep[0];
  Nb_Batteries = Recep[1];
  Port = Recep[2];
  Nb_Erreur = Recep[3];
  Indicateur = Recep[4];
}
