#include <Adafruit_NeoPixel.h>
#include <Wire.h>

// for SPI Communication
#include <SPI.h>
#include <PN532_SPI.h>
#include <PN532.h>
#include <NfcAdapter.h>

#define Num_Module           116 //numéro d'adresse esclave de ce module (ne pas mettre 2 identiques)

#define PIXEL_PIN_Led_RGB         2
#define PIXEL_COUNT_Led_RGB       1
Adafruit_NeoPixel stripRGB(PIXEL_COUNT_Led_RGB, PIXEL_PIN_Led_RGB, NEO_GRB + NEO_KHZ800);

PN532_SPI interface(SPI, 10); // create a PN532 SPI interface with the SPI CS terminal located at digital pin 10
NfcAdapter nfc = NfcAdapter(interface); // create an NFC adapter object


String UID = "00 00 00 00 00 00 00";
const String PORT_USB  = "1D C4 73 DB 93 00 00"; // a changer en fonction de vos tag NFC
const String PORT_USBC = "1D A6 73 DB 93 00 00"; // a changer en fonction de vos tag NFC
const String PORT_ETH  = "1D B4 73 DB 93 00 00"; // a changer en fonction de vos tag NFC
const String PORT_HDMI = "1D B3 73 DB 93 00 00"; // a changer en fonction de vos tag NFC
const String PORT_JACK = "1D A8 73 DB 93 00 00"; // a changer en fonction de vos tag NFC
const String PORT_RCA  = "1D AA 73 DB 93 00 00"; // a changer en fonction de vos tag NFC
const String PORT_PS2  = "1D A9 73 DB 93 00 00"; // a changer en fonction de vos tag NFC

int Recep[6];
int Numero_de_serie = 0;
int Nb_Batteries = 2;
int Port = 0;
int Nb_Erreur = 0;
int Indicateur = 0;
int Strike = 0;
int Module_fini = 0;
int Val_temps = 0;
int Val_temps_1 = 0;
int Val_temps_4 = 0;
int Val_temps_5 = 0;
int Demmarage = 0;

int Port_e = 0;
unsigned long millis_pause;

void setup(void) {
  Wire.begin(Num_Module);                // join i2c bus with address ...
  Wire.onReceive(onReceive);
  Wire.onRequest(onRequest);
  stripRGB.begin();
  stripRGB.setPixelColor(0, 150, 150, 150);         //  Set pixel's color (in RAM)
  stripRGB.show();
  Serial.begin(9600);
  Serial.println("\n Module PORT KTANE");
  
  nfc.begin();
}

void loop(void) {
  
  if (millis_pause < millis()) {
    millis_pause = millis() + 1000;
    if (nfc.tagPresent()) {
      Serial.println("\nScan a NFC tag\n");
      NfcTag tag = nfc.read();
      Serial.println(tag.getTagType());
      UID = tag.getUidString();
      Serial.print("UID: ");Serial.println(UID);
      Serial.print("Le port connecté est : ");
      if (PORT_HDMI == UID) {Serial.println("HDMI");      Port_e = 1; }
      if (PORT_USBC == UID) {Serial.println("USB C");     Port_e = 2; }
      if (PORT_USB  == UID) {Serial.println("USB");       Port_e = 3; }
      if (PORT_ETH  == UID) {Serial.println("Ethernet");  Port_e = 4; }
      if (PORT_PS2  == UID) {Serial.println("PS/2");      Port_e = 5; }
      if (PORT_RCA  == UID) {Serial.println("Mono RCA");  Port_e = 6; }
      if (PORT_JACK == UID) {Serial.println("Mini Jack"); Port_e = 7; }
    }
    else {
      Serial.println("...");
    }
  }

  if (Port_e != 0) {
    if (Port == Port_e) {
      Module_fini = 1;
      stripRGB.setPixelColor(0, 255, 0, 0);             //  Set pixel's color (in RAM)
      stripRGB.show(); 
    }
    else {
      Module_fini = 0;
      stripRGB.setPixelColor(0,   0, 255,   0);
      stripRGB.show();
    }
  }
  else {
    stripRGB.setPixelColor(0,   0,   0, 100);
    stripRGB.show();
  }
}

void onRequest() {
  Serial.print("onRequest : ");
  Wire.write(Strike);
  Wire.write(Module_fini);
  Wire.write(Port_e);
  Strike = 0;
}

void onReceive(int len){
  Serial.print("onReceive : ");
  int i = 0;
  while(Wire.available()){
    int c = Wire.read();
    Recep[i] = c;
    Serial.print(c);
    Serial.print(" ");
    i++;
  }
  Serial.println();
  Numero_de_serie = Recep[0];
  Nb_Batteries = Recep[1];
  Port = Recep[2];
  Nb_Erreur = Recep[3];
  Indicateur = Recep[4];
  Val_temps = Recep[5];
}
