#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <U8g2lib.h>

#define Num_Module 66

#define PIXEL_PIN_Led_RGB         2
#define PIXEL_COUNT_Led_RGB       1
Adafruit_NeoPixel stripRGB(PIXEL_COUNT_Led_RGB, PIXEL_PIN_Led_RGB, NEO_GRB + NEO_KHZ800);
U8G2_ST7920_128X64_1_SW_SPI u8g2(U8G2_R0, /* clock=*/ 13, /* data=*/ 11, /* CS=*/ 10, /* reset=*/ 8);

// txt bouton
#define BP_Haut_1      5
#define BP_Haut_2      6
#define BP_Haut_3      7
#define BP_Haut_4      8
#define BP_Haut_5      9
#define BP_Bas_1       A0
#define BP_Bas_2       A1
#define BP_Bas_3       A2
#define BP_Bas_4       A3
#define BP_Bas_5       A5

#define BP_Valide       12

const char liste_mots[35][5] = {
{ 'A', 'B', 'A', 'T', 'S'},
{ 'A', 'B', 'I', 'M', 'E'},
{ 'A', 'B', 'O', 'I', 'S'},
{ 'A', 'D', 'I', 'E', 'U'},
{ 'D', 'E', 'L', 'T', 'A'},
{ 'D', 'E', 'N', 'S', 'E'},
{ 'D', 'E', 'V', 'I', 'N'},
{ 'D', 'I', 'V', 'I', 'N'},
{ 'D', 'R', 'A', 'M', 'E'},
{ 'D', 'R', 'O', 'I', 'T'},
{ 'E', 'N', 'V', 'O', 'L'},
{ 'E', 'N', 'V', 'I', 'E'},
{ 'E', 'N', 'V', 'O', 'I'},
{ 'E', 'R', 'R', 'E', 'S'},
{ 'E', 'S', 'S', 'A', 'I'},
{ 'F', 'L', 'E', 'U', 'R'},
{ 'F', 'I', 'N', 'I', 'T'},
{ 'F', 'I', 'O', 'L', 'E'},
{ 'K', 'I', 'L', 'O', 'S'},
{ 'L', 'I', 'T', 'R', 'E'},
{ 'L', 'I', 'V', 'R', 'E'},
{ 'M', 'A', 'S', 'S', 'E'},
{ 'M', 'A', 'T', 'C', 'H'},
{ 'M', 'A', 'T', 'I', 'N'},
{ 'M', 'A', 'U', 'V', 'E'},
{ 'P', 'O', 'S', 'E', 'R'},
{ 'P', 'O', 'R', 'T', 'S'},
{ 'P', 'O', 'U', 'L', 'E'},
{ 'S', 'A', 'L', 'I', 'R'},
{ 'T', 'A', 'I', 'R', 'E'},
{ 'T', 'A', 'R', 'I', 'F'},
{ 'T', 'A', 'S', 'S', 'E'},
{ 'V', 'A', 'L', 'V', 'E'},
{ 'V', 'A', 'N', 'N', 'E'},
{ 'V', 'E', 'N', 'T', 'E'}
};
char Mot_choisi[5];
char lettre_possible[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y'};
char lettre_choisi[5][5];

int lettre_1 = 0;
int lettre_2 = 0;
int lettre_3 = 0;
int lettre_4 = 0;
int lettre_5 = 0;

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
int kval_old = 0;

void setup() {
  stripRGB.begin();
  stripRGB.show();
    pinMode(BP_Haut_1, INPUT_PULLUP);
    pinMode(BP_Haut_2, INPUT_PULLUP);
    pinMode(BP_Haut_3, INPUT_PULLUP);
    pinMode(BP_Haut_4, INPUT_PULLUP);
    pinMode(BP_Haut_5, INPUT_PULLUP);
    pinMode(BP_Bas_1, INPUT_PULLUP);
    pinMode(BP_Bas_2, INPUT_PULLUP);
    pinMode(BP_Bas_3, INPUT_PULLUP);
    pinMode(BP_Bas_4, INPUT_PULLUP);
    pinMode(BP_Bas_5, INPUT_PULLUP);
    pinMode(BP_Valide, INPUT_PULLUP);
  
  Wire.begin(Num_Module);                // join i2c bus with address ...
  Wire.onRequest(requestEvent); // register event
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);
  Serial.println("\n Module Mot de Passe KTANE");
  u8g2.begin();
  while (bouton_appuye == 0) {
    bouton_appuye = BP_Appuye();
    delay(200);
  }
  randomSeed(millis()+ analogRead(A7));
  affiche();
    choix_mot(random(0, 35));
}

void loop() {
  bouton_appuye = BP_Appuye();
    if(bouton_appuye == 1) lettre_1--;
    if(bouton_appuye == 6) lettre_1++;
    if(bouton_appuye == 2) lettre_2--;
    if(bouton_appuye == 7) lettre_2++;
    if(bouton_appuye == 3) lettre_3--;
    if(bouton_appuye == 8) lettre_3++;
    if(bouton_appuye == 4) lettre_4--;
    if(bouton_appuye == 9) lettre_4++;
    if(bouton_appuye == 5) lettre_5--;
    if(bouton_appuye == 10) lettre_5++;
    if(lettre_1 < 0) lettre_1 = 4;
    if(lettre_2 < 0) lettre_2 = 4;
    if(lettre_3 < 0) lettre_3 = 4;
    if(lettre_4 < 0) lettre_4 = 4;
    if(lettre_5 < 0) lettre_5 = 4;
    if(lettre_1 > 4) lettre_1 = 0;
    if(lettre_2 > 4) lettre_2 = 0;
    if(lettre_3 > 4) lettre_3 = 0;
    if(lettre_4 > 4) lettre_4 = 0;
    if(lettre_5 > 4) lettre_5 = 0;
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
  u8g2.drawStr(0, 10, lettre_choisi[0][lettre_1]);
  u8g2.drawStr(0, 30, lettre_choisi[1][lettre_2]);
  u8g2.drawStr(0, 50, lettre_choisi[2][lettre_3]);
  u8g2.drawStr(0, 70, lettre_choisi[3][lettre_4]);
  u8g2.drawStr(0, 90, lettre_choisi[4][lettre_5]);
}

int BP_Appuye() { //fonction qui donne une valeur pour le BP appuyé
    int nombre_appuye = 0;
    int kval = 0;
    if (digitalRead(BP_Bas_1) == LOW) {
        kval = 1;
        nombre_appuye++;}
    if (digitalRead(BP_Bas_2) == LOW) {
        kval = 2;
        nombre_appuye++;}
    if (digitalRead(BP_Bas_3) == LOW) {
        kval = 3;
        nombre_appuye++;}
    if (digitalRead(BP_Bas_4) == LOW) {
        kval = 4;
        nombre_appuye++;}
    if (digitalRead(BP_Bas_5) == LOW) {
        kval = 5;
        nombre_appuye++;}
    if (digitalRead(BP_Haut_1) == LOW) {
        kval = 6;
        nombre_appuye++;}
    if (digitalRead(BP_Haut_2) == LOW) {
        kval = 7;
        nombre_appuye++;}
    if (digitalRead(BP_Haut_3) == LOW) {
        kval = 8;
        nombre_appuye++;}
    if (digitalRead(BP_Haut_4) == LOW) {
        kval = 9;
        nombre_appuye++;}
    if (digitalRead(BP_Haut_5) == LOW) {
        kval = 10;
        nombre_appuye++;}
    if (digitalRead(BP_Valide) == LOW) {
        kval = 11;
        nombre_appuye++;}
    if (nombre_appuye > 1){ //si plusieurs BP sont appuyé, on renvoie 26 (erreur)
        return 26;}
        else if (kval_old == kval) { //si BP identique au précédent resultat, on renvois 0
            return 0;}
            else{kval_old = kval; // sinon on renvoie la valeur du BP appuyé
                return kval;}
}

void choix_mot(int val) {
    Serial.println("Mot choisi");
    for(int i = 0; i < 5; i++){
        Mot_choisi[i] = liste_mots[val][i];
        lettre_choisi[i][0] = Mot_choisi[i];
        Serial.print(Mot_choisi[i]);
        Serial.print("  ");
    }
    Serial.println();
    int Mauvais_choix = 0;
    int Mot_ok = 0;
    int test_lettre = 0;
    int lettre_identique = 0;
    while(Mot_ok == 0) {
        for(int i = 0; i < 5; i++) {
            while(test_lettre == 0) {
                for (int h = 0; h < 2000; h++) { //mellange les lettres
                    int k = random(0, 7); 
                    int l = random(0, 25);
                    int swap = lettre_possible[l];
                    lettre_possible[l] = lettre_possible[k];
                    lettre_possible[k] = swap;
                }
                for(int j = 1; j <5; j++) {
                    lettre_choisi[i][j] = lettre_possible[j];
                }
                for(int j = 1; j <5; j++) {
                    if(lettre_choisi[i][0] == lettre_choisi[i][j]) Mauvais_choix ++;
                }
                if(Mauvais_choix != 0) {
                    Mauvais_choix = 0;
                    test_lettre = 0;
                }
                else {
                    test_lettre = 1;
                    Mauvais_choix = 0;
                }
            }
            test_lettre = 0;
        }
        Serial.println("Lettres choisies");
        for(int i = 0; i<5; i++){
            for(int j = 0; j < 5; j++){
                Serial.print(lettre_choisi[i][j]);
                Serial.print("  ");
            }
            Serial.println();
        }
        for(int i = 0; i <35; i++) {
            if(i == val) i++;
            for(int j = 0; j < 5; j++) {
                for(int k = 0; k < 5; k++) {
                    if(liste_mots[i][j] == lettre_choisi[j][k]) lettre_identique ++;
                }
            }
            if(lettre_identique == 5) {
                Mauvais_choix ++;
                Serial.print("Mot identique trouvee :  ");
                for(int j = 0; j < 5; j++){
                    Serial.print(liste_mots[i][j]);
                }
                Serial.println();
            }
            lettre_identique = 0;
        }
        if(Mauvais_choix != 0) {
            Serial.println("il existe des mots identiques");
            Mot_ok = 0;
            Mauvais_choix = 0;
        }
        else {
            Serial.println("Il n'existe pas d'autres mots identiques");
            Mot_ok = 1;
            Mauvais_choix = 0;
        }
    }
    for(int i = 0; i < 5; i++) {
        for (int h = 0; h < 100; h++) { //mellange les lettres
            int k = random(0, 5); 
            int l = random(0, 5);
            int swap = lettre_choisi[i][l];
            lettre_choisi[i][l] = lettre_choisi[i][k];
            lettre_choisi[i][k] = swap;
        }
    }
    Serial.println("Melange des lettres");
    for(int i = 0; i<5; i++){
        for(int j = 0; j < 5; j++){
            Serial.print(lettre_choisi[i][j]);
            Serial.print("  ");
        }
        Serial.println();
    }
}

void verification() {
    int bonne_lettre = 0;
    if(Mot_choisi[0] ==  lettre_choisi[0][lettre_1]) bonne_lettre++;
    if(Mot_choisi[1] ==  lettre_choisi[1][lettre_2]) bonne_lettre++;
    if(Mot_choisi[2] ==  lettre_choisi[2][lettre_3]) bonne_lettre++;
    if(Mot_choisi[3] ==  lettre_choisi[3][lettre_4]) bonne_lettre++;
    if(Mot_choisi[4] ==  lettre_choisi[4][lettre_5]) bonne_lettre++;

    if(bonne_lettre == 5) {
        
        Module_fini == 1;
    }
    else Strike = 1;
}
