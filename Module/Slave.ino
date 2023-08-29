#include <Wire.h>

#define Num_Module 14

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
}

void loop() {
  // put your main code here, to run repeatedly:

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
