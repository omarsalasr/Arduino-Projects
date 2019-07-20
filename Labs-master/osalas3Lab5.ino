/*
 * Author: Omar Salas-Rodriguez
 * UIN: 652945181
 * NetID: osalas3
 * Lab 5 - Photoresistor and Passive buzzer
 * 
 * Description: More sophisticated program that uses LEDs, Photoresistor,
 *              Passive Buzzer, and a Potentiameter.
 *              
 *              The Photoresistor gets input analog values which then determine
 *              the level of brightness  and turns a certain number of LEDs on
 *              according to this scale:
 *              4 LEDS:           <= 500
 *              3 LEDs:           500 <= 600
 *              2 LEDs:           600 <= 700
 *              1 LED:            700 <= 800
 *              0 LEDs:           800 >
 *              
 *              
 *              The potentiameter is used as an analog input to control the
 *              tone of the passive buzzer.
 *              The analog input from the potentiameter is mapped as such:
 *              ********************
 *              * Analog * Digital *
 *              ********************
 *              * 0-1023 -> 0-255  *
 *              ********************
 *              Since the potentiameter has analog 10 bit input, that value
 *              must be mapped to its relative value in 8 bit digital output.
 *              The new mapped value is then used to control the tone of the buzzer.
 *              
 *              
 * References: Map function doc from the arduino page
 *             Elegoo Super Starter Kit pdf
 * 
 */

// Initialize the Photoresistor analog input and value
const int photoRes = A0;
int photoValue = 0;

// Initialize the LED pins
const int l7 = 7;
const int l8 = 8;
const int l9 = 9;
const int l10 = 10;

// Initialize the Potentiometer pin
const int potent = A1;
int potentValue = 0;

// Initialize the Passive Buzzer pin
const int buzzer = 11;

void setup() {
  // Set up LED ouputs
  pinMode(l7, OUTPUT);
  pinMode(l8, OUTPUT);
  pinMode(l9, OUTPUT);
  pinMode(l10, OUTPUT);
  
  // Set up analog input for photoresistor
  pinMode(photoRes, INPUT);
  delay(500);
}

void loop() {
  // Read in the value of the photoresistor
  photoValue = analogRead(photoRes);

  // Check the level of brightness being recorded and adjust LEDs
  if(photoValue <= 500){ // 4 LEDs on
    digitalWrite(l7, HIGH);
    digitalWrite(l8, HIGH);
    digitalWrite(l9, HIGH);
    digitalWrite(l10, HIGH);
  }
  else if(photoValue > 500 && photoValue <= 600){ // 3 LEDs on
    digitalWrite(l7, HIGH);
    digitalWrite(l8, HIGH);
    digitalWrite(l9, HIGH);
    digitalWrite(l10, LOW);
  }
  else if(photoValue > 600 && photoValue <= 700){ // 2 LEDs on
    digitalWrite(l7, HIGH);
    digitalWrite(l8, HIGH);
    digitalWrite(l9, LOW);
    digitalWrite(l10, LOW);
  }
  else if(photoValue > 700 && photoValue <= 800){ // 1 LED on
    digitalWrite(l7, HIGH);
    digitalWrite(l8, LOW);
    digitalWrite(l9, LOW);
    digitalWrite(l10, LOW);
  }else{ // 0 LEDs on
    digitalWrite(l7, LOW);
    digitalWrite(l8, LOW);
    digitalWrite(l9, LOW);
    digitalWrite(l10, LOW);
  }

  // Read in the value of the potentiameter
  potentValue = analogRead(potent);
  // Map the 10 bit value to 8 bit value
  potentValue = map(potentValue, 0, 1023, 0, 255);
  
  // Adjust the output of the buzzer
  analogWrite(buzzer, potentValue);
    
  delay(100);
  
}
