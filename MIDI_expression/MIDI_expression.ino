#include <BLEMIDI_Transport.h>

#include <hardware/BLEMIDI_ESP32_NimBLE.h>
//#include <hardware/BLEMIDI_ESP32.h>
//#include <hardware/BLEMIDI_nRF52.h>
//#include <hardware/BLEMIDI_ArduinoBLE.h>

BLEMIDI_CREATE_INSTANCE("BLE Expression", MIDI);

unsigned long t0 = millis();
bool isConnected = false;

#define enablePin D6
#define s2 D5
#define s3 D4
#define s0 D3
#define s1 D2

#define expanderIO A0
#define jack1 A1
#define jack2 A2

#define pot1CC 41
#define pot2CC 42
#define pot3CC 43
#define pot4CC 44
#define pot5CC 45
#define pot6CC 46
#define pot7CC 47
#define pot8CC 48
#define pot9CC 49
#define pot10CC 50
#define pot11CC 51
#define pot12CC 52
#define pot13CC 53
#define pot14CC 54
#define pot15CC 55
#define jack1CC 56
#define jack2CC 57

byte pot1state = 0;
byte pot2State = 0;
byte pot3state = 0;
byte pot4state = 0;
byte pot5state = 0;
byte pot6state = 0;
byte pot7state = 0;
byte pot8state = 0;
byte pot9state = 0;
byte pot10state = 0;
byte pot11state = 0;
byte pot12state = 0;
byte pot13state = 0;
byte pot14state = 0;
byte pot15state = 0;
byte jack1state = 0;
byte jack2state = 0;

float linear1 = 0;
float linear2 = 0;

byte lastpot1state = 0;
byte lastpot2state = 0;
byte lastpot3state = 0;
byte lastpot4state = 0;
byte lastpot5state = 0;
byte lastpot6state = 0;
byte lastpot7state = 0;
byte lastpot8state = 0;
byte lastpot9state = 0;
byte lastpot10state = 0;
byte lastpot11state = 0;
byte lastpot12state = 0;
byte lastpot13state = 0;
byte lastpot14state = 0;
byte lastpot15state = 0;
byte lastjack1state = 0;
byte lastjack2state = 0;


byte midichannel = 4;


void controlChange(byte channel, byte control, byte value) {
  MIDI.sendControlChange(control, value, channel);  // note 60, velocity 127 on channel 1
}



void expression(byte buttonstate, byte lastbuttonstate, byte channel, byte CCnum) {
  if (buttonstate != lastbuttonstate) {
    controlChange(channel, CCnum, buttonstate);  // Send the value of the expression pedal to midi
  }
}


void setup() {
  //Serial.begin(115200);
  MIDI.begin();

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  pinMode(expanderIO,INPUT);
  pinMode(s0,OUTPUT);
  pinMode(s1,OUTPUT);
  pinMode(s2,OUTPUT);
  pinMode(s3,OUTPUT);

  digitalWrite(s0,HIGH);
  digitalWrite(s1,HIGH);
  digitalWrite(s2,HIGH);
  digitalWrite(s3,HIGH);

  BLEMIDI.setHandleConnected(OnConnected);
  BLEMIDI.setHandleDisconnected(OnDisconnected);
}

// -----------------------------------------------------------------------------
// Device connected
// -----------------------------------------------------------------------------
void OnConnected() {
  isConnected = true;
  digitalWrite(LED_BUILTIN, HIGH);
}

// -----------------------------------------------------------------------------
// Device disconnected
// -----------------------------------------------------------------------------
void OnDisconnected() {
  isConnected = false;
  digitalWrite(LED_BUILTIN, LOW);
}


void loop() {



  pot4state = analogRead(expanderIO) / 32;
  Serial.print(pot4state);
  Serial.print(" | ");
  jack1state = analogRead(jack1) / 32;
  Serial.println(jack1state);

  expression(pot4state, lastpot4state, midichannel, pot4CC);
  expression(jack1state, lastjack1state, midichannel, jack1CC);

  lastpot4state = pot4state;
  lastjack1state = jack1state;

  delay(10);
}
