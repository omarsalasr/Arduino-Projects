/*
 * Author: Omar Salas-Rodriguez
 * UIN: 652945181
 * NetID: osalas3
 * Lab 4 - LCD and Photoresistor
 * 
 * Description: Simple Photoresistor program that outputs the
 *              value for the amount of light being received
 *              by the Photoresistor onto the LCD. 
 *              By doing some tests, the resistor has an average
 *              max value of 100 in a fully lit room. Then, by
 *              varying the brightness of the lightbulb and
 *              dividing the max by 5, the result coincides
 *              with the 5 text values as such:
 *              Dark:            <= 500
 *              Partially Dark:  500 <= 600
 *              Medium:          600 <= 700
 *              Partially Lit:   70 <= 800
 *              Fully List:      800 >
 *              
 * References: Photoresistor tutorial on instructables.com
 * 
 */

#include <LiquidCrystal.h>

// Initialize all the pins connected from the LCD to the arduino
const int rs = 12;
const int en = 11;
const int d4 = 5;
const int d5 = 4;
const int d6 = 3;
const int d7 = 2;

// Initialize the LCD object
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Initialize the Photoresistor analog input and value
const int photoRes = A0;
int photoValue = 0;

void setup() {
  // Set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Set up analog input for photoresistor
  pinMode(photoRes, INPUT);
  delay(1000);
}

void loop() {
  // Read in the value of the photoresistor
  photoValue = analogRead(photoRes);
  
  // Clear the screen and display the value
  lcd.clear();
  lcd.print(photoValue);
  lcd.setCursor(0,1);

  // Check the level of brightness being recorded and print it
  if(photoValue <= 500)
    lcd.print("Dark");
  else if(photoValue > 500 && photoValue <= 600)
    lcd.print("Partially Dark");
  else if(photoValue > 600 && photoValue <= 700)
    lcd.print("Medium");
  else if(photoValue > 700 && photoValue <= 800)
    lcd.print("Partially Lit");
  else
    lcd.print("Fully Lit");
  
  lcd.setCursor(0,0);
  delay(100);
  
}
