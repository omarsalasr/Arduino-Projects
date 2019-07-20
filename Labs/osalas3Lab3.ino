/*
 * Author: Omar Salas-Rodriguez
 * UIN: 652945181
 * NetID: osalas3
 * Lab 3 - LCD and schematic practice
 * 
 * Description: Simple program that uses a 16x2 LCD and potentiameter.
 *              The program displays a message (my name) in the first row
 *              and a quote in the second row. The first row stays
 *              stationary while the second one moves endlessly along the
 *              screen.
 *              
 * References: LCD scrolling tutorial on the arduino website.
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

// Initialize quote string and boundary indices
String quote = "I don't lose, I win or learn. ";
int startInd = 0;
int endInd = 16;

void setup() {
  // Set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  delay(1000);
}

void loop() {
  // Clear the screen and display the first row
  lcd.clear();
  lcd.print("Omar Salas");
  lcd.setCursor(0,1);

  // Check if the boundary of the quote is in the right order
  if(startInd < endInd) // There is no cutoff
    lcd.print(quote.substring(startInd, endInd));
  else // There is a cutoff
    lcd.print(quote.substring(startInd, quote.length()) +
              quote.substring(0, endInd));
              
  // Increase the index to simulate the movements
  startInd++;
  endInd++;

  // Check if the boundaries have reached the end of the quote
  if(startInd == 30)
    startInd = 0;  
  if(endInd == 30)
    endInd = 0;

  // Moves the cursor back to the first row
  lcd.setCursor(0,0);
  delay(300);
}
