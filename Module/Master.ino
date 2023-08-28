#include <Adafruit_NeoPixel.h>
#include <Wire.h>

#define PIXEL_PIN_Led_RGB         2
#define PIXEL_COUNT_Led_RGB       1

Adafruit_NeoPixel stripRGB(PIXEL_COUNT_Led_RGB, PIXEL_PIN_Led_RGB, NEO_GRB + NEO_KHZ800);

int nDevices = 0;
byte adresse_exist[127];
uint8_t Buffer[5];
uint8_t Recep[2];

byte Numero_de_serie = 0;
byte Nb_Batteries = 0;
byte Port = 0;
byte Nb_Erreur = 0;
byte Indicateur = 0;

byte Module_fini = 0;
byte Erreur_recu = 0;

void setup() {
  Wire.begin();
  stripRGB.begin();
  stripRGB.show();

  Serial.begin(9600);
//  while (!Serial); // Leonardo: wait for Serial Monitor
  Serial.println("\n Module Master KTANE");

  delay(5000);
  
  Serial.println("Scanning...");

  for (byte address = 1; address < 127; ++address) {
    Wire.beginTransmission(address);
    byte error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.print(address, HEX);
      Serial.println("  !");

      adresse_exist[nDevices] = address;

      ++nDevices;
    } else if (error == 4) {
      Serial.print("Unknown error at address 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.println(address, HEX);
    }
  }
  Buffer[0] = Numero_de_serie;
  Buffer[1] = Nb_Batteries;
  Buffer[2] = Port;
  Buffer[4] = Indicateur;
}

void loop() {
  Buffer[3] = Nb_Erreur;
  Erreur_recu = 0;
  Module_fini = 0;
  
  for (int i = 0; i = nDevices; i++) {
    Wire.beginTransmission(adresse_exist[i]);        // commence la transmition vers un esclave
    Wire.write(Buffer,5);                            // envoie les valeur du tableau
    Wire.endTransmission();                          // arrete la transmition
  }
  delay(100);
  for (int i = 0; i = nDevices; i++) {
    Wire.requestFrom(adresse_exist[i], 1);
    for (int j = 0; j = 2; j++) {
      int c = Wire.read();
      Recep[j] = c;
    }
    if (Recep[0] == 1) {
      Erreur_recu ++;
    }
    if (Recep[1] == 1= {
      Module_fini ++;
    }
  }
  if (Erreur_recu =! 0) {
    Nb_Erreur = Nb_Erreur + Erreur_recu;
    // emission_son(duree du bip)
  }
  if (Module_fini == nDevices) {
    // fin du jeu
  }
}
