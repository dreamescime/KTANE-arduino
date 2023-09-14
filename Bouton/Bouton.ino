#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <U8g2lib.h>

#define Num_Module 26

#define PIXEL_PIN_Led_RGB         2
#define PIXEL_COUNT_Led_RGB       1
Adafruit_NeoPixel stripRGB(PIXEL_COUNT_Led_RGB, PIXEL_PIN_Led_RGB, NEO_GRB + NEO_KHZ800);

#define PIXEL_PIN_Anneau          4
#define PIXEL_COUNT_Anneau        1
Adafruit_NeoPixel stripAnneau(PIXEL_COUNT_Anneau, PIXEL_PIN_Anneau, NEO_GRB + NEO_KHZ800);

#define PIXEL_PIN_Bande           5
#define PIXEL_COUNT_Bande         1
Adafruit_NeoPixel stripBande(PIXEL_COUNT_Bande, PIXEL_PIN_Bande, NEO_GRB + NEO_KHZ800);

#define BP                        3

// txt bouton
#define Annuler      1
#define Exploser     2
#define Maintenir    3
#define Pousser      4
// couleur led et bande
#define Bleu         1
#define Rouge        2
#define Blanc        3
#define Jaune        4
#define Vert         5
// duree du relacher le bouton immediatement en milli seconde
#define Temps_relacher 500

// Create a color:
int color_Bleu  = strip.Color(   0 ,   0 , 255 );
int color_Rouge = strip.Color( 255 ,   0 ,   0 );
int color_Blanc = strip.Color( 255 , 255 , 255 );
int color_Jaune = strip.Color( 255 , 255 ,   0 );
int color_Vert  = strip.Color(   0 , 255 ,   0 );


uint8_t Recep[6];
byte Numero_de_serie = 0;
byte Nb_Batteries = 0;
byte Port = 0;
byte Nb_Erreur = 0;
byte Indicateur = 0;
uint8_t Strike = 0;
uint8_t Module_fini = 0;
byte Val_temps = 0;
byte Val_temps_1 = 0;
byte Val_temps_4 = 0;
byte Val_temps_5 = 0;

byte couleur_Bande = 0;
byte couleur_Bouton = 0;
byte txt = 0;
String txt_display;

byte bouton_appuye = 0;

void setup() {
	stripRGB.begin();
	stripAnneau.begin();
	stripBande.begin();
	stripRGB.show();
	stripAnneau.show();
	stripBande.show();
	
	Wire.begin(Num_Module);                // join i2c bus with address ...
	Wire.onRequest(requestEvent); // register event
	Wire.onReceive(receiveEvent); // register event
	Serial.begin(9600);
	Serial.println("\n Module Jeu de Mot KTANE");
	u8g2.begin();
	randomSeed(millis());
	couleur_Bande = random(1, 6);
	couleur_Bouton = random(1, 6);
	txt = random(1, 5);
	if (txt == Annuler) txt_display = "Annuler";
	if (txt == Exploser) txt_display = "Exploser";
	if (txt == Maintenir) txt_display = "Maintenir";
	if (txt == Pousser) txt_display = "Pousser";
	affiche();
}

void loop() {
	bouton_appuye = BP_Appuye();
	if (bouton_appuye == 1)
		Appuyer();
	affiche();
}

void requestEvent() {
  Wire.write(Strike);
  Wire.write(Module_fini);
  Strike = 0;
}

void receiveEvent(int howMany) {
  for (int i = 0; i = 6; i++) {
    int c = Wire.read();
    Recep[i] = c;
  }
  Numero_de_serie = Recep[0];
  Nb_Batteries = Recep[1];
  Port = Recep[2];
  Nb_Erreur = Recep[3];
  Indicateur = Recep[4];
  Val_temps = Recep[5];
  Val_temps_5 = Val_temps / 100;
  Val_temps_4 = (Val_temps - 100 * Val_temps_5) / 10;
  Val_temps_1 = (Val_temps - 100 * Val_temps_5 - 10 * Val_temps_4);
}

void affiche() {
	u8g2.setFont(u8g2_font_ncenB14_tf);
	u8g2.setFontDirection(0);
	u8g2.drawStr(0, 10, txt_display);
	for (i = 0; i < PIXEL_COUNT_Anneau; i++) {
		if (couleur_Bouton == Bleu ) stripAnneau.setPixelColor(i, color_Bleu);
		if (couleur_Bouton == Rouge) stripAnneau.setPixelColor(i, color_Rouge);
		if (couleur_Bouton == Blanc) stripAnneau.setPixelColor(i, color_Blanc);
		if (couleur_Bouton == Jaune) stripAnneau.setPixelColor(i, color_Jaune);
		if (couleur_Bouton == Vert ) stripAnneau.setPixelColor(i, color_Vert);
	}
	if (bouton_appuye != 0) {
		for (i = 0; i < PIXEL_COUNT_Bande; i++) {
			if (couleur_Bande == Bleu ) stripBande.setPixelColor(i, color_Bleu);
			if (couleur_Bande == Rouge) stripBande.setPixelColor(i, color_Rouge);
			if (couleur_Bande == Blanc) stripBande.setPixelColor(i, color_Blanc);
			if (couleur_Bande == Jaune) stripBande.setPixelColor(i, color_Jaune);
			if (couleur_Bande == Vert ) stripBande.setPixelColor(i, color_Vert);
		}
	}
}

int BP_Appuye() { //fonction qui donne une valeur pour le BP appuyé
    int nombre_appuye = 0;
    kval = 0;
    if (digitalRead(BP) == LOW) {
        kval = 1;
        nombre_appuye++;}
    if (nombre_appuye > 1){ //si plusieurs BP sont appuyé, on renvoie 26 (erreur)
        return 26;}
        else if (kval_old == kval) { //si BP identique au précédent resultat, on renvois 0
            return 0;}
            else{kval_old = kval; // sinon on renvoie la valeur du BP appuyé
                return kval;}
}

void Appuyer() {
	affiche();
	if (couleur_Bouton == Bleu && txt == Annuler)
		Maintenir();
	else if (Nb_Batteries > 1 && txt == Exploser)
		Relacher();
	else if (couleur_Bouton == Blanc && Indicateur == 2)
		Maintenir();
	else if (Nb_Batteries > 2 && Indicateur == 10)
		Relacher();
	else if (couleur_Bouton == Jaune)
		Maintenir();
	else if (couleur_Bouton == Rouge)
		Relacher();
	else Maintenir();
}

void Maintenir() {
	if (couleur_Bande == Bleu) {
		while(bouton_appuye == 1) {
			bouton_appuye = BP_Appuye();
		}
		if (Val_temps_4 == 1) {
			Module_fini = 1;
		} else Strike = 1;
	} else if (couleur_Bande == Blanc) {
		while(bouton_appuye == 1) {
			bouton_appuye = BP_Appuye();
		}
		if (Val_temps_1 == 1) {
			Module_fini = 1;
		} else Strike = 1;
		
	} else if (couleur_Bande == Jaune) {
		while(bouton_appuye == 1) {
			bouton_appuye = BP_Appuye();
		}
		if (Val_temps_5 == 1) {
			Module_fini = 1;
		} else Strike = 1;
		
	} else {
		while(bouton_appuye == 1) {
			bouton_appuye = BP_Appuye();
		}
		if (Val_temps_1 == 1) {
			Module_fini = 1;
		} else Strike = 1;
	}
}

void Relacher() {
	unsigned long temps_fin = millis() + Temps_relacher;
	while(bouton_appuye == 1) {
		bouton_appuye = BP_Appuye();
	}
	if (millis() > temps_fin) {
			Module_fini = 1;
		} else Strike = 1;
}

