
#include <Wire.h>
#include "rgb_lcd.h"
#include <stdlib.h>
  
rgb_lcd lcd;

const int colorR = 50;
const int colorG = 0;
const int colorB = 100;
int cpt = 0;
unsigned long timeLimit = 5000;
unsigned long timeStart;
unsigned long previousMillis = 0;
long interval = 1200; 
long intervalOn = 1000; 
int ledState1 = LOW;  
int ledState2 = LOW;  
int ledState3 = LOW; 

int light1On = 0;
int light2On = 0;
int light3On = 0;
int fini = 0;
srand(time(NULL));


// the setup routine runs once when you press reset:
void setup() {
  pinMode(4, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(7, OUTPUT);
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  timeStart = millis();
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  
  lcd.setRGB(colorR, colorG, colorB);
  
  // Print a message to the LCD.
  lcd.print("Score : ");
  lcd.setCursor(0, 1); 
  lcd.print(cpt); 

  delay(1000);
}

// the loop routine runs over and over again forever:
void loop() {
  
  int sensorValue1 = analogRead(A0);
  int sensorValue2 = analogRead(A1);
  int sensorValue3 = analogRead(A2);
  int ledStates[] = {ledState1, ledState2, ledState3};
  int sensors[] = {sensorValue1, sensorValue2, sensorValue3};
  int ledOns[] = {light1On, light2On, light3On};
  int randValue = rand() % 3 + 1;
  //Serial.println(sensorValue1);
  //Serial.println(sensorValue2);

  lcd.setCursor(0, 1);
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    ledStates[randValue] = HIGH;
    ledOns[randValue] = 1;
    
    

    /* if the LED is off turn it on and vice-versa:
    if (ledState1 == LOW) {
      ledState1 = HIGH;
      ledState2 = LOW;
      ledState3 = LOW;
      interval = intervalOn;
      light1On = 1;
      light2On = 0;
      light3On = 0;
    } else if (ledState2 == LOW) {
        ledState1 = LOW;
        ledState2 = HIGH;
        ledState3 = LOW;
        interval = intervalOn;
        light1On = 0;
        light2On = 1;
        light3On = 0;
    } else if (ledState3 == LOW) {
        ledState1 = LOW;
        ledState2 = LOW;
        ledState3 = HIGH;
        interval = intervalOn;
        light1On = 0;
        light2On = 0;
        light3On = 1;
    }  else {
        ledState1 = LOW;
        ledState2 = LOW;
        ledState3 = LOW;
        interval = 1000;
        light1On = 0;
        light2On = 0;
        light3On = 0;
    }
    */

    ledStates[randValue] = LOW;
    ledOns[randValue] = 0;
    

    // set the LED with the ledState of the variable:
    digitalWrite(4, ledState1);
    digitalWrite(2, ledState2);
    digitalWrite(7, ledState3);
  }

if (ledStates[randValue] >200 && ledOns[randValue] == 1) {
    lcd.print(cpt+=1);
    ledOns[randValue] = 0;
    if (interval > 100) {
      intervalOn -= 100;
    }
  }
  
/*
  if (sensorValue1 > 200 && light1On == 1) {
    lcd.print(cpt+=1);
    light1On = 0;
    if (interval > 100) {
      intervalOn -= 100;
    }
  }
  
  if (sensorValue2 > 200 && light2On == 1) {
    lcd.print(cpt+=1);
    light2On = 0;
    if (interval > 100) {
      intervalOn -= 100;
    }
  }
  
  if (sensorValue3 > 200 && light3On == 1) {
    lcd.print(cpt+=1);
    light2On = 0;
    if (interval > 100) {
      intervalOn -= 100;
    }
  }
  */
  
  if (currentMillis > 30000) { 
    if (cpt == 0) {
      lcd.print("Perdu !");
    } else { 
      lcd.print("Bravo ! Vous avez fait : ");
      lcd.print(cpt);
      if (cpt == 1) {
        lcd.print(" point.");
      } else {
        lcd.print(" points.");
      }
      delay(400);
      lcd.scrollDisplayLeft();
    }
    ledState1 = HIGH;
    ledState2 = HIGH;
    ledState3 = HIGH;
  }
  
  //else if (sensorValue > 200 && penalityOn == 0 && cpt > 0 && fini < 9) {
    //  lcd.print(cpt-=1);
    //  penalityOn = 1;
    //  fini += 1;
  //}
}
