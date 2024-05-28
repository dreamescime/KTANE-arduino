#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>
#include <Keypad.h>

/*
en face visible
1 collonne 2
2 ligne 1 2 3
3 collonne 1
4 ligne * 0 #
5 collonne 3
6 ligne 7 8 9
7 ligne 4 5 6
*/

#define Num_Module 51

#define PIXEL_PIN_Led_RGB         2
#define PIXEL_COUNT_Led_RGB       1
Adafruit_NeoPixel stripRGB(PIXEL_COUNT_Led_RGB, PIXEL_PIN_Led_RGB, NEO_GRB + NEO_KHZ800);
U8G2_ST7567_OS12864_1_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);  

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {A0, A1, A2, A3}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {3, 4, 5}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

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

char key = ' ';

byte dizaine_1 = 0;
byte unitee_1 = 0;
byte aleatoire_signe = 0;
bool signe = 0;   // signe de l'operation  0 = soutraction    1 = adition
byte dizaine_2 = 0;
byte unitee_2 = 0;
int resultat = 0;
byte val_affiche[5];

bool val_signe = 1;
byte val_centaine = 0;
byte val_dizaine = 0;
byte val_unitee = 0;
int val_resultat = 0;
byte nombre_val = 0;

void setup(void) {
  stripRGB.begin();
  stripRGB.setPixelColor(0,   150,   150, 150);
  stripRGB.show();
  Wire.begin(Num_Module);                // join i2c bus with address ...
  Wire.onReceive(onReceive);
  Wire.onRequest(onRequest);
  u8g2.begin();
  Serial.begin(9600);
  Serial.println("\n Module Emojy Math");
  Serial.println("En attente du démarrage");
}

void loop(void) {
  if (Demmarage == 0) {
    while (Demmarage == 0) {
      delay(250);
      Serial.println(Demmarage);
      Demmarage = 1; // a supprimer !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    }
    delay(100);
    randomSeed(millis());
    initialisation();
    affiche();
  }
  if (Module_fini == 0) {
    key = keypad.getKey();
    stripRGB.setPixelColor(0, 0, 0, 100);             //  Set pixel's color (in RAM)
    stripRGB.show(); 
    if (key){
      if (key == '*') {
        if (val_signe == 0) val_signe = 1;
        else val_signe = 0; 
      }
      else if (key == '#') {
        if (val_signe == 0) val_resultat = - (val_centaine * 100 + val_dizaine * 10 + val_unitee);
        else val_resultat = (val_centaine * 100 + val_dizaine * 10 + val_unitee);

        if (val_resultat == resultat) {
          Module_fini = 1;
          Serial.println("Module fini");
        }
        else {
          val_signe = 1;
          val_centaine = 0;
          val_dizaine = 0;
          val_unitee = 0;
          val_resultat = 0;
          nombre_val = 0;
          delay(600);
          Strike = 0;
          Serial.println("Strike");
        }
      }
      else lecture();
    }
  }
  if (Module_fini == 1) {
    delay(100);
    stripRGB.setPixelColor(0, 255, 0, 0);             //  Set pixel's color (in RAM)
    stripRGB.show(); 
  }
}

void onRequest() {
  Wire.write(Strike);
  Wire.write(Module_fini);
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
  if (Val_temps >= 4) Val_temps_5 = 1;
  else Val_temps_5 = 0;
  if ((Val_temps - 4 * Val_temps_5) >= 2) Val_temps_4 = 1;
  else Val_temps_4 = 0;
  if ((Val_temps - 4 * Val_temps_5 - 2 * Val_temps_4) >= 1) Val_temps_1 = 1;
  else Val_temps_1 = 0;
  if (Val_temps == 9) Demmarage = 1;
  if (Numero_de_serie > 5) Numero_de_serie = Numero_de_serie - 5;
}

void initialisation() {
  dizaine_1 = random(0, 10);
  unitee_1 = random(0, 10);
  dizaine_2 = random(0, 10);
  unitee_2 = random(0, 10);
  aleatoire_signe = random(0, 100);
  if (aleatoire_signe < 50) signe = 0;
  else signe = 1;

  if (signe == 0) resultat = ((dizaine_1 * 10 + unitee_1) - (dizaine_2 * 10 + unitee_2));
  else resultat = ((dizaine_1 * 10 + unitee_1) + (dizaine_2 * 10 + unitee_2));
}

void affiche() {
  
  Serial.print("Le calcul est : ");
  Serial.print(dizaine_1);
  Serial.print(unitee_1);
  if (signe == 0) Serial.print(" - ");
  else Serial.print(" + ");
  Serial.print(dizaine_2);
  Serial.println(unitee_2);

  Serial.print("le resultat est : ");
  Serial.println(resultat);

  Serial.println("Ce qui va s'afficher a l'ecran est  : ");

  if (dizaine_1 == 0) Serial.print(" :) ");
  if (dizaine_1 == 1) Serial.print(" =( ");
  if (dizaine_1 == 2) Serial.print(" (: ");
  if (dizaine_1 == 3) Serial.print(" )= ");
  if (dizaine_1 == 4) Serial.print(" :( ");
  if (dizaine_1 == 5) Serial.print(" ): ");
  if (dizaine_1 == 6) Serial.print(" =) ");
  if (dizaine_1 == 7) Serial.print(" (= ");
  if (dizaine_1 == 8) Serial.print(" :| ");
  if (dizaine_1 == 9) Serial.print(" |: ");

  if (unitee_1 == 0) Serial.print(" :) ");
  if (unitee_1 == 1) Serial.print(" =( ");
  if (unitee_1 == 2) Serial.print(" (: ");
  if (unitee_1 == 3) Serial.print(" )= ");
  if (unitee_1 == 4) Serial.print(" :( ");
  if (unitee_1 == 5) Serial.print(" ): ");
  if (unitee_1 == 6) Serial.print(" =) ");
  if (unitee_1 == 7) Serial.print(" (= ");
  if (unitee_1 == 8) Serial.print(" :| ");
  if (unitee_1 == 9) Serial.print(" |: ");

  if (signe == 0) Serial.print(" - ");
  else Serial.print(" + ");

  if (dizaine_2 == 0) Serial.print(" :) ");
  if (dizaine_2 == 1) Serial.print(" =( ");
  if (dizaine_2 == 2) Serial.print(" (: ");
  if (dizaine_2 == 3) Serial.print(" )= ");
  if (dizaine_2 == 4) Serial.print(" :( ");
  if (dizaine_2 == 5) Serial.print(" ): ");
  if (dizaine_2 == 6) Serial.print(" =) ");
  if (dizaine_2 == 7) Serial.print(" (= ");
  if (dizaine_2 == 8) Serial.print(" :| ");
  if (dizaine_2 == 9) Serial.print(" |: ");

  if (unitee_2 == 0) Serial.println(" :) ");
  if (unitee_2 == 1) Serial.println(" =( ");
  if (unitee_2 == 2) Serial.println(" (: ");
  if (unitee_2 == 3) Serial.println(" )= ");
  if (unitee_2 == 4) Serial.println(" :( ");
  if (unitee_2 == 5) Serial.println(" ): ");
  if (unitee_2 == 6) Serial.println(" =) ");
  if (unitee_2 == 7) Serial.println(" (= ");
  if (unitee_2 == 8) Serial.println(" :| ");
  if (unitee_2 == 9) Serial.println(" |: ");
  
  val_affiche[0] = dizaine_1;
  val_affiche[1] = unitee_1;
  val_affiche[2] = dizaine_2;
  val_affiche[3] = unitee_2;
//  val_affiche[0] = 0;
//  val_affiche[1] = 0;
//  val_affiche[2] = 0;
//  val_affiche[3] = 0;

  int x = 5;
  int y = 36;

  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_ncenB10_tr);
    for (int i = 0; i < 4; i++) {
      if (i == 0) x = 13;
      if (i == 1) x = 38;
      if (i == 2) x = 75;
      if (i == 3) x = 100;
      if (val_affiche[i] ==  0) u8g2.drawStr(x,y,":)");
      if (val_affiche[i] ==  1) u8g2.drawStr(x,y,"=(");
      if (val_affiche[i] ==  2) u8g2.drawStr(x,y,"(:");
      if (val_affiche[i] ==  3) u8g2.drawStr(x,y,")=");
      if (val_affiche[i] ==  4) u8g2.drawStr(x,y,":(");
      if (val_affiche[i] ==  5) u8g2.drawStr(x,y,"):");
      if (val_affiche[i] ==  6) u8g2.drawStr(x,y,"=)");
      if (val_affiche[i] ==  7) u8g2.drawStr(x,y,"(=");
      if (val_affiche[i] ==  8) u8g2.drawStr(x,y,":|");
      if (val_affiche[i] ==  9) u8g2.drawStr(x,y,"|:");
    }
      if (signe == 0) u8g2.drawStr(60,36,"-");
      else u8g2.drawStr(60,36,"+");
  } while ( u8g2.nextPage() );
}

void lecture() {
  int val_recu = 0;
  if (key == '0') val_recu = 0;
  if (key == '1') val_recu = 1;
  if (key == '2') val_recu = 2;
  if (key == '3') val_recu = 3;
  if (key == '4') val_recu = 4;
  if (key == '5') val_recu = 5;
  if (key == '6') val_recu = 6;
  if (key == '7') val_recu = 7;
  if (key == '8') val_recu = 8;
  if (key == '9') val_recu = 9;

  if (nombre_val == 0) {
    val_unitee = val_recu;
  }

  if (nombre_val == 1) {
    val_dizaine = val_unitee;
    val_unitee = val_recu;
  }

  if (nombre_val >= 2) {
    val_centaine = val_dizaine;
    val_dizaine = val_unitee;
    val_unitee = val_recu;
  }

  nombre_val ++;
  
  Serial.print("nombre d'appuis : ");
  Serial.print(nombre_val);
  Serial.print("           ");
  if (val_signe == 0) Serial.print(" - ");
  else Serial.print(" + ");
  Serial.print(val_centaine);
  Serial.print(val_dizaine);
  Serial.println(val_unitee);
  Serial.println("   .   ");
  
}
