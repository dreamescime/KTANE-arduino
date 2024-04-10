#include <GxEPD2_BW.h>
#include <GxEPD2_3C.h>
#include <GxEPD2_7C.h>
#include <Fonts/FreeMonoBold24pt7b.h>
#include <LedControl.h>
#include <FastLED.h>
#include "Wire.h"
#include <PN532_I2C.h>
#include <PN532.h>
#include <NfcAdapter.h>

#define MAX7219DIN  12
#define MAX7219CS   15
#define MAX7219CLK  13
#define PIXEL_PIN_Led_Erreur      2
#define PIXEL_COUNT_Led_Erreur    2

// +3.3V            Pile    Pile    Pile    Pile    Pile    Pile    Pile    0V
//      3.9kOhm     1kOhm   1kOhm   1kOhm   1kOhm   1kOhm   1kOhm   1kOhm
// les piles sont en série, avec en parralele de chaque une resistance de 1kOhm, on detecte la tension globale, directement le nombre de batterie
#define Pin_batterie      33 
#define Pin_BP            34
#define BP_AUG            27
#define BP_DIM            14
#define Son_Bombe         25
#define Son_Victoire      32
#define Son_Erreur        26

GxEPD2_BW<GxEPD2_213_BN, GxEPD2_213_BN::HEIGHT> display(GxEPD2_213_BN(/*CS=5*/ 5, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4)); // DEPG0213BN 122x250, SSD1680, TTGO T5 V2.4.1, V2.3.1
// BUSY -> 4, RST -> 16, DC -> 17, CS -> SS(5), CLK -> SCK(18), DIN -> MOSI(23), GND -> GND, 3.3V -> 3.3V

CRGB stripErreur[PIXEL_COUNT_Led_Erreur];

LedControl lc=LedControl(MAX7219DIN, MAX7219CLK, MAX7219CS,4);

PN532_I2C pn532_i2c(Wire);
NfcAdapter nfc = NfcAdapter(pn532_i2c);


byte zero   [8]={B00111000,B01000100,B01000100,B01000100,B01000100,B01000100,B01000100,B00111000};
byte un     [8]={B00010000,B00110000,B01010000,B00010000,B00010000,B00010000,B00010000,B01111100};
byte deux   [8]={B00111000,B01000100,B00000100,B00000100,B00001000,B00010000,B00100000,B01111100};
byte trois  [8]={B01111000,B00000100,B00000100,B00111000,B00000100,B00000100,B00000100,B01111000};
byte quatre [8]={B00001000,B00011000,B00101000,B01001000,B01111100,B00001000,B00001000,B00001000};
byte cinq   [8]={B01111100,B01000000,B01000000,B01111000,B00000100,B00000100,B00000100,B01111000};
byte six    [8]={B00111100,B01000000,B01000000,B01111000,B01000100,B01000100,B01000100,B00111000};
byte sept   [8]={B01111100,B00000100,B00000100,B00001000,B00001000,B00010000,B00010000,B00010000};
byte huit   [8]={B00111000,B01000100,B01000100,B00111000,B01000100,B01000100,B01000100,B00111000};
byte neuf   [8]={B00111000,B01000100,B01000100,B00111100,B00000100,B00000100,B00000100,B00111000};
byte dix    [8]={B00000000,B00000000,B00101110,B01101010,B10101010,B00101010,B00101110,B00000000};
byte onze   [8]={B00000000,B00000000,B00100010,B01100110,B10101010,B00100010,B00100010,B00000000};
byte douze  [8]={B00000000,B00000000,B00101110,B01100010,B10101110,B00101000,B00101110,B00000000};


byte vide   [8]={B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000};

byte zero2  [8]={B00111000,B01000100,B01000100,B01000101,B01000100,B01000101,B01000100,B00111000};
byte un2    [8]={B00010000,B00110000,B01010000,B00010001,B00010000,B00010001,B00010000,B01111100};
byte deux2  [8]={B00111000,B01000100,B00000100,B00000101,B00001000,B00010001,B00100000,B01111100};
byte trois2 [8]={B01111000,B00000100,B00000100,B00111001,B00000100,B00000101,B00000100,B01111000};
byte quatre2[8]={B00001000,B00011000,B00101000,B01001001,B01111100,B00001001,B00001000,B00001000};
byte cinq2  [8]={B01111100,B01000000,B01000000,B01111001,B00000100,B00000101,B00000100,B01111000};
byte six2   [8]={B00111100,B01000000,B01000000,B01111001,B01000100,B01000101,B01000100,B00111000};
byte sept2  [8]={B01111100,B00000100,B00000100,B00001001,B00001000,B00010001,B00010000,B00010000};
byte huit2  [8]={B00111000,B01000100,B01000100,B00111001,B01000100,B01000101,B01000100,B00111000};
byte neuf2  [8]={B00111000,B01000100,B01000100,B00111101,B00000100,B00000101,B00000100,B00111000};

byte module1 [8]={B00000000,B00000000,B10100100,B11101010,B10101010,B10101010,B10100100,B00000000};
byte module2 [8]={B00000000,B00000000,B11001010,B10101010,B10101010,B10101010,B11000100,B00000000};
byte module3 [8]={B00000000,B00000000,B10011011,B10010010,B10011011,B10010001,B11011011,B00000000};

byte booom1 [8]={B01111000,B01000101,B01000101,B01111001,B01000101,B01000101,B01000101,B01111000};
byte booom2 [8]={B11100011,B00010100,B00010100,B00010100,B00010100,B00010100,B00010100,B11100011};
byte booom3 [8]={B10001110,B01010001,B01010001,B01010001,B01010001,B01010001,B01010001,B10001110};
byte booom4 [8]={B01000100,B01101100,B01010100,B01000100,B01000100,B01000100,B01000100,B01000100};
byte Victoire1 [8]={B00000000,B01000101,B01000101,B00101001,B00101001,B00010001,B00000000,B00000000};
byte Victoire2 [8]={B00000000,B00110111,B01000010,B01000010,B01000010,B00110010,B00000000,B00000000};
byte Victoire3 [8]={B00000000,B00110010,B01001010,B01001010,B01001010,B00110010,B00000000,B00000000};
byte Victoire4 [8]={B00000000,B11101110,B10101000,B11001100,B10101000,B10101110,B00000000,B00000000};


char Numero_de_serie[6];
char consonne[21] = {'B', 'C', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 'M', 'N', 'P', 'Q', 'R', 'S', 'T', 'V', 'W', 'X', 'Z'};
char voyelle[5] = {'A', 'E', 'I', 'U'};
char chiffre_pair[5] = {'2', '4', '6', '8'};
char chiffre_impair[6] = {'1', '3', '5', '7', '9'};
char chiffre[10] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
byte variable = 0;
String txt_Indicateur = "SND";
String txt_Port = "HDMI";

byte Num_de_serie = 0;
byte Nb_Batteries = 0;
byte Port = 0;
byte Nb_Erreur = 0;
byte Indicateur = 0;
byte Val_temps = 0;
byte Val_temps_1 = 0;
byte Val_temps_4 = 0;
byte Val_temps_5 = 0;
int Val_batterie = 0;
byte Module_fini = 0;
byte Erreur_recu = 0;

int timeMin_1stDigit;
int timeMin_2ndDigit;
int timeSec_1stDigit;
int timeSec_2ndDigit;
unsigned long duree = 5;                     // duree du jeu en minutes
unsigned long temps_demarage;
unsigned long temps_fin;
unsigned long millis_restant;
long temps_restant;
long minutes_restant;
long secondes_restant;
long ex_temps_restant;
bool en_cours;
String temps;

byte kval = 0;
byte kval_old = 0;
byte kvaltmp = 0;
byte kvaltmp_old = 0;
byte bouton_appuye = 0;

unsigned long millis_pause;
bool etat = 0;

byte PORT_NFC = 0;
String UID = "00 00 00 00 00 00 00";
const String PORT_USB  = "1D C4 73 DB 93 00 00"; // a changer en fonction de vos tag NFC
const String PORT_USBC = "1D A6 73 DB 93 00 00"; // a changer en fonction de vos tag NFC
const String PORT_ETH  = "1D C6 73 DB 93 00 00"; // a changer en fonction de vos tag NFC
const String PORT_HDMI = "1D A5 73 DB 93 00 00"; // a changer en fonction de vos tag NFC

int nDevices = 0;
int adresse_exist[12];
uint8_t Buffer[5];
uint8_t Recep[2];

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("\n Module Master KTANE");
  Wire.begin();
  delay(500);
  
  Wire.beginTransmission(36);
  byte error = Wire.endTransmission(true);
  if (error == 0) {
    Serial.println("port NFC detecte");
    PORT_NFC = 1;
    nfc.begin();
  }
  else Serial.println("pas de port NFC detecte");

  FastLED.addLeds<PL9823, PIXEL_PIN_Led_Erreur, RGB>(stripErreur, PIXEL_COUNT_Led_Erreur);
  FastLED.setBrightness(10);
    stripErreur[0].setRGB(0, 0, 0);
    stripErreur[1].setRGB(0, 0, 0);
  FastLED.show();
  //  stripErreur.begin();
  //  stripErreur.show();
  
  for (int i = 0; i < 4; i++) {
    lc.shutdown(i,false);
    lc.setIntensity(i,1);
    lc.clearDisplay(i);
  }
  for (int i = 0; i < 12; i++) adresse_exist[i] = 0;
  
  pinMode(Pin_batterie, INPUT);
  pinMode(Pin_BP, INPUT);
  pinMode(Son_Bombe, OUTPUT);
  pinMode(Son_Victoire, OUTPUT);
  pinMode(Son_Erreur, OUTPUT);
  digitalWrite(Son_Bombe, HIGH);
  digitalWrite(Son_Victoire, HIGH);
  digitalWrite(Son_Erreur, HIGH);
    
  display.init(115200, true, 2, false); // USE THIS for Waveshare boards with "clever" reset circuit, 2ms reset pulse
  Affiche_txt();
  display.hibernate();
  
  bouton_appuye = BP_Appuye();
  bouton_appuye = BP_Appuye();

  while (bouton_appuye == 0) {
    if (choix_temps() == 1) {
      duree ++;
      if (duree > 30) duree = 30;
      Serial.print("Duree de la partie modifié : ");
      Serial.println(duree);
    }
    if (choix_temps() == 2) {
      duree --;
      if (duree < 2) duree = 2;
      Serial.print("Duree de la partie modifié : ");
      Serial.println(duree);
    }
    if (millis_pause < millis()) {
      millis_pause = millis() + 400;
      etat = !etat;
      if (etat == 0) {
        afficher_modules();
        stripErreur[0].setRGB(0, 0, 0);
        stripErreur[1].setRGB(100, 100, 100);
        FastLED.show();}
      else {
        afficher_duree();
        stripErreur[0].setRGB(100, 100, 100);
        stripErreur[1].setRGB(0, 0, 0);
        FastLED.show();}
      Serial.println("Scanning...");
      nDevices = 0;
      
      for (int address = 1; address < 127; ++address) {
        if (address == 36) address ++;
        Wire.beginTransmission(address);
        byte error = Wire.endTransmission(true);
    
        if (error == 0) {
          Serial.print("I2C device found at address ");
          adresse_exist[nDevices] = address;
          Serial.print(adresse_exist[nDevices]);
          Serial.println("  !");
          ++nDevices;
        } else if (error == 4) {
          Serial.print("Unknown error at address ");
          Serial.println(address);}
      }
      Serial.print(" il y a ");
      Serial.print(nDevices);
      Serial.println(" esclaves trouvés");
    }
    bouton_appuye = BP_Appuye();
  }
  
  randomSeed(millis());
  
  // création du numéro de série
  Num_de_serie = random(1,5);
  variable = random(0,4);
  if (variable == 0) {
    if (Num_de_serie <= 2) Numero_de_serie[0] = voyelle[random(0,4)];
    if (Num_de_serie >= 3)Numero_de_serie[0] = consonne[random(0,20)];
  } 
  else Numero_de_serie[0] = consonne[random(0,20)];
  if (variable == 1) {
    if (Num_de_serie <= 2) Numero_de_serie[1] = voyelle[random(0,4)];
    if (Num_de_serie >= 3)Numero_de_serie[1] = consonne[random(0,20)];
  } 
  else Numero_de_serie[1] = consonne[random(0,20)];
  Numero_de_serie[2] = chiffre[random(0,10)];
  if (variable == 2) {
    if (Num_de_serie <= 2) Numero_de_serie[3] = voyelle[random(0,4)];
    if (Num_de_serie >= 3)Numero_de_serie[3] = consonne[random(0,20)];
  } 
  else Numero_de_serie[3] = consonne[random(0,20)];
  if (variable == 3) {
    if (Num_de_serie <= 2) Numero_de_serie[4] = voyelle[random(0,4)];
    if (Num_de_serie >= 3)Numero_de_serie[4] = consonne[random(0,20)];
  } 
  else Numero_de_serie[4] = consonne[random(0,20)];
  if (Num_de_serie == 1 || Num_de_serie == 3) Numero_de_serie[5] = chiffre_pair[random(0,4)];
  else Numero_de_serie[5] = chiffre_impair[random(0,5)];
  Serial.print("Le numéro de série de cette KTANE est :  ");
  Serial.println(Numero_de_serie);
  
  // Combien de batteries sont sur KTANE ?
  Nb_Batteries = Nb_Batterie();
  Serial.print("Nous avons ");
  Serial.print(Nb_Batteries);
  Serial.println(" batterie(s).");
  
  
  // Quel port est connecté a KTANE ?
  Port = 0;
  if (PORT_NFC == 1){
    if (nfc.tagPresent()) {
      NfcTag tag = nfc.read();
      Serial.println(tag.getTagType());
      Serial.print("UID: ");Serial.println(tag.getUidString());
    }
    if (Port == 0) txt_Port = "Null 0";
    if (Port == 1) txt_Port = "DVID";
    if (Port == 2) txt_Port = "Parallele";
    if (Port == 3) txt_Port = "PS2";
    if (Port == 4) txt_Port = "RJ45";
    if (Port == 5) txt_Port = "Serie";
    if (Port == 6) txt_Port = "Stereo RCA";
    if (Port == 7) txt_Port = "USB";
    if (Port == 8) txt_Port = "Null 8";
    Serial.print("Le port connecté est : ");
    Serial.println(txt_Port);
  }

  // création de l'indicateur 3 lettres
  Indicateur = random(0,11);
  switch (Indicateur) {
    case 0 :
    txt_Indicateur = "SND";
    break;
    case 1 :
    txt_Indicateur = "CLR";
    break;
    case 2 :
    txt_Indicateur = "CAR";
    break;
    case 3 :
    txt_Indicateur = "IND";
    break;
    case 4 :
    txt_Indicateur = "FRQ";
    break;
    case 5 :
    txt_Indicateur = "SIG";
    break;
    case 6 :
    txt_Indicateur = "NSA";
    break;
    case 7 :
    txt_Indicateur = "MSA";
    break;
    case 8 :
    txt_Indicateur = "TRN";
    break;
    case 9 :
    txt_Indicateur = "BOB";
    break;
    case 10 :
    txt_Indicateur = "FRK";
    break;
  }
  Serial.print("L'indicateur est : ");
  Serial.println(txt_Indicateur);
  

  Buffer[0] = Num_de_serie;
  Buffer[1] = Nb_Batteries;
  Buffer[2] = Port;
  Buffer[3] = 0;
  Buffer[4] = Indicateur;
  Buffer[5] = 9;
  //Write message to the slave
  for (int i = 0; i < nDevices; i++) {
    Wire.beginTransmission(adresse_exist[i]); 
    Wire.write(Buffer,6);
    uint8_t error = Wire.endTransmission(true);
    Serial.printf("endTransmission: %u\n", error);
  }
  
  display.init(115200, true, 2, false); // USE THIS for Waveshare boards with "clever" reset circuit, 2ms reset pulse
  Affiche_txt();
  display.hibernate();
  
  temps_demarage = millis();
  temps_fin = (temps_demarage + (duree * 60000)); 
}

void loop() {
  Buffer[3] = Nb_Erreur;
  
  Erreur_recu = 0;
  Module_fini = 0;

  if (millis_pause < millis()) {
    millis_pause = millis() + 250;
    millis_restant = (temps_fin - millis());
    if (temps_fin < millis()) {
      millis_restant = 0;
      Nb_Erreur = 3;
    }
    afficher_temps();
    
    Buffer[5] = Val_temps_5 * 4 + Val_temps_4 * 2+ Val_temps_1;
    
    digitalWrite(Son_Erreur, HIGH);

    //Write message to the slave
    Serial.print("onTransmission : ");
    for (int i = 0; i < nDevices; i++) {
      Serial.print("adresse ");
      Serial.print(adresse_exist[i]);
      Wire.beginTransmission(adresse_exist[i]); 
      Wire.write(Buffer,6);
      uint8_t error = Wire.endTransmission(true);
      Serial.print("  endTransmission: ");
      Serial.println(error);
      //if (error != 0) Nb_Erreur = 3;                   // Si module deconnecté, on arete tout
    }
    
    Serial.print("onReceive : ");
    for (int i = 0; i < nDevices; i++) {
      int j = 0;
      Serial.print("adresse ");
      Serial.println(adresse_exist[i]);
      Wire.requestFrom(adresse_exist[i], 2);
      while(Wire.available()){
        int c = Wire.read();
        Recep[j] = c;
        Serial.print(c);
        Serial.print(" ");
        j++;
      }
      Serial.println();
      if (Recep[0] == 1) {
        Erreur_recu = 1;
        Serial.println(" Erreur recu !!!");
      }
      if (Recep[1] == 1) {
        Module_fini ++;
        Serial.println(" 1 module de fini :p");
      }
    }
  }
  
  if (Erreur_recu > 0) {
    Nb_Erreur ++;
    Serial.print("il y a ");
    Serial.print(Nb_Erreur);
    Serial.println(" Erreur");
    digitalWrite(Son_Erreur, LOW);
  }
  if (Module_fini == nDevices) {
    // fin du jeu
    Serial.println("Tous les modules sont fini.");
    digitalWrite(Son_Victoire, LOW);
    delay(100);
    digitalWrite(Son_Victoire, HIGH);
    while (1) {
      affiche_Victoire1();
      affiche_Victoire2();
      affiche_Victoire3();
      affiche_Victoire4();
      delay(500);
      afficher_temps();
      delay(500);
    }
  }
  afficher_erreur();
}

void afficher_temps() {
  Val_temps_5 = 0;
  Val_temps_4 = 0;
  Val_temps_1 = 0;

  temps_restant    = millis_restant / 1000;
  minutes_restant  = temps_restant  /   60;
  secondes_restant = temps_restant  %   60;

  timeMin_1stDigit = minutes_restant  / 10;
  timeMin_2ndDigit = minutes_restant  % 10;
  timeSec_1stDigit = secondes_restant / 10;
  timeSec_2ndDigit = secondes_restant % 10;

  if (timeSec_2ndDigit % 2 == 0) 
    temps = (String (timeMin_1stDigit) + String (timeMin_2ndDigit) + ":" + String (timeSec_1stDigit) + String (timeSec_2ndDigit));
  else
    temps = (String (timeMin_1stDigit) + String (timeMin_2ndDigit) + " " + String (timeSec_1stDigit) + String (timeSec_2ndDigit));
  Serial.println(temps);

  if (timeMin_1stDigit == 9) affiche_neuf(3);
  if (timeMin_1stDigit == 8) affiche_huit(3);
  if (timeMin_1stDigit == 7) affiche_sept(3);
  if (timeMin_1stDigit == 6) affiche_six(3);
  if (timeMin_1stDigit == 5) {affiche_cinq(3); Val_temps_5 = 1;}
  if (timeMin_1stDigit == 4) {affiche_quatre(3); Val_temps_4 = 1;}
  if (timeMin_1stDigit == 3) affiche_trois(3);
  if (timeMin_1stDigit == 2) affiche_deux(3);
  if (timeMin_1stDigit == 1) {affiche_un(3); Val_temps_1 = 1;}
  if (timeMin_1stDigit == 0) affiche_vide(3);

  if (timeSec_2ndDigit % 2 == 0) {
    if (timeMin_2ndDigit == 9) affiche_neuf2(2);
    if (timeMin_2ndDigit == 8) affiche_huit2(2);
    if (timeMin_2ndDigit == 7) affiche_sept2(2);
    if (timeMin_2ndDigit == 6) affiche_six2(2);
    if (timeMin_2ndDigit == 5) {affiche_cinq2(2); Val_temps_5 = 1;}
    if (timeMin_2ndDigit == 4) {affiche_quatre2(2); Val_temps_4 = 1;}
    if (timeMin_2ndDigit == 3) affiche_trois2(2);
    if (timeMin_2ndDigit == 2) affiche_deux2(2);
    if (timeMin_2ndDigit == 1) {affiche_un2(2); Val_temps_1 = 1;}
    if (timeMin_2ndDigit == 0) affiche_zero2(2);
  }
  else {
    if (timeMin_2ndDigit == 9) affiche_neuf(2);
    if (timeMin_2ndDigit == 8) affiche_huit(2);
    if (timeMin_2ndDigit == 7) affiche_sept(2);
    if (timeMin_2ndDigit == 6) affiche_six(2);
    if (timeMin_2ndDigit == 5) {affiche_cinq(2); Val_temps_5 = 1;}
    if (timeMin_2ndDigit == 4) {affiche_quatre(2); Val_temps_4 = 1;}
    if (timeMin_2ndDigit == 3) affiche_trois(2);
    if (timeMin_2ndDigit == 2) affiche_deux(2);
    if (timeMin_2ndDigit == 1) {affiche_un(2); Val_temps_1 = 1;}
    if (timeMin_2ndDigit == 0) affiche_zero(2);
  }
  
  if (timeSec_1stDigit == 9) affiche_neuf(1);
  if (timeSec_1stDigit == 8) affiche_huit(1);
  if (timeSec_1stDigit == 7) affiche_sept(1);
  if (timeSec_1stDigit == 6) affiche_six(1);
  if (timeSec_1stDigit == 5) {affiche_cinq(1); Val_temps_5 = 1;}
  if (timeSec_1stDigit == 4) {affiche_quatre(1); Val_temps_4 = 1;}
  if (timeSec_1stDigit == 3) affiche_trois(1);
  if (timeSec_1stDigit == 2) affiche_deux(1);
  if (timeSec_1stDigit == 1) {affiche_un(1); Val_temps_1 = 1;}
  if (timeSec_1stDigit == 0) affiche_zero(1);
  
  if (timeSec_2ndDigit == 9) affiche_neuf(0);
  if (timeSec_2ndDigit == 8) affiche_huit(0);
  if (timeSec_2ndDigit == 7) affiche_sept(0);
  if (timeSec_2ndDigit == 6) affiche_six(0);
  if (timeSec_2ndDigit == 5) {affiche_cinq(0); Val_temps_5 = 1;}
  if (timeSec_2ndDigit == 4) {affiche_quatre(0); Val_temps_4 = 1;}
  if (timeSec_2ndDigit == 3) affiche_trois(0);
  if (timeSec_2ndDigit == 2) affiche_deux(0);
  if (timeSec_2ndDigit == 1) {affiche_un(0); Val_temps_1 = 1;}
  if (timeSec_2ndDigit == 0) affiche_zero(0);
}

void afficher_erreur() {
  if (Nb_Erreur == 0) {
    stripErreur[0].setRGB(0, 0, 0);
    stripErreur[1].setRGB(0, 0, 0);}
  if (Nb_Erreur == 1) {
    stripErreur[0].setRGB(250, 0, 0);
    stripErreur[1].setRGB(0, 0, 0);}
  if (Nb_Erreur == 2) {
    stripErreur[0].setRGB(250, 0, 0);
    stripErreur[1].setRGB(250, 0, 0);}
  FastLED.show();
  if (Nb_Erreur > 2) {
    digitalWrite(Son_Erreur, HIGH);
    delay(200);
    digitalWrite(Son_Bombe, LOW);
    delay(100);
    digitalWrite(Son_Bombe, HIGH);
    while (1) {
      affiche_booom1();
      affiche_booom2();
      affiche_booom3();
      affiche_booom4();
      stripErreur[0].setRGB(250, 0, 0);
      stripErreur[1].setRGB(250, 0, 0);
      FastLED.show();
      delay(500);
      afficher_temps();
      delay(500);
      }
  }
}

void afficher_modules() {
  if (nDevices == 12) affiche_douze(3);
  if (nDevices == 11) affiche_onze(3);
  if (nDevices == 10) affiche_dix(3);
  if (nDevices == 9)  affiche_neuf(3);
  if (nDevices == 8)  affiche_huit(3);
  if (nDevices == 7)  affiche_sept(3);
  if (nDevices == 6)  affiche_six(3);
  if (nDevices == 5)  affiche_cinq(3);
  if (nDevices == 4)  affiche_quatre(3);
  if (nDevices == 3)  affiche_trois(3);
  if (nDevices == 2)  affiche_deux(3);
  if (nDevices == 1)  affiche_un(3);
  if (nDevices == 0)  affiche_zero(3);

  affiche_module1();
  affiche_module2();
  affiche_module3();
  int batt = Nb_Batterie();
  if (batt > 0) lc.setLed(0,0,0,true);
  if (batt > 1) lc.setLed(0,0,1,true);
  if (batt > 2) lc.setLed(0,0,2,true);
  if (batt > 3) lc.setLed(0,0,3,true);
  if (batt > 4) lc.setLed(0,0,4,true);
  if (batt > 5) lc.setLed(0,0,5,true);
  if (batt > 6) lc.setLed(0,0,6,true);
  if (batt > 7) lc.setLed(0,0,7,true);
}

void affiche_zero(byte active_display)    {for(int i=0;i<8;i++) lc.setRow(active_display,i,zero[i]);}
void affiche_un(byte active_display)      {for(int i=0;i<8;i++) lc.setRow(active_display,i,un[i]);}
void affiche_deux(byte active_display)    {for(int i=0;i<8;i++) lc.setRow(active_display,i,deux[i]);}
void affiche_trois(byte active_display)   {for(int i=0;i<8;i++) lc.setRow(active_display,i,trois[i]);}
void affiche_quatre(byte active_display)  {for(int i=0;i<8;i++) lc.setRow(active_display,i,quatre[i]);}
void affiche_cinq(byte active_display)    {for(int i=0;i<8;i++) lc.setRow(active_display,i,cinq[i]);}
void affiche_six(byte active_display)     {for(int i=0;i<8;i++) lc.setRow(active_display,i,six[i]);}
void affiche_sept(byte active_display)    {for(int i=0;i<8;i++) lc.setRow(active_display,i,sept[i]);}
void affiche_huit(byte active_display)    {for(int i=0;i<8;i++) lc.setRow(active_display,i,huit[i]);}
void affiche_neuf(byte active_display)    {for(int i=0;i<8;i++) lc.setRow(active_display,i,neuf[i]);}
void affiche_dix(byte active_display)     {for(int i=0;i<8;i++) lc.setRow(active_display,i,dix[i]);}
void affiche_onze(byte active_display)    {for(int i=0;i<8;i++) lc.setRow(active_display,i,onze[i]);}
void affiche_douze(byte active_display)   {for(int i=0;i<8;i++) lc.setRow(active_display,i,douze[i]);}
void affiche_vide(byte active_display)    {for(int i=0;i<8;i++) lc.setRow(active_display,i,vide[i]);}
void affiche_zero2(byte active_display)   {for(int i=0;i<8;i++) lc.setRow(active_display,i,zero2[i]);}
void affiche_un2(byte active_display)     {for(int i=0;i<8;i++) lc.setRow(active_display,i,un2[i]);}
void affiche_deux2(byte active_display)   {for(int i=0;i<8;i++) lc.setRow(active_display,i,deux2[i]);}
void affiche_trois2(byte active_display)  {for(int i=0;i<8;i++) lc.setRow(active_display,i,trois2[i]);}
void affiche_quatre2(byte active_display) {for(int i=0;i<8;i++) lc.setRow(active_display,i,quatre2[i]);}
void affiche_cinq2(byte active_display)   {for(int i=0;i<8;i++) lc.setRow(active_display,i,cinq2[i]);}
void affiche_six2(byte active_display)    {for(int i=0;i<8;i++) lc.setRow(active_display,i,six2[i]);}
void affiche_sept2(byte active_display)   {for(int i=0;i<8;i++) lc.setRow(active_display,i,sept2[i]);}
void affiche_huit2(byte active_display)   {for(int i=0;i<8;i++) lc.setRow(active_display,i,huit2[i]);}
void affiche_neuf2(byte active_display)   {for(int i=0;i<8;i++) lc.setRow(active_display,i,neuf2[i]);}
void affiche_module1()                    {for(int i=0;i<8;i++) lc.setRow(2,i,module1[i]);}
void affiche_module2()                    {for(int i=0;i<8;i++) lc.setRow(1,i,module2[i]);}
void affiche_module3()                    {for(int i=0;i<8;i++) lc.setRow(0,i,module3[i]);}
void affiche_booom1()                     {for(int i=0;i<8;i++) lc.setRow(3,i,booom1[i]);}
void affiche_booom2()                     {for(int i=0;i<8;i++) lc.setRow(2,i,booom2[i]);}
void affiche_booom3()                     {for(int i=0;i<8;i++) lc.setRow(1,i,booom3[i]);}
void affiche_booom4()                     {for(int i=0;i<8;i++) lc.setRow(0,i,booom4[i]);}
void affiche_Victoire1()                  {for(int i=0;i<8;i++) lc.setRow(3,i,Victoire1[i]);}
void affiche_Victoire2()                  {for(int i=0;i<8;i++) lc.setRow(2,i,Victoire2[i]);}
void affiche_Victoire3()                  {for(int i=0;i<8;i++) lc.setRow(1,i,Victoire3[i]);}
void affiche_Victoire4()                  {for(int i=0;i<8;i++) lc.setRow(0,i,Victoire4[i]);}

int Nb_Batterie() {
  Val_batterie = analogRead(Pin_batterie);
  Serial.println(Val_batterie);
  if (Val_batterie > 3000) {
    Serial.println("   Erreur de cablage");
    return 50;}
  else if (Val_batterie > 2350) {
    Serial.println("   0 piles");   // 2430
    return 0;}
  else if (Val_batterie > 2190) {
    Serial.println("   1 piles");   // 2280
    return 1;}
  else if (Val_batterie > 1990) {
    Serial.println("   2 piles");   // 2100
    return 2;}
  else if (Val_batterie > 1740) {
    Serial.println("   3 piles");   // 1880
    return 3;}
  else if (Val_batterie > 1400) {
    Serial.println("   4 piles");   // 1600
    return 4;}
  else if (Val_batterie >  940) {
    Serial.println("   5 piles");   // 1205
    return 5;}
  else if (Val_batterie >  340) {
    Serial.println("   6 piles");   //  670
    return 6;}
  else {
    Serial.println("   7 piles");   //    0
  return 7;}
  }



void Affiche_txt() {
  display.setRotation(3);
  display.setFont(&FreeMonoBold24pt7b);
  display.setTextColor(GxEPD_BLACK);
  int16_t tbx, tby; uint16_t tbw, tbh;
  display.getTextBounds(Numero_de_serie, 0, 0, &tbx, &tby, &tbw, &tbh);
  // center the bounding box by transposition of the origin:
  uint16_t x = ((display.width() - tbw) / 2) - tbx;
  uint16_t y = ((display.height() - tbh) / 2) - tby;
  display.setFullWindow();
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(x, y+40);
    display.print(Numero_de_serie);
    display.setCursor(160, 40);
    display.print(txt_Indicateur);
    display.fillCircle(140, 27, 10, GxEPD_BLACK);
  }
  while (display.nextPage());
  }

int BP_Appuye() { //fonction qui donne une valeur pour le BP appuyé
  int nombre_appuye = 0;
  kval = 0;
  if (analogRead(Pin_BP) > 4000) {
    kval = 1;
    nombre_appuye++;
    Serial.println("BP start");}
  if (nombre_appuye > 1){ //si plusieurs BP sont appuyé, on renvoie 26 (erreur)
    return 5;}
    else if (kval_old == kval) { //si BP identique au précédent resultat, on renvois 0
      return 0;}
      else{kval_old = kval; // sinon on renvoie la valeur du BP appuyé
        return kval;}
  }

int choix_temps() {
  int nombre_appuye = 0;
  kvaltmp = 0;
  if (touchRead(BP_AUG) < 20) {
    kvaltmp = 1;
    nombre_appuye ++;
    //Serial.println("BP AUG");
  }
  if (touchRead(BP_DIM) < 20) {
    kvaltmp = 2;
    nombre_appuye ++;
    //Serial.println("BP DIM");
  }
  if (nombre_appuye > 1){ //si plusieurs BP sont appuyé, on renvoie 26 (erreur)
    return 5;}
    else if (kvaltmp_old == kvaltmp) { //si BP identique au précédent resultat, on renvois 0
      return 0;}
      else{kvaltmp_old = kvaltmp; // sinon on renvoie la valeur du BP appuyé
        return kvaltmp;}
  }

void afficher_duree() {

  timeMin_1stDigit = duree  / 10;
  timeMin_2ndDigit = duree  % 10;

  if (timeMin_1stDigit == 9) affiche_neuf(3);
  if (timeMin_1stDigit == 8) affiche_huit(3);
  if (timeMin_1stDigit == 7) affiche_sept(3);
  if (timeMin_1stDigit == 6) affiche_six(3);
  if (timeMin_1stDigit == 5) affiche_cinq(3);
  if (timeMin_1stDigit == 4) affiche_quatre(3);
  if (timeMin_1stDigit == 3) affiche_trois(3);
  if (timeMin_1stDigit == 2) affiche_deux(3);
  if (timeMin_1stDigit == 1) affiche_un(3);
  if (timeMin_1stDigit == 0) affiche_vide(3);

  if (timeMin_2ndDigit == 9) affiche_neuf(2);
  if (timeMin_2ndDigit == 8) affiche_huit(2);
  if (timeMin_2ndDigit == 7) affiche_sept(2);
  if (timeMin_2ndDigit == 6) affiche_six(2);
  if (timeMin_2ndDigit == 5) affiche_cinq(2);
  if (timeMin_2ndDigit == 4) affiche_quatre(2);
  if (timeMin_2ndDigit == 3) affiche_trois(2);
  if (timeMin_2ndDigit == 2) affiche_deux(2);
  if (timeMin_2ndDigit == 1) affiche_un(2);
  if (timeMin_2ndDigit == 0) affiche_zero(2);
  
  affiche_zero(1);
  affiche_zero(0);
  }
