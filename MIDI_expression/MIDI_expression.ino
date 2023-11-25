#include <BLEMIDI_Transport.h>

#include <hardware/BLEMIDI_ESP32_NimBLE.h>
//#include <hardware/BLEMIDI_ESP32.h>
//#include <hardware/BLEMIDI_nRF52.h>
//#include <hardware/BLEMIDI_ArduinoBLE.h>

BLEMIDI_CREATE_INSTANCE("BLE Expression", MIDI);

int midichannel = 4;

#define analogconversionfactor 32

//filter gains must add to 1
#define filtergain1 0.04
#define filtergain2 0.96

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
#define pot16CC 56
#define jack1CC 57
#define jack2CC 58

#define pot1loc 0b0011
#define pot2loc 0b1011
#define pot3loc 0b0111
#define pot4loc 0b1111
#define pot5loc 0b0000
#define pot6loc 0b1000
#define pot7loc 0b0100
#define pot8loc 0b1100
#define pot9loc 0b0010
#define pot10loc 0b1010
#define pot11loc 0b0110
#define pot12loc 0b1110
#define pot13loc 0b0101
#define pot14loc 0b1101
#define pot15loc 0b0001
#define pot16loc 0b1001


unsigned long t0 = millis();
bool isConnected = false;

int pot1state = 0;
int pot2state = 0;
int pot3state = 0;
int pot4state = 0;
int pot5state = 0;
int pot6state = 0;
int pot7state = 0;
int pot8state = 0;
int pot9state = 0;
int pot10state = 0;
int pot11state = 0;
int pot12state = 0;
int pot13state = 0;
int pot14state = 0;
int pot15state = 0;
int pot16state = 0;
int jack1state = 0;
int jack2state = 0;

int newpot1state = 0;
int newpot2state = 0;
int newpot3state = 0;
int newpot4state = 0;
int newpot5state = 0;
int newpot6state = 0;
int newpot7state = 0;
int newpot8state = 0;
int newpot9state = 0;
int newpot10state = 0;
int newpot11state = 0;
int newpot12state = 0;
int newpot13state = 0;
int newpot14state = 0;
int newpot15state = 0;
int newpot16state = 0;
int newjack1state = 0;
int newjack2state = 0;

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
byte lastpot16state = 0;
byte lastjack1state = 0;
byte lastjack2state = 0;




void controlChange(byte channel, byte control, byte value) {
  MIDI.sendControlChange(control, value, channel);  // note 60, velocity 127 on channel 1
}

int readExpander(){
  int valuestorage = analogRead(expanderIO);
  valuestorage = 0.5 * valuestorage + 0.5 * analogRead(expanderIO);
  return valuestorage;
}

int readJack(int jackid){}

byte expression(int buttonstate, int lastbuttonstate, byte channel, byte CCnum) {
  buttonstate = buttonstate / analogconversionfactor;
  if (buttonstate != lastbuttonstate) {
    byte valuestorage = buttonstate;
    controlChange(channel, CCnum, valuestorage);  // Send the value of the expression pedal to midi
  }
  return buttonstate;
}

void configureexpander(byte inputloc){
  if(inputloc&0b1000){
    digitalWrite(s0,HIGH);
  }
  else{
    digitalWrite(s0,LOW);
  }  if(inputloc&0b0100){
    digitalWrite(s1,HIGH);
  }
  else{
    digitalWrite(s1,LOW);
  }  if(inputloc&0b0010){
    digitalWrite(s2,HIGH);
  }
  else{
    digitalWrite(s2,LOW);
  }  if(inputloc&0b0001){
    digitalWrite(s3,HIGH);
  }
  else{
    digitalWrite(s3,LOW);
  }
}


void setup() {
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

  configureexpander(pot1loc);
  newpot1state = readExpander();
  pot1state = newpot1state * filtergain1 + pot1state * filtergain2;
  configureexpander(pot2loc);  
  newpot2state = readExpander();
  pot2state = newpot2state * filtergain1 + pot2state * filtergain2; 
  configureexpander(pot3loc); 
  newpot3state = readExpander();
  pot3state = newpot3state * filtergain1 + pot3state * filtergain2;
  configureexpander(pot4loc);  
  newpot4state = readExpander();
  pot4state = newpot4state * filtergain1 + pot4state * filtergain2;
  configureexpander(pot5loc);  
  newpot5state = readExpander();
  pot5state = newpot5state * filtergain1 + pot5state * filtergain2;
  configureexpander(pot6loc);  
  newpot6state = readExpander();
  pot6state = newpot6state * filtergain1 + pot6state * filtergain2;
  configureexpander(pot7loc);  
  newpot7state = readExpander();
  pot7state = newpot7state * filtergain1 + pot7state * filtergain2;
  configureexpander(pot8loc);  
  newpot8state = readExpander();
  pot8state = newpot8state * filtergain1 + pot8state * filtergain2;
  configureexpander(pot9loc);  
  newpot9state = readExpander();
  pot9state = newpot9state * filtergain1 + pot9state * filtergain2;
  configureexpander(pot10loc);  
  newpot10state = readExpander();
  pot10state = newpot10state * filtergain1 + pot10state * filtergain2;
  configureexpander(pot11loc);  
  newpot11state = readExpander();
  pot11state = newpot11state * filtergain1 + pot11state * filtergain2;
  configureexpander(pot12loc);  
  newpot12state = readExpander();
  pot12state = newpot12state * filtergain1 + pot12state * filtergain2;
  configureexpander(pot13loc);  
  newpot13state = readExpander();
  pot13state = newpot13state * filtergain1 + pot13state * filtergain2;
  configureexpander(pot14loc);  
  newpot14state = readExpander();
  pot14state = newpot14state * filtergain1 + pot14state * filtergain2;
  configureexpander(pot15loc);  
  newpot15state = readExpander();
  pot15state = newpot15state * filtergain1 + pot15state * filtergain2;
  configureexpander(pot16loc);
  newpot16state = readExpander();
  pot16state = newpot16state * filtergain1 + pot16state * filtergain2;
  
  newjack1state = analogRead(jack1);
  jack1state = newjack1state * filtergain1 + jack1state * filtergain2;  
  newjack2state = analogRead(jack2);
  jack2state = newjack2state * filtergain1 + jack2state * filtergain2;

  lastpot1state = expression(pot1state, lastpot1state, midichannel, pot1CC);
  lastpot2state = expression(pot2state, lastpot2state, midichannel, pot2CC);
  lastpot3state = expression(pot3state, lastpot3state, midichannel, pot3CC);
  lastpot4state = expression(pot4state, lastpot4state, midichannel, pot4CC);
  lastpot5state = expression(pot5state, lastpot5state, midichannel, pot5CC);
  lastpot6state = expression(pot6state, lastpot6state, midichannel, pot6CC);
  lastpot7state = expression(pot7state, lastpot7state, midichannel, pot7CC);
  lastpot8state = expression(pot8state, lastpot8state, midichannel, pot8CC);
  lastpot9state = expression(pot9state, lastpot9state, midichannel, pot9CC);
  lastpot10state = expression(pot10state, lastpot10state, midichannel, pot10CC);
  lastpot11state = expression(pot11state, lastpot11state, midichannel, pot11CC);
  lastpot12state = expression(pot12state, lastpot12state, midichannel, pot12CC);
  lastpot13state = expression(pot13state, lastpot13state, midichannel, pot13CC);
  lastpot14state = expression(pot14state, lastpot14state, midichannel, pot14CC);
  lastpot15state = expression(pot15state, lastpot15state, midichannel, pot15CC);
  lastpot16state = expression(pot16state, lastpot16state, midichannel, pot16CC);
  lastjack1state = expression(jack1state, lastjack1state, midichannel, jack1CC);
  lastjack2state = expression(jack2state, lastjack2state, midichannel, jack2CC);

  delayMicroseconds(100);
}
