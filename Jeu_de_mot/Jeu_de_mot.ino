#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <U8g2lib.h>

const byte liste_mots[28][14] = {
{ 5, 11,  6, 10,  8, 13,  9,  3,  0,  2,  1,  7,  4, 12},//0  PRÊT
{ 8, 11,  5, 10,  2,  9,  4,  7, 12,  0,  3,  6, 13,  1},//1  PREMIER
{ 3,  7, 12,  1,  6,  0,  9,  5,  4,  8, 13, 11,  2, 10},//2  NON
{12,  9, 11, 10,  3, 13,  0,  4,  2,  6,  8,  7,  5,  1},//3  VIDE
{ 7,  9, 11, 10,  5,  3,  2, 13,  8,  6, 12,  1,  4,  0},//4  RIEN
{11,  9,  7, 10,  1,  6, 13,  0,  4,  5,  8,  3,  2, 12},//5  OUI
{ 7,  6,  8,  4,  0,  3, 10,  2, 11,  1, 12,  5, 13,  9},//6  EUX
{ 0,  4,  8,  6, 11,  5,  9,  2, 13,  3,  7, 10, 12,  1},//7  EUHHH
{ 9,  8,  1,  2, 10,  5,  3,  6,  7, 12, 13,  0, 11,  4},//8  GAUCHE
{ 5,  4,  0, 13,  2, 12,  6,  9, 10,  8,  7,  3, 11,  1},//9  DROITE
{ 3,  0, 11,  6,  4, 13,  2, 12,  8, 10,  9,  1,  7,  5},//10 MILIEU
{10,  2,  1,  5,  7,  4, 12, 11,  8,  0,  3, 13,  6,  9},//11 E
{ 7,  2,  3, 11,  5,  8,  1, 13,  6, 12,  4,  0,  9, 10},//12 ATTENDS
{ 9, 10,  5,  0, 13, 11,  4,  7,  3,  8,  1,  6,  2, 12},//13 APPUIE
{26, 15, 16, 17, 24, 20, 18, 25, 22, 14, 21, 27, 23, 19},//14 TOI
{16, 24, 27, 20, 22, 23, 21, 25, 14, 19, 17, 26, 18, 15},//15 THON
{21, 15, 20, 16, 24, 18, 26, 19, 17, 14, 22, 25, 27, 23},//16 TON
{14, 17, 18, 24, 21, 15, 19, 16, 22, 20, 26, 23, 27, 25},//17 TONS
{23, 19, 18, 20, 22, 26, 16, 25, 17, 27, 24, 21, 15, 14},//18 T'ES
{20, 26, 24, 22, 17, 18, 21, 23, 19, 14, 27, 25, 15, 16},//19 TES
{20, 16, 15, 14, 23, 25, 21, 24, 26, 27, 17, 18, 19, 22},//20 AVANT
{18, 19, 15, 17, 24, 21, 23, 14, 20, 27, 16, 26, 25, 22},//21 QUOI
{14, 25, 17, 16, 19, 23, 21, 27, 15, 20, 18, 24, 22, 26},//22 QUOI ?
{26, 20, 24, 22, 16, 18, 17, 25, 27, 14, 19, 15, 21, 23},//23 FAIT
{22, 20, 21, 16, 25, 26, 24, 27, 23, 15, 18, 17, 19, 14},//24 SUIVANT
{15, 19, 23, 21, 14, 18, 26, 22, 17, 24, 25, 20, 16, 27},//25 MAINTIENS
{15, 23, 27, 17, 14, 25, 20, 18, 26, 19, 22, 24, 16, 21},//26 OK
{17, 24, 19, 18, 25, 23, 21, 22, 20, 14, 27, 26, 15, 16} //27 COMME
};

#define Num_Module 41

#define PIXEL_PIN_Led_RGB         2
#define PIXEL_COUNT_Led_RGB       1
Adafruit_NeoPixel stripRGB(PIXEL_COUNT_Led_RGB, PIXEL_PIN_Led_RGB, NEO_GRB + NEO_KHZ800);
U8G2_ST7920_128X64_1_SW_SPI u8g2(U8G2_R0, /* clock=*/ 13, /* data=*/ 11, /* CS=*/ 10, /* reset=*/ 8);

#define BP_1          A0
#define BP_2          A3
#define BP_3          A1
#define BP_4          5
#define BP_5          A2
#define BP_6          4

#define Maximum_LVL   5

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

byte mot_master = 0;
byte mot[6];
byte regard = 0;
byte bouton_a_appuye = 0;
byte bouton_appuye = 0;
unsigned long old_time;
byte lvl = 0;
byte NB_lvl = 0;

String txt_master;
String txt0;
String txt1;
String txt2;
String txt3;
String txt4;
String txt5;

byte kval_old = 0;
byte mot_a_appuye = 0;
byte mot_a_regarder = 0;

void setup() {
  stripRGB.begin();
  stripRGB.setPixelColor(0,   150,   150, 150);
  stripRGB.show();
  pinMode(BP_1, INPUT_PULLUP);
  pinMode(BP_2, INPUT_PULLUP);
  pinMode(BP_3, INPUT_PULLUP);
  pinMode(BP_4, INPUT_PULLUP);
  pinMode(BP_5, INPUT_PULLUP);
  pinMode(BP_6, INPUT_PULLUP);
  Wire.begin(Num_Module);                // join i2c bus with address ...
  Wire.onReceive(onReceive);
  Wire.onRequest(onRequest);
  u8g2.begin();
  Serial.begin(9600);
  Serial.println("\n Module Jeu de Mot KTANE");
  Serial.println("En attente du démarrage");
}

void loop() {
  if (Demmarage == 0) {
    while (Demmarage == 0) {
      delay(250);
      Serial.println(Demmarage);
    }
    delay(1000);
    randomSeed(millis());
    initialisation();
    NB_lvl = random(3, Maximum_LVL + 1);
  }
  if (Module_fini == 0) {
    stripRGB.setPixelColor(0, 0, 0, 100);             //  Set pixel's color (in RAM)
    stripRGB.show(); 
    if (lvl < NB_lvl) {
      bouton_appuye = BP_Appuye();
      if (bouton_appuye == bouton_a_appuye) {
        lvl ++;
        initialisation();
      }
      else if (bouton_appuye != bouton_a_appuye && bouton_appuye != 0) {
        initialisation();
        Strike = 1;
        lvl = 0;
        while (Strike == 1) {
          delay(600);
          Strike = 0;
        }
      }
    }
    if (lvl >= NB_lvl) Module_fini = 1;
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
}

void initialisation() {
  randomSeed(millis());
  mot_master = random(1, 29);
  if (mot_master == 21)
    regard = 0;
  if (mot_master ==  2 || mot_master ==  4 || mot_master == 27)
    regard = 1;
  if (mot_master ==  1 || mot_master ==  6 || mot_master == 10 || mot_master == 25)
    regard = 2;
  if (mot_master ==  8 || mot_master == 12 || mot_master == 13 || mot_master == 17 || mot_master == 19 || mot_master == 20 || mot_master == 24)
    regard = 3;
  if (mot_master ==  7 || mot_master == 14 || mot_master == 15 || mot_master == 23)
    regard = 4;
  if (mot_master ==  3 || mot_master ==  5 || mot_master ==  9 || mot_master == 11 || mot_master == 16 || mot_master == 18 || mot_master == 22 || mot_master == 26 || mot_master == 28)
    regard = 5;
  
  int Mot_ok = 0;
  int Mauvais_choix = 0;
  while(Mot_ok == 0) {
    mot[0] = random(0, 28);
    mot[1] = random(0, 28);
    mot[2] = random(0, 28);
    mot[3] = random(0, 28);
    mot[4] = random(0, 14);
    mot[5] = random(14, 28);
    for(int i = 1; i <6; i++) {
      if(mot[0] == mot[i]) Mauvais_choix++;
    }
    for(int i = 2; i <6; i++) {
      if(mot[1] == mot[i]) Mauvais_choix++;
    }
    for(int i = 3; i <6; i++) {
      if(mot[2] == mot[i]) Mauvais_choix++;
    }
    for(int i = 4; i <6; i++) {
      if(mot[3] == mot[i]) Mauvais_choix++;
    }
    if(mot[4] == mot[5]) Mauvais_choix++;
    if(Mauvais_choix == 0) {
      Mot_ok = 1;
    }
    Mauvais_choix = 0;
  }
  for (int h = 0; h < 500; h++) { //mellange la premiere ligne
    byte i = random(0, 6); 
    byte j = random(0, 6);
    byte swap = mot[i];
    mot[i] = mot[j];
    mot[j] = swap;}
  
  mot_a_appuye = 100;
  for (byte i = 0; i < 14; i++) {
    for (byte j = 0; j < 6; j++) {
      if ((mot[j] == liste_mots[mot[regard]][i]) && (mot_a_appuye == 100)) {
        mot_a_appuye = liste_mots[mot[regard]][i];
        mot_a_regarder = j;
      }
    }
  }
  Serial.print("Mot a regarder : ");
  Serial.print(mot_a_regarder + 1);
  bouton_a_appuye = 0;
  for (byte i = 0; i < 6; i++) {
    if (mot[i] == mot_a_appuye && bouton_a_appuye == 0) bouton_a_appuye = i+1;
  }

  Serial.print("Mot a appuyer : ");
  Serial.print(bouton_a_appuye);
  affiche();
}

byte BP_Appuye() { //fonction qui donne une valeur pour le BP appuyé
    byte nombre_appuye = 0;
    byte kval = 0;
    if (digitalRead(BP_1) == LOW) {
        kval = 1;
        nombre_appuye++;}
    if (digitalRead(BP_2) == LOW) {
        kval = 2;
        nombre_appuye++;}
    if (digitalRead(BP_3) == LOW) {
        kval = 3;
        nombre_appuye++;}
    if (digitalRead(BP_4) == LOW) {
        kval = 4;
        nombre_appuye++;}
    if (digitalRead(BP_5) == LOW) {
        kval = 5;
        nombre_appuye++;}
    if (digitalRead(BP_6) == LOW) {
        kval = 6;
        nombre_appuye++;}
    if (nombre_appuye > 1){ //si plusieurs BP sont appuyé, on renvoie 26 (erreur)
        return 26;}
        else if (kval_old == kval) { //si BP identique au précédent resultat, on renvois 0
            return 0;}
            else{kval_old = kval; // sinon on renvoie la valeur du BP appuyé
                return kval;}
}

void affiche() {
  u8g2.clearDisplay();
  delay(1000);
  u8g2.firstPage();
  do {
    u8g2.setFontDirection(1);
    u8g2.drawLine(105,  0, 105,  63);
    u8g2.drawLine( 35,  0,  35,  63);
    u8g2.drawLine( 70,  0,  70,  63);
    u8g2.drawLine(  0, 32, 105,  32);
    int val = 60 / NB_lvl;
    if (lvl > 0) u8g2.drawLine(  127, 0 * val, 127,  1 * val);
    if (lvl > 1) u8g2.drawLine(  127, 1 * val, 127,  2 * val);
    if (lvl > 2) u8g2.drawLine(  127, 2 * val, 127,  3 * val);
    if (lvl > 3) u8g2.drawLine(  127, 3 * val, 127,  4 * val);
    if (lvl > 4) u8g2.drawLine(  127, 4 * val, 127,  5 * val);
    u8g2.setFont(u8g2_font_ncenB08_tf);  // change ref pos to vertical center of the font
    u8g2.setFontPosCenter();
    int x = 112;
    int y = 5;
    if (mot_master-1 ==  0) u8g2.drawStr(x, y+15, "OUI");//0
    if (mot_master-1 ==  1) u8g2.drawStr(x, y+ 0, "PREMIER");//1
    if (mot_master-1 ==  2) u8g2.drawStr(x, y+ 8, "VERRE");//2
    if (mot_master-1 ==  3) u8g2.drawStr(x, y+19, "OK");//3
    if (mot_master-1 ==  4) u8g2.drawStr(x, y+13, "MOTS");//4
    if (mot_master-1 ==  5) u8g2.drawStr(x, y+13, "RIEN");//5
    if (mot_master-1 ==  6) u8g2.drawStr(x, y, "");//6
    if (mot_master-1 ==  7) u8g2.drawStr(x, y+13, "VIDE");//7
    if (mot_master-1 ==  8) u8g2.drawStr(x, y+15, "NON");//8
    if (mot_master-1 ==  9) u8g2.drawStr(x, y+13, "MOT");//9
    if (mot_master-1 == 10) u8g2.drawStr(x, y+ 9, "MAUX");//10
    if (mot_master-1 == 11) u8g2.drawStr(x, y+ 7, "BOUGE");//11
    if (mot_master-1 == 12) u8g2.drawStr(x, y+ 6, "ROUGE");//12
    if (mot_master-1 == 13) u8g2.drawStr(x, y+19, "AU");//13
    if (mot_master-1 == 14) u8g2.drawStr(x, y+16, "EAU");//14
    if (mot_master-1 == 15) u8g2.drawStr(x, y+ 0, "ATTENDS");//15
    if (mot_master-1 == 16) u8g2.drawStr(x, y+17, "TES");//16
    if (mot_master-1 == 17) u8g2.drawStr(x, y+15, "T'ES");//17
    if (mot_master-1 == 18) u8g2.drawStr(x, y+17, "TON");//18
    if (mot_master-1 == 19) u8g2.drawStr(x, y+13, "TONS");//19
    if (mot_master-1 == 20) u8g2.drawStr(x, y+12, "THON");//20
    if (mot_master-1 == 21) u8g2.drawStr(x, y+11, "TU ES");//21
    if (mot_master-1 == 22) u8g2.drawStr(x, y+10, "HAUT");//21
    if (mot_master-1 == 23) u8g2.drawStr(x, y+11, "VERS");//23
    if (mot_master-1 == 24) u8g2.drawStr(x, y+11, "VERT");//24
    if (mot_master-1 == 25) u8g2.drawStr(x, y+11, "C'EST");//25
    if (mot_master-1 == 26) u8g2.drawStr(x, y+23, "C");//26
    if (mot_master-1 == 27) u8g2.drawStr(x, y+16, "VER");//27
    u8g2.setFont(u8g2_font_4x6_tf);
    for (int i = 0; i < 6; i++) {
      if (i == 0) {x = 85; y =  2;}
      if (i == 1) {x = 85; y = 35;}
      if (i == 2) {x = 50; y =  2;}
      if (i == 3) {x = 50; y = 35;}
      if (i == 4) {x = 15; y =  2;}
      if (i == 5) {x = 15; y = 35;}
      if (mot[i] ==  0) u8g2.drawStr(x, y+ 6, "PRET");//0
      if (mot[i] ==  1) u8g2.drawStr(x, y+ 0, "PREMIER");//1
      if (mot[i] ==  2) u8g2.drawStr(x, y+ 8, "NON");//2
      if (mot[i] ==  3) u8g2.drawStr(x, y+ 6, "VIDE");//3
      if (mot[i] ==  4) u8g2.drawStr(x, y+ 6, "RIEN");//4
      if (mot[i] ==  5) u8g2.drawStr(x, y+ 8, "OUI");//5
      if (mot[i] ==  6) u8g2.drawStr(x, y+ 8, "EUX");//6
      if (mot[i] ==  7) u8g2.drawStr(x, y+ 4, "EUHHH");//7
      if (mot[i] ==  8) u8g2.drawStr(x, y+ 2, "GAUCHE");//8
      if (mot[i] ==  9) u8g2.drawStr(x, y+ 2, "DROITE");//9
      if (mot[i] == 10) u8g2.drawStr(x, y+ 2, "MILIEU");//10
      if (mot[i] == 11) u8g2.drawStr(x, y+13, "E");//11
      if (mot[i] == 12) u8g2.drawStr(x, y+ 0, "ATTENDS");//12
      if (mot[i] == 13) u8g2.drawStr(x, y+ 2, "APPUIE");//13
      if (mot[i] == 14) u8g2.drawStr(x, y+ 8, "TOI");//14
      if (mot[i] == 15) u8g2.drawStr(x, y+ 6, "THON");//15
      if (mot[i] == 16) u8g2.drawStr(x, y+ 8, "TON");//16
      if (mot[i] == 17) u8g2.drawStr(x, y+ 6, "TONS");//17
      if (mot[i] == 18) u8g2.drawStr(x, y+ 6, "T'ES");//18
      if (mot[i] == 19) u8g2.drawStr(x, y+ 8, "TES");//19
      if (mot[i] == 20) u8g2.drawStr(x, y+ 2, "AVANT");//20
      if (mot[i] == 21) u8g2.drawStr(x, y+ 6, "QUOI");//21
      if (mot[i] == 22) u8g2.drawStr(x, y+ 2, "QUOI ?");//22
      if (mot[i] == 23) u8g2.drawStr(x, y+ 6, "FAIT");//23
      if (mot[i] == 24) u8g2.drawStr(x, y+ 0, "SUIVANT");//24
      if (mot[i] == 25) u8g2.drawStr(x, y+ 4, "TIENT");//25
      if (mot[i] == 26) u8g2.drawStr(x, y+10, "OK");//26
      if (mot[i] == 27) u8g2.drawStr(x, y+ 4, "COMME");//27
    }
  } while ( u8g2.nextPage() );
  old_time = millis();
}
