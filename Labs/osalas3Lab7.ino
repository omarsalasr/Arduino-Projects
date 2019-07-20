/*
 * Author: Omar Salas-Rodriguez and Harsh Gupta
 * NetID: osalas3, hgupta20
 * Lab 7 - Dual Arduino Communication
 * 
 * Description: Simple arduino to arduino Serial communcation utilizing
 *              the transmit and receive pins on each arduino, a single
 *              push button, and a single LED in each arduino.
 *              The program is identical in each arduino where it's
 *              responsible for sending and receiving bytcode so that
 *              each arduino turns on the LED of the other arduino with its
 *              push button.
 *              The button clicks toggle the LED and stay lit when the button is clicked,
 *              holding the button keeps the LED on and letting go of the button is LED off.
 *              
 * References: https://iotguider.in/arduino/serial-communication-between-two-arduino-boards/ 
 * 
 */

// Button and LED pins
const int BUT = 12;
const int LED = 8;

// Button and LED states
int currState = 0;
int prevState = 0;
char ledState = 0;

void setup() {
  Serial.begin(9600);
  
  // Initialize button input
  pinMode(BUT, INPUT);
  // Initialize LED output
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
  // Store the state of the setup at setup
  prevState = digitalRead(BUT);
}

// Helper function that returns any available serial input
int getPress(){
  if(Serial.available() > 0){
    return Serial.read();
  }
  return 2;
}

void loop() {
  // Get the Serial input
  ledState = getPress();

  // Modify the LED state according to the Serial input received
  if(ledState == 0){
    digitalWrite(LED, LOW);
  }else if(ledState == 1){
    digitalWrite(LED, HIGH);
  }
  // Get the durrent button state
  currState = digitalRead(BUT);
  // Check if the button has been pressed or released
  if(currState != prevState){
    if(currState == LOW){ // Button released
      Serial.write(0); // Send 0 through Serial output (LED off)
    }else{ // Button pressed
      Serial.write(1); // Send 1 through Serial output (LED on)
    }
  }
  // Store the most recent state for next loop iteration
  prevState = currState;

}
