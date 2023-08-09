#include <FastLED.h>

#define DATA_PIN_laby    3  // Digital IO pin connected to the NeoPixels
#define NUM_LEDS_laby 64  // Number of NeoPixels (8 lignes de 8 points)
#define LUMINOSITE_laby 8

#define DATA_PIN_etat    4  // Digital IO pin connected to the NeoPixels
#define NUM_LEDS_etat 5  // Number of NeoPixels (8 lignes de 8 points)

const char BP_HAUT = 5;
const char BP_BAS = 6;
const char BP_GAUCHE = 7;
const char BP_DROITE = 8;

CRGB leds_laby[NUM_LEDS_laby];
CRGB leds_etat[NUM_LEDS_etat];

const int labyrinthe_1[15] [15] = {
{0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0}, // ligne 0
{1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0}, // ligne 1
{0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0}, // ligne 2
{0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0}, // ligne 3
{0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0}, // ligne 4
{0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1}, // ligne 5
{0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0}, // ligne 6
{0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0}, // ligne 7
{0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0}, // ligne 8
{1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0}, // ligne 9
{0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0}, // ligne 10
{0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0}, // ligne 11
{0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0}, // ligne 12
{0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0}, // ligne 13
{0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0}  // ligne 14
} ;

const int labyrinthe_2[15] [15] = {
{0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0}, // ligne 0
{0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0}, // ligne 1
{0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0}, // ligne 2
{0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0}, // ligne 3
{0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0}, // ligne 4
{1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0}, // ligne 5
{0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0}, // ligne 6
{0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1}, // ligne 7
{0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0}, // ligne 8
{0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0}, // ligne 9
{0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0}, // ligne 10
{0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0}, // ligne 11
{0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0}, // ligne 12
{0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1}, // ligne 13
{0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0}  // ligne 14
} ;

const int labyrinthe_3[15] [15] = {
{0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0}, // ligne 0
{0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0}, // ligne 1
{0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0}, // ligne 2
{1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0}, // ligne 3
{0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0}, // ligne 4
{0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0}, // ligne 5
{0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0}, // ligne 6
{0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0}, // ligne 7
{0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0}, // ligne 8
{0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0}, // ligne 9
{0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0}, // ligne 10
{1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0}, // ligne 11
{0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0}, // ligne 12
{0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0}, // ligne 13
{0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}  // ligne 14
} ;

const int labyrinthe_4[15] [15] = {
{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // ligne 0
{0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0}, // ligne 1
{0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0}, // ligne 2
{0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0}, // ligne 3
{0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0}, // ligne 4
{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0}, // ligne 5
{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0}, // ligne 6
{0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1}, // ligne 7
{0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0}, // ligne 8
{1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0}, // ligne 9
{0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0}, // ligne 10
{0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0}, // ligne 11
{0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0}, // ligne 12
{0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1}, // ligne 13
{0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0}  // ligne 14
} ;

const int labyrinthe_5[15] [15] = {
{0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0}, // ligne 0
{0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1}, // ligne 1
{0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0}, // ligne 2
{0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0}, // ligne 3
{0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0}, // ligne 4
{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0}, // ligne 5
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0}, // ligne 6
{1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1}, // ligne 7
{0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0}, // ligne 8
{0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0}, // ligne 9
{0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0}, // ligne 10
{0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1}, // ligne 11
{0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0}, // ligne 12
{0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0}, // ligne 13
{0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0}  // ligne 14
} ;

const int labyrinthe_6[15] [15] = {
{0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0}, // ligne 0
{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0}, // ligne 1
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0}, // ligne 2
{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0}, // ligne 3
{0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0}, // ligne 4
{1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1}, // ligne 5
{0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0}, // ligne 6
{1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0}, // ligne 7
{0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0}, // ligne 8
{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0}, // ligne 9
{0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0}, // ligne 10
{1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1}, // ligne 11
{0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0}, // ligne 12
{0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0}, // ligne 13
{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0}  // ligne 14
} ;

const int labyrinthe_7[15] [15] = {
{0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0}, // ligne 0
{0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1}, // ligne 1
{0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0}, // ligne 2
{0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0}, // ligne 3
{0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0}, // ligne 4
{0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0}, // ligne 5
{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0}, // ligne 6
{1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0}, // ligne 7
{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0}, // ligne 8
{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0}, // ligne 9
{0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0}, // ligne 10
{0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0}, // ligne 11
{0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0}, // ligne 12
{0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0}, // ligne 13
{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}  // ligne 14
} ;

const int labyrinthe_8[15] [15] = {
{0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0}, // ligne 0
{0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1}, // ligne 1
{0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0}, // ligne 2
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0}, // ligne 3
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0}, // ligne 4
{1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1}, // ligne 5
{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0}, // ligne 6
{0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0}, // ligne 7
{0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0}, // ligne 8
{0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1}, // ligne 9
{0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0}, // ligne 10
{1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0}, // ligne 11
{0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0}, // ligne 12
{0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0}, // ligne 13
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0}  // ligne 14
} ;

int labyrinthe[15] [15] = {};

int code[] = {1, 2, 3, 4, 5, 6, 7, 8};

int pos_x = 0;
int pos_y = 0;
int pos_xy = 0;
int marqueur_A_X = 0;
int marqueur_A_Y = 0;
int pos_A = 0;
int marqueur_B_X = 0;
int marqueur_B_Y = 0;
int pos_B = 0;
int marqueur_S_X = 0;
int marqueur_S_Y = 0;
int pos_S = 0;

int NB_erreur = 0;

byte bouton_appuye = 0;
byte kval = 0;
byte kval_old = 0;
byte num_labyrinthe = 0;

void setup() {
	pinMode(BP_HAUT, INPUT_PULLUP);
	pinMode(BP_BAS, INPUT_PULLUP);
	pinMode(BP_GAUCHE, INPUT_PULLUP);
	pinMode(BP_DROITE, INPUT_PULLUP);
	FastLED.addLeds<NEOPIXEL, DATA_PIN_laby>(leds_laby, NUM_LEDS_laby);
	FastLED.addLeds<NEOPIXEL, DATA_PIN_etat>(leds_etat, NUM_LEDS_etat);
	FastLED.setBrightness(LUMINOSITE_laby);

	while (bouton_appuye == 0) {
		bouton_appuye = BP_Appuye();
		delay(50);
	}

	randomSeed(millis());

	int code[] = {1, 2, 3, 4, 5, 6, 7, 8};

	for (int h = 0; h < 250; h++) { //mellange
		int i = random(0, 8); 
		int j = random(0, 8);
		int swap = code[i];
		code[i] = code[j];
		code[j] = swap;
	}

	choix_labyrinthe(code[num_labyrinthe]);

	position_A_B_S();
	allume_led();
}

void loop() {
	deplacement();
	allume_led();
	
	
	if (((pos_x * 2) == marqueur_S_X) && ((pos_y * 2) == marqueur_S_Y)) {
		reussite();
	}
}

void choix_labyrinthe(int val_labyrinthe) {
	if (val_labyrinthe == 1) {
		for(int i = 0; i < 15; i++) {
			for(int j = 0; j < 15; j++) {
				labyrinthe[i] [j] = labyrinthe_1[i] [j];
			}
		}
	}
	if (val_labyrinthe == 2) {
		for(int i = 0; i < 15; i++) {
			for(int j = 0; j < 15; j++) {
				labyrinthe[i] [j] = labyrinthe_2[i] [j];
			}
		}
	}
	if (val_labyrinthe == 3) {
		for(int i = 0; i < 15; i++) {
			for(int j = 0; j < 15; j++) {
				labyrinthe[i] [j] = labyrinthe_3[i] [j];
			}
		}
	}
	if (val_labyrinthe == 4) {
		for(int i = 0; i < 15; i++) {
			for(int j = 0; j < 15; j++) {
				labyrinthe[i] [j] = labyrinthe_4[i] [j];
			}
		}
	}
	if (val_labyrinthe == 5) {
		for(int i = 0; i < 15; i++) {
			for(int j = 0; j < 15; j++) {
				labyrinthe[i] [j] = labyrinthe_5[i] [j];
			}
		}
	}
	if (val_labyrinthe == 6) {
		for(int i = 0; i < 15; i++) {
			for(int j = 0; j < 15; j++) {
				labyrinthe[i] [j] = labyrinthe_6[i] [j];
			}
		}
	}
	if (val_labyrinthe == 7) {
		for(int i = 0; i < 15; i++) {
			for(int j = 0; j < 15; j++) {
				labyrinthe[i] [j] = labyrinthe_7[i] [j];
			}
		}
	}
	if (val_labyrinthe == 8) {
		for(int i = 0; i < 15; i++) {
			for(int j = 0; j < 15; j++) {
				labyrinthe[i] [j] = labyrinthe_8[i] [j];
			}
		}
	}
}

void position_A_B_S() {
	for(int i = 0; i < 15; i++) {
		for(int j = 0; j < 15; j++) {
			if (labyrinthe[i] [j] == 3) {
				marqueur_A_X = (i/2);
				marqueur_A_Y = (j/2);
			}
			if (labyrinthe[i] [j] == 4) {
				marqueur_B_X = (i/2);
				marqueur_B_Y = (j/2);
			}
			if (labyrinthe[i] [j] == 5) {
				marqueur_S_X = (i/2);
				marqueur_S_Y = (j/2);
			}
		}
	}
	if (marqueur_A_Y == 0) pos_A = ( 0 + marqueur_A_X);
	if (marqueur_A_Y == 1) pos_A = (15 - marqueur_A_X);
	if (marqueur_A_Y == 2) pos_A = (16 + marqueur_A_X);
	if (marqueur_A_Y == 3) pos_A = (31 - marqueur_A_X);
	if (marqueur_A_Y == 4) pos_A = (32 + marqueur_A_X);
	if (marqueur_A_Y == 5) pos_A = (47 - marqueur_A_X);
	if (marqueur_A_Y == 6) pos_A = (48 + marqueur_A_X);
	if (marqueur_A_Y == 7) pos_A = (63 - marqueur_A_X);

	if (marqueur_B_Y == 0) pos_B = ( 0 + marqueur_B_X);
	if (marqueur_B_Y == 1) pos_B = (15 - marqueur_B_X);
	if (marqueur_B_Y == 2) pos_B = (16 + marqueur_B_X);
	if (marqueur_B_Y == 3) pos_B = (31 - marqueur_B_X);
	if (marqueur_B_Y == 4) pos_B = (32 + marqueur_B_X);
	if (marqueur_B_Y == 5) pos_B = (47 - marqueur_B_X);
	if (marqueur_B_Y == 6) pos_B = (48 + marqueur_B_X);
	if (marqueur_B_Y == 7) pos_B = (63 - marqueur_B_X);

	if (marqueur_S_Y == 0) pos_S = ( 0 + marqueur_S_X);
	if (marqueur_S_Y == 1) pos_S = (15 - marqueur_S_X);
	if (marqueur_S_Y == 2) pos_S = (16 + marqueur_S_X);
	if (marqueur_S_Y == 3) pos_S = (31 - marqueur_S_X);
	if (marqueur_S_Y == 4) pos_S = (32 + marqueur_S_X);
	if (marqueur_S_Y == 5) pos_S = (47 - marqueur_S_X);
	if (marqueur_S_Y == 6) pos_S = (48 + marqueur_S_X);
	if (marqueur_S_Y == 7) pos_S = (63 - marqueur_S_X);
}

void deplacement() {
	bouton_appuye = 0;
	
	while (bouton_appuye == 0) {
		bouton_appuye = BP_Appuye();
		delay(50);
	}
	if (bouton_appuye == 1) {
		if (pos_x == 7) {}
		else if (labyrinthe[(pos_x * 2 + 1)] == 0) pos_x ++;
		else if (labyrinthe[(pos_x * 2 + 1)] == 1) erreur();
	}
	if (bouton_appuye == 2) {
		if (pos_x == 0) {}
		else if (labyrinthe[(pos_x * 2 - 1)] == 0) pos_x --;
		else if (labyrinthe[(pos_x * 2 - 1)] == 1) erreur();
	}
	if (bouton_appuye == 3) {
		if (pos_y == 7) {}
		else if (labyrinthe[(pos_x * 2 + 1)] == 0) pos_y ++;
		else if (labyrinthe[(pos_x * 2 + 1)] == 1) erreur();
	}
	if (bouton_appuye == 4) {
		if (pos_y == 0) {}
		else if (labyrinthe[(pos_x * 2 - 1)] == 0) pos_y --;
		else if (labyrinthe[(pos_x * 2 - 1)] == 1) erreur();
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
	if (pos_y == 0) pos_xy = ( 0 + pos_x);
	if (pos_y == 1) pos_xy = (15 - pos_x);
	if (pos_y == 2) pos_xy = (16 + pos_x);
	if (pos_y == 3) pos_xy = (31 - pos_x);
	if (pos_y == 4) pos_xy = (32 + pos_x);
	if (pos_y == 5) pos_xy = (47 - pos_x);
	if (pos_y == 6) pos_xy = (48 + pos_x);
	if (pos_y == 7) pos_xy = (63 - pos_x);

	leds_laby[pos_A].setRGB(0, 0, 255);
	leds_laby[pos_B].setRGB(0, 0, 255);
	leds_laby[pos_S].setRGB(0, 255, 0);
	leds_laby[pos_xy].setRGB(200, 200, 200);

	FastLED.show();
}

void erreur() {
	NB_erreur ++;
	for(int i = 0; i < NB_erreur; i++) {
		leds_etat[i].setRGB(255, 0, 0);
	}
	FastLED.show();
	if (NB_erreur == 1) {
		for(int i = 0; i < 64; i++) {
			leds_laby[i].setRGB(255, 0, 0);
		}
		FastLED.show();
		delay(250);
		for(int i = 0; i < 64; i++) {
			leds_laby[i].setRGB(0, 0, 0);
		}
		FastLED.show();
		allume_led();
	}
	if (NB_erreur == 2) {
		for(int i = 0; i < 64; i++) {
			leds_laby[i].setRGB(255, 0, 0);
		}
		FastLED.show();
		delay(100);
		for(int i = 0; i < 64; i++) {
			leds_laby[i].setRGB(0, 0, 0);
		}
		FastLED.show();
		delay(100);
		for(int i = 0; i < 64; i++) {
			leds_laby[i].setRGB(255, 0, 0);
		}
		FastLED.show();
		delay(100);
		for(int i = 0; i < 64; i++) {
			leds_laby[i].setRGB(0, 0, 0);
		}
		FastLED.show();
		allume_led();
		
	}
	if (NB_erreur == 3) {
		for(int i = 0; i < 64; i++) {
			leds_laby[i].setRGB(255, 0, 0);
		}
		FastLED.show();
		delay(100);
		for(int i = 0; i < 64; i++) {
			leds_laby[i].setRGB(0, 0, 0);
		}
		FastLED.show();
		delay(100);
		for(int i = 0; i < 64; i++) {
			leds_laby[i].setRGB(255, 0, 0);
		}
		FastLED.show();
		delay(100);
		for(int i = 0; i < 64; i++) {
			leds_laby[i].setRGB(0, 0, 0);
		}
		FastLED.show();
		delay(100);
		for(int i = 0; i < 64; i++) {
			leds_laby[i].setRGB(255, 0, 0);
		}
		FastLED.show();
		delay(100);
		for(int i = 0; i < 64; i++) {
			leds_laby[i].setRGB(0, 0, 0);
		}
		FastLED.show();
		allume_led();
		while(1) {}
	}
}

void reussite() {
	delay(250);
	for(int i = 0; i < 64; i++) {
		leds_laby[i].setRGB(0, 255, 0);
	}
	FastLED.show();
	delay(100);
	for(int i = 0; i < 64; i++) {
		leds_laby[i].setRGB(0, 0, 0);
	}
	allume_led();
	delay(100);
	for(int i = 0; i < 64; i++) {
		leds_laby[i].setRGB(0, 255, 0);
	}
	FastLED.show();
	delay(100);
	for(int i = 0; i < 64; i++) {
		leds_laby[i].setRGB(0, 0, 0);
	}
	allume_led();
	delay(100);
	for(int i = 0; i < 64; i++) {
		leds_laby[i].setRGB(0, 255, 0);
	}
	FastLED.show();
	delay(100);
	for(int i = 0; i < 64; i++) {
		leds_laby[i].setRGB(0, 0, 0);
	}
	FastLED.show();
	num_labyrinthe ++;

	if (num_labyrinthe < 8) {
		choix_labyrinthe(code[num_labyrinthe]);

		position_A_B_S();
		int pos_x = 0;
		int pos_y = 0;
		int pos_xy = 0;

		allume_led();
	}
	else {
		rainbow();
	}
}

void rainbow() {
	int r = 0;
	int g = 0;
	int b = 0;
	int val_rgb = 0;
	
	for(int i = 0; i < NUM_LEDS_laby; i++) {
		val_rgb = 65536L * i / NUM_LEDS_laby
		if (val_rgb < 10923) {
			r = 255;
			g = map(val_rgb, 0, 10923, 0, 255);
			b = 0;
		}
		else if (val_rgb < 21845) {
			r = map(val_rgb, 10923, 21845, 255, 0);
			g = 255;
			b = 0;
		}
		else if (val_rgb < 32768) {
			r = 0;
			g = 255;
			b = map(val_rgb, 21845, 32768, 0, 255);
		}
		else if (val_rgb < 43691) {
			r = 0;
			g = map(val_rgb, 32768, 43691, 255, 0);
			b = 255;
		}
		else if (val_rgb < 54613) {
			r = map(val_rgb, 43691, 54613, 0, 255);
			g = 0;
			b = 255;
		}
		else if (val_rgb < 43691) {
			r = 255;
			g = 0;
			b = map(val_rgb, 32768, 43691, 255, 0);
		}
		for(int i = 0; i < 64; i++) {
			leds_laby[i].setRGB(r, g, b);
		}
		FastLED.show();
		delay(100);
	}
}

