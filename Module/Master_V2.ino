#include <Adafruit_NeoPixel.h>
#include <Wire.h>

#define PIXEL_PIN_Led_RGB         14
#define PIXEL_COUNT_Led_RGB       1
#define PIXEL_PIN_Led_Erreur      15
#define PIXEL_COUNT_Led_Erreur    2

#define Pin_batterie_1        33
#define Pin_batterie_2        32
#define Pin_batterie_3        35
#define Pin_batterie_4        34
#define Pin_port_1        25
#define Pin_port_2        26

Adafruit_NeoPixel stripRGB(PIXEL_COUNT_Led_RGB, PIXEL_PIN_Led_RGB, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripErreur(PIXEL_COUNT_Led_Erreur, PIXEL_PIN_Led_Erreur, NEO_GRB + NEO_KHZ800);

int nDevices = 0;
byte adresse_exist[127];
uint8_t Buffer[5];
uint8_t Recep[2];

char Numero_de_serie[6];
char consonne[21] = "BCDFGHJKLMNPQRSTVWXZ";
char voyelle[5] = "AEIU";
char chiffre_pair[5] = "2468";
char chiffre_impair[6] = "13579";
byte variable = 0;
String txt_Indicateur = "SND";
String txt_Port = "HDMI";

byte Num_de_serie = 0;
byte Nb_Batteries = 0;
byte Port = 0;
byte Nb_Erreur = 0;
byte Indicateur = 0;
int Val_batterie_1 = 0;
int Val_batterie_2 = 0;
int Val_batterie_3 = 0;
int Val_batterie_4 = 0;
int Val_port_1 = 0;
int Val_port_2 = 0;

byte Module_fini = 0;
byte Erreur_recu = 0;

void setup() {
  Wire.begin();
  stripRGB.begin();
  stripErreur.begin();
  stripRGB.show();
  stripErreur.show();

  pinMode(Pin_batterie_1, INPUT);
  pinMode(Pin_batterie_2, INPUT);
  pinMode(Pin_batterie_3, INPUT);
  pinMode(Pin_batterie_4, INPUT);
  pinMode(Pin_port_1, INPUT);
  pinMode(Pin_port_2, INPUT);
  
  Serial.begin(9600);
  Serial.println("\n Module Master KTANE");

  delay(5000);
  
  Serial.println("Scanning...");

  for (byte address = 1; address < 127; ++address) {
    Wire.beginTransmission(address);
    byte error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.print(address, HEX);
      Serial.println("  !");

      adresse_exist[nDevices] = address;

      ++nDevices;
    } else if (error == 4) {
      Serial.print("Unknown error at address 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.println(address, HEX);
    }
  }
  
  randomSeed(millis());
  
  // création du numéro de série
  Num_de_serie = random(1,5);
  variable = random(0,4);
  if (variable == 0) {
	  if (Num_de_serie <= 2) Numero_de_serie[0] = voyelle[random(0,4)];
	  if (Num_de_serie >= 3)Numero_de_serie[0] = consonne[random(0,20)];
  } 
  else Numero_de_serie[0] = consonne[random(0,20)];
  if (variable == 1) {
	  if (Num_de_serie <= 2) Numero_de_serie[1] = voyelle[random(0,4)];
	  if (Num_de_serie >= 3)Numero_de_serie[1] = consonne[random(0,20)];
  } 
  else Numero_de_serie[1] = consonne[random(0,20)];
  Numero_de_serie[2] = random(1,10);
  if (variable == 2) {
	  if (Num_de_serie <= 2) Numero_de_serie[3] = voyelle[random(0,4)];
	  if (Num_de_serie >= 3)Numero_de_serie[3] = consonne[random(0,20)];
  } 
  else Numero_de_serie[3] = consonne[random(0,20)];
  if (variable == 3) {
	  if (Num_de_serie <= 2) Numero_de_serie[4] = voyelle[random(0,4)];
	  if (Num_de_serie >= 3)Numero_de_serie[4] = consonne[random(0,20)];
  } 
  else Numero_de_serie[4] = consonne[random(0,20)];
  if (Num_de_serie == 1 || Num_de_serie == 3) Numero_de_serie[5] = chiffre_pair[random(0,4)];
  else Numero_de_serie[5] = chiffre_impair[random(0,5)];
  Serial.print("Le numéro de série de cette KTANE est :  ");
  Serial.println(Numero_de_serie);
  
  // Combien de batteries sont sur KTANE ?
  Val_batterie_1 = analogRead(Pin_batterie_1);
  Val_batterie_2 = analogRead(Pin_batterie_2);
  Val_batterie_3 = analogRead(Pin_batterie_3);
  Val_batterie_4 = analogRead(Pin_batterie_4);
  if ((Val_batterie_1 > 1000) && (Val_batterie_1 < 2000)) {Nb_Batteries ++;}
  if ((Val_batterie_2 > 1000) && (Val_batterie_2 < 2000)) {Nb_Batteries ++;}
  if ((Val_batterie_3 > 1000) && (Val_batterie_3 < 2000)) {Nb_Batteries ++;}
  if ((Val_batterie_4 > 1000) && (Val_batterie_4 < 2000)) {Nb_Batteries ++;}
  Serial.print("Batterie 1 : ");
  Serial.println(Val_batterie_1);
  Serial.print("Batterie 2 : ");
  Serial.println(Val_batterie_2);
  Serial.print("Batterie 3 : ");
  Serial.println(Val_batterie_3);
  Serial.print("Batterie 4 : ");
  Serial.println(Val_batterie_4);
  Serial.print("Nous avons ");
  Serial.print(Nb_Batteries);
  Serial.println(" batterie(s).");
  
  
  // Quel port est connecté a KTANE ?
  Val_port_1 = analogRead(Pin_port_1);
  Val_port_2 = analogRead(Pin_port_2);
  if (Val_port_1 < 1000) {
	  if (Val_port_2 < 1000) {Port = 0; txt_Port = "Null 0";}
	  if (Val_port_2 > 1000 && Val_port_2 < 2000) {Port = 1; txt_Port = "DVID";}
	  if (Val_port_2 > 2000 && Val_port_2 < 3000) {Port = 2; txt_Port = "Parallele";}}
  if (Val_port_1 > 1000 && Val_port_2 < 2000) {
	  if (Val_port_2 < 1000) {Port = 3; txt_Port = "PS2";}
	  if (Val_port_2 > 1000 && Val_port_2 < 2000) {Port = 4; txt_Port = "RJ45";}
	  if (Val_port_2 > 2000 && Val_port_2 < 3000) {Port = 5; txt_Port = "Serie";}}
  if (Val_port_1 > 2000 && Val_port_2 < 3000) {
	  if (Val_port_2 < 1000) {Port = 6; txt_Port = "Stereo RCA";}
	  if (Val_port_2 > 1000 && Val_port_2 < 2000) {Port = 7; txt_Port = "USB";}
	  if (Val_port_2 > 2000 && Val_port_2 < 3000) {Port = 8; txt_Port = "Null 8";}}
  
  // création de l'indicateur 3 lettres
  Indicateur = random(0,11);
  switch (Indicateur) {
	  case 0 :
	  txt_Indicateur = "SND";
	  break;
	  case 1 :
	  txt_Indicateur = "CLR";
	  break;
	  case 2 :
	  txt_Indicateur = "CAR";
	  break;
	  case 3 :
	  txt_Indicateur = "IND";
	  break;
	  case 4 :
	  txt_Indicateur = "FRQ";
	  break;
	  case 5 :
	  txt_Indicateur = "SIG";
	  break;
	  case 6 :
	  txt_Indicateur = "NSA";
	  break;
	  case 7 :
	  txt_Indicateur = "MSA";
	  break;
	  case 8 :
	  txt_Indicateur = "TRN";
	  break;
	  case 9 :
	  txt_Indicateur = "BOB";
	  break;
	  case 10 :
	  txt_Indicateur = "FRK";
	  break;
  }
  Serial.print("L'indicateur est : ");
  Serial.println(txt_Indicateur);
  
  Buffer[0] = Num_de_serie;
  Buffer[1] = Nb_Batteries;
  Buffer[2] = Port;
  Buffer[4] = Indicateur;
}

void loop() {
  Buffer[3] = Nb_Erreur;
  Erreur_recu = 0;
  Module_fini = 0;
  
  for (int i = 0; i = nDevices; i++) {
    Wire.beginTransmission(adresse_exist[i]);        // commence la transmition vers un esclave
    Wire.write(Buffer,5);                            // envoie les valeur du tableau
    Wire.endTransmission();                          // arrete la transmition
  }
  delay(100);
  for (int i = 0; i = nDevices; i++) {
    Wire.requestFrom(adresse_exist[i], 1);
    for (int j = 0; j = 2; j++) {
      int c = Wire.read();
      Recep[j] = c;
    }
    if (Recep[0] == 1) {
      Erreur_recu ++;
    }
    if (Recep[1] == 1) {
      Module_fini ++;
    }
  }
  if (Erreur_recu =! 0) {
    Nb_Erreur = Nb_Erreur + Erreur_recu;
    // emission_son(duree du bip)
	for (int i = 0; i = Nb_Erreur; i++) stripErreur.setPixelColor(i, 0, 255, 0);
	stripErreur.show();
  }
  if (Module_fini == nDevices) {
    // fin du jeu
  }
}
