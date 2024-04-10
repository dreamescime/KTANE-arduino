#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <TM1637Display.h>

#define DOT_TIME 300

int freqs[16] = {
  3505,
  3515,
  3522,
  3532,
  3535,
  3542,
  3545,
  3552,
  3555,
  3565,
  3572,
  3575,
  3582,
  3592,
  3595,
  3600
};

String words[16] = {
  "vitre",
  "ville",
  "chose",
  "signe",
  "linge",
  "ligne",
  "champ",
  "litre",
  "phase",
  "chaud",
  "bille",
  "balle",
  "singe",
  "plume",
  "pluie",
  "salle"
};

String morse[36] = {
  ".-",   // a
  "-...", // b
  "-.-.", // c
  "-..",  // d (not used)
  ".",    // e
  "..-.", // f
  "--.",  // g
  "....", // h
  "..",   // i
  ".---", // j (not used)
  "-.-",  // k
  ".-..", // l
  "--",   // m
  "-.",   // n
  "---",  // o
  ".--.", // p (not used)
  "--.-", // q (not used)
  ".-.",  // r
  "...",  // s
  "-",    // t
  "..-",  // u (not used)
  "...-", // v
  ".--",  // w (not used)
  "-..-", // x
  "-.--", // y (not used)
  "--..", // z (not used)
  "-----",// 0
  ".----",// 1
  "..---",// 2
  "...--",// 3
  "....-",// 4
  ".....",// 5
  "-....",// 6
  "--...",// 7
  "---..",// 8
  "----." // 9
};

#define Num_Module 61

#define PIXEL_PIN_Led_RGB         2
#define PIXEL_COUNT_Led_RGB       1
Adafruit_NeoPixel stripRGB(PIXEL_COUNT_Led_RGB, PIXEL_PIN_Led_RGB, NEO_GRB + NEO_KHZ800);
#define MORSE_LED_PIN             3
#define Morse_COUNT_Led           1
Adafruit_NeoPixel stripMorse(PIXEL_COUNT_Led_RGB, MORSE_LED_PIN, NEO_GRB + NEO_KHZ800);

#define BUTTON_R_PIN A2
#define BUTTON_L_PIN A0
#define BUTTON_TX_PIN A1

#define CLK 5
#define DIO 4
TM1637Display display = TM1637Display(CLK, DIO);

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
byte test = 0;

int goal_freq;
int selected_freq = 0;
uint8_t morse_bits[8];
int morse_index;
int morse_length;

unsigned long last_char_time = 0;

byte bouton_appuye = 0;
byte kval_old = 0;

void setup() {
stripRGB.begin();
stripMorse.begin();
stripRGB.setPixelColor(0,   150,   150, 150);
stripMorse.setPixelColor(0,   0,   0,   0);
stripRGB.show();
stripMorse.show();

pinMode(BUTTON_R_PIN, INPUT_PULLUP);
pinMode(BUTTON_L_PIN, INPUT_PULLUP);
pinMode(BUTTON_TX_PIN, INPUT_PULLUP);
Serial.begin(9600);
Serial.println("\n Module Morse KTANE");
Wire.begin(Num_Module);                // join i2c bus with address ...
  Wire.onReceive(onReceive);
  Wire.onRequest(onRequest);


  display.setBrightness(4); // 0-7 luminosite
  display.showNumberDec(1234);

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
    morse_index = 0;
    goal_freq = random(0, 16);
    selected_freq = random(0, 16);
    for(int i = 0; i < 8; i++) Serial.println(morse_bits[i], BIN);
    Serial.print("Mot choisi : ");
    Serial.println(words[goal_freq]);
    delay(100);
    for(int i = 0; i < words[goal_freq].length(); i++) {
      char lettre_desc = words[goal_freq][i];
      String morse_desc = morse[lettre_desc - 97];
      delay(100);
      for(int j = 0; j < 5; j++) {
        if(morse_desc[j] == '.') {
          Serial.print(".");
          setMorseBit(morse_bits, morse_index++, 1);
          setMorseBit(morse_bits, morse_index++, 0);
        } else if(morse_desc[j] == '-') {
          Serial.print("-");
          setMorseBit(morse_bits, morse_index++, 1);
          setMorseBit(morse_bits, morse_index++, 1);
          setMorseBit(morse_bits, morse_index++, 1);
          setMorseBit(morse_bits, morse_index++, 0);
        }
      }
      Serial.print("  ");
      setMorseBit(morse_bits, morse_index++, 0);
      setMorseBit(morse_bits, morse_index++, 0);
    }
    Serial.println("____");
    setMorseBit(morse_bits, morse_index++, 0);
    setMorseBit(morse_bits, morse_index++, 0);
    setMorseBit(morse_bits, morse_index++, 0);
    setMorseBit(morse_bits, morse_index++, 0);
    morse_length = morse_index;
    morse_index = 0;
    
    for(int i = 0; i < 8; i++) Serial.println(morse_bits[i], BIN);
    Serial.println("fin du demarage");
  }
  doMorse();
  bouton_appuye = BP_Appuye();

  if(Module_fini == 0){
    stripRGB.setPixelColor(0, 0, 0, 100);             //  Set pixel's color (in RAM)
    stripRGB.show();                                  //  Update strip to match
    if(bouton_appuye == 2) {
        Serial.println("BP Freq -");
        selected_freq--;
        if(selected_freq < 0) {
        selected_freq = 0;
        }
      }
      if(bouton_appuye == 1) {
        Serial.println("BP Freq +");
        selected_freq++;
        if(selected_freq > 15){
          selected_freq = 15;
        }
      }

      display.showNumberDec(freqs[selected_freq]);

      if(bouton_appuye == 3) {
        Serial.println("BP valide");
        if(selected_freq == goal_freq) {
          Module_fini = 1;
        Serial.println("!!! GAGNE !!!");
        } else {
          Strike = 1;
          while (Strike == 1) {
            delay(600);
            Strike = 0;
          }
          Serial.println("!!! PERDU !!!");
        }
      }
  }
  else
    stripRGB.setPixelColor(0, 255, 0, 0);             //  Set pixel's color (in RAM)
    stripRGB.show();                                  //  Update strip to match
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
}

int BP_Appuye() { //fonction qui donne une valeur pour le BP appuyé
    int nombre_appuye = 0;
    int kval = 0;
    if (digitalRead(BUTTON_R_PIN) == LOW) {
        kval = 1;
        nombre_appuye++;}
    if (digitalRead(BUTTON_L_PIN) == LOW) {
        kval = 2;
        nombre_appuye++;}
    if (digitalRead(BUTTON_TX_PIN) == LOW) {
        kval = 3;
        nombre_appuye++;}
    if (nombre_appuye > 1){ //si plusieurs BP sont appuyé, on renvoie 26 (erreur)
        return 26;}
        else if (kval_old == kval) { //si BP identique au précédent resultat, on renvois 0
            return 0;}
            else{kval_old = kval; // sinon on renvoie la valeur du BP appuyé
                return kval;}
}

void setMorseBit(uint8_t *bits, int index, int val) {
  uint8_t and_mask, or_mask;
  and_mask = ~(1 << (index % 8));  
  or_mask = ((!!val) << (index % 8));
  bits[index/8] = (bits[index/8] & and_mask) | or_mask;
}

int getMorseBit(uint8_t *bits, int index) {
  uint8_t mask;
  mask = (1 << (index % 8));
  return bits[index/8] & mask;
}

void doMorse() {
  if(millis() - last_char_time >= DOT_TIME){
//    Serial.print("Morse ");
    last_char_time = millis();
    bool affiche = getMorseBit(morse_bits, morse_index);
//    Serial.print(affiche);
    if (affiche == 1) stripMorse.setPixelColor(0, 200, 200, 200);
    else stripMorse.setPixelColor(0,   0,   0,   0);
    stripMorse.show();
    //digitalWrite(MORSE_LED_PIN, getMorseBit(morse_bits, morse_index));
    morse_index = (morse_index + 1) % morse_length;
  }
}
