#include "Wire.h"
#include <FastLED.h>

#define DATA_PIN_laby    3  // Digital IO pin connected to the NeoPixels
#define NUM_LEDS_laby   64  // Number of NeoPixels (8 lignes de 8 points)
#define LUMINOSITE_laby  10

#define DATA_PIN_etat    2  // Digital IO pin connected to the NeoPixels
#define NUM_LEDS_etat    1  // Number of NeoPixels (8 lignes de 8 points)

#define BP_HAUT          A3
#define BP_BAS           A1
#define BP_GAUCHE        A0
#define BP_DROITE        A2

CRGB leds_laby[NUM_LEDS_laby];
CRGB leds_etat[NUM_LEDS_etat];

#define Num_Module 81

const int labyrinthe_1[15] = {
0b0000100000100010, // ligne 0
0b0110101110101010, // ligne 1
0b0000100010101010, // ligne 2
0b0011111010101010, // ligne 3
0b0010000010101000, // ligne 4
0b0010111010101111, // ligne 5
0b0010001010001000, // ligne 6
0b0011111011101010, // ligne 7
0b0000101000100010, // ligne 8
0b0110101111111110, // ligne 9
0b0010100000001000, // ligne 10
0b0010100000001110, // ligne 11
0b0010100000100010, // ligne 12
0b0010111010111010, // ligne 13
0b0000000010000000  // ligne 14
};

const int labyrinthe_2[15] = {
0b0000100010000010, // ligne 0
0b0010101110101010, // ligne 1
0b0010100000101000, // ligne 2
0b0010111111101110, // ligne 3
0b0010100010101000, // ligne 4
0b0110101010101010, // ligne 5
0b0000101010001010, // ligne 6
0b0011101011101011, // ligne 7
0b0000101010001000, // ligne 8
0b0011101011111110, // ligne 9
0b0000001000100010, // ligne 10
0b0011111110101110, // ligne 11
0b0010000000100000, // ligne 12
0b0010111110101011, // ligne 13
0b0010000010001000   // ligne 14
};

const int labyrinthe_3[15] = {
0b0000001000100000, // ligne 0
0b0010101010101110, // ligne 1
0b0010100010101010, // ligne 2
0b0110101111101010, // ligne 3
0b0000100010001010, // ligne 4
0b0011111010111010, // ligne 5
0b0010001010100010, // ligne 6
0b0010101010101010, // ligne 7
0b0010101010001010, // ligne 8
0b0010101011111110, // ligne 9
0b0000101000000010, // ligne 10
0b0111111011111010, // ligne 11
0b0000000010000010, // ligne 12
0b0011101111111110, // ligne 13
0b0000100000000000   // ligne 14
};

const int labyrinthe_4[15] = {
0b0000001000000000, // ligne 0
0b0011101011101110, // ligne 1
0b0010101000100010, // ligne 2
0b0010101111111010, // ligne 3
0b0010001000000010, // ligne 4
0b0011111111111110, // ligne 5
0b0000001000001000, // ligne 6
0b0011101110101011, // ligne 7
0b0000100010101010, // ligne 8
0b0110101010101010, // ligne 9
0b0010101000100010, // ligne 10
0b0010101111111110, // ligne 11
0b0010101000100000, // ligne 12
0b0010111010101011, // ligne 13
0b0000000010001000   // ligne 14
};

const int labyrinthe_5[15] = {
0b0000100000100000, // ligne 0
0b0010111110111011, // ligne 1
0b0010000010100010, // ligne 2
0b0011111010101110, // ligne 3
0b0000001000100000, // ligne 4
0b0011111111111110, // ligne 5
0b0000000000001000, // ligne 6
0b0111101111101011, // ligne 7
0b0000100010000010, // ligne 8
0b0010111110111110, // ligne 9
0b0010100010001000, // ligne 10
0b0011101010101011, // ligne 11
0b0010001000101010, // ligne 12
0b0010101111101010, // ligne 13
0b0000100000100000   // ligne 14
};

const int labyrinthe_6[15] = {
0b0000100000001000, // ligne 0
0b0011111111101010, // ligne 1
0b0000000000001010, // ligne 2
0b0011111111111110, // ligne 3
0b0000000010001000, // ligne 4
0b0111111010101011, // ligne 5
0b0000100010101000, // ligne 6
0b0110101110101110, // ligne 7
0b0000100000100000, // ligne 8
0b0011111111101110, // ligne 9
0b0000001000101000, // ligne 10
0b0111101011101011, // ligne 11
0b0000101000101010, // ligne 12
0b0010101000101010, // ligne 13
0b0010000000001000   // ligne 14
};

const int labyrinthe_7[15] = {
0b0000001010001000, // ligne 0
0b0011101010101011, // ligne 1
0b0010001000101000, // ligne 2
0b0010111111101110, // ligne 3
0b0010001000000010, // ligne 4
0b0011111110111110, // ligne 5
0b0000000000100010, // ligne 6
0b0110111111101010, // ligne 7
0b0010000000001010, // ligne 8
0b0011111111111010, // ligne 9
0b0010000000100010, // ligne 10
0b0010111010101110, // ligne 11
0b0010001010001010, // ligne 12
0b0011101011111010, // ligne 13
0b0000001000000000   // ligne 14
};

const int labyrinthe_8[15] = {
0b0010001000100000, // ligne 0
0b0010101010111011, // ligne 1
0b0000100010000000, // ligne 2
0b0111111111111110, // ligne 3
0b0000000000001000, // ligne 4
0b0111101111111011, // ligne 5
0b0000001000001000, // ligne 6
0b0011111011101110, // ligne 7
0b0010001010100000, // ligne 8
0b0010101010111111, // ligne 9
0b0000100010100000, // ligne 10
0b0111111010101110, // ligne 11
0b0000000010101010, // ligne 12
0b0011111110101010, // ligne 13
0b0000000000001000   // ligne 14
};

const int labyrinthe_9[15] = {
0b0000000000001000, // ligne 0
0b0111101110101110, // ligne 1
0b0000101000100010, // ligne 2
0b0010111011111010, // ligne 3
0b0010000010100000, // ligne 4
0b0011111010101111, // ligne 5
0b0000100010001000, // ligne 6
0b0110101110111010, // ligne 7
0b0000101000000010, // ligne 8
0b0111111011111111, // ligne 9
0b0000000010000010, // ligne 10
0b0010111110111010, // ligne 11
0b0010001000101000, // ligne 12
0b0011101011101011, // ligne 13
0b0000100010000000   // ligne 14
};

byte labyrinthe[15] [15] = {};

byte code[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
byte grille[8]; // tableau de 8 octets contenant l'état de chaque LED

byte pos_x = 0;
byte pos_y = 0;
byte pos_xy = 0;
byte marqueur_A_X = 0;
byte marqueur_A_Y = 0;
byte pos_A = 0;
byte marqueur_B_X = 0;
byte marqueur_B_Y = 0;
byte pos_B = 0;
byte marqueur_S_X = 0;
byte marqueur_S_Y = 0;
byte pos_S = 0;

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

byte NB_erreur = 0;
byte bouton_appuye = 0;
byte kval = 0;
byte kval_old = 0;
byte num_labyrinthe = 0;

byte i = 0;
byte j = 0;
byte choix = 0;

void setup() {
  Wire.begin(Num_Module);                // join i2c bus with address ...
  Wire.onReceive(onReceive);
  Wire.onRequest(onRequest);
  Serial.begin(9600);
  Serial.println("\n Module Labyrinthe");
  pinMode(BP_HAUT, INPUT_PULLUP);
  pinMode(BP_BAS, INPUT_PULLUP);
  pinMode(BP_GAUCHE, INPUT_PULLUP);
  pinMode(BP_DROITE, INPUT_PULLUP);
  FastLED.addLeds<NEOPIXEL, DATA_PIN_laby>(leds_laby, NUM_LEDS_laby);
  FastLED.addLeds<NEOPIXEL, DATA_PIN_etat>(leds_etat, NUM_LEDS_etat);
  FastLED.setBrightness(LUMINOSITE_laby);
  for(i = 0; i < 64; i++) {
    leds_laby[i].setRGB(0, 0, 0);
  }
  leds_etat[0].setRGB(150, 150, 150);
  FastLED.show();
  i = 0;
  j = 0;
  Serial.println("En attente du démarrage");
}

void loop() {
  if (Demmarage == 0) {
    while (Demmarage == 0) {
      delay(250);
      Serial.println(Demmarage);
    }
    delay(1000);
    Serial.println("Demarrage");
    randomSeed(millis());
    initialisation();
  }
  if(Module_fini == 0){
    leds_etat[0].setRGB(0, 0, 100);
    FastLED.show();
    deplacement();
    allume_led();
    if ((pos_x == marqueur_S_X) && (pos_y == marqueur_S_Y)) {
      Module_fini = 1;
    }
  }
  if (Module_fini == 1) {
    delay(100);
    allume_led();
    leds_etat[0].setRGB(255, 0, 0);
    FastLED.show();
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
  if (Val_temps == 9) Demmarage = 1;
}

void initialisation() {
  pos_x = 0;
  pos_y = 0;
  pos_xy = 0;
  marqueur_A_X = 0;
  marqueur_A_Y = 0;
  pos_A = 0;
  marqueur_B_X = 0;
  marqueur_B_Y = 0;
  pos_B = 0;
  marqueur_S_X = 0;
  marqueur_S_Y = 0;
  pos_S = 0;
  NB_erreur = 0;
  bouton_appuye = 0;
  kval = 0;
  kval_old = 0;
  num_labyrinthe = 0;
  i = 0;
  j = 0;
  
  randomSeed(millis());

  for (byte h = 0; h < 250; h++) { //mellange
    i = random(0, 9); 
    j = random(0, 9);
    byte swap = code[i];
    code[i] = code[j];
    code[j] = swap;
  }

  choix_labyrinthe(code[num_labyrinthe]);

  position_A_B_S();
  allume_led();
}

void choix_labyrinthe(byte val_labyrinthe) {
    Serial.print("Labyrinthe choisi : ");
  Serial.println(val_labyrinthe);
  if (val_labyrinthe == 1) {
    for(i = 0; i < 15; i++) {
      for(j = 0; j < 15; j++) {
        bool resultatBool = labyrinthe_1[i] & (1 << (14 - j));
        labyrinthe[i] [j] = resultatBool;
      }
    }
    marqueur_A_X = 2;
    marqueur_A_Y = 1;
    marqueur_B_X = 4;
    marqueur_B_Y = 5;
  }
  if (val_labyrinthe == 2) {
    for(i = 0; i < 15; i++) {
      for(j = 0; j < 15; j++) {
        bool resultatBool = labyrinthe_2[i] & (1 << (14 - j));
       labyrinthe[i] [j] = resultatBool;
      }
    }
    marqueur_A_X = 2;
    marqueur_A_Y = 1;
    marqueur_B_X = 2;
    marqueur_B_Y = 6;
  }
  if (val_labyrinthe == 3) {
    for(i = 0; i < 15; i++) {
      for(j = 0; j < 15; j++) {
        bool resultatBool = labyrinthe_3[i] & (1 << (14 - j));
       labyrinthe[i] [j] = resultatBool;
      }
    }
    marqueur_A_X = 2;
    marqueur_A_Y = 1;
    marqueur_B_X = 6;
    marqueur_B_Y = 1;
  }
  if (val_labyrinthe == 4) {
    for(i = 0; i < 15; i++) {
      for(j = 0; j < 15; j++) {
        bool resultatBool = labyrinthe_4[i] & (1 << (14 - j));
       labyrinthe[i] [j] = resultatBool;
      }
    }
    marqueur_A_X = 4;
    marqueur_A_Y = 5;
    marqueur_B_X = 6;
    marqueur_B_Y = 6;
  }
  if (val_labyrinthe == 5) {
    for(i = 0; i < 15; i++) {
      for(j = 0; j < 15; j++) {
        bool resultatBool = labyrinthe_5[i] & (1 << (14 - j));
       labyrinthe[i] [j] = resultatBool;
      }
    }
    marqueur_A_X = 2;
    marqueur_A_Y = 6;
    marqueur_B_X = 6;
    marqueur_B_Y = 6;
  }
  if (val_labyrinthe == 6) {
    for(i = 0; i < 15; i++) {
      for(j = 0; j < 15; j++) {
        bool resultatBool = labyrinthe_6[i] & (1 << (14 - j));
       labyrinthe[i] [j] = resultatBool;
      }
    }
    marqueur_A_X = 6;
    marqueur_A_Y = 1;
    marqueur_B_X = 6;
    marqueur_B_Y = 6;
  }
  if (val_labyrinthe == 7) {
    for(i = 0; i < 15; i++) {
      for(j = 0; j < 15; j++) {
        bool resultatBool = labyrinthe_7[i] & (1 << (14 - j));
       labyrinthe[i] [j] = resultatBool;
      }
    }
    marqueur_A_X = 4;
    marqueur_A_Y = 3;
    marqueur_B_X = 4;
    marqueur_B_Y = 5;
  }
  if (val_labyrinthe == 8) {
    for(i = 0; i < 15; i++) {
      for(j = 0; j < 15; j++) {
        bool resultatBool = labyrinthe_8[i] & (1 << (14 - j));
       labyrinthe[i] [j] = resultatBool;
      }
    }
    marqueur_A_X = 4;
    marqueur_A_Y = 3;
    marqueur_B_X = 2;
    marqueur_B_Y = 6;
  }
  if (val_labyrinthe == 9) {
    for(i = 0; i < 15; i++) {
      for(j = 0; j < 15; j++) {
        bool resultatBool = labyrinthe_9[i] & (1 << (14 - j));
       labyrinthe[i] [j] = resultatBool;
      }
    }
    marqueur_A_X = 6;
    marqueur_A_Y = 1;
    marqueur_B_X = 4;
    marqueur_B_Y = 3;
  }
  
  labyrinthe[2 * marqueur_A_Y] [2 * marqueur_A_X] = 2;
  labyrinthe[2 * marqueur_B_Y] [2 * marqueur_B_X] = 2;
  
  Serial.println("Dessin labyrinthe choisi : ");
  for(i = 0; i < 15; i++) {
    for(j = 0; j < 15; j++) {
  Serial.print(labyrinthe[i] [j]);
  }
  Serial.println("");
  }
}

void position_A_B_S() {
  choix = random(0, 8);
  if (choix == 0) {
    pos_x = 0;
    pos_y = 0;
  }
  if (choix == 1) {
    pos_x = 7;
    pos_y = 0;
  }
  if (choix == 2) {
    pos_x = 0;
    pos_y = 7;
  }
  if (choix == 3) {
    pos_x = 7;
    pos_y = 7;
  }
  if (choix == 4) {
    pos_x = 4;
    pos_y = 0;
  }
  if (choix == 5) {
    pos_x = 0;
    pos_y = 4;
  }
  if (choix == 6) {
    pos_x = 4;
    pos_y = 7;
  }
  if (choix == 7) {
    pos_x = 7;
    pos_y = 4;
  }

  Serial.print("pos blanc    x = ");
  Serial.print(pos_x);
  Serial.print("   y = ");
  Serial.println(pos_y);
 
  marqueur_S_X = (7 - pos_x);
  marqueur_S_Y = (7 - pos_y);
  
  Serial.print("pos vert    x = ");
  Serial.print(marqueur_S_X);
  Serial.print("   y = ");
  Serial.println(marqueur_S_Y);
  
  pos_A = (marqueur_A_Y * 8 + marqueur_A_X);
  pos_B = (marqueur_B_Y * 8 + marqueur_B_X);
  pos_S = (marqueur_S_Y * 8 + marqueur_S_X);
}

void deplacement() {
  bouton_appuye = 0;
  
  while (bouton_appuye == 0) {
    bouton_appuye = BP_Appuye();
    delay(50);
  }
  if (bouton_appuye == 4) {//BP_DROITE
    if (pos_x == 7) {}
    else if (labyrinthe[(pos_y * 2)][(pos_x * 2 + 1)] == 0) pos_x ++;
    else if (labyrinthe[(pos_y * 2)][(pos_x * 2 + 1)] == 1) erreur();
  }
  if (bouton_appuye == 3) {//BP_GAUCHE
    if (pos_x == 0) {}
    else if (labyrinthe[(pos_y * 2)][(pos_x * 2 - 1)] == 0) pos_x --;
    else if (labyrinthe[(pos_y * 2)][(pos_x * 2 - 1)] == 1) erreur();
  }
  if (bouton_appuye == 2) {//BP_BAS
    if (pos_y == 7) {}
    else if (labyrinthe[(pos_y * 2 + 1)][(pos_x * 2)] == 0) pos_y ++;
    else if (labyrinthe[(pos_y * 2 + 1)][(pos_x * 2)] == 1) erreur();
  }
  if (bouton_appuye == 1) {//BP_HAUT
    if (pos_y == 0) {}
    else if (labyrinthe[(pos_y * 2 - 1)][(pos_x * 2)] == 0) pos_y --;
    else if (labyrinthe[(pos_y * 2 - 1)][(pos_x * 2)] == 1) erreur();
  }
}

int BP_Appuye() { //fonction qui donne une valeur pour le BP appuyé
  int nombre_appuye = 0;
  kval = 0;
  if (digitalRead(BP_HAUT) == LOW) {
    kval = 1;
    nombre_appuye++;}
  if (digitalRead(BP_BAS) == LOW) {
    kval = 2;
    nombre_appuye++;}
  if (digitalRead(BP_GAUCHE) == LOW) {
    kval = 3;
    nombre_appuye++;}
  if (digitalRead(BP_DROITE) == LOW) {
    kval = 4;
    nombre_appuye++;}
  if (nombre_appuye > 1){ //si plusieurs BP sont appuyé, on renvoie 5 (erreur)
    return 5;}
  else if (kval_old == kval) { //si BP identique au précédent resultat, on renvois 0
    return 0;}
  else{kval_old = kval; // sinon on renvoie la valeur du BP appuyé
    return kval;}
}

void allume_led () {
  for(i = 0; i < 64; i++) {
    leds_laby[i].setRGB(0, 0, 0);
  }
  pos_xy = (pos_y * 8 + pos_x);

  leds_laby[pos_A].setRGB(0, 0, 255);
  leds_laby[pos_B].setRGB(0, 0, 255);
  leds_laby[pos_S].setRGB(0, 255, 0);
  leds_laby[pos_xy].setRGB(200, 200, 200);

  FastLED.show();
}

void erreur() {
  for(i = 0; i < 64; i++) {
    leds_laby[i].setRGB(255, 0, 0);
  }
  FastLED.show();
  delay(250);
  for(i = 0; i < 64; i++) {
    leds_laby[i].setRGB(0, 0, 0);
  }
  FastLED.show();
  allume_led();
  Strike = 1;
  leds_etat[0].setRGB(255, 0, 0);
  FastLED.show();
  while (Strike == 1) {
    delay(1000);
    Strike = 0;
  }
}
