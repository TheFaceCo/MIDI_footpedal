/*
   MIDIUSB_test.ino

   Created: 4/6/2015 10:47:08 AM
   Author: gurbrinder grewal
   Modified by Arduino LLC (2015)
*/

#include "MIDIUSB.h"

#define button1 12
#define button2 11
#define button3 10
#define button4 9
#define button5 8
#define button6 2
#define button7 0
#define button8 1
#define button9 13
#define button10 A0

#define button1CC 21
#define button2CC 22
#define button3CC 23
#define button4CC 24
#define button5CC 25
#define button6CC 26
#define button7CC 27
#define button8CC 28
#define button9CC 29
#define button10CC 30

#define button11CC 31
#define button12CC 32
#define button13CC 33
#define button14CC 34
#define button15CC 35
#define button16CC 36
#define button17CC 37
#define button18CC 38
#define button19CC 39
#define button20CC 40

#define led1 7
#define led2 6
#define led3 5
#define led4 4
#define led5 3
#define led6 A1
#define led7 A2
#define led8 A3
#define led9 A4
#define led10 A5

int button1State = 0;
int button2State = 0;
int button3State = 0;
int button4State = 0;
int button5State = 0;
int button6State = 0;
int button7State = 0;
int button8State = 0;
int button9State = 0;
int button10State = 0;

int lastbutton1State = 0;
int lastbutton2State = 0;
int lastbutton3State = 0;
int lastbutton4State = 0;
int lastbutton5State = 0;
int lastbutton6State = 0;
int lastbutton7State = 0;
int lastbutton8State = 0;
int lastbutton9State = 0;
int lastbutton10State = 0;

int midichannel = 1;

unsigned long midiclockperiod = 20833; //120bpm in microseconds at 24pulses/quarternote
unsigned long midiclockflag = 0;
unsigned long microsbuffer = 0;

bool midilooper = false;

void controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}

void sendclock(byte channel, byte control, byte value) {
  midiEventPacket_t event = {0x0B, 0xF8 | channel, control, value};
  MidiUSB.sendMIDI(event);
  MidiUSB.flush();
}

// First parameter is the event type (0x0B = control change).
// Second parameter is the event type, combined with the channel.
// Third parameter is the control number number (0-119).
// Fourth parameter is the control value (0-127).


void momentarytoggle(int buttonstate, int lastbuttonstate, int led, int channel, int CCnum) {
  if (buttonstate != lastbuttonstate) {
    // if the state has changed, increment the counter
    if (buttonstate == LOW) {
      // if the current state is LOW then the button went from off to on:
      if (digitalRead(led)) {
        //turn off output
        controlChange(channel, CCnum, 0); // Set the value of controller 10 on channel 0 to 65
        digitalWrite(led, LOW);
      }
      else {
        //turn on output
        controlChange(channel, CCnum, 127); // Set the value of controller 10 on channel 0 to 65
        digitalWrite(led, HIGH);
      }
    }
    else {
    }
    delay(50);
  }
}

void changechannel(int buttonstate, int lastbuttonstate, int led, int channel, int CCnum) {
  if (buttonstate != lastbuttonstate) {
    // if the state has changed, increment the counter
    if (buttonstate == LOW) {
      // if the current state is LOW then the button went from off to on:
      if (digitalRead(led)) {
        //turn off output
        midichannel = 1; // Set the value of controller 10 on channel 0 to 65
        digitalWrite(led, LOW);
      }
      else {
        //turn on output
        midichannel = 2; // Set the value of controller 10 on channel 0 to 65
        digitalWrite(led, HIGH);
      }
    }
    else {
    }
    delay(50);
  }
}

void momentarycommand(int buttonstate, int lastbuttonstate, int led, int channel, int CCnum) {
  if (buttonstate != lastbuttonstate) {
    // if the state has changed, increment the counter
    if (buttonstate == LOW) {
      // if the current state is LOW then the button went from off to on:
      controlChange(channel, CCnum, 127); // Set the value of controller 10 on channel 0 to 65
      delay(5);
      controlChange(channel, CCnum, 0); // Set the value of controller 10 on channel 0 to 65
    }
    delay(50);
  }
}

void setup() {

  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);
  pinMode(button4, INPUT_PULLUP);
  pinMode(button5, INPUT_PULLUP);
  pinMode(button6, INPUT_PULLUP);
  pinMode(button7, INPUT_PULLUP);
  pinMode(button8, INPUT_PULLUP);
  pinMode(button9, INPUT_PULLUP);
  pinMode(button10, INPUT_PULLUP);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);
  pinMode(led7, OUTPUT);
  pinMode(led8, OUTPUT);
  pinMode(led9, OUTPUT);
  pinMode(led10, OUTPUT);

  midiclockflag = micros();

  //  Serial.begin(115200);
}




void loop() {

//  microsbuffer = micros();
//  if (microsbuffer - midiclockflag >= midiclockperiod) {
//    sendclock(0, 0, 0);
//    midiclockflag = microsbuffer;
//  }

  button1State = digitalRead(button1);
  button2State = digitalRead(button2);
  button3State = digitalRead(button3);
  button4State = digitalRead(button4);
  button5State = digitalRead(button5);
  button6State = digitalRead(button6);
  button7State = digitalRead(button7);
  button8State = digitalRead(button8);
  button9State = digitalRead(button9);
  button10State = digitalRead(button10);

  if (midichannel == 1) {
    momentarytoggle (button1State, lastbutton1State, led1, midichannel, button1CC);
    momentarytoggle (button2State, lastbutton2State, led2, midichannel, button2CC);
    momentarytoggle (button3State, lastbutton3State, led3, midichannel, button3CC);
    momentarytoggle (button4State, lastbutton4State, led4, midichannel, button4CC);
    momentarytoggle (button5State, lastbutton5State, led5, midichannel, button5CC);
    momentarytoggle (button6State, lastbutton6State, led6, midichannel, button6CC);
    momentarytoggle (button7State, lastbutton7State, led7, midichannel, button7CC);
    momentarytoggle (button8State, lastbutton8State, led8, midichannel, button8CC);
    momentarytoggle (button9State, lastbutton9State, led9, midichannel, button9CC);
  }
  else if (midichannel == 2) {
    momentarycommand (button1State, lastbutton1State, led1, midichannel, button11CC);
    momentarycommand (button2State, lastbutton2State, led2, midichannel, button12CC);
    momentarycommand (button3State, lastbutton3State, led3, midichannel, button13CC);
    momentarycommand (button4State, lastbutton4State, led4, midichannel, button14CC);
    momentarycommand (button5State, lastbutton5State, led5, midichannel, button15CC);
    momentarycommand (button6State, lastbutton6State, led6, midichannel, button16CC);
    momentarycommand (button7State, lastbutton7State, led7, midichannel, button17CC);
    momentarycommand (button8State, lastbutton8State, led8, midichannel, button18CC);
    momentarycommand (button9State, lastbutton9State, led9, midichannel, button19CC);
  }

  changechannel (button10State, lastbutton10State, led10, midichannel, button10CC);

  // save the current state as the last state, for next time through the loop
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

  MidiUSB.flush();

}
