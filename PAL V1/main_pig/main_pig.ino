
#include "bitmap.hpp"
#include <Wire.h>
#include <U8g2lib.h>


U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

#define bout1 6
int boutstate1 = 0;
int boul = 0;

void boutread(){
  boutstate1 = digitalRead(bout1);

  if(!boul && boutstate1)
  {
    boul = true;
    
  }
  else if(!boutstate1)
  {
    boul = false;
  }

}

void setup()   {

  Serial.begin(9600);
  pinMode(bout1, INPUT);

  u8g2.begin();
  u8g2.enableUTF8Print(); //nécessaire pour écrire des caractères accentués
  u8g2.setColorIndex(0);

  u8g2.clearBuffer(); // on efface ce qui se trouve déjà dans le buffer
  u8g2.drawXBMP( 0, 0, 128, 64, title_screen); // position, largeur, hauteur
  u8g2.sendBuffer();  // l'image qu'on vient de construire est affichée à l'écran

  delay(2000);

  u8g2.clearBuffer(); // on efface ce qui se trouve déjà dans le buffer
  u8g2.drawXBMP( 0, 0, 128, 64, bit_pig_default); // position, largeur, hauteur
  u8g2.sendBuffer();  // l'image qu'on vient de construire est affichée à l'écran
}

void loop(){
  static unsigned long int last_time = millis(); 
  static bool blink_state = false;
  static int wait_time = random(5000, 10000);

  boutread();

  if (boul==0){

    if(millis()-last_time >= wait_time){

      int face_rand_goofy =random(1, 5);
      int face_rand_sleep =random(1, 20);
      static int sleep_time = random(10000, 30000);

      if(blink_state) {
        u8g2.clearBuffer(); // on efface ce qui se trouve déjà dans le buffer
        u8g2.drawXBMP( 0, 0, 128, 64, bit_pig_default); // position, largeur, hauteur
        u8g2.sendBuffer();  // l'image qu'on vient de construire est affichée à l'écran
        wait_time = random(3000, 5000);
      }
      
      else if (face_rand_sleep == 2){
        static unsigned long sleep_start = millis();
        while (millis() -sleep_start <= sleep_time ){
          Serial.println(sleep_start);
          Serial.println(millis()- sleep_start );

          u8g2.clearBuffer(); // on efface ce qui se trouve déjà dans le buffer
          u8g2.drawXBMP( 0, 0, 128, 64, bit_pig_sleep_1); // position, largeur, hauteur
          u8g2.sendBuffer();  // l'image qu'on vient de construire est affichée à l'écran
          
          delay(500);

          u8g2.clearBuffer(); // on efface ce qui se trouve déjà dans le buffer
          u8g2.drawXBMP( 0, 0, 128, 64, bit_pig_sleep_2); // position, largeur, hauteur
          u8g2.sendBuffer();  // l'image qu'on vient de construire est affichée à l'écran;

          delay(500);
        }

        u8g2.clearBuffer(); // on efface ce qui se trouve déjà dans le buffer
        u8g2.drawXBMP( 0, 0, 128, 64, bit_pig_default); // position, largeur, hauteur
        u8g2.sendBuffer();  // l'image qu'on vient de construire est affichée à l'écran
      }

      else {
      
        u8g2.clearBuffer(); // on efface ce qui se trouve déjà dans le buffer
        u8g2.drawXBMP( 0, 0, 128, 64, bit_pig_blink); // position, largeur, hauteur
        u8g2.sendBuffer();  // l'image qu'on vient de construire est affichée à l'écran
        wait_time = 100;
      

        if (face_rand_goofy == 1){
          u8g2.clearBuffer(); // on efface ce qui se trouve déjà dans le buffer
          u8g2.drawXBMP( 0, 0, 128, 64, bit_pig_goofy); // position, largeur, hauteur
          u8g2.sendBuffer();  // l'image qu'on vient de construire est affichée à l'écran
          wait_time = 1500;
        }
      }

      blink_state = ! blink_state;
      last_time = millis();
    }
  }

  if (boul == 1){
    int face_rand_pet =random(1, 4);
    Serial.println(face_rand_pet);

    while (boul) {

      boutread();
      Serial.println("bouton");
      if (face_rand_pet == 1){
        u8g2.clearBuffer(); // on efface ce qui se trouve déjà dans le buffer
        u8g2.drawXBMP( 0, 0, 128, 64, bit_pig_angy); // position, largeur, hauteur
        u8g2.sendBuffer();  // l'image qu'on vient de construire est affichée à l'écran
        
      }

      else if(face_rand_pet ==2 ){
        u8g2.clearBuffer(); // on efface ce qui se trouve déjà dans le buffer
        u8g2.drawXBMP( 0, 0, 128, 64, bit_pig_flip); // position, largeur, hauteur
        u8g2.sendBuffer();  // l'image qu'on vient de construire est affichée à l'écran
      }

      else if(face_rand_pet == 3){
        u8g2.clearBuffer(); // on efface ce qui se trouve déjà dans le buffer
        u8g2.drawXBMP( 0, 0, 128, 64, bit_pig_love); // position, largeur, hauteur
        u8g2.sendBuffer();  // l'image qu'on vient de construire est affichée à l'écran
      }

      delay(1000);
    }

    boul=0;
    wait_time =0 ;
    last_time = millis();

  }
  

}

