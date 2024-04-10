//Mario's Ideas
//MAX7219 - using Led Control library to display 8x8 bitmap on 4 8x8 matrixes
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <LedControl.h>
#include <TM1637Display.h>

#define Num_Module 51

#define PIXEL_PIN_Led_RGB         2
#define PIXEL_COUNT_Led_RGB       1
Adafruit_NeoPixel stripRGB(PIXEL_COUNT_Led_RGB, PIXEL_PIN_Led_RGB, NEO_GRB + NEO_KHZ800);

#define TM1637CLK    4
#define TM1637DIO    3
#define MAX7219DIN  12
#define MAX7219CS   11
#define MAX7219CLK  10

#define BUTTON1_PIN A3
#define BUTTON2_PIN A2
#define BUTTON3_PIN A1
#define BUTTON4_PIN A0


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

LedControl lc=LedControl(MAX7219DIN, MAX7219CLK, MAX7219CS,1);
TM1637Display display = TM1637Display(TM1637CLK, TM1637DIO);

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

uint8_t bottom_nums[5][4];
uint8_t top_nums[5];
uint8_t buttons_to_press[5];
int stage = 0;

int nombre_bas = 0;

unsigned long millis_pause;

byte bouton_appuye = 0;
byte kval_old = 0;

void setup() {
  stripRGB.begin();
  stripRGB.setPixelColor(0, 150, 150, 150);         //  Set pixel's color (in RAM)
  stripRGB.show();                                 //  Update strip to match
  Serial.begin(9600);
  Serial.println("\n Module Memory");
  pinMode(BUTTON1_PIN, INPUT_PULLUP);
  pinMode(BUTTON2_PIN, INPUT_PULLUP);
  pinMode(BUTTON3_PIN, INPUT_PULLUP);
  pinMode(BUTTON4_PIN, INPUT_PULLUP);
  Wire.begin(Num_Module);                // join i2c bus with address ...
  Wire.onReceive(onReceive);
  Wire.onRequest(onRequest);
  delay(200);
  lc.shutdown(0,false);
  lc.setIntensity(0,1);
  lc.clearDisplay(0);
  affiche_zero();
  display.setBrightness(4); // 0-7 luminosite
  display.showNumberDec(1234);
  Serial.println("En attente du démarrage");
}
  
void loop() {
  if (Demmarage == 0) {
    while (Demmarage == 0) {
      if (millis_pause < millis()) {
        millis_pause = millis() + 250;
        Serial.println(Demmarage);}
    }
    delay(100);
    Serial.println("Demarrage");
    randomSeed(millis());
    generateRandomNumbers();
    afficheall();
    affiche();
  }
  if(Module_fini == 0){
    stripRGB.setPixelColor(0, 0, 0, 100);             //  Set pixel's color (in RAM)
    stripRGB.show();                                  //  Update strip to match
    bouton_appuye = BP_Appuye();
    if (millis_pause < millis()) {
      millis_pause = millis() + 100;
      if(bouton_appuye != 0) {
        if(bouton_appuye == buttons_to_press[stage]) {
          stage++;
        } else {
          stage = 0;
          generateRandomNumbers();
          Strike = 1;
          while (Strike == 1) {
            if (millis_pause < millis()) {
              millis_pause = millis() + 250;
              Serial.println("en attente, Strike en cours");
            }
          }
        }
        if(stage == 5){
          Module_fini = 1;
        } else {
        affiche();
        }
      }
    }
  }
  if (Module_fini == 1) {
    delay(100);
    affiche();
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
  if (Val_temps == 9) Demmarage = 1;
}

void affiche() {
  Serial.println("");
  Serial.print("Numero du stage :  ");
  Serial.println(stage + 1);
  Serial.print("Numero haut :    ");
  Serial.println(top_nums[stage]);
  Serial.print("Numero bas :  ");
  Serial.print(bottom_nums[stage][0]);
  Serial.print(bottom_nums[stage][1]);
  Serial.print(bottom_nums[stage][2]);
  Serial.println(bottom_nums[stage][3]);
  Serial.print("bouton a appuyer :  ");
  Serial.println(buttons_to_press[stage]);
  nombre_bas = 1000 * bottom_nums[stage][0] + 100 * bottom_nums[stage][1] + 10 * bottom_nums[stage][2] + bottom_nums[stage][3];
  display.showNumberDec(nombre_bas);
  if (top_nums[stage] == 1) affiche_un();
  if (top_nums[stage] == 2) affiche_deux();
  if (top_nums[stage] == 3) affiche_trois();
  if (top_nums[stage] == 4) affiche_quatre();
  if (stage > 0) lc.setLed(0,7,7,true);
  if (stage > 1) lc.setLed(0,6,7,true);
  if (stage > 2) lc.setLed(0,5,7,true);
  if (stage > 3) lc.setLed(0,4,7,true);
  if (stage > 4) lc.setLed(0,3,7,true);
}

void afficheall() {
  for (int i = 0; i < 5; i++) {
    Serial.println("");
    Serial.print("Numero du stage :  ");
    Serial.println(i + 1);
    Serial.print("Numero haut :    ");
    Serial.println(top_nums[i]);
    Serial.print("Numero bas :  ");
    Serial.print(bottom_nums[i][0]);
    Serial.print(bottom_nums[i][1]);
    Serial.print(bottom_nums[i][2]);
    Serial.println(bottom_nums[i][3]);
    Serial.print("bouton a appuyer :  ");
    Serial.println(buttons_to_press[i]);
  }
  Serial.println("-------------------");
}

void affiche_zero() {for(int i=0;i<8;i++) lc.setRow(0,i,zero[i]);}
void affiche_un() {for(int i=0;i<8;i++) lc.setRow(0,i,un[i]);}
void affiche_deux() {for(int i=0;i<8;i++) lc.setRow(0,i,deux[i]);}
void affiche_trois() {for(int i=0;i<8;i++) lc.setRow(0,i,trois[i]);}
void affiche_quatre() {for(int i=0;i<8;i++) lc.setRow(0,i,quatre[i]);}
void affiche_cinq() {for(int i=0;i<8;i++) lc.setRow(0,i,cinq[i]);}
void affiche_six() {for(int i=0;i<8;i++) lc.setRow(0,i,six[i]);}
void affiche_sept() {for(int i=0;i<8;i++) lc.setRow(0,i,sept[i]);}
void affiche_huit() {for(int i=0;i<8;i++) lc.setRow(0,i,huit[i]);}
void affiche_neuf() {for(int i=0;i<8;i++) lc.setRow(0,i,neuf[i]);}

int BP_Appuye() { //fonction qui donne une valeur pour le BP appuyé
    int nombre_appuye = 0;
    int kval = 0;
    if (digitalRead(BUTTON1_PIN) == LOW) {
        kval = 1;
        nombre_appuye++;}
    if (digitalRead(BUTTON2_PIN) == LOW) {
        kval = 2;
        nombre_appuye++;}
    if (digitalRead(BUTTON3_PIN) == LOW) {
        kval = 3;
        nombre_appuye++;}
    if (digitalRead(BUTTON4_PIN) == LOW) {
        kval = 4;
        nombre_appuye++;}
    if (nombre_appuye > 1){ //si plusieurs BP sont appuyé, on renvoie 26 (erreur)
        return 26;}
        else if (kval_old == kval) { //si BP identique au précédent resultat, on renvois 0
            return 0;}
            else{kval_old = kval; // sinon on renvoie la valeur du BP appuyé
                return kval;}
}

void generateRandomNumbers() {
  int r1, r2;
  uint8_t temp;
  for(int i = 0; i < 5; i++){
    bottom_nums[i][0] = 1;
    bottom_nums[i][1] = 2;
    bottom_nums[i][2] = 3;
    bottom_nums[i][3] = 4;

    for(int j = 0; j < 20; j++){
      r1 = random(0, 4);
      r2 = random(0, 4);
      temp = bottom_nums[i][r1];
      bottom_nums[i][r1] = bottom_nums[i][r2];
      bottom_nums[i][r2] = temp;
    }

    top_nums[i] = random(1,5);
  }

  switch(top_nums[0]) {
    case(1):
      buttons_to_press[0] = 2; // Second Position
      break;
    case(2):
      buttons_to_press[0] = 2; // Second Position
      break;
    case(3):
      buttons_to_press[0] = 3; // Third Position
      break;
    case(4):
      buttons_to_press[0] = 4; // Fourth Position
      break;
  }
  switch(top_nums[1]) {
    case(1):
      // Button labeled 4
      buttons_to_press[1] = getIndexFromNumber(bottom_nums[1], 4) + 1;
      break;
    case(2):
      buttons_to_press[1] = buttons_to_press[0]; // Same position as stage 1
      break;
    case(3):
      buttons_to_press[1] = 1; // First Position
      break;
    case(4):
      buttons_to_press[1] = buttons_to_press[0]; // Same position as stage 1
      break;
  }
  switch(top_nums[2]) {
    case(1):
      // Same label as stage 2
      buttons_to_press[2] = getIndexFromNumber(bottom_nums[2], bottom_nums[1][buttons_to_press[1] -1 ]) + 1;
      break;
    case(2):
      // Same label as stage 1
      buttons_to_press[2] = getIndexFromNumber(bottom_nums[2], bottom_nums[0][buttons_to_press[0]] - 1) + 1;
      break;
    case(3):
      buttons_to_press[2] = 3;  // Third Position
      break;
    case(4):
      // Button labeled 4
      buttons_to_press[2] = getIndexFromNumber(bottom_nums[2], 4) + 1 ;
      break;
  }
  switch(top_nums[3]) {
    case(1):
      buttons_to_press[3] = buttons_to_press[0]; // Same position as stage 1
      break;
    case(2):
      buttons_to_press[3] = 1;  // First Position
      break;
    case(3):
      buttons_to_press[3] = buttons_to_press[1]; // Same position as stage 2
      break;
    case(4):
      buttons_to_press[3] = buttons_to_press[1]; // Same position as stage 2
      break;
  }
  switch(top_nums[4]) {
    case(1):
      // Same label as stage 1
      buttons_to_press[4] = getIndexFromNumber(bottom_nums[4], bottom_nums[0][buttons_to_press[0]] - 1) + 1;
      break;
    case(2):
      // Same label as stage 2
      buttons_to_press[4] = getIndexFromNumber(bottom_nums[4], bottom_nums[1][buttons_to_press[1]] - 1) + 1;
      break;
    case(3):
      // Same label as stage 3
      buttons_to_press[4] = getIndexFromNumber(bottom_nums[4], bottom_nums[2][buttons_to_press[3]] - 1) + 1;
      break;
    case(4):
      // Same label as stage 4
      buttons_to_press[4] = getIndexFromNumber(bottom_nums[4], bottom_nums[3][buttons_to_press[2]] - 1) + 1;
      break;
  }

    for(int i = 0; i < 5; i++) {
      Serial.println("");
      Serial.println("");
      Serial.println(top_nums[i]);
      Serial.println(buttons_to_press[i]);
      for(int j = 0; j < 4; j++){
        Serial.print(bottom_nums[i][j]);
      }
    }
    Serial.println("");
}

uint8_t getIndexFromNumber(uint8_t *buttons, uint8_t num){
  for(int i = 0; i < 4; i++) {
    if(buttons[i] == num) {
      return i;
    }
  }
  return 255;
}
