
void setup() {
  // put your setup code here, to run once:
int GREEN = 8; //D8
int YELLOW = 6;
int RED = 0;
}

TurnGREEN(){
  digitalWrite(8,HIGH);
  digitalWrite(6,LOW);
  digitalWrite(0,LOW);
}

TurnYELLOW(){
  digitalWrite(6,HIGH);
  digitalWrite(8,LOW);
  digitalWrite(0,LOW);
}

TurnRED(){
  digitalWrite(0,HIGH);
  digitalWrite(8,LOW);
  digitalWrite(6,LOW);
}

TurnOFF(){
  digitalWrite(8,LOW);
  digitalWrite(6,LOW);
  digitalWrite(0,LOW);
}

CYCLE(){
  digitalWrite(8,HIGH);
  delay(2000); //Wait 2 seconds
  digitalWrite(8,LOW);
  digitalWrite(6,HIGH);
  delay(2000);
  digitalWrite(6,LOW);
  digitalWrite(0,HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  TurnGREEN();
}
