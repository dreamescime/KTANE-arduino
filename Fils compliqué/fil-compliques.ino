#include <Adafruit_NeoPixel.h>

#define PIXEL_PIN_Led_RGB         2
#define PIXEL_PIN_Led_Blanc       3
#define PIXEL_PIN_Led_Etoile      4

#define PIXEL_COUNT_Led_RGB       1
#define PIXEL_COUNT_Led_Blanc     6
#define PIXEL_COUNT_Led_Etoile    6

Adafruit_NeoPixel stripRGB(PIXEL_COUNT_Led_RGB, PIXEL_PIN_Led_RGB, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripLedBlanc(PIXEL_COUNT_Led_Blanc, PIXEL_PIN_Led_Blanc, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripLedEtoile(PIXEL_COUNT_Led_Etoile, PIXEL_PIN_Led_Etoile, NEO_GRB + NEO_KHZ800);

// a passer en variable avec communication master
byte serial_number = 1;
byte Port_parralele = 1;
byte nombre_piles = 4;
// fin des variable master

const byte borne[6] = {0, 1, 2, 3, 6, 7};
byte Fil_present[6];
byte Bleu[6];
byte Rouge[6];
byte Led[6];
byte Etoile[6];
int Nb_fil_a_couper = 0;
byte tension = 0;
byte tension_fil[6];
byte Fil[6];
byte ligne = 0;
byte colonne = 0;

const byte test[4][4] = {
	{0, 0, 2, 0},
	{1, 3, 2, 2},
	{3, 1, 2, 3},
	{4, 4, 4, 1}};

void setup() {
	Serial.begin(9600);
	stripRGB.begin();
	stripLedBlanc.begin();
	stripLedEtoile.begin();
	stripRGB.show();
	stripLedBlanc.show();
	stripLedEtoile.show();

	pinMode(A0, INPUT);
	pinMode(A1, INPUT);
	pinMode(A2, INPUT);
	pinMode(A3, INPUT);
	pinMode(A6, INPUT);
	pinMode(A7, INPUT);
	
	delay(10);
	
	couleur_Fil();
	mise_en_place_1();
	
	for(int i = 0; i < 6; i++) {
		if (Led[i] == 1) stripLedBlanc.setPixelColor(i, 255, 255, 255);
		if (Etoile[i] == 1) stripLedEtoile.setPixelColor(i, 255, 255, 255);
	}
	stripLedBlanc.show();
	stripLedEtoile.show();
}

void loop() {
	for(int i = 0; i < 6; i++) {
		if(Fil_present[i] != 0){
			if(tension_fil[i] != tension_sur_fil(analogRead(borne[i]))) {
				delay(100);
				if(tension_fil[i] != tension_sur_fil(analogRead(borne[i]))) { // Check again for debouncing reasons
					if(Fil[i] == 1) {
						Fil[i] = 0;
						reussite();
					} else {
						erreur();
					}
					tension_fil[i] = tension_sur_fil(analogRead(borne[i]));
				}
			}
			delay(10);
		}
	}
}

void couleur_Fil() {
	for (int i = 0; i = 6; i++) {
		tension = analogRead(borne[i]);
		if(tension < 10) { // pas de fil
			Fil_present[i] = 0;
			Bleu[i] = 0;
			Rouge[i] = 0;
			tension_fil[i] = 0;
		} else if(tension < 138) { // fil blanc
			Fil_present[i] = 1;
			Bleu[i] = 0;
			Rouge[i] = 0;
			tension_fil[i] = 1;
		} else if(tension < 384) { // fil rouge
			Fil_present[i] = 1;
			Bleu[i] = 0;
			Rouge[i] = 1;
			tension_fil[i] = 2;
		} else if(tension < 640) { // fil bleu et rouge
			Fil_present[i] = 1;
			Bleu[i] = 1;
			Rouge[i] = 1;
			tension_fil[i] = 3;
		} else if(tension < 896) { // fil bleu
			Fil_present[i] = 1;
			Bleu[i] = 1;
			Rouge[i] = 0;
			tension_fil[i] = 4;
		} else { // fil noir
			Fil_present[i] = 1;
			Bleu[i] = 0;
			Rouge[i] = 0;
			tension_fil[i] = 5;
		}
	}
}

int tension_sur_fil(int tension) {
	if(tension < 10) {          return 0;
	} else if(tension < 138) {  return 1;
	} else if(tension < 384) {  return 2;
	} else if(tension < 640) {  return 3;
	} else if(tension < 896) {  return 4;
	} else {                    return 5;
	}
	return 0;
}

void reussite() {
	Nb_fil_a_couper = 0;
	for(int j = 0; j < 6; j++) {
		if (Fil[j] == 1) Nb_fil_a_couper ++;
	}
	if (Nb_fil_a_couper = 0) {
		module_desarme();
	}
}

void module_desarme() {
	stripRGB.setPixelColor(0, 0, 255, 0);
	stripRGB.show();
	while(1){}
}

void erreur() {
	stripRGB.setPixelColor(0, 255, 0, 0);
	stripRGB.show();
	delay(1000);
	stripRGB.setPixelColor(0, 0, 0, 0);
	stripRGB.show();
}

void mise_en_place_1() {
	while (Nb_fil_a_couper < 1) {
		mise_en_place_2();
		for (int i = 0; i = 6; i++) {
			if (Fil[i] == 1) {
				Nb_fil_a_couper ++;
			}
		}
	}
}

void mise_en_place_2() {
	for (int i = 0; i = 6; i++) {
		if (Fil_present[i] == 1) {
			Led[i] = random(2);
			Etoile[i] = random(2);
			if (Led[i] == 0) {
				if (Bleu[i] == 0) ligne = 0;
				if (Bleu[i] == 1) ligne = 1;}
			if (Led[i] == 1) {
				if (Bleu[i] == 1) ligne = 2;
				if (Bleu[i] == 0) ligne = 3;}
			if (Etoile[i] == 1) {
				if (Rouge[i] == 0) colonne = 0;
				if (Rouge[i] == 1) colonne = 1;}
			if (Etoile[i] == 0) {
				if (Rouge[i] == 1) colonne = 2;
				if (Rouge[i] == 0) colonne = 3;}

			if (test[ligne][colonne] == 0) {
				Fil[i] = 1;}
			if (test[ligne][colonne] == 1) {
				Fil[i] = 0;}
			if (test[ligne][colonne] == 2) {
				if (serial_number == 0) Fil[i] = 1;
				else Fil[i] = 0;}
			if (test[ligne][colonne] == 3) {
				if (Port_parralele == 1) Fil[i] = 1;
				else Fil[i] = 0;}
			if (test[ligne][colonne] == 4) {
				if (nombre_piles > 2) Fil[i] = 1;
				else Fil[i] = 0;}
		}
	}
}
