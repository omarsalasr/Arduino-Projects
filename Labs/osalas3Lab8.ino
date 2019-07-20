/*
 * Author: Omar Salas-Rodriguez
 * UIN: 652945181
 * NetID: osalas3
 * Lab 8 - LCD with Button Interrupts
 * 
 * Description: Simple program that utilizes an LCD to display the amount of time elapsed since the program
 *              was executed or the button being pressed. The buttons are handled by pins 2 and 3 so that 
 *              interrupts are being utilized for the events. The first button pauses the time, while the
 *              second button resets the timer to 0 and starts counting again.
 *              
 * References: http://arduino.cc/en/Reference/attachInterrupt 
 * 
 */

#include <LiquidCrystal.h>

// Initialize all the pins connected from the LCD to the arduino
const int rs = 12;
const int en = 11;
const int d4 = 7;
const int d5 = 6;
const int d6 = 5;
const int d7 = 4;

// Initialize the LCD object
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Button pins
const int PAUSE_BUTTON = 2;
const int RESTART_BUTTON = 3;

bool countTime = true;
int seconds = 0;

void setup() {
  // Set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  onRestartAction();
  // Initialize button input
  pinMode(PAUSE_BUTTON, INPUT);
  pinMode(RESTART_BUTTON, INPUT);
  // Attach the interrupts for pins 2 and 3
  attachInterrupt(digitalPinToInterrupt(PAUSE_BUTTON), onPauseAction, CHANGE);
  attachInterrupt(digitalPinToInterrupt(RESTART_BUTTON), onRestartAction, CHANGE);
  delay(1000);
}

// Interrupt pin 2 function to call for button press
void onPauseAction(){
  lcd.clear();
  lcd.print("Interrupted!!!");
  // Stop counting time
  countTime = false;
}

// Interrupt pin 3 function to call for button press
void onRestartAction(){
  // Start counting time
  countTime = true;
}

void loop() {
  // Only count time for the restart state
  if(countTime){
    lcd.clear();
    lcd.print("Waited: " + String(seconds) + " sec");
    delay(1000);
    seconds++;
  }else{
    // Reset the time
    seconds = 0;
  }
}
