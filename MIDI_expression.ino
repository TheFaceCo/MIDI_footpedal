/*
   MIDIUSB_test.ino

   Created: 4/6/2015 10:47:08 AM
   Author: gurbrinder grewal
   Modified by Arduino LLC (2015)
*/

#include "MIDIUSB.h"

#define button1 A0
#define button2 A1
#define button3 A2
#define button4 A3
#define button5 A4
#define button6 A5
#define button7 A6
#define button8 A7
#define button9 A8
#define button10 A9
#define button11 A10
#define button12 A11


#define button1CC 41
#define button2CC 42
#define button3CC 43
#define button4CC 44
#define button5CC 45
#define button6CC 46
#define button7CC 47
#define button8CC 48
#define button9CC 49
#define button10CC 50

byte button1State = 0;
byte button2State = 0;
byte button3State = 0;
byte button4State = 0;
byte button5State = 0;
byte button6State = 0;
byte button7State = 0;
byte button8State = 0;
byte button9State = 0;
byte button10State = 0;

float linear1 = 0;
float linear2 = 0;

byte lastbutton1State = 0;
byte lastbutton2State = 0;
byte lastbutton3State = 0;
byte lastbutton4State = 0;
byte lastbutton5State = 0;
byte lastbutton6State = 0;
byte lastbutton7State = 0;
byte lastbutton8State = 0;
byte lastbutton9State = 0;
byte lastbutton10State = 0;


byte midichannel = 3;

//unsigned long midiclockperiod = 20833; //120bpm in microseconds at 24pulses/quarternote
//unsigned long midiclockflag = 0;
//unsigned long microsbuffer = 0;
//
//bool midilooper = false;

void controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}

//void sendclock(byte channel, byte control, byte value) {
//  midiEventPacket_t event = {0x0B, 0xF8 | channel, control, value};
//  MidiUSB.sendMIDI(event);
//  MidiUSB.flush();
//}

// First parameter is the event type (0x0B = control change).
// Second parameter is the event type, combined with the channel.
// Third parameter is the control number number (0-119).
// Fourth parameter is the control value (0-127).


//void momentarytoggle(int buttonstate, int lastbuttonstate, int led, int channel, int CCnum) {
//  if (buttonstate != lastbuttonstate) {
//    // if the state has changed, increment the counter
//    if (buttonstate == LOW) {
//      // if the current state is LOW then the button went from off to on:
//      if (digitalRead(led)) {
//        //turn off output
//        controlChange(channel, CCnum, 0); // Set the value of controller 10 on channel 0 to 65
//        digitalWrite(led, LOW);
//      }
//      else {
//        //turn on output
//        controlChange(channel, CCnum, 127); // Set the value of controller 10 on channel 0 to 65
//        digitalWrite(led, HIGH);
//      }
//    }
//    else {
//    }
//    delay(50);
//  }
//}
//
//void changechannel(int buttonstate, int lastbuttonstate, int led, int channel, int CCnum) {
//  if (buttonstate != lastbuttonstate) {
//    // if the state has changed, increment the counter
//    if (buttonstate == LOW) {
//      // if the current state is LOW then the button went from off to on:
//      if (digitalRead(led)) {
//        //turn off output
//        midichannel = 1; // Set the value of controller 10 on channel 0 to 65
//        digitalWrite(led, LOW);
//      }
//      else {
//        //turn on output
//        midichannel = 2; // Set the value of controller 10 on channel 0 to 65
//        digitalWrite(led, HIGH);
//      }
//    }
//    else {
//    }
//    delay(50);
//  }
//}
//
//void momentarycommand(int buttonstate, int lastbuttonstate, int led, int channel, int CCnum) {
//  if (buttonstate != lastbuttonstate) {
//    // if the state has changed, increment the counter
//    if (buttonstate == LOW) {
//      // if the current state is LOW then the button went from off to on:
//      controlChange(channel, CCnum, 127); // Set the value of controller 10 on channel 0 to 65
//      delay(5);
//      controlChange(channel, CCnum, 0); // Set the value of controller 10 on channel 0 to 65
//    }
//    delay(50);
//  }
//}

void expression(byte buttonstate, byte lastbuttonstate, byte channel, byte CCnum) {
  if (buttonstate != lastbuttonstate) {
    controlChange(channel, CCnum, buttonstate); // Send the value of the expression pedal to midi
  }
}


void setup() {
  Serial.begin(115200);


}




void loop() {

  button1State = analogRead(button1) / 8;
  Serial.print(button1State);
  Serial.print(" | ");
  button2State = analogRead(button2) / 8;
  Serial.print(button2State);
  Serial.print(" | ");
  button3State = analogRead(button3) / 8;
  Serial.print(button3State);
  Serial.print(" | ");
  button4State = analogRead(button4) / 8;
  Serial.print(button4State);
  Serial.print(" | ");
  button5State = analogRead(button5) / 8;
  Serial.print(button5State);
  Serial.print(" | ");
  button6State = analogRead(button6) / 8;
  Serial.print(button6State);
  Serial.print(" | ");
  button7State = analogRead(button7) / 8;
  Serial.print(button7State);
  Serial.print(" | ");
  button8State = analogRead(button8) / 8;
  Serial.print(button8State);
  Serial.print(" | ");
  button9State = analogRead(button9) / 8;
  Serial.print(button9State);
  Serial.print(" | ");
  button10State = analogRead(button10) / 8;
  Serial.println(button10State);




  expression(button1State, lastbutton1State, midichannel, button1CC);
  expression(button2State, lastbutton2State, midichannel, button2CC);
  expression(button3State, lastbutton3State, midichannel, button3CC);
  expression(button4State, lastbutton4State, midichannel, button4CC);
  expression(button5State, lastbutton5State, midichannel, button5CC);
  expression(button6State, lastbutton6State, midichannel, button6CC);
  expression(button7State, lastbutton7State, midichannel, button7CC);
  expression(button8State, lastbutton8State, midichannel, button8CC);
  expression(button9State, lastbutton9State, midichannel, button9CC);
  expression(button10State, lastbutton10State, midichannel, button10CC);

  MidiUSB.flush();

  lastbutton1State = button1State;
  lastbutton2State = button2State;
  lastbutton3State = button3State;
  lastbutton4State = button4State;
  lastbutton5State = button5State;
  lastbutton6State = button6State;
  lastbutton7State = button7State;
  lastbutton8State = button8State;
  lastbutton9State = button9State;
  lastbutton10State = button10State;

  delay(10);
}
