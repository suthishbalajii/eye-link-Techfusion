#include <SoftwareSerial.h>
SoftwareSerial HC05(10, 11); // HC-06-TX Pin 10, HC-06-RX to Arduino Pin 11

void setup() {
  HC05.begin(9600);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(5, OUTPUT);
}

int noise_remove(int analogPin, int digitalPin){
  digitalWrite(digitalPin, HIGH);   
  delayMicroseconds(500); 
  int a = analogRead(analogPin);        
  digitalWrite(digitalPin, LOW);   
  delayMicroseconds(500); 
  int b = analogRead(analogPin);      
  int c = a - b;
  return c;
}

int average(int analogPin, int digitalPin){  
  int average = 0;
  for(int i = 0; i < 10; i++){
    average += noise_remove(analogPin, digitalPin);
  }
  return average / 10;
}

void loop() {
  int left = average(A0, 6);
  int right = average(A1, 7);
  int up = average(A2, 8);
  int down = average(A5, 5);

  if (left < 500 && left > right && left > up && left > down) {
    HC05.println('l');
  } else if (right < 500 && right > left && right > up && right > down) {
    HC05.println('r');
  } else if (up < 500 && up > left && up > right && up > down) {
    HC05.println('u');
  } else if (down < 500 && down > left && down > right && down > up) {
    HC05.println('d');
  } else if (left > 500 && down > 500 && left > right && left > up && down > right && down > up) {
    HC05.println('b');
  } else if (right > 500 && up > 500 && right > left && right > down && up > left && up > down) {
    HC05.println('a');
  } else if (left > 500 && right > 500 && up > 500 && down > 500) {
    HC05.println('q');
  }

  delay(1000);
}
