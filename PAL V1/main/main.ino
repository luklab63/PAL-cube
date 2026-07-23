
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
}

void loop(){
  static unsigned long int last_time = millis(); 
  static bool blink_state = false;
  static int wait_time = random(5000, 10000);

  boutread();

  if (boul==0){

    if(millis()-last_time >= wait_time){

      int face_rand =random(1, 4);
      Serial.println(face_rand);
      int face_rand3 =random(1, 3);
      Serial.println(face_rand3);

      if(blink_state) {
        display.clearDisplay();
        display.drawBitmap(0, 0, bit_default, 128 , 64, WHITE);
        display.display();
        wait_time = random(3000, 5000);
      }

      else {
        if (face_rand == 5 || 6 || 7 || 8 ||9){
          display.clearDisplay();
          display.drawBitmap(0, 0, bit_blink, 128 , 64, WHITE);
          display.display();
          wait_time = 100;
        }

        else if(face_rand ==2 || 3){
          display.clearDisplay();
          display.drawBitmap(0, 0, bit_right, 128 , 64, WHITE);
          display.display();
          wait_time = random(500,1000);
        }

        else if(face_rand == 1 || 4){
          display.clearDisplay();
          display.drawBitmap(0, 0, bit_left, 128 , 64, WHITE);
          display.display();
          wait_time = random(500,1000);
        }

        if (face_rand3 == 2){
        display.clearDisplay();
        display.drawBitmap(0, 0, bit_fuck, 128 , 64, WHITE);
        display.display();
        wait_time = 800;

        }
      }

      blink_state = ! blink_state;
      last_time = millis();
    }
  }

  if (boul == 1){
    int face_rand2 =random(1, 4);
    Serial.println(face_rand2);

    while (boul) {

      boutread();

      if (face_rand2 == 1){
        display.clearDisplay();
        display.drawBitmap(0, 0, bit_sleep, 128 , 64, WHITE);
        display.display();
      }

      else if(face_rand2 ==2 ){
        display.clearDisplay();
        display.drawBitmap(0, 0, bit_love, 128 , 64, WHITE);
        display.display();
      }

      else if(face_rand2 == 3){
        display.clearDisplay();
        display.drawBitmap(0, 0, bit_angy, 128 , 64, WHITE);
        display.display();
      }

      delay(1000);
    }

    boul=0;
    wait_time =0 ;
    last_time = millis();

  }
  

}

