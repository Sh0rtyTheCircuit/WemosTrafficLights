#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>
//#include <avr/wdt.h> Watchdog timer library

// #### LED Pin Setup #### //
int GREEN = D5; 
int YELLOW = D7;
int RED = D6;

// ##### Wifi Connection Setup #### //
char WifiName[] = "Verizon-SM-G935V";            //SSID
char Password[] = "password";
ESP8266WebServer server(80);                     //Server is on Port 80


// #### Web Page Setup #### //
char WebPage[] = "<html><title><Choose Wisely></title><body><form action=\"/green\"><button>Green</button></form><br><form action=\"/yellow\"><button>Yellow</button></form><br><form action=\"/red\"><button>Red</button></form><br><form action=\"/turnoff\"><button>Clear</button></form><br><form action=\"/cycle\"><button>Cycle</button></form><br></body></html>";
char AutoRespond[] = "text/html\nRefresh: 1";   //header: content type/conent type\ how often refresh

void NoClient(){
  server.send(404);
  Serial.println("Reconnecting to server");
}

void HOME(){                //HomePage
  server.send(302, AutoRespond, WebPage);
  Serial.println("Home Page Opened");
}

// #### LED Functions Setup #### //
void TurnGREEN(){
  //TurnOFF();
  AllClear();
  digitalWrite(GREEN,HIGH);
  //digitalWrite(YELLOW,LOW);
  //digitalWrite(RED,LOW);
  Serial.println("GREEN");
  server.send(302, AutoRespond, WebPage);
}

void TurnYELLOW(){
  //TurnOFF();
  AllClear();
  digitalWrite(YELLOW,HIGH);
  //digitalWrite(GREEN,LOW);
  //digitalWrite(RED,LOW);
  Serial.println("YELLOW");
  server.send(302, AutoRespond, WebPage);
}

void TurnRED(){
  AllClear();
  digitalWrite(RED,HIGH);
  Serial.println("RED");
  server.send(302, AutoRespond, WebPage);
}

void TurnOFF(){
  AllClear();
  Serial.println("All Clear");
  server.send(302, AutoRespond, WebPage);
}

void AllClear(){
  digitalWrite(GREEN,LOW);
  digitalWrite(YELLOW,LOW);
  digitalWrite(RED,LOW);
}

void CYCLE(){
  //TurnOFF();
  AllClear();
  Serial.println("Cycling");
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
  server.on("/green", TurnGREEN);
  server.on("/yellow", TurnYELLOW);
  server.on("/red", TurnRED);
  server.on("/turnoff", TurnOFF);
  server.on ("/cycle", CYCLE);
  server.on("/", HOME);

  server.onNotFound(NoClient);            //When client not found

  server.begin();
  Serial.println("Server Ready");
}

void loop() {                                // put your main code here, to run repeatedly:
  server.handleClient();                     //Listen for clients (Connections to the webpage)
}
