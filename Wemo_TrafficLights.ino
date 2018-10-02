#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>
#include <SPI.h>
//#include <avr/wdt.h> Watchdog timer library

// #### LED Pin Setup #### //
int GREEN = D1; 
int YELLOW = D2;
int RED = D4;

// ##### Wifi Connection Setup #### //
char WifiName[] = 
"Verizon-SM-G935V";            //SSID
char Password[] = "password";
ESP8266WebServer server(80);                     //Server is on Port 80


void setup() {
  // put your setup code here, to run once:
  pinMode(GREEN,OUTPUT);
  pinMode(YELLOW,OUTPUT);
  pinMode(RED,OUTPUT);
  Serial.begin(115200);                          //Starts the Serial Monitor (Input printed on screen)

  WiFi.begin(WifiName,Password);
  while (WiFi.status() !=WL_CONNECTED){          //If not connected to Wifi, delay until connected
    delay (2000);
    Serial.println("Finding a Connection...");
  }

  Serial.println("Connection Started");         //Begin Connection to Wifi
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());               //IP assigned to Server by host wifi

// #### Activate Functions #### //
  //If "/ " is seen in the URL, do this function
  server.on("/GREEN", TurnGREEN);
  server.on("/YELLOW", TurnYELLOW);
  server.on("/RED", TurnRED);
  server.on("/TurnOFF", TurnOFF);
  server.on ("/Cycle", CYCLE);

  server.onNotFound(NoClient);            //When client not found

  server.begin();
  Serial.println("Server Ready");
}


// #### Web Page Setup #### //
char WebPage[] = "<html><title><Choose Wisely></title><body><form action=\"/GREEN\"><button>Green</button></form><br><form action=\"/YELLOW\"><button>Yellow</button></form><br><form action=\"/RED\"><button>Red</button></form><br><form action=\"/TurnOFF\"><button>Clear</button></form><br><form action=\"/CYCLE\"><button>Cycle</button></form><br></body></html>";
char AutoRespond[] = "text/html\nRefresh: 1";   //header: content type/conent type\ how often refresh

void NoClient(){
  server.send(302, AutoRespond, WebPage);
  Serial.println("Reconnecting to server");
}

// #### LED Functions Setup #### //
void TurnGREEN(){
  TurnOFF();
  digitalWrite(GREEN,HIGH);
  digitalWrite(YELLOW,LOW);
  digitalWrite(RED,LOW);
  Serial.print("GREEN");
  server.send(302, AutoRespond, WebPage);
}

void TurnYELLOW(){
  TurnOFF();
  digitalWrite(YELLOW,HIGH);
  digitalWrite(GREEN,LOW);
  digitalWrite(RED,LOW);
  Serial.print("YELLOW");
  server.send(302, AutoRespond, WebPage);
}

void TurnRED(){
  TurnOFF();
  digitalWrite(RED,HIGH);
  digitalWrite(GREEN,LOW);
  digitalWrite(YELLOW,LOW);
  Serial.print("RED");
  server.send(302, AutoRespond, WebPage);
}

void TurnOFF(){
  TurnOFF();
  digitalWrite(GREEN,LOW);
  digitalWrite(YELLOW,LOW);
  digitalWrite(RED,LOW);
  Serial.print("TurnedOFF");
  server.send(302, AutoRespond, WebPage);
}

void CYCLE(){
  TurnOFF();
  digitalWrite(GREEN,HIGH);
  delay(2000); //Wait 2 seconds
  digitalWrite(GREEN,LOW);
  digitalWrite(YELLOW,HIGH);
  delay(2000);
  digitalWrite(YELLOW,LOW);
  digitalWrite(RED,HIGH);
  delay(2000);
  server.send(302, AutoRespond, WebPage);
}

void loop() {                                // put your main code here, to run repeatedly:
  server.handleClient();                     //Listen for clients (Connections to the webpage)
}
