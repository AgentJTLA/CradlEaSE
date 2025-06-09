// CradlEaSE
// Embedded Based Baby Cradle with Raindrop and Sound Sensor

// Group 6:
// 2702228892 - Nelson Ferdinand Wangsaputra
// 2702261580 - Jayson Kelvin
// 2702275604 - Nisa Jamalia Hanif

#include <Servo.h>

int pissSensor = A4; // Using rain sensor, set to analog pin for accurate wet indicator
int crySensor = 4; // Using sound sensor, set to digital pin, with pre-adjusted sensitivity using the built in potentiometer from the sound sensor
int wetThreshold = 800; // Wetness level threshold for the pissSensor to detect
int loudThreshold = HIGH; // Loudness level threshold, set to just HIGH as sensitivity has been already adjusted from the sound sensor (using potentiometer)
int buzzer = 5; // Buzzer to notify the parents when the baby pisses

Servo swing; //Servo to swing the baby cradle when the baby cries

void setup(){
  Serial.begin(9600);
  pinMode(crySensor, INPUT);
  pinMode(buzzer, OUTPUT);
  swing.attach(3);
  swing.write(80); //Initialization, neutral position
}

void loop(){
  int wetLevel = analogRead(pissSensor); // The lower the value, the wetter it is
  int loudLevel = digitalRead(crySensor);

  // For debugging purpose
  Serial.print("Wetness value: ");
  Serial.print(wetLevel);
  Serial.print(" Cry detected: ");
  loudLevel == loudThreshold? Serial.println("Yes") : Serial.println("No");

  // Baby pisses
  if(wetLevel < wetThreshold){
    // Tone buzzer 5 times
    for(int i = 0; i<5; i++){
      tone(buzzer, 330);
      delay(1000);
      noTone(buzzer);
      delay(500);
    }
  }

  // Baby cries
  if(loudLevel == loudThreshold){
    // Swing cradle 5 times
    for(int j = 0; j<5; j++){
      //Smooth swing motion
      for (int i = 80; i<=105; i+=5){
        swing.write(i);
        delay(50);
      }
      for (int i = 105; i>=55; i-=5){
        swing.write(i);
        delay(50);
      }
      for (int i = 55; i<=80; i+=5){
        swing.write(i);
        delay(50);
      }
    }
  }

  //Return to neutral position
  else swing.write(80);
}