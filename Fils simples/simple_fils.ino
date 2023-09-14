#include <Adafruit_NeoPixel.h>
#include <Wire.h>

#define Num_Module 57

#define PIXEL_PIN_Led_RGB         2
#define PIXEL_COUNT_Led_RGB       1
Adafruit_NeoPixel stripRGB(PIXEL_COUNT_Led_RGB, PIXEL_PIN_Led_RGB, NEO_GRB + NEO_KHZ800);

#define Blanc    1
#define Bleu     2
#define Jaune    3
#define Rouge    4
#define Noir     5

uint8_t Recep[6];
byte Numero_de_serie = 0;
byte Nb_Batteries = 0;
byte Port = 0;
byte Nb_Erreur = 0;
byte Indicateur = 0;
uint8_t Strike = 0;
uint8_t Module_fini = 0;

const byte borne[6] = {0, 1, 2, 3, 6, 7};
byte Fil_present[6];
byte Nb_couleur[6];
byte Nb_fil = 0;
byte Fil_a_couper = 0;
byte Fil_a_couper_index = 0;

void setup() {
	Serial.begin(9600);
	stripRGB.begin();
	stripRGB.show();

	pinMode(A0, INPUT);
	pinMode(A1, INPUT);
	pinMode(A2, INPUT);
	pinMode(A3, INPUT);
	pinMode(A6, INPUT);
	pinMode(A7, INPUT);

	Wire.begin(Num_Module);                // join i2c bus with address ...
	Wire.onRequest(requestEvent); // register event
	Wire.onReceive(receiveEvent); // register event

	delay(10);

	for(int i = 0; i < 6; i++) {
		Fil_present[i] = tension_sur_fil(analogRead(borne[i]));
		Nb_couleur[Fil_present[i]] = Nb_couleur[Fil_present[i]] + 1;
		if (Fil_present[i] != 0)
			Nb_fil++;
	}

	delay(10);

  // Detect Solution:
  switch(Nb_fil) {

    case(3):
      if(Nb_couleur[Rouge] == 0){
        Fil_a_couper = 2; // Second wire
      } else if(Fil_present[dernier_fil()] == Blanc) {
        Fil_a_couper = Nb_fil; // Last wire
      } else if(Nb_couleur[Bleu] > 1) {
        Fil_a_couper = Dernier_fil_de_couleur(Bleu) + 1; // Last blue wire
      } else {
        Fil_a_couper = Nb_fil; // Last wire
      }
      break;

    case(4):
      if(Nb_couleur[Rouge] > 1 && (Numero_de_serie == 2 || Numero_de_serie == 4)){
        Fil_a_couper = Dernier_fil_de_couleur(Rouge) + 1; // Last red wire
      } else if(Fil_present[dernier_fil()] == Jaune && Nb_couleur[Rouge] == 0) {
        Fil_a_couper = 1; // First wire
      } else if(Nb_couleur[Bleu] == 1) {
        Fil_a_couper = 1; // First wire
      } else if(Nb_couleur[Jaune] > 1) {
        Fil_a_couper = Nb_fil; // Last wire
      } else {
        Fil_a_couper = 2; // Second wire
      }
      break;

    case(5):
      if(Fil_present[dernier_fil()] == (Numero_de_serie == 2 || Numero_de_serie == 4)) {
        Fil_a_couper = 4; // Fourth wire
      } else if(Nb_couleur[Rouge] == 1 && Nb_couleur[Jaune] > 1) {
        Fil_a_couper = 1; // First wire
      } else if(Nb_couleur[Noir] == 0) {
        Fil_a_couper = 2; // Second wire
      } else {
        Fil_a_couper = 1; // First wire
      }
      break;

    case(6):
      if(Nb_couleur[Jaune] == 0 && (Numero_de_serie == 2 || Numero_de_serie == 4)) {
        Fil_a_couper = 3; // Third wire
      } else if(Nb_couleur[Jaune] == 1 && Nb_couleur[Blanc] > 1) {
        Fil_a_couper = 4; // Fourth wire
      } else if(Nb_couleur[Rouge] == 0) {
        Fil_a_couper = Nb_fil; // Last wire
      } else {
        Fil_a_couper = 4; // Fourth wire
      }
      break;

    default:
      Strike = 1;
  }
    int temp = Fil_a_couper;
	for(int i = 0; i < 6; i++) {
		if(Fil_present[i] != 0){
			temp--;
			if(temp == 0){
				Fil_a_couper_index = i;
				break;
			}
		}
	}
}

void loop() {
	if(Module_fini == 0){
		for(int i = 0; i < 6; i++) {
			if(Fil_present[i] != 0){
				if(Fil_present[i] != tension_sur_fil(analogRead(borne[i]))) {
					delay(100);
					if(Fil_present[i] != tension_sur_fil(analogRead(borne[i]))) { // Check again for debouncing reasons
						if(i == Fil_a_couper_index) {
							Module_fini = 1;
						} else {
							Strike = 1;
							Fil_present[i] = tension_sur_fil(analogRead(borne[i]));
						}
					}
				}
				delay(10);
			}
		}
	}
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
}

int tension_sur_fil(int tension) {
	if(tension < 10) {          return 0; // pas de fils
	} else if(tension < 138) {  return 1; // Blanc
	} else if(tension < 384) {  return 2; // Bleu
	} else if(tension < 640) {  return 3; // Jaune
	} else if(tension < 896) {  return 4; // Rouge
	} else {                    return 5; // Noir
	}
	return 0;
}

int dernier_fil() {
  for(int i = 5; i >= 0; i++) {
    if(Fil_present[i] != 0){
      return i;
    }
  }
  return 0;
}

int Dernier_fil_de_couleur(int color) {
  int index = 0;
  int retIndex = 0;
  for(int i = 0; i < 6; i++) {
    if(Fil_present[i] != 0){
      if(Fil_present[i] == color){
        retIndex = index;
      }
      index++;
    }
  }
  return retIndex;
}

