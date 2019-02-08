
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

int fini = 0;

long randValue = 0;
long lastRand = 0;

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
  
  int ledStates[] = {LOW, LOW, LOW};
  int sensors[] = {analogRead(A0), analogRead(A1), analogRead(A3)};
  int ledOns[] = {0, 0, 0};

  lcd.setCursor(0, 1);
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    lastRand = random(3);

    while (lastRand == randValue) {
      lastRand = random(3);
    }

    randValue = lastRand;
    
    previousMillis = currentMillis;

    if (ledStates[randValue] == LOW) {
      ledStates[randValue] = HIGH;
      interval = intervalOn;
      ledOns[randValue] = 1;
    } else {
      interval = 1000;
      ledStates[0] = LOW;
      ledStates[1] = LOW;
      ledStates[2] = LOW;
      ledOns[0] = 0;
      ledOns[1] = 0;
      ledOns[2] = 0;
    }

    // set the LED with the ledState of the variable:        
    digitalWrite(4, ledStates[0]);
    digitalWrite(2, ledStates[1]);
    digitalWrite(7, ledStates[2]);
  }
  
  
  if (sensors[randValue] > 300 && ledOns[randValue] == 1) {
    Serial.println("Tap");
    lcd.print(cpt+=1);
    ledOns[randValue] = 0;
    if (interval > 100) {
      intervalOn -= 100;
    }
  }
    
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
    ledStates[0] = HIGH;
    ledStates[1] = HIGH;
    ledStates[2] = HIGH;
  }
}
