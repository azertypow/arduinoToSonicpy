#define led 13                                    // affectation des broches
#define RX 10
#define TX 11
#define POTAR_PIN 0

// Création d'une liaison série 
#include <SoftwareSerial.h>                  
SoftwareSerial bluetooth(RX,TX);   

String dataToSend;

// Mux control pins
int s0 = 3;
int s1 = 4;
int s2 = 5;
int s3 = 6;

// Mux in “SIG” pin
int SIG_pin = 15;


/* LED */
int led11 = 22;
int led12 = 24;
int led13 = 26;

int led21 = 23;
int led22 = 25;
int led23 = 27;

int led31 = 28;
int led32 = 30;
int led33 = 32;

int led41 = 29;
int led42 = 31;
int led43 = 33;

int led51 = 34;
int led52 = 36;
int led53 = 38;

int led61 = 35;
int led62 = 37;
int led63 = 39;

int led71 = 40;
int led72 = 42;
int led73 = 44;

/* RECEIVE_API */
#define RECEIVE_API 13

/* Multiplexer */

void setup()
{
  Serial.begin(9600);
  bluetooth.begin(9600);                    // initialisation connexion série Bluetooth à 9600 bauds
  initLed();
  initMultiplexer();
  pinMode(RECEIVE_API, INPUT);
  Serial.println();
  Serial.println("ready");
}

void loop()
{
  analogWriteLedColor();
  
  /* Volume */
  int vol1 = analogRead(A0);
  int vol2 = analogRead(A1);
  int vol3 = analogRead(A2);
  int vol4 = analogRead(A3);
  int vol5 = analogRead(A4);
  int vol6 = analogRead(A5);
  int vol7 = analogRead(A6);

  addData("vol1", vol1);
  addData("vol2", vol2);
  addData("vol3", vol3);
  addData("vol4", vol4);
  addData("vol5", vol5);
  addData("vol6", vol6);
  addData("vol7", vol7);
  
  int fx_1_1 = analogRead(A7);
  int fxc_1_1 = map(fx_1_1, 1018, 0, 0, 1023);
  int fx_1_2 = analogRead(A8);
  int fxc_1_2 = map(fx_1_2, 1018, 0, 0, 1023);
  int fx_1_3 = analogRead(A9);
  int fxc_1_3 = map(fx_1_3, 1018, 0, 0, 1023);
  int fx_1_4 = analogRead(A10);
  int fxc_1_4 = map(fx_1_4, 1018, 0, 0, 1023);
  int fx_1_5 = analogRead(A11);
  int fxc_1_5 = map(fx_1_5, 1018, 0, 0, 1023);
  int fx_1_6 = analogRead(A12);
  int fxc_1_6 = map(fx_1_6, 1018, 0, 0, 1023);
  int fx_1_7 = analogRead(A13);
  int fxc_1_7 = map(fx_1_7, 1018, 0, 0, 1023);
  
  /* FX 1 */ 
  addData("fxc_1_1", fxc_1_1);
  addData("fxc_1_2", fxc_1_2);
  addData("fxc_1_3",fxc_1_3);
  addData("fxc_1_4",fxc_1_4);
  addData("fxc_1_5",fxc_1_5);
  addData("fxc_1_6",fxc_1_6);
  addData("fxc_1_7",fxc_1_7);

  /* RECEIVE_API */
  int receiveApi = digitalRead(RECEIVE_API);
  addData("status_api", receiveApi);

  /* send multiplexer data */
  addData( "fx_2_7", readMux(0));
  addData( "fx_2_6", readMux(1));
  addData( "fx_2_5", readMux(2));
  addData( "fx_2_4", readMux(3));
  addData( "fx_2_3", readMux(4));
  addData( "fx_2_2", readMux(5));
  addData( "fx_2_1", readMux(6));
  addData( "long", readMux(7));
  addData( "lat", readMux(8));
  
  sendData();
  
  delay(10); 
}

/*
 * void declaration
*/
void initLed() {
  pinMode(led11, OUTPUT);
  pinMode(led12, OUTPUT);
  pinMode(led13, OUTPUT); 
  
  pinMode(led21, OUTPUT);
  pinMode(led22, OUTPUT);
  pinMode(led23, OUTPUT); 
  
  pinMode(led31, OUTPUT);
  pinMode(led32, OUTPUT);
  pinMode(led33, OUTPUT); 
  
  pinMode(led41, OUTPUT);
  pinMode(led42, OUTPUT);
  pinMode(led43, OUTPUT); 
  
  pinMode(led51, OUTPUT);
  pinMode(led52, OUTPUT);
  pinMode(led53, OUTPUT); 
  
  pinMode(led61, OUTPUT);
  pinMode(led62, OUTPUT);
  pinMode(led63, OUTPUT); 
  
  pinMode(led71, OUTPUT);
  pinMode(led72, OUTPUT);
  pinMode(led73, OUTPUT);
}

void initMultiplexer() {
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  
  digitalWrite(s0, LOW);
  digitalWrite(s1, LOW);
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
}

void analogWriteLedColor() {
  analogWrite(led11, 0);
  analogWrite(led12,255);
  analogWrite(led13, 0); 
  
  analogWrite(led21, 0);
  analogWrite(led22,255);
  analogWrite(led23, 0); 
  
  analogWrite(led31, 0);
  analogWrite(led32,255);
  analogWrite(led33, 0); 
  
  analogWrite(led41, 0);
  analogWrite(led42,255);
  analogWrite(led43, 0); 
  
  analogWrite(led51, 0);
  analogWrite(led52,255);
  analogWrite(led53, 0); 
  
  analogWrite(led61, 0);
  analogWrite(led62,255);
  analogWrite(led63, 0); 
  
  analogWrite(led71, 0);
  analogWrite(led72,255);
  analogWrite(led73, 0);
}

void addData(String paramName, int data) {
  if(dataToSend != "") {
    dataToSend += ",";
  } else {
    dataToSend = "{";
  }
  dataToSend += "\"" + paramName + "\":" + data;
}

void sendData() {
  Serial.println(dataToSend + "}");
  bluetooth.println(dataToSend + "}");
  dataToSend = "";
}

int readMux(int channel) {
  int controlPin[] = {s0, s1, s2, s3};
  int muxChannel[16][4] = {
    {0,0,0,0}, //channel 0
    {1,0,0,0}, //channel 1
    {0,1,0,0}, //channel 2
    {1,1,0,0}, //channel 3
    {0,0,1,0}, //channel 4
    {1,0,1,0}, //channel 5
    {0,1,1,0}, //channel 6
    {1,1,1,0}, //channel 7
    {0,0,0,1}, //channel 8
    {1,0,0,1}, //channel 9
    {0,1,0,1}, //channel 10
    {1,1,0,1}, //channel 11
    {0,0,1,1}, //channel 12
    {1,0,1,1}, //channel 13
    {0,1,1,1}, //channel 14
    {1,1,1,1} //channel 15
  };
    
  //loop through the 4 sig
  for(int i = 0; i < 4; i ++)
  {
    digitalWrite(controlPin[i], muxChannel[channel][i]);
  }
  
  //read the value at the SIG pin
  int val = analogRead(SIG_pin);
  //return the value
  return val;
}

