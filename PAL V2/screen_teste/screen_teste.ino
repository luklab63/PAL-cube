/*******************************************************
  Utilisation d'un écran OLED avec ESP32, ESP8266 ou STM32
  (bibliothèque u8g2)
  Plus d'infos:
  https://electroniqueamateur.blogspot.com/2019/09/ecran-oled-sh1106-i2c-et-esp32-ou.html
  https://electroniqueamateur.blogspot.com/2019/11/ecran-oled-sh1106-i2c-et-stm32.html
  
********************************************************/
#include "bitmap.hpp"
#include <U8g2lib.h>
#include <Wire.h>

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
// U8G2_R0 ou U8G2_R2: mode paysage, U8G2_R1 ou U8G2_R3: mode portrait

/* Définition d'une image bitmap: logo du blog Électronique en Amateur
sauvegardé dans un fichier XBM, puis ouvert avec un éditeur de texte: */


void setup(void) {
  u8g2.begin();
  u8g2.enableUTF8Print(); //nécessaire pour écrire des caractères accentués
  u8g2.setColorIndex(0); 

  u8g2.clearBuffer(); // on efface ce qui se trouve déjà dans le buffer
  u8g2.drawXBMP( 0, 0, 128, 64, sleep_face); // position, largeur, hauteur
  u8g2.sendBuffer();  // l'image qu'on vient de construire est affichée à l'écran
}

void loop(void) {


 
}