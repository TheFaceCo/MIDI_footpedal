/*
   MIDIUSB_test.ino

   Created: 4/6/2015 10:47:08 AM
   Author: gurbrinder grewal
   Modified by Arduino LLC (2015)
*/

#include "MIDIUSB.h"

const int button1 = 4;
const int button2 = 5;
const int button3 = 6;
const int button4 = 7;
const int button5 = 8;

const int led1 = A0;
const int led2 = A1;
const int led3 = A2;
const int led4 = A3;
const int led5 = A4;

int button1State = 0;
int button2State = 0;
int button3State = 0;
int button4State = 0;
int button5State = 0;
int lastbutton1State = 0;
int lastbutton2State = 0;
int lastbutton3State = 0;
int lastbutton4State = 0;
int lastbutton5State = 0;

void controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}
// First parameter is the event type (0x0B = control change).
// Second parameter is the event type, combined with the channel.
// Third parameter is the control number number (0-119).
// Fourth parameter is the control value (0-127).

void setup() {
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);
  pinMode(button4, INPUT_PULLUP);
  pinMode(button5, INPUT_PULLUP);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);

  //  Serial.begin(115200);
}





void loop() {

  button1State = digitalRead(button1);
  button2State = digitalRead(button2);
  button3State = digitalRead(button3);
  button4State = digitalRead(button4);
  button5State = digitalRead(button5);

  // compare the buttonState to its previous state
  if (button1State != lastbutton1State) {
    // if the state has changed, increment the counter
    if (button1State == LOW) {
      // if the current state is LOW then the button went from off to on:
      if (digitalRead(led1)) {
        //turn off output
        controlChange(1, 21, 0); // Set the value of controller 10 on channel 0 to 65
        digitalWrite(led1, LOW);
      }
      else {
        //turn on output
        controlChange(1, 21, 127); // Set the value of controller 10 on channel 0 to 65
        digitalWrite(led1, HIGH);
      }
    }
    else {
    }
    delay(50);
  }
  if (button2State != lastbutton2State) {
    // if the state has changed, increment the counter
    if (button2State == LOW) {
      // if the current state is LOW then the button went from off to on:
      if (digitalRead(led2)) {
        //turn off output
        controlChange(1, 22, 0); // Set the value of controller 10 on channel 0 to 65
        digitalWrite(led2, LOW);
      }
      else {
        //turn on output
        controlChange(1, 22, 127); // Set the value of controller 10 on channel 0 to 65
        digitalWrite(led2, HIGH);
      }
    }
    else {
    }
    delay(50);
  }
  if (button3State != lastbutton3State) {
    // if the state has changed, increment the counter
    if (button3State == LOW) {
      // if the current state is LOW then the button went from off to on:
      if (digitalRead(led3)) {
        //turn off output
        controlChange(1, 23, 0); // Set the value of controller 10 on channel 0 to 65
        digitalWrite(led3, LOW);
      }
      else {
        //turn on output
        controlChange(1, 23, 127); // Set the value of controller 10 on channel 0 to 65
        digitalWrite(led3, HIGH);
      }
    }
    else {
    }
    delay(50);
  }
  if (button4State != lastbutton4State) {
    // if the state has changed, increment the counter
    if (button4State == LOW) {
      // if the current state is LOW then the button went from off to on:
      if (digitalRead(led4)) {
        //turn off output
        controlChange(1, 24, 0); // Set the value of controller 10 on channel 0 to 65
        digitalWrite(led4, LOW);
      }
      else {
        //turn on output
        controlChange(1, 24, 127); // Set the value of controller 10 on channel 0 to 65
        digitalWrite(led4, HIGH);
      }
    }
    else {
    }
    delay(50);
  }
  if (button5State != lastbutton5State) {
    // if the state has changed, increment the counter
    if (button5State == LOW) {
      // if the current state is LOW then the button went from off to on:
      if (digitalRead(led5)) {
        //turn off output
        controlChange(1, 25, 0); // Set the value of controller 10 on channel 0 to 65
        digitalWrite(led5, LOW);
      }
      else {
        //turn on output
        controlChange(1, 25, 127); // Set the value of controller 10 on channel 0 to 65
        digitalWrite(led5, HIGH);
      }
    }
    else {
    }
    delay(50);
  }
  // save the current state as the last state, for next time through the loop
  lastbutton1State = button1State;
  lastbutton2State = button2State;
  lastbutton3State = button3State;
  lastbutton4State = button4State;
  lastbutton5State = button5State;
  MidiUSB.flush();

}
