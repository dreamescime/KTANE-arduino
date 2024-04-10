#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <U8g2lib.h>

#define Num_Module 11

#define PIXEL_PIN_Led_RGB         2
#define PIXEL_COUNT_Led_RGB       1
Adafruit_NeoPixel stripRGB(PIXEL_COUNT_Led_RGB, PIXEL_PIN_Led_RGB, NEO_GRB + NEO_KHZ800);

#define PIXEL_PIN_BP          4
#define PIXEL_COUNT_BP        8
Adafruit_NeoPixel stripBP(PIXEL_COUNT_BP, PIXEL_PIN_BP, NEO_GRB + NEO_KHZ800);

#define PIXEL_PIN_Bande           3
#define PIXEL_COUNT_Bande         4
Adafruit_NeoPixel stripBande(PIXEL_COUNT_Bande, PIXEL_PIN_Bande, NEO_GRB + NEO_KHZ800);

#define BP                        A0

U8G2_SSD1306_128X64_NONAME_1_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);

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

int Recep[6];
int Numero_de_serie = 0;
int Nb_Batteries = 0;
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

byte couleur_Bande = 0;
byte couleur_Bouton = 0;
byte txt = 0;

byte bouton_appuye = 0;
byte kval = 0;
byte lecture = 0;
byte lecture_old = 0;
unsigned long lastDebounceTime  = 0;
unsigned long debounceDelay  = 100;


void setup() {
  stripRGB.begin();
  stripBP.begin();
  stripBande.begin();
  stripRGB.setPixelColor(0, 150, 150, 150);         //  Set pixel's color (in RAM)
  stripRGB.show();
  stripBP.show();
  stripBande.show();
  pinMode(BP, INPUT_PULLUP);
  Wire.begin(Num_Module);                // join i2c bus with address ...
  Wire.onReceive(onReceive);
  Wire.onRequest(onRequest);
  Serial.begin(9600);
  Serial.println("\n Module Bouton KTANE");
  u8g2.begin();
  Serial.println("En attente du démarrage");
  bouton_appuye = BP_Appuye();
}

void loop() {
  if (Demmarage == 0) {
    while (Demmarage == 0) {
      delay(250);
      Serial.println(Demmarage);
    }
    delay(1000);
    randomSeed(millis());
    couleur_Bande = random(1, 6);
    couleur_Bouton = random(1, 6);
    txt = random(1, 5);
    affiche();
    if (txt == Annuler)   Serial.print("TXT = Annuler   ");
    if (txt == Exploser)  Serial.print("TXT = Exploser   ");
    if (txt == Maintenir) Serial.print("TXT = Maintenir   ");
    if (txt == Pousser)   Serial.print("TXT = Pousser   ");
    if (couleur_Bouton == Bleu )  Serial.print("BP  = Bleu   ");
    if (couleur_Bouton == Rouge)  Serial.print("BP  = Rouge   ");
    if (couleur_Bouton == Blanc)  Serial.print("BP  = Blanc   ");
    if (couleur_Bouton == Jaune)  Serial.print("BP  = Jaune   ");
    if (couleur_Bouton == Vert )  Serial.print("BP  = Vert   ");
    if (couleur_Bande == Bleu ) Serial.println("Bande  = Bleu");
    if (couleur_Bande == Rouge) Serial.println("Bande  = Rouge");
    if (couleur_Bande == Blanc) Serial.println("Bande  = Blanc");
    if (couleur_Bande == Jaune) Serial.println("Bande  = Jaune");
    if (couleur_Bande == Vert ) Serial.println("Bande  = Vert");
    if (couleur_Bouton == Bleu && txt == Annuler)         Serial.println("Bouton bleu et text annuler donc tenir appuyer");
    else if (Nb_Batteries > 1 && txt == Exploser)         Serial.println("plusieurs batteries et text exploser donc relacher");
    else if (couleur_Bouton == Blanc && Indicateur == 2)  Serial.println("Bouton blanc et indicateur CAR donc tenir appuyer");
    else if (Nb_Batteries > 2 && Indicateur == 10)        Serial.println("plus de 2 batteries et indicateur FRK donc relacher");
    else if (couleur_Bouton == Jaune)                     Serial.println("Bouton jaune donc tenir appuyer");
    else if (couleur_Bouton == Rouge && txt == Maintenir) Serial.println("Bouton rouge et text maintenir donc relacher");
    else                                                  Serial.println("derniere possibilité : tenir appuyer");
  }
	if(Module_fini == 0){
      stripRGB.setPixelColor(0, 0, 0, 100);             //  Set pixel's color (in RAM)
      stripRGB.show();                                  //  Update strip to match
    bouton_appuye = BP_Appuye();
    if (bouton_appuye == 1){
      Appuyer();
      Serial.println("BP appuyé");}
    affiche();
    while (Strike == 1) {
      stripRGB.setPixelColor(0, 0, 100, 0);             //  Set pixel's color (in RAM)
      stripRGB.show();                                  //  Update strip to match
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
  Serial.print(Nb_Batteries);
  Serial.print(" batteries   Val 1 : ");
  Serial.print(Val_temps_1);
  Serial.print("   Val 4 : ");
  Serial.print(Val_temps_4);
  Serial.print("   Val 5 : ");
  Serial.println(Val_temps_5);
}

void affiche() {
  u8g2.firstPage();  
  do {
  u8g2.setFont(u8g2_font_spleen12x24_mr);
  u8g2.setFontDirection(0);
  if (txt == Annuler) u8g2.drawStr(5, 40, "Annuler");
  if (txt == Exploser) u8g2.drawStr(5, 40, "Exploser");
  if (txt == Maintenir) u8g2.drawStr(5, 40, "Maintenir");
  if (txt == Pousser) u8g2.drawStr(5, 40, "Pousser");
  } while( u8g2.nextPage() );

  for (int i = 0; i < PIXEL_COUNT_BP; i++) {
    if (couleur_Bouton == Bleu ) stripBP.setPixelColor(i,   0,   0, 255);
    if (couleur_Bouton == Rouge) stripBP.setPixelColor(i,   0, 255,   0);
    if (couleur_Bouton == Blanc) stripBP.setPixelColor(i, 255, 255, 255);
    if (couleur_Bouton == Jaune) stripBP.setPixelColor(i, 125, 255,   0);
    if (couleur_Bouton == Vert ) stripBP.setPixelColor(i, 255,   0,   0);
  }  
  if (bouton_appuye == 1) {
    for (int i = 0; i < PIXEL_COUNT_Bande; i++) {
      if (couleur_Bande == Bleu ) stripBande.setPixelColor(i,   0,   0, 255);
      if (couleur_Bande == Rouge) stripBande.setPixelColor(i,   0, 255,   0);
      if (couleur_Bande == Blanc) stripBande.setPixelColor(i, 255, 255, 255);
      if (couleur_Bande == Jaune) stripBande.setPixelColor(i, 125, 255,   0);
      if (couleur_Bande == Vert ) stripBande.setPixelColor(i, 255,   0,   0);
    }
  }
  else for (int i = 0; i < PIXEL_COUNT_Bande; i++) stripBande.setPixelColor(i,   0,   0,   0);
  stripRGB.show();
  stripBP.show();
  stripBande.show();
}

int BP_Appuye() { //fonction qui donne une valeur pour le BP appuyé
    lecture = digitalRead(BP);
    if (lecture != lecture_old) lastDebounceTime = millis();
    if ((millis() - lastDebounceTime)>= debounceDelay) {
      if (lecture != kval) {
        kval = lecture;
      }
    }
    lecture_old = lecture;

    if (kval==  LOW) return 1;
    if (kval == HIGH) return 0;
}

void Appuyer() {
  affiche();
  if (couleur_Bouton == Bleu && txt == Annuler) {
    Serial.println("Bouton bleu et text annuler donc tenir appuyer");
    Tenir_appuyer();}
  else if (Nb_Batteries > 1 && txt == Exploser) {
    Serial.println("plusieurs batteries et text exploser donc relacher");
    Relacher();}
  else if (couleur_Bouton == Blanc && Indicateur == 2) {
    Serial.println("Bouton blanc et indicateur CAR donc tenir appuyer");
    Tenir_appuyer();}
  else if (Nb_Batteries > 2 && Indicateur == 10) {
    Serial.println("plus de 2 batteries et indicateur FRK donc relacher");
    Relacher();}
  else if (couleur_Bouton == Jaune) {
    Serial.println("Bouton jaune donc tenir appuyer");
    Tenir_appuyer();}
  else if (couleur_Bouton == Rouge && txt == Maintenir) {
    Serial.println("Bouton rouge et text maintenir donc relacher");
    Relacher();}
  else {
    Serial.println("derniere possibilité : tenir appuyer");
    Tenir_appuyer();}
}

void Tenir_appuyer() {
  Serial.println("Tenir appuyé !");
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
  Serial.println("Relacher !");
  unsigned long temps_fin = millis() + Temps_relacher;
  while(bouton_appuye == 1) {
    bouton_appuye = BP_Appuye();
  }
  if (millis() < temps_fin) {
      Module_fini = 1;
    } else Strike = 1;
}
