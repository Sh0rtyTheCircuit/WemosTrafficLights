#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>

#include <WiFiClient.h>


int GREEN = D1; //DGREEN
int YELLOW = D2;
int RED = D4;

void setup() {
  // put your setup code here, to run once:
  pinMode(GREEN,OUTPUT);
  pinMode(YELLOW,OUTPUT);
  pinMode(RED,OUTPUT);
  Serial.begin(115200);
}

void TurnGREEN(){
  TurnOFF();
  digitalWrite(GREEN,HIGH);
  digitalWrite(YELLOW,LOW);
  digitalWrite(RED,LOW);
  Serial.print("GREEN");
}

void TurnYELLOW(){
  TurnOFF();
  digitalWrite(YELLOW,HIGH);
  digitalWrite(GREEN,LOW);
  digitalWrite(RED,LOW);
  Serial.print("YELLOW");
}

void TurnRED(){
  TurnOFF();
  digitalWrite(RED,HIGH);
  digitalWrite(GREEN,LOW);
  digitalWrite(YELLOW,LOW);
  Serial.print("RED");
}

void TurnOFF(){
  TurnOFF();
  digitalWrite(GREEN,LOW);
  digitalWrite(YELLOW,LOW);
  digitalWrite(RED,LOW);
  Serial.print("TurnedOFF");
}

/*void CYCLE(){
//  digitalWrite(GREEN,HIGH);
  delay(2000); //Wait 2 seconds
  digitalWrite(GREEN,LOW);
  digitalWrite(YELLOW,HIGH);
  delay(2000);
  digitalWrite(YELLOW,LOW);
  digitalWrite(RED,HIGH);
  delay(2000);
}*/

void loop() {
  // put your main code here, to run repeatedly:
  TurnOFF();
  TurnGREEN();
  delay(1000);
  TurnRED();
  delay(1000);
  TurnYELLOW();
  delay(1000);
  Serial.print("Looped");
}
