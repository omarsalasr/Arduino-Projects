/*
 * Author: Omar Salas-Rodriguez
 * UIN: 652945181
 * NetID: osalas3
 * Lab 1 - Blinking LEDs
 * 
 * Description: This simple program turns on 3 LEDs one at a time.
 *              There is a 1 second delay between each LED since
 *              only 1 is on at any given time.
 *              The program uses the on board LED as 1 of the 3, and 
 *              there are 2 more connected through pins 4 and 7.
 *              
 * References: Built in "Blink" arduino tutorial
 * 
 */


const int GREEN = 4; // Pin 4 for green LED
const int RED = 3; // Pin 7 for red LED

void setup() {
  // Initialize digital pin for the on board LED.
  pinMode(LED_BUILTIN, OUTPUT);
  // Initialize digital pin for the green LED.
  pinMode(GREEN, OUTPUT);
  // Initialize digital pin for the red LED.
  pinMode(RED, OUTPUT);

}

void loop() {
  // Turn on the green LED
  digitalWrite(GREEN, HIGH);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000); // Wait 1 second
  
  // Turn on the red LED
  digitalWrite(GREEN, LOW);
  digitalWrite(RED, HIGH);
  delay(1000); // Wait 1 second

  // Turn on the on board LED
  digitalWrite(RED, LOW);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000); // Wait 1 second
}
