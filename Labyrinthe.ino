#include <FastLED.h>

#define DATA_PIN_laby    3  // Digital IO pin connected to the NeoPixels
#define NUM_LEDS_laby   64  // Number of NeoPixels (8 lignes de 8 points)
#define LUMINOSITE_laby  8

#define DATA_PIN_etat    4  // Digital IO pin connected to the NeoPixels
#define NUM_LEDS_etat    5  // Number of NeoPixels (8 lignes de 8 points)

#define BP_HAUT          5
#define BP_BAS           6
#define BP_GAUCHE        7
#define BP_DROITE        8

CRGB leds_laby[NUM_LEDS_laby];
CRGB leds_etat[NUM_LEDS_etat];


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

byte labyrinthe[15] [15] = {};

byte code[] = {1, 2, 3, 4, 5, 6, 7, 8};

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

byte NB_erreur = 0;

byte bouton_appuye = 0;
byte kval = 0;
byte kval_old = 0;
byte num_labyrinthe = 0;

byte i = 0;
byte j = 0;

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

	for (byte h = 0; h < 250; h++) { //mellange
		i = random(0, 8); 
		j = random(0, 8);
		byte swap = code[i];
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

void choix_labyrinthe(byte val_labyrinthe) {
	if (val_labyrinthe == 1) {
		for(i = 0; i < 15; i++) {
			for(j = 0; j < 15; j++) {
        bool resultatBool = labyrinthe_1[i] & (1 << (15 - j));
				labyrinthe[i] [j] = resultatBool;
			}
		}
	}
	if (val_labyrinthe == 2) {
		for(i = 0; i < 15; i++) {
			for(j = 0; j < 15; j++) {
        bool resultatBool = labyrinthe_2[i] & (1 << (15 - j));
       labyrinthe[i] [j] = resultatBool;
			}
		}
	}
	if (val_labyrinthe == 3) {
		for(i = 0; i < 15; i++) {
			for(j = 0; j < 15; j++) {
        bool resultatBool = labyrinthe_3[i] & (1 << (15 - j));
       labyrinthe[i] [j] = resultatBool;
			}
		}
	}
	if (val_labyrinthe == 4) {
		for(i = 0; i < 15; i++) {
			for(j = 0; j < 15; j++) {
        bool resultatBool = labyrinthe_4[i] & (1 << (15 - j));
       labyrinthe[i] [j] = resultatBool;
			}
		}
	}
	if (val_labyrinthe == 5) {
		for(i = 0; i < 15; i++) {
			for(j = 0; j < 15; j++) {
        bool resultatBool = labyrinthe_5[i] & (1 << (15 - j));
       labyrinthe[i] [j] = resultatBool;
			}
		}
	}
	if (val_labyrinthe == 6) {
		for(i = 0; i < 15; i++) {
			for(j = 0; j < 15; j++) {
        bool resultatBool = labyrinthe_6[i] & (1 << (15 - j));
       labyrinthe[i] [j] = resultatBool;
			}
		}
	}
	if (val_labyrinthe == 7) {
		for(i = 0; i < 15; i++) {
			for(j = 0; j < 15; j++) {
        bool resultatBool = labyrinthe_7[i] & (1 << (15 - j));
       labyrinthe[i] [j] = resultatBool;
			}
		}
	}
	if (val_labyrinthe == 8) {
		for(i = 0; i < 15; i++) {
			for(j = 0; j < 15; j++) {
        bool resultatBool = labyrinthe_8[i] & (1 << (15 - j));
       labyrinthe[i] [j] = resultatBool;
			}
		}
	}
}

void position_A_B_S() {
	for(byte i = 0; i < 15; i++) {
		for(byte j = 0; j < 15; j++) {
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
		else if (labyrinthe[(pos_x * 2 + 1)][(pos_y * 2)] == 0) pos_x ++;
		else if (labyrinthe[(pos_x * 2 + 1)][(pos_y * 2)] == 1) erreur();
	}
	if (bouton_appuye == 2) {
		if (pos_x == 0) {}
		else if (labyrinthe[(pos_x * 2 - 1)][(pos_y * 2)] == 0) pos_x --;
		else if (labyrinthe[(pos_x * 2 - 1)][(pos_y * 2)] == 1) erreur();
	}
	if (bouton_appuye == 3) {
		if (pos_y == 7) {}
		else if (labyrinthe[(pos_x * 2)][(pos_y * 2 + 1)] == 0) pos_y ++;
		else if (labyrinthe[(pos_x * 2)][(pos_y * 2 + 1)] == 1) erreur();
	}
	if (bouton_appuye == 4) {
		if (pos_y == 0) {}
		else if (labyrinthe[(pos_x * 2)][(pos_y * 2 - 1)] == 0) pos_y --;
		else if (labyrinthe[(pos_x * 2)][(pos_y * 2 - 1)] == 1) erreur();
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
	for(i = 0; i < NB_erreur; i++) {
		leds_etat[i].setRGB(255, 0, 0);
	}
	FastLED.show();
	if (NB_erreur == 1) {
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
	}
	if (NB_erreur == 2) {
		for(i = 0; i < 64; i++) {
			leds_laby[i].setRGB(255, 0, 0);
		}
		FastLED.show();
		delay(100);
		for(i = 0; i < 64; i++) {
			leds_laby[i].setRGB(0, 0, 0);
		}
		FastLED.show();
		delay(100);
		for(i = 0; i < 64; i++) {
			leds_laby[i].setRGB(255, 0, 0);
		}
		FastLED.show();
		delay(100);
		for(i = 0; i < 64; i++) {
			leds_laby[i].setRGB(0, 0, 0);
		}
		FastLED.show();
		allume_led();
		
	}
	if (NB_erreur == 3) {
		for(i = 0; i < 64; i++) {
			leds_laby[i].setRGB(255, 0, 0);
		}
		FastLED.show();
		delay(100);
		for(i = 0; i < 64; i++) {
			leds_laby[i].setRGB(0, 0, 0);
		}
		FastLED.show();
		delay(100);
		for(i = 0; i < 64; i++) {
			leds_laby[i].setRGB(255, 0, 0);
		}
		FastLED.show();
		delay(100);
		for(i = 0; i < 64; i++) {
			leds_laby[i].setRGB(0, 0, 0);
		}
		FastLED.show();
		delay(100);
		for(i = 0; i < 64; i++) {
			leds_laby[i].setRGB(255, 0, 0);
		}
		FastLED.show();
		delay(100);
		for(i = 0; i < 64; i++) {
			leds_laby[i].setRGB(0, 0, 0);
		}
		FastLED.show();
		allume_led();
		while(1) {}
	}
}

void reussite() {
	delay(250);
	for(i = 0; i < 64; i++) {
		leds_laby[i].setRGB(0, 255, 0);
	}
	FastLED.show();
	delay(100);
	for(i = 0; i < 64; i++) {
		leds_laby[i].setRGB(0, 0, 0);
	}
	allume_led();
	delay(100);
	for(i = 0; i < 64; i++) {
		leds_laby[i].setRGB(0, 255, 0);
	}
	FastLED.show();
	delay(100);
	for(i = 0; i < 64; i++) {
		leds_laby[i].setRGB(0, 0, 0);
	}
	allume_led();
	delay(100);
	for(i = 0; i < 64; i++) {
		leds_laby[i].setRGB(0, 255, 0);
	}
	FastLED.show();
	delay(100);
	for(i = 0; i < 64; i++) {
		leds_laby[i].setRGB(0, 0, 0);
	}
	FastLED.show();
	num_labyrinthe ++;

	if (num_labyrinthe < 8) {
		choix_labyrinthe(code[num_labyrinthe]);

		position_A_B_S();
		byte pos_x = 0;
		byte pos_y = 0;
		byte pos_xy = 0;

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
		val_rgb = 65536L * i / NUM_LEDS_laby;
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
