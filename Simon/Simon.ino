#include <Adafruit_NeoPixel.h>
#include <Wire.h>

#define Adresse_esclave           61 //numéro d'adresse esclave de ce module (ne pas mettre 2 identiques)

#define PIXEL_PIN_Led_RGB         2
#define PIXEL_COUNT_Led_RGB       1
Adafruit_NeoPixel stripRGB(PIXEL_COUNT_Led_RGB, PIXEL_PIN_Led_RGB, NEO_GRB + NEO_KHZ800);


#define ROUGE     1
#define JAUNE     2
#define VERT      3
#define BLEU      4

#define Maximum_LVL 5

byte lvl = 0;
byte NB_lvl = 0;
byte bouton_appuye = 0;
byte bouton_lvl = 0;
byte voyant_lvl = 0;
byte stage_couleur[Maximum_LVL];
byte bouton_pin[4] = {3, 4, 5, 6};
byte led_pin[4] = {7, 8, 9, 10};
unsigned long old_time;
unsigned long old_bouton;
bool flag = 0;
byte strike = 0;
byte voyelle = 0;

bool module_fini = 0;

byte kval = 0;
byte kval_old = 0;

mapping[2][3][4] = {
	{//pas de voyelles
		{BLEU, ROUGE, VERT, JAUNE},
		{ROUGE, VERT, JAUNE, BLEU},
		{JAUNE, ROUGE, BLEU, VERT}
	},
	{//avec voyelles
		{BLEU, VERT, JAUNE, ROUGE},
		{JAUNE, ROUGE, BLEU, VERT},
		{VERT, BLEU, JAUNE, ROUGE}
	}
}

void setup() {
	Wire.begin(Adresse_esclave);
	stripRGB.begin();
	stripRGB.show();
	Serial.begin(9600);
	Serial.println("\n Module SIMON KTANE");
	for (int i = 0, i < 4, i++) {
		pinMode(bouton_pin[i], INPUT_PULLUP);
		pinMode(led_pin[i], OUTPUT);
		digitalWrite(led_pin[i], LOW);
	}
	NB_lvl = random(3, Maximum_LVL + 1);
	for (int i = 0, i < NB_lvl, i++)
		stage_couleur[i] = random(0, 4);
}

void loop() {
	if (module_fini == 0) {
		affiche_lumiere();
		Simon();
		if (reussite == false){
			lvl = 0;
			strike = 1;
			while (strike == 1) {
				delay(100);
				
			}
		}
		if (reussite == true){
			lvl++;
		}
		if (lvl > NB_lvl) module_fini = 1;
	}
	if (module_fini == 1) {
		delay(1000);
	}
}


int BP_Appuye() { //fonction qui donne une valeur pour le BP appuyé
    int nombre_appuye = 0;
    kval = 0;
    if (digitalRead(bouton_pin[0]) == LOW) {
        kval = ROUGE;
        nombre_appuye++;}
    if (digitalRead(bouton_pin[1]) == LOW) {
        kval = JAUNE;
        nombre_appuye++;}
    if (digitalRead(bouton_pin[2]) == LOW) {
        kval = VERT;
        nombre_appuye++;}
    if (digitalRead(bouton_pin[3]) == LOW) {
        kval = BLEU;
        nombre_appuye++;}
    if (nombre_appuye > 1){ //si plusieurs BP sont appuyé, on renvoie 5 (erreur)
        return 5;}
        else if (kval_old == kval) { //si BP identique au précédent resultat, on renvois 0
            return 0;}
            else{kval_old = kval; // sinon on renvoie la valeur du BP appuyé
                return kval;}
}

void affiche_lumiere() {
	if (voyant_lvl >= ((lvl + 1) * 2)) {
		if (millis() - old_time > 700) {
			old_time = millis();
			voyant_lvl = 0;
		}
	} else {
		if ((voyant_lvl % 2 == 0) && (millis() + old_time > 300)) {
			digitalWrite(led_pin[stage_couleur[voyant_lvl / 2]], HIGH);
			old_time = millis();
			voyant_lvl ++;
		} else if ((voyant_lvl % 2 == 1) && (millis() + old_time > 700)) {
			digitalWrite(led_pin[stage_couleur[voyant_lvl / 2]], LOW);
			old_time = millis();
			voyant_lvl ++;
		}
	}
}

void Simon() {
	for(int i = 0; i < (lvl + 1); i++){
		flag = 0;
		reussite = false;
		while (flag == 0){
			affiche_lumiere();
			bouton_appuye = BP_Appuye();
			if (bouton_appuye == mapping[voyelle][strike][stage_couleur[i]){
				flag = 1;
				delay(300);
			}
			if (bouton_appuye != mapping[voyelle][strike][stage_couleur[i]  &&  bouton_appuye != 0){
				delay(300);
				return;
			}
		}
	}
	reussite = true;
}
