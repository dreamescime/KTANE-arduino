const byte liste_mots[28][14] = {
{ 6, 12,  7, 11,  9, 14, 10,  4,  1,  3,  2,  8,  5, 13},
{ 9, 12,  6, 11,  3, 10,  5,  8, 13,  1,  4,  7, 14,  2},
{ 4,  8, 13,  2,  7,  1, 10,  6,  5,  9, 14, 12,  3, 11},
{13, 10, 12, 11,  4, 14,  1,  5,  3,  7,  9,  8,  6,  2},
{ 8, 10, 12, 11,  6,  4,  3, 14,  9,  7, 13,  2,  5,  1},
{12, 10,  8, 11,  2,  7, 14,  1,  5,  6,  9,  4,  3, 13},
{ 8,  7,  9,  5,  1,  4, 11,  3, 12,  2, 13,  6, 14, 10},
{ 1,  5,  9,  7, 12,  6, 10,  3, 14,  4,  8, 11, 13,  2},
{10,  9,  2,  3, 11,  6,  4,  7,  8, 13, 14,  1, 12,  5},
{ 6,  5,  1, 14,  3, 13,  7, 10, 11,  9,  8,  4, 12,  2},
{ 4,  1, 12,  7,  5, 14,  3, 13,  9, 11, 10,  2,  8,  6},
{11,  3,  2,  6,  8,  5, 13, 12,  9,  1,  4, 14,  7, 10},
{ 8,  3,  4, 12,  6,  9,  2, 14,  7, 13,  5,  1, 10, 11},
{10, 11,  6,  1, 14, 12,  5,  8,  4,  9,  2,  7,  3, 13},
{27, 16, 17, 18, 25, 21, 19, 26, 23, 15, 22, 28, 24, 20},
{17, 25, 28, 21, 23, 24, 22, 26, 15, 20, 18, 27, 19, 16},
{22, 16, 21, 17, 25, 19, 27, 20, 18, 15, 23, 26, 28, 24},
{15, 18, 19, 25, 22, 16, 20, 17, 23, 21, 27, 24, 28, 26},
{24, 20, 19, 21, 23, 27, 17, 26, 18, 28, 25, 22, 16, 15},
{21, 27, 25, 23, 18, 19, 22, 24, 20, 15, 28, 26, 16, 17},
{21, 17, 16, 15, 24, 26, 22, 25, 27, 28, 18, 19, 20, 23},
{19, 20, 16, 18, 25, 22, 24, 15, 21, 28, 17, 27, 26, 23},
{15, 26, 18, 17, 20, 24, 22, 28, 16, 21, 19, 25, 23, 27},
{27, 21, 25, 23, 17, 19, 18, 26, 28, 15, 20, 16, 22, 24},
{23, 21, 22, 17, 26, 27, 25, 28, 24, 16, 19, 18, 20, 15},
{16, 20, 24, 22, 15, 19, 27, 23, 18, 25, 26, 21, 17, 28},
{16, 24, 28, 18, 15, 26, 21, 19, 27, 20, 23, 25, 17, 22},
{18, 25, 20, 19, 26, 24, 22, 23, 21, 15, 28, 27, 16, 17}
}

#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <U8g2lib.h>

#define Num_Module 14

#define PIXEL_PIN_Led_RGB         2
#define PIXEL_COUNT_Led_RGB       1
Adafruit_NeoPixel stripRGB(PIXEL_COUNT_Led_RGB, PIXEL_PIN_Led_RGB, NEO_GRB + NEO_KHZ800);

#define BP_1          3
#define BP_2          4
#define BP_3          5
#define BP_4          6
#define BP_5          7
#define BP_6          8

#define Maximum_LVL   5

uint8_t Recep[5];
byte Numero_de_serie = 0;
byte Nb_Batteries = 0;
byte Port = 0;
byte Nb_Erreur = 0;
byte Indicateur = 0;
uint8_t Strike = 0;
uint8_t Module_fini = 0;

byte mot_master = 0;
byte mot[6];
byte regard = 0;
byte bouton_a_appuye = 0;
byte bouton_appuye = 0;
unsigned long old_time;
byte lvl = 0;
byte NB_lvl = 0;

String txt_master = "";
string txt[6];


void setup() {
	Wire.begin(Num_Module);                // join i2c bus with address ...
	Wire.onRequest(requestEvent); // register event
	Wire.onReceive(receiveEvent); // register event
	Serial.begin(9600);
	Serial.println("\n Module Jeu de Mot KTANE");
	u8g2.begin();
	initialisation();
	NB_lvl = random(3, Maximum_LVL + 1);
}

void loop() {
	if (millis() - old_time > 1000) affiche();
	if (Module_fini == 0) {
		if (lvl < NB_lvl) {
			bouton_appuye = BP_Appuye();
			if (bouton_appuye == bouton_a_appuye) {
				lvl ++;
				initialisation();
			}
			else if (bouton_appuye == bouton_a_appuye) {
				initialisation();
				strike = 1;
				while (strike == 1) {
					delay(100);
				}
			}
		}
	}
	if (Module_fini == 1) delay(1000);
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
	
	mot[0] = random(0, 28);
	mot[1] = random(0, 28);
	mot[2] = random(0, 28);
	mot[3] = random(0, 28);
	mot[4] = random(0, 14);
	mot[5] = random(14, 28);
	for (int h = 0; h < 500; h++) { //mellange la premiere ligne
		int i = random(0, 6); 
		int j = random(0, 6);
		int swap = mot[i];
		mot[i] = mot[j];
		mot[j] = swap;}
	
	byte bouton_a_appuye = 0;
	for (i = 0; i < 14; i++) {
		for (j = 0; j < 6; j++) {
			if ((mot[j] == liste_mots[mot[regard]][i]) && (bouton_a_appuye == 0)) bouton_a_appuye = j+1;
		}
	}

	if (mot_master ==  1) txt_master = "OUI";
	if (mot_master ==  2) txt_master = "PREMIER";
	if (mot_master ==  3) txt_master = "VERRE";
	if (mot_master ==  4) txt_master = "OK";
	if (mot_master ==  5) txt_master = "MOTS";
	if (mot_master ==  6) txt_master = "RIEN";
	if (mot_master ==  7) txt_master = "";
	if (mot_master ==  8) txt_master = "VIDE";
	if (mot_master ==  9) txt_master = "NON";
	if (mot_master == 10) txt_master = "MOT";
	if (mot_master == 11) txt_master = "MAUX";
	if (mot_master == 12) txt_master = "BOUGE";
	if (mot_master == 13) txt_master = "ROUGE";
	if (mot_master == 14) txt_master = "AU";
	if (mot_master == 15) txt_master = "EAU";
	if (mot_master == 16) txt_master = "ATTENDS";
	if (mot_master == 17) txt_master = "TES";
	if (mot_master == 18) txt_master = "T'ES";
	if (mot_master == 19) txt_master = "TON";
	if (mot_master == 20) txt_master = "TONS";
	if (mot_master == 21) txt_master = "THON";
	if (mot_master == 22) txt_master = "TU ES";
	if (mot_master == 23) txt_master = "HAUT";
	if (mot_master == 24) txt_master = "VERS";
	if (mot_master == 25) txt_master = "VERT";
	if (mot_master == 26) txt_master = "C'EST";
	if (mot_master == 27) txt_master = "C";
	if (mot_master == 28) txt_master = "VER";

	for (i = 0; i < 6; i++) {
			if (mot[i] ==  1) txt[i] = "PRÊT";
			if (mot[i] ==  2) txt[i] = "PREMIER";
			if (mot[i] ==  3) txt[i] = "NON";
			if (mot[i] ==  4) txt[i] = "VIDE";
			if (mot[i] ==  5) txt[i] = "RIEN";
			if (mot[i] ==  6) txt[i] = "OUI";
			if (mot[i] ==  7) txt[i] = "EUX";
			if (mot[i] ==  8) txt[i] = "EUHHH";
			if (mot[i] ==  9) txt[i] = "GAUCHE";
			if (mot[i] == 10) txt[i] = "DROITE";
			if (mot[i] == 11) txt[i] = "MILIEU";
			if (mot[i] == 12) txt[i] = "E";
			if (mot[i] == 13) txt[i] = "ATTENDS";
			if (mot[i] == 14) txt[i] = "APPUIE";
			if (mot[i] == 15) txt[i] = "TOI";
			if (mot[i] == 16) txt[i] = "THON";
			if (mot[i] == 17) txt[i] = "TON";
			if (mot[i] == 18) txt[i] = "TONS";
			if (mot[i] == 19) txt[i] = "T'ES";
			if (mot[i] == 20) txt[i] = "TES";
			if (mot[i] == 21) txt[i] = "AVANT";
			if (mot[i] == 22) txt[i] = "QUOI";
			if (mot[i] == 23) txt[i] = "QUOI ?";
			if (mot[i] == 24) txt[i] = "FAIT";
			if (mot[i] == 25) txt[i] = "SUIVANT";
			if (mot[i] == 26) txt[i] = "MAINTIENS";
			if (mot[i] == 27) txt[i] = "OK";
			if (mot[i] == 28) txt[i] = "COMME";
	}

	affiche();
}

int BP_Appuye() { //fonction qui donne une valeur pour le BP appuyé
    int nombre_appuye = 0;
    kval = 0;
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
	u8g2.setFont(u8g2_font_ncenB14_tf);
	u8g2.setFontDirection(1);
	u8g2.drawStr(15, 20, txt_master);
	u8g2.drawStr(15, 20, txt[0]);
	u8g2.drawStr(15, 20, txt[1]);
	u8g2.drawStr(15, 20, txt[2]);
	u8g2.drawStr(15, 20, txt[3]);
	u8g2.drawStr(15, 20, txt[4]);
	u8g2.drawStr(15, 20, txt[5]);
	u8g2.sendBuffer();
	old_time = millis();
}
