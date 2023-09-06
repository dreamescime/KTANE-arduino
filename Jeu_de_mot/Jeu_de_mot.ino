//"OUI, PREMIER, VERRE, OK, MOTS, RIEN, '', VIDE, NON, MOT, MAUX, BOUGE, ROUGE, AU, EAU, ATTENDS, TES, T'ES, TON, TONS, THON, TU ES, HAUT, VERS, VERT, C'EST, C, VER"
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

u8g2.setFont(u8g2_font_ncenB14_tf);
u8g2.setFontDirection(0);
u8g2.drawStr(15, 20, "Abc");
u8g2.setFontDirection(1);
u8g2.drawStr(15, 20, "Abc");

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



void setup() {
	Wire.begin(Num_Module);                // join i2c bus with address ...
	Wire.onRequest(requestEvent); // register event
	Wire.onReceive(receiveEvent); // register event
	Serial.begin(9600);
	Serial.println("\n Module Jeu de Mot KTANE");
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

void intialisation() {
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
}
