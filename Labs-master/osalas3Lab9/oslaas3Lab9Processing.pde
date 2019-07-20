/*
 * Author: Omar Salas-Rodriguez
 * UIN: 652945181
 * NetID: osalas3
 * Lab 9 Piping Dual Analog Inputs to Processing for Visual Graphs
 * 
 * Description: Simple program that reads in input from 2 different analog devices
 *              and pipes the result to a processing program that graphs each input.
 *              Since the graphs have max height of 500, the value is mapped from standard
 *              0 - 1024 |-> 0 - 500
 *
 * References: http://arduino.cc/en/Tutorial/Graph 
 *             https://learn.sparkfun.com/tutorials/connecting-arduino-to-processing#introduction 
 * 
*/
import processing.serial.*;

Serial myPort;        // The serial port

int x1Pos = 0;        // Horizontal position of the graph for potentiometer
float potentInput;

int x2Pos = 500;      // Horizontal position of the graph for photoresistor
float photoInput;


void setup () {
  // Set the window size:
  size(1000, 500);

  // List all the available serial ports
  println(Serial.list());

  // Open port for the Arduino
  myPort = new Serial(this, Serial.list()[0], 9600);

  // Don't generate a serialEvent() unless you get a newline character:
  myPort.bufferUntil('\n');

  // Set initial background:
  background(0);
  // Create the two different graphs
  fill(100);
  rect(0,0,500,500);
  fill(100);
  rect(500,0,500,500);
}

void draw () {
  // Draw the first input:
  stroke(0, 250, 0);
  line(x1Pos, 500, x1Pos, 500 - potentInput);
  
  // First graph edge
  if (x1Pos >= 500) { // Reset graph
    x1Pos = 0;
    fill(100);
    rect(0,0,500,500);
  }
  // Increment the horizontal position:
  x1Pos++;
  
  // Draw the second input:
  stroke(0, 0, 250);
  line(x2Pos, 500, x2Pos, 500 - photoInput);
  
  // Second graph edge
  if (x2Pos >= 1000) { // Reset graph
    x2Pos = 500;
    fill(100);
    rect(500,0,500,500);
  }
  // Increment the horizontal position:
  x2Pos++;
}

void serialEvent (Serial myPort) {
  // Get the ASCII string:
  String inString = myPort.readStringUntil('\n');
  
  if (inString != null) {
    // Trim off any whitespace:
    inString = trim(inString);
    // Get the comma seperated inputs
    float[] inputs = float(splitTokens(inString, ","));
    potentInput = inputs[0];
    photoInput = inputs[1];
  }
}
