/*
 * Author: Omar Salas-Rodriguez
 * UIN: 652945181
 * NetID: osalas3
 * Lab 2 - Push button bit counter
 * 
 * Description: Simple program that demonstrates the use of tactile buttons and LEDs.
 *              The program keeps track of an integer counter which gets incremented
 *              and decremented according to one of two buttons. A helper function is
 *              then used to process that counter and turn on an LED according to the
 *              3 bit binary representation of the current counter. The number in decimal
 *              ranges from 0-7 and in binary range from 000-111.
 *              When the counter reaches 0 and is decremented, it is set to the max number
 *              which is 7. Likewise, when the counter reaches 7 and is incremented, it is
 *              set to the min number which is 0;
 *              
 * References: Elegoo Super Starter Kit for UNO pdf
 * 
 */


const int ZERO = 9; // Pin 3 for the zero power bit
const int ONE = 8; // Pin 4 for the first power bit
const int TWO = 7; // Pin 3 for second power bit 
const int DECR = 11; // Pin 8 for decrementing push button
const int INCR = 12; // Pin 9 for incrementing push button

int counter = 0; // Decimal number
int bitCounter = 0; // Temp counter that computes the bit value

// Variables to keep track of the current and last value read from the increment button
int incBtnRead = 0;
int lastIncBtnRead = 0;

// Variable to keep track of the current and last value read from the decrement button
int decBtnRead = 0;
int lastDecBtnRead = 0;

void setup() {
  // Initialize digital pin for the on board LED.
  pinMode(ZERO, OUTPUT);
  // Initialize digital pin for the green LED.
  pinMode(ONE, OUTPUT);
  // Initialize digital pin for the red LED.
  pinMode(TWO, OUTPUT);

  // Initialize digital input for incrementing
  pinMode(INCR, INPUT_PULLUP);
  // Initialize digital input for decrementing
  pinMode(DECR, INPUT_PULLUP);

  // Turn off all LEDs
  digitalWrite(ZERO, LOW);
  digitalWrite(ONE, LOW);
  digitalWrite(TWO, LOW);
}

void loop() {
  // Get the current state of the button (pressed or released)
  incBtnRead = digitalRead(INCR);
  decBtnRead = digitalRead(DECR);

  // Check if the button state has changed since the last loop iteration (no long pressing allowed)
  if(incBtnRead != lastIncBtnRead)
    if(incBtnRead == LOW) // Button has been pressed
      counter++;

  // Check if the button state has changed since the last loop iteration (no long pressing allowed)
  if(decBtnRead != lastDecBtnRead)
    if(decBtnRead == LOW) // Button has been pressed
      counter--;

  // Save the last state read in
  lastIncBtnRead = incBtnRead;
  lastDecBtnRead = decBtnRead;

  // Check if the boundaries have been reached
  if(counter > 7)
    counter = 0;
  else if(counter < 0)
    counter = 7;

  // Process the decimal coutner
  convertCounter();
}

/*
 * 
 * Description: Helper function that processes the current counter value
 *              for outputing to the LEDs as the binary representation
 * Pre: None
 * 
 * Post: Nones
 * 
 */
void convertCounter(){
  // Copy the current counter
  bitCounter = counter;

  // Turn off LEDs
  digitalWrite(ZERO, LOW);
  digitalWrite(ONE, LOW);
  digitalWrite(TWO, LOW);

  // Process the counter by converting to its binary equivalence by checking
  // when the remainder is 1 and then performing integer division by 2.
  if(bitCounter % 2 == 1)
    digitalWrite(ZERO, HIGH);
    
  bitCounter /= 2;
  if(bitCounter % 2 == 1)
    digitalWrite(ONE, HIGH);

  bitCounter /= 2;
  if(bitCounter % 2 == 1)
    digitalWrite(TWO, HIGH);
}
