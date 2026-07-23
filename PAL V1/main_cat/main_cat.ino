
#include "bitmap.hpp"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_SH1106.h"


Adafruit_SH1106 display(23); 

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
  display.begin();  // initialisation de l'afficheur
  display.clearDisplay();   // ça efface à la fois le buffer et l'écran
  display.drawBitmap(0, 0, title_screen, 128 , 64, WHITE);
  display.display();
  delay(2000);
  display.clearDisplay();   
  display.drawBitmap(0, 0, bit_cat_default, 128 , 64, WHITE);
  display.display();
}

void loop(){
  static unsigned long int last_time = millis(); 
  static bool blink_state = false;
  static int wait_time = random(5000, 10000);

  boutread();

  if (boul==0){

    if(millis()-last_time >= wait_time){

      int face_rand_goofy =random(1, 5);
      int face_rand_sleep =random(1, 5);
      static int sleep_time = random(10000, 30000);

      if(blink_state) {
        display.clearDisplay();
        display.drawBitmap(0, 0, bit_cat_default, 128 , 64, WHITE);
        display.display();
        wait_time = random(3000, 5000);
      }
      
      else if (face_rand_sleep == 2){
        static unsigned long sleep_start = millis();
        while (millis() -sleep_start <= sleep_time ){
          Serial.println(sleep_start);
          Serial.println(millis()- sleep_start );
          display.clearDisplay();
          display.drawBitmap(0, 0, bit_cat_sleep, 128 , 64, WHITE);
          display.display();
          delay(500);

          display.clearDisplay();
          display.drawBitmap(0, 0, bit_cat_sleep2, 128 , 64, WHITE);
          display.display();
          delay(500);
        }

        display.clearDisplay();
        display.drawBitmap(0, 0, bit_cat_default, 128 , 64, WHITE);
        display.display();
      }

      else {
      
        display.clearDisplay();
        display.drawBitmap(0, 0, bit_cat_blink, 128 , 64, WHITE);
        display.display();
        wait_time = 100;
      

        if (face_rand_goofy == 1){
        display.clearDisplay();
        display.drawBitmap(0, 0, bit_cat_goofy, 128 , 64, WHITE);
        display.display();
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

      if (face_rand_pet == 1){
        display.clearDisplay();
        display.drawBitmap(0, 0, bit_cat_feral, 128 , 64, WHITE);
        display.display();
      }

      else if(face_rand_pet ==2 ){
        display.clearDisplay();
        display.drawBitmap(0, 0, bit_cat_angy, 128 , 64, WHITE);
        display.display();
      }

      else if(face_rand_pet == 3){
        display.clearDisplay();
        display.drawBitmap(0, 0,bit_cat_love, 128 , 64, WHITE);
        display.display();
      }

      delay(1000);
    }

    boul=0;
    wait_time =0 ;
    last_time = millis();

  }
  

}

