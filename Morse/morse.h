#pragma once
#include "Arduino.h"

#define DOT_TIME 300

char freqs[16][4] = {
  "505",
  "515",
  "522",
  "532",
  "535",
  "542",
  "545",
  "552",
  "555",
  "565",
  "572",
  "575",
  "582",
  "592",
  "595",
  "600"
};

char words[16][5] = {
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

char morse[36][5] = {
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
