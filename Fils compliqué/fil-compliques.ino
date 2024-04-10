#include <Adafruit_NeoPixel.h>
#include <Wire.h>

#define Num_Module 71

#define PIXEL_PIN_Led_RGB         2
#define PIXEL_PIN_Led_Blanc       4
#define PIXEL_PIN_Led_Etoile      3

#define PIXEL_COUNT_Led_RGB       1
#define PIXEL_COUNT_Led_Blanc     6
#define PIXEL_COUNT_Led_Etoile    6

Adafruit_NeoPixel stripRGB(PIXEL_COUNT_Led_RGB, PIXEL_PIN_Led_RGB, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripLedBlanc(PIXEL_COUNT_Led_Blanc, PIXEL_PIN_Led_Blanc, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripLedEtoile(PIXEL_COUNT_Led_Etoile, PIXEL_PIN_Led_Etoile, NEO_GRB + NEO_KHZ800);


int Recep[6];
int Numero_de_serie = 0;
int Nb_Batteries = 2;
int Port = 0;
int Nb_Erreur = 0;
int Indicateur = 0;
int Strike = 1;
int Module_fini = 0;
int Val_temps = 0;
int Val_temps_1 = 0;
int Val_temps_4 = 0;
int Val_temps_5 = 0;
int Demmarage = 0;

const byte borne[6] = {0, 1, 2, 3, 6, 7};
byte Fil_present[6];
byte Bleu[6];
byte Rouge[6];
byte Led[6];
byte Etoile[6];
int Nb_fil_a_couper = 0;
int tension = 0;
byte tension_fil[6];
byte Fil[6];
byte ligne = 0;
byte colonne = 0;

const byte test[4][4] = {
  {0, 0, 2, 0},
  {1, 3, 2, 2},
  {3, 1, 2, 3},
  {4, 4, 4, 1}
  };

void setup() {
  
  Wire.begin(Num_Module);                // join i2c bus with address ...
  Wire.onReceive(onReceive);
  Wire.onRequest(onRequest);
  Serial.begin(9600);
  Serial.println("\n Module fils complexe KTANE");
  stripRGB.begin();
  stripRGB.setPixelColor(0, 150, 150, 150);         //  Set pixel's color (in RAM)
  stripRGB.show();  
  stripLedBlanc.begin();
  stripLedEtoile.begin();
  stripLedBlanc.show();
  stripLedEtoile.show();

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A6, INPUT);
  pinMode(A7, INPUT);

  Serial.println("En attente du démarrage");  
}


void loop() {
  if (Demmarage == 0) {
    while (Demmarage == 0) {
      delay(250);
      Serial.println(Demmarage);
    }
    delay(1000);
    Serial.println("Demarrage");
    randomSeed(millis());

    couleur_Fil();
    delay(300);
    Serial.println("piege");
    for(int i = 0; i < 6; i++) {
      if (tension_fil[i] == 0) Serial.println("Pas de fil");
      if (tension_fil[i] == 1) Serial.println("Fil Vert");
      if (tension_fil[i] == 2) Serial.println("Fil Bleu");
      if (tension_fil[i] == 3) Serial.println("Fil bleu et rouge");
      if (tension_fil[i] == 4) Serial.println("Fil Rouge");
      if (tension_fil[i] == 5) Serial.println("Fil Noir");
    }
    delay(300);
    mise_en_place_1();
    
    for(int i = 0; i < 6; i++) {
      if (tension_fil[i] == 0) Serial.println("Pas de fil");
      if (tension_fil[i] == 1) Serial.println("Fil Vert");
      if (tension_fil[i] == 2) Serial.println("Fil Bleu");
      if (tension_fil[i] == 3) Serial.println("Fil bleu et rouge");
      if (tension_fil[i] == 4) Serial.println("Fil Rouge");
      if (tension_fil[i] == 5) Serial.println("Fil Noir");
      if (Led[i] == 1) {
      stripLedBlanc.setPixelColor((5 - i), 100, 100, 100);
      Serial.print("Lumiere blanche sur fil :");
      Serial.println(i + 1);
      }
      if (Etoile[i] == 1) {
      stripLedEtoile.setPixelColor(i, 100, 100, 0);
      Serial.print("Lumiere etoile sur fil :");
      Serial.println(i + 1);
      }
    }
    stripLedBlanc.show();
    stripLedEtoile.show();
  }
  if(Module_fini == 0){
    for(int i = 0; i < 6; i++) {
      if(Fil_present[i] != 0){
        if(tension_fil[i] != tension_sur_fil(analogRead(borne[i]))) {
          delay(100);
          if(tension_fil[i] != tension_sur_fil(analogRead(borne[i]))) { // Check again for debouncing reasons
            if(Fil[i] == 1) {
              Fil[i] = 0;
              Serial.println("bon fil coupé");
              reussite();
            } else {
              Serial.println("mauvais fil coupé !!!");
              erreur();
            }
            tension_fil[i] = tension_sur_fil(analogRead(borne[i]));
          }
        }
        delay(10);
      }
    }
  }
  if (Module_fini == 1) {
    delay(100);
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
  if (Val_temps >= 4) Val_temps_5 = 1;
  else Val_temps_5 = 0;
  if ((Val_temps - 4 * Val_temps_5) >= 2) Val_temps_4 = 1;
  else Val_temps_4 = 0;
  if ((Val_temps - 4 * Val_temps_5 - 2 * Val_temps_4) >= 1) Val_temps_1 = 1;
  else Val_temps_1 = 0;
  if (Val_temps == 9) Demmarage = 1;
}

void couleur_Fil() {
  for (int i = 0; i < 6; i++) {
    tension = analogRead(borne[i]);
	Serial.print("fil ");
	Serial.print(i + 1);
	Serial.print(" valeur ");
	Serial.println(tension);
    if(tension < 10) { // pas de fil
      Fil_present[i] = 0;
      Bleu[i] = 0;
      Rouge[i] = 0;
      tension_fil[i] = 0;
    } else if(tension < 138) { // fil vert
      Fil_present[i] = 1;
      Bleu[i] = 0;
      Rouge[i] = 0;
      tension_fil[i] = 1;
    } else if(tension < 384) { // fil bleu
      Fil_present[i] = 1;
      Bleu[i] = 1;
      Rouge[i] = 0;
      tension_fil[i] = 2;
    } else if(tension < 640) { // fil bleu et rouge
      Fil_present[i] = 1;
      Bleu[i] = 1;
      Rouge[i] = 1;
      tension_fil[i] = 3;
    } else if(tension < 896) { // fil rouge
      Fil_present[i] = 1;
      Bleu[i] = 0;
      Rouge[i] = 1;
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
    if (Fil[j] == 1) {
		Nb_fil_a_couper ++;
		Serial.print(j + 1);
		}
  }
  Serial.println("\n il reste fils a couper : ");
  Serial.println(Nb_fil_a_couper);
  if (Nb_fil_a_couper == 0) {
	Serial.println("Module fini");
    module_desarme();
  }
}

void module_desarme() {
  stripRGB.setPixelColor(0, 255, 0, 0);
  stripRGB.show();
  while(1){}
}

void erreur() {
  stripRGB.setPixelColor(0, 0, 255, 0);
  stripRGB.show();
  delay(1000);
  stripRGB.setPixelColor(0, 0, 0, 0);
  stripRGB.show();
}

void mise_en_place_1() {
	byte test_fil = 0;
  while (test_fil == 0) {
    Nb_fil_a_couper = 0;
    mise_en_place_2();
    Serial.println("\n liste des fils a couper : ");
    for (int i = 0; i < 6; i++) {
      if (Fil[i] == 1) {
        Nb_fil_a_couper ++;
        Serial.print(i + 1);
      }
    }
	if (Nb_fil_a_couper > 1) test_fil = 1;
  }
  Serial.print("\n Nb de fil a couper : ");
  Serial.println(Nb_fil_a_couper);
}

void mise_en_place_2() {
  for (int i = 0; i < 6; i++) {
	if (Fil[i] == 1) i++;
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
        if (Numero_de_serie == 1 || Numero_de_serie == 3) Fil[i] = 1;
        else Fil[i] = 0;}
      if (test[ligne][colonne] == 3) {
        if (Port == 3) Fil[i] = 1;
        else Fil[i] = 0;}
      if (test[ligne][colonne] == 4) {
        if (Nb_Batteries > 1) Fil[i] = 1;
        else Fil[i] = 0;}
    }
  }
}
