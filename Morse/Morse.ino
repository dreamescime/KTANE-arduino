#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <TM1637Display.h>
#include "morse.h"

#define Num_Module 81

#define PIXEL_PIN_Led_RGB         2
#define PIXEL_COUNT_Led_RGB       1
Adafruit_NeoPixel stripRGB(PIXEL_COUNT_Led_RGB, PIXEL_PIN_Led_RGB, NEO_GRB + NEO_KHZ800);

#define BUTTON_R_PIN A3
#define BUTTON_L_PIN A2
#define BUTTON_TX_PIN A1
#define MORSE_LED_PIN 5

#define CLK 12
#define DIO 13
TM1637Display display = TM1637Display(CLK, DIO);

uint8_t Recep[5];

byte Numero_de_serie = 0;
byte Nb_Batteries = 0;
byte Port = 0;
byte Nb_Erreur = 0;
byte Indicateur = 0;

uint8_t Strike = 0;
uint8_t Module_fini = 0;

int goal_freq;
int selected_freq = 0;
uint8_t morse_bits[8];
int morse_index;
int morse_length;

unsigned long last_char_time = 0;

unsigned long last_button_time = 0;

void setup() {
stripRGB.begin();
stripRGB.show();
Wire.begin(Num_Module);                // join i2c bus with address ...
Wire.onRequest(requestEvent); // register event
Wire.onReceive(receiveEvent); // register event

// Set the display brightness (0-7):
  display.setBrightness(5);
// Clear the display:
  display.clear();

  randomSeed(millis());
  morse_index = 0;
  goal_freq = random(0, 16);
  for(unsigned int i = 0; i < strlen(words[goal_freq]); i++) {
    char *morse_desc = morse[words[goal_freq][i] - 'a'];
    for(unsigned int j = 0; j < strlen(morse_desc); j++) {
      if(morse_desc[j] == '.') {
        setMorseBit(morse_bits, morse_index++, 1);
        setMorseBit(morse_bits, morse_index++, 0);
      } else if(morse_desc[j] == '-') {
        setMorseBit(morse_bits, morse_index++, 1);
        setMorseBit(morse_bits, morse_index++, 1);
        setMorseBit(morse_bits, morse_index++, 1);
        setMorseBit(morse_bits, morse_index++, 0);
      }
    }
    setMorseBit(morse_bits, morse_index++, 0);
    setMorseBit(morse_bits, morse_index++, 0);
  }
  setMorseBit(morse_bits, morse_index++, 0);
  setMorseBit(morse_bits, morse_index++, 0);
  setMorseBit(morse_bits, morse_index++, 0);
  setMorseBit(morse_bits, morse_index++, 0);
  morse_length = morse_index;
  morse_index = 0;
}

void loop() {
	doMorse();

	if(Module_fini == 0){
		if(!module.is_solved){
			if(!digitalRead(BUTTON_L_PIN) && (millis() - last_button_time > 250)) {
				last_button_time = millis();
				selected_freq--;
				if(selected_freq < 0) {
				selected_freq = 0;
				}
			}
			if(!digitalRead(BUTTON_R_PIN) && (millis() - last_button_time > 250)) {
				last_button_time = millis();
				selected_freq++;
				if(selected_freq > 15){
					selected_freq = 15;
				}
			}


			matrix.writeDigitNum(0, 3);
			matrix.writeDigitNum(1, freqs[selected_freq][0] - '0');
			matrix.writeDigitNum(3, freqs[selected_freq][1] - '0');
			matrix.writeDigitNum(4, freqs[selected_freq][2] - '0');
			matrix.writeDisplay();

			if(!digitalRead(BUTTON_TX_PIN)) {
				if(selected_freq == goal_freq) {
					Module_fini = 1;
				} else {
					Strike = 1;
				}
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
  for (int i = 0; i = 5; i++) {
    int c = Wire.read();
    Recep[i] = c;
  }
  Numero_de_serie = Recep[0];
  Nb_Batteries = Recep[1];
  Port = Recep[2];
  Nb_Erreur = Recep[3];
  Indicateur = Recep[4];
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
  Serial.println("morse");
  if(millis() - last_char_time >= DOT_TIME){
    last_char_time = millis();
    digitalWrite(MORSE_LED_PIN, getMorseBit(morse_bits, morse_index));
    morse_index = (morse_index + 1) % morse_length;
  }
}

