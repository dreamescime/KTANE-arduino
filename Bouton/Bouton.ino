#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <U8g2lib.h>

#define Num_Module 26

#define PIXEL_PIN_Led_RGB         2
#define PIXEL_COUNT_Led_RGB       1
Adafruit_NeoPixel stripRGB(PIXEL_COUNT_Led_RGB, PIXEL_PIN_Led_RGB, NEO_GRB + NEO_KHZ800);

#define PIXEL_PIN_Anneau          4
#define PIXEL_COUNT_Anneau        1
Adafruit_NeoPixel stripRGB(PIXEL_COUNT_Anneau, PIXEL_PIN_Anneau, NEO_GRB + NEO_KHZ800);

#define PIXEL_PIN_Bande           5
#define PIXEL_COUNT_Bande         1
Adafruit_NeoPixel stripRGB(PIXEL_COUNT_Bande, PIXEL_PIN_Bande, NEO_GRB + NEO_KHZ800);

#define BP                        3

// txt bouton
#define Annuler      1
#define Exploser     2
#define Relache      3
#define Pousser      4
// couleur led et bande
#define Bleu         1
#define Rouge        2
#define Blanc        3
#define Jaune        4
#define Vert         5


uint8_t Recep[6];
byte Numero_de_serie = 0;
byte Nb_Batteries = 0;
byte Port = 0;
byte Nb_Erreur = 0;
byte Indicateur = 0;
uint8_t Strike = 0;
uint8_t Module_fini = 0;

byte couleur_Bande = 0;
byte couleur_Bouton = 0;
byte txt = 0;

void setup() {
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
}

void loop() {

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

voir affiche() {
	u8g2.setFont(u8g2_font_ncenB14_tf);
	u8g2.setFontDirection(0);
	u8g2.drawStr(0, 10, txt_master);
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
