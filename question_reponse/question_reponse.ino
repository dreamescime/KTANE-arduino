/*
liste des questions :
1 - Etes-vous un sale tricheur ? N
2 - « Hakuna Matata » est une phrase merveilleuse ? O
3 - « Hakuna Matata » est un engouement passager ? N
4 - Exploser ? N
5 - Cette question comporte-t-elle 3 lignes ? O
5 - Cette question comporte-t-elle 6 lignes ? N
7 - Presence d'erreur? O si 1 ou plusieurs erreus, sinon N
8 - Beaucoup d'erreurs ? O si 2 erreurs ou plus, sinon N
9 - Le numero de serie contient-il des caractères en double ? Y si le S/N comporte des caractères en double, sinon N
10- Quelle a été votre dernière réponse ? O si votre dernière réponse était O, sinon N
11- Quelle n'était pas votre dernière réponse ? O si votre dernière réponse était N, sinon N
*/

#include <Arduino.h>
#include <Wire.h>
#include <U8g2lib.h>
#include <TM1637Display.h>

#define Num_Module 106

U8G2_ST7920_128X64_1_SW_SPI u8g2(U8G2_R0, /* clock=*/ 13, /* data=*/ 11, /* CS=*/ 10, /* reset=*/ 8);

#define CLK 5
#define DIO 4
TM1637Display display = TM1637Display(CLK, DIO);

// txt bouton
#define BP_OUI          A0
#define BP_NON          A1
#define LUM_Ecran       A3

#define temps_needle     20 //en seconde
#define interval_needle 150000 // en milliseconde

int Recep[7];
long duree = 5;
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

byte serie_double = 0;
byte numero_question = 0; //test
byte derniere_reponse = 0;

unsigned long millis_demarage;
unsigned long millis_prochain;
byte deja_fini = 0;
byte bouton_appuye = 0;
int kval_old = 0;
unsigned long delta_temps;

void setup() {
	pinMode(BP_OUI, INPUT_PULLUP);
	pinMode(BP_NON, INPUT_PULLUP);
	pinMode(LUM_Ecran, OUTPUT);
  


  Wire.begin(Num_Module);                // join i2c bus with address ..
  Wire.onReceive(onReceive);
  Wire.onRequest(onRequest);
  Serial.begin(9600);
  Serial.println("\n Module Question reponse KTANE");
  u8g2.begin();
  display.setBrightness(4); // 0-7 luminosite
  display.showNumberDec(1234);
  Serial.println("En attente du démarrage");

  digitalWrite(LUM_Ecran, LOW);
    affiche();

  
/*    randomSeed(millis());
    deja_fini = 1;
    Serial.println("module desarme");
    unsigned long duree_min = duree *  5000;
    unsigned long duree_max = duree * 10000;
    delta_temps = random(duree_min, duree_max);
    Serial.println(delta_temps);
    millis_prochain = (millis() + delta_temps);
    Serial.println(millis());
    Serial.println(millis_prochain);
    numero_question = 0;
    affiche();
    Module_fini = 1;*/
}

void loop() {
  if (Demmarage == 0) {
    while (Demmarage == 0) {
      delay(250);
      Serial.println(Demmarage);
    }
    delay(100);
    randomSeed(millis());
    Serial.println("module desarme");
    unsigned long duree_min = duree *  5000;
    unsigned long duree_max = duree * 10000;
    delta_temps = random(duree_min, duree_max);
    Serial.println(delta_temps);
    millis_prochain = (millis() + delta_temps);
    Serial.println(millis());
    Serial.println(millis_prochain);
    numero_question = 0;
    affiche();
    digitalWrite(LUM_Ecran, HIGH);
    Module_fini = 1;
    deja_fini = 1;
  }
  if (Module_fini == 0) {
    digitalWrite(LUM_Ecran, LOW);
    bouton_appuye = BP_Appuye();
    affiche_temps();

    if (bouton_appuye != 0) verification();

    while (Strike == 1) {
      Serial.println("erreur");
      delay(600);
      Strike = 0;
    }
  }
  if (Module_fini == 1) {
    display.clear();
    digitalWrite(LUM_Ecran, HIGH);
    if (deja_fini == 0) {
      deja_fini = 1;
      Serial.println("module desarme");
      delta_temps = random((interval_needle - 50000), (interval_needle));
      millis_prochain = (millis() + delta_temps);
      Serial.println(millis());
      Serial.println(millis_prochain);
      numero_question = 0;
      affiche();
    }
    if (millis_prochain < millis()) {
      Module_fini = 0;
      randomSeed(millis());
      if (derniere_reponse == 0) numero_question = random(1, 10);
      else numero_question = random(1, 12);
      Serial.print("numero de la question : ");
      Serial.println(numero_question);
      affiche();
      millis_demarage = millis();
      deja_fini = 0;
    }
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
  if (Val_temps == 9) {
    Demmarage = 1;
    Serial.print("Demmarage");}
  if (Numero_de_serie > 5) {
    Numero_de_serie = Numero_de_serie - 5;
    serie_double = 1;
    }
}

void verification() {
         if ((numero_question ==  1) && (bouton_appuye == 2)) Module_fini = 1;
    else if ((numero_question ==  2) && (bouton_appuye == 1)) Module_fini = 1;
    else if ((numero_question ==  3) && (bouton_appuye == 2)) Module_fini = 1;
    else if ((numero_question ==  4) && (bouton_appuye == 2)) Module_fini = 1;
    else if ((numero_question ==  5) && (bouton_appuye == 1)) Module_fini = 1;
    else if ((numero_question ==  6) && (bouton_appuye == 2)) Module_fini = 1;
    else if (numero_question ==  7) {
      if ((bouton_appuye == 1) && (Nb_Erreur != 0)) Module_fini = 1;
      if ((bouton_appuye == 2) && (Nb_Erreur == 0)) Module_fini = 1;}
    else if (numero_question ==  8) {
      if ((bouton_appuye == 1) && (Nb_Erreur >= 2)) Module_fini = 1;
      if ((bouton_appuye == 2) && (Nb_Erreur <= 1)) Module_fini = 1;}
    else if (numero_question ==  9) {
      if ((bouton_appuye == 1) && (serie_double == 1)) Module_fini = 1;
      if ((bouton_appuye == 2) && (serie_double == 0)) Module_fini = 1;}
    else if (numero_question == 10) {
      if ((bouton_appuye == 1) && (derniere_reponse == 1)) Module_fini = 1;
      if ((bouton_appuye == 2) && (derniere_reponse == 2)) Module_fini = 1;}
    else if (numero_question == 11) {
      if ((bouton_appuye == 1) && (derniere_reponse == 2)) Module_fini = 1;
      if ((bouton_appuye == 2) && (derniere_reponse == 1)) Module_fini = 1;}
    else (Strike = 1);

    derniere_reponse = bouton_appuye;
}

void affiche() {
  if (numero_question != 0) Serial.println("Question choisi :");

  u8g2.firstPage();
    do {
      u8g2.setFontDirection(0);
      for (int i = 0; i < 5; i++) {
        if (numero_question ==  1) {
          u8g2.setFont(u8g2_font_ncenB10_tf);
          u8g2.drawStr(17, 25,"Etes-vous un");
          u8g2.drawStr( 7, 45,"vilain tricheur ?");}
        if (numero_question ==  2) {
          u8g2.setFont(u8g2_font_ncenB10_tf);
          u8g2.drawStr( 0, 17,"''Hakuna Matata''");
          u8g2.drawStr( 9, 36,"est une phrase");
          u8g2.drawStr(10, 55,"merveilleuse ?");}
        if (numero_question ==  3) {
          u8g2.setFont(u8g2_font_ncenB08_tf);
          u8g2.drawStr(17, 17,"''Hakuna Matata''");
          u8g2.drawStr(13, 36,"est un engouement");
          u8g2.drawStr(38, 55,"passager ?");}
        if (numero_question ==  4) {
          u8g2.setFont(u8g2_font_ncenB10_tf);
          u8g2.drawStr(28, 36,"Exploser ?");}
        if (numero_question ==  5) {
          u8g2.setFont(u8g2_font_ncenB10_tf);
          u8g2.drawStr(11, 17,"Cette question");
          u8g2.drawStr( 7, 36,"comporte-t-elle");
          u8g2.drawStr(32, 55,"3 lignes ?");}
        if (numero_question ==  6) {
          u8g2.setFont(u8g2_font_ncenB10_tf);
          u8g2.drawStr(11, 17,"Cette question");
          u8g2.drawStr( 7, 36,"comporte-t-elle");
          u8g2.drawStr(32, 55,"6 lignes ?");}
        if (numero_question ==  7) {
          u8g2.setFont(u8g2_font_ncenB10_tf);
          u8g2.drawStr(30, 25,"Presence");
          u8g2.drawStr(28, 45,"d'erreur ?");}
        if (numero_question ==  8) {
          u8g2.setFont(u8g2_font_ncenB10_tf);
          u8g2.drawStr(30, 25,"Beaucoup");
          u8g2.drawStr(28, 45,"d'erreurs ?");}
        if (numero_question ==  9) {
          u8g2.setFont(u8g2_font_ncenB08_tf);
          u8g2.drawStr(11, 17,"Le numero de serie");
          u8g2.drawStr(20, 36,"contient-il des");
          u8g2.drawStr( 4, 55,"caracteres en double ?");}
        if (numero_question == 10) {
          u8g2.setFont(u8g2_font_ncenB10_tf);
          u8g2.drawStr(18, 17,"Quelle a ete");
          u8g2.drawStr(10, 36,"votre derniere");
          u8g2.drawStr(28, 55,"reponse ?");}
        if (numero_question == 11) {
          u8g2.setFont(u8g2_font_ncenB08_tf);
          u8g2.drawStr(15, 17,"Quelle n'etait pas");
          u8g2.drawStr(23, 36,"votre derniere");
          u8g2.drawStr(35, 55,"reponse ?");}
        }
    } while ( u8g2.nextPage() );
}

int BP_Appuye() { //fonction qui donne une valeur pour le BP appuyé
    int nombre_appuye = 0;
    int kval = 0;
    if (digitalRead(BP_OUI) == LOW) {
        kval = 1;
        Serial.println("BP OUI");
        nombre_appuye++;}
    if (digitalRead(BP_NON) == LOW) {
        kval = 2;
        Serial.println("BP NON");
        nombre_appuye++;}
    if (nombre_appuye > 1){ //si plusieurs BP sont appuyé, on renvoie 26 (erreur)
        return 26;}
        else if (kval_old == kval) { //si BP identique au précédent resultat, on renvois 0
            return 0;}
            else{kval_old = kval; // sinon on renvoie la valeur du BP appuyé
                return kval;}
}

void affiche_temps() {
  long temps = (temps_needle- (millis() - millis_demarage)/1000);
  
  display.showNumberDec(temps);

  if (temps <= 0) {
    Strike = 1;
    Module_fini = 1;
  }
}
