#include <Adafruit_NeoPixel.h>
#include <Wire.h>

#define Num_Module           31 //numéro d'adresse esclave de ce module (ne pas mettre 2 identiques)

#define PIXEL_PIN_Led_RGB         2
#define PIXEL_COUNT_Led_RGB       1
Adafruit_NeoPixel stripRGB(PIXEL_COUNT_Led_RGB, PIXEL_PIN_Led_RGB, NEO_GRB + NEO_KHZ800);


#define ROUGE     1
#define BLEU      2
#define VERT      3
#define JAUNE     4

#define Maximum_LVL 5


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

byte lvl = 0;
byte NB_lvl = Maximum_LVL;
byte bouton_appuye = 0;
byte bouton_lvl = 0;
byte voyant_lvl = 0;
byte stage_couleur[Maximum_LVL];
byte bouton_pin[4] = {A0, A1, A3, A2};
byte led_pin[4] = {3, 4, 6, 5};
unsigned long old_time;
unsigned long old_bouton;
bool flag = 0;
byte voyelle = 0;

bool reussite = false;

byte kval = 0;
byte kval_old = 0;

byte mapping[2][3][4] = {
  {//pas de voyelles
    {BLEU, JAUNE, VERT, ROUGE},
    {ROUGE, BLEU, JAUNE, VERT},
    {JAUNE, VERT, BLEU, ROUGE}
  },
  {//avec voyelles
    {BLEU, ROUGE, JAUNE, VERT},
    {JAUNE, VERT, BLEU, ROUGE},
    {VERT, ROUGE, JAUNE, BLEU}
  }
};

void setup() {
  Wire.begin(Num_Module);                // join i2c bus with address ...
  Wire.onReceive(onReceive);
  Wire.onRequest(onRequest);
  stripRGB.begin();
  stripRGB.setPixelColor(0, 150, 150, 150);         //  Set pixel's color (in RAM)
  stripRGB.show();
  Serial.begin(9600);
  Serial.println("\n Module SIMON KTANE");
  for (int i = 0; i < 4; i++) {
    pinMode(bouton_pin[i], INPUT_PULLUP);
    pinMode(led_pin[i], OUTPUT);
    digitalWrite(led_pin[i], LOW);
  }
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
    NB_lvl = random(3, Maximum_LVL + 1);
    Serial.print("Nb de lvl :");
    Serial.println(NB_lvl);
    int ok = 0;
    while (ok == 0) {
    int nombre_identique_0 = 0;
    int nombre_identique_1 = 0;
    int nombre_identique_2 = 0;
    int nombre_identique_3 = 0;
      for (int i = 0; i < NB_lvl; i++){
        stage_couleur[i] = random(0, 4);
        if (stage_couleur[i] == 0) {
          Serial.println("Led Rouge");
          nombre_identique_0 ++;
        }
        if (stage_couleur[i] == 1) {
          Serial.println("Led Bleu");
          nombre_identique_1 ++;
        }
        if (stage_couleur[i] == 2) {
          Serial.println("Led Vert");
          nombre_identique_2 ++;
        }
        if (stage_couleur[i] == 3) {
          Serial.println("Led Jaune");
          nombre_identique_3 ++;
        }
      }
      if (nombre_identique_0 < 3 && nombre_identique_1 < 3 && nombre_identique_2 < 3 && nombre_identique_3 < 3)
        ok = 1;
    }
  }
  if (Module_fini == 0) {
    stripRGB.setPixelColor(0, 0, 0, 100);             //  Set pixel's color (in RAM)
    stripRGB.show();  
    affiche_lumiere();
    Simon();
    if (reussite == false){
      lvl = 0;
      Strike = 1;
      while (Strike == 1) {
        delay(600);
        Strike = 0;
      }
    }
    if (reussite == true){
      lvl++;
    }
    if (lvl >= NB_lvl) {
      Module_fini = 1;
      lvl --;
    }
  }
  if (Module_fini == 1) {
    delay(100);
    affiche_lumiere();
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
  if (Numero_de_serie == 1 || Numero_de_serie == 2) voyelle = 1;
  if (Val_temps == 9) {
    Demmarage = 1;
    Serial.print("Demmarage");}
}

int BP_Appuye() { //fonction qui donne une valeur pour le BP appuyé
    int nombre_appuye = 0;
    kval = 0;
    if (digitalRead(bouton_pin[0]) == LOW) {
        kval = ROUGE;
        nombre_appuye++;}
    if (digitalRead(bouton_pin[1]) == LOW) {
        kval = BLEU;
        nombre_appuye++;}
    if (digitalRead(bouton_pin[2]) == LOW) {
        kval = VERT;
        nombre_appuye++;}
    if (digitalRead(bouton_pin[3]) == LOW) {
        kval = JAUNE;
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
    if ((voyant_lvl % 2 == 0) && (millis() - old_time > 300)) {
      digitalWrite(led_pin[stage_couleur[voyant_lvl / 2]], HIGH);
      old_time = millis();
      voyant_lvl ++;
    } else if ((voyant_lvl % 2 == 1) && (millis() - old_time > 700)) {
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
    Serial.print("Presence voyelle : ");
    Serial.print(voyelle);
    Serial.print("  Nb erreur : ");
    Serial.print(Nb_Erreur);
    Serial.print("  bouton a appuyer :  ");
    if (mapping[voyelle][Nb_Erreur][stage_couleur[i]] == 1) Serial.println("bouton Rouge");
    if (mapping[voyelle][Nb_Erreur][stage_couleur[i]] == 2) Serial.println("bouton Bleu");
    if (mapping[voyelle][Nb_Erreur][stage_couleur[i]] == 3) Serial.println("bouton Vert");
    if (mapping[voyelle][Nb_Erreur][stage_couleur[i]] == 4) Serial.println("bouton Jaune");
    while (flag == 0){
      affiche_lumiere();
      bouton_appuye = BP_Appuye();
      if (bouton_appuye == 1) Serial.println("bouton appuye : Rouge");
      if (bouton_appuye == 2) Serial.println("bouton appuye : Bleu");
      if (bouton_appuye == 3) Serial.println("bouton appuye : Vert");
      if (bouton_appuye == 4) Serial.println("bouton appuye : Jaune");
      if (bouton_appuye == mapping[voyelle][Nb_Erreur][stage_couleur[i]]) {
        flag = 1;
        Serial.println("Bien appuye");
        delay(300);
      }
      if (bouton_appuye != mapping[voyelle][Nb_Erreur][stage_couleur[i]]  &&  bouton_appuye != 0) {
        delay(300);
        return;
      }
    }
  }
  reussite = true;
}
