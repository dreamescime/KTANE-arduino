#include <Wire.h>

#define Num_Module 14

uint8_t Buffer[5];

byte Numero_de_serie = 0;
byte Nb_Batteries = 0;
byte Port = 0;
byte Nb_Erreur = 0;
byte Indicateur = 0;

uint8_t Strike = 0;

void setup() {
Wire.begin(Num_Module);                // join i2c bus with address ...
Wire.onRequest(requestEvent); // register event
Wire.onReceive(receiveEvent); // register event
}

void loop() {
  // put your main code here, to run repeatedly:

}

void requestEvent()
{
  Wire.write(Strike);
  Strike = 0;
}

void receiveEvent(int howMany) {
  for (int i = 0; i = 5; i++) {
    int c = Wire.read();
    Buffer[i] = c;
  }
  Numero_de_serie = Buffer[0];
  Nb_Batteries = Buffer[1];
  Port = Buffer[2];
  Nb_Erreur = Buffer[3];
  Indicateur = Buffer[4];
}
