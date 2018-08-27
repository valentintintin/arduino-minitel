/**
   Use Fnct T + E to disable echo
*/

#include <Minitel.h>

Minitel m(10, 11);

unsigned int number;
unsigned int maxi = 10;
byte coups = 0;

void setup() {
  m.clearScreen();
  m.textMode();
  m.useDefaultColors();

  randomSeed(analogRead(0));
  number = random(maxi);
}

void loop() {
  m.charSize(SIZE_NORMAL);
  m.rect('X', 1, 1, 39, 6);
  m.charSize(SIZE_DOUBLE);
  m.text("Jeu du + et du -", 5, 4);
  
  m.charSize(SIZE_NORMAL);
  m.text("Coups : " + String(coups), 1, 10);
  m.text("Proposition [0; " + String(maxi) + "] : ", 1, 14);
  m.cursor();

  coups++;
  unsigned int given = atol(readLine().c_str());
  if (given < number) {
    m.charSize(SIZE_DOUBLE);
    m.text("Plus grand !", 9, 20);
    delay(1000);
  } else if (given > number) {
    m.charSize(SIZE_DOUBLE);
    m.text("Plus petit !", 9, 20);
    delay(1000);
  } else {
    m.clearScreen();
    m.spiral(20, 5, 2, SPE_CHAR_HASHTAG);
    m.charSize(SIZE_DOUBLE);
    m.text("Gagné en " + String(coups) + " coups !", 3, 14);
    m.noCursor();
    delay(2500);
    m.clearScreen();
    coups = 0;
    maxi *= 10;
    number = random(maxi);
  }

  m.clearScreen();
}

String readLine() {
  String tmp = "";
  char c;

  do {
    m.listen();
    m.readKey();

    if (m.isCharacterKey()) {
      c = m.getCharacterKey();
      m.textChar(c);
      tmp += c;
    } else if (m.isMenuKey()) {
      int key = m.getMenuKey();
      if (key == CORRECTION) {
        tmp.remove(tmp.length() - 1);
        m.moveCursor(LEFT, 1);
        m.textChar(' ');
        m.moveCursor(LEFT, 1);
      } else if (key == ANNULATION) {
        m.text("Réponse : " + String(number));
      }
  }
  } while(c != 13); // 13

  return tmp;
}

