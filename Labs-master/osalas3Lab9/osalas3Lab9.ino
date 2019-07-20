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

const int potentPin = 0;
int potentValue = 0;
const int photoPin = 5;
int photoValue = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  potentValue = analogRead(potentPin);
  photoValue = analogRead(photoPin);
  Serial.print(map(potentValue,0,1024,0,500));
  Serial.print(",");
  Serial.println(map(photoValue,0,1024,0,500));
  delay(20);

}
