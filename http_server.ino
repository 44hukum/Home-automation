
/**
 *  CONNECT TO YOUR HOME NEWORK AND USE ESP8266-01 MODULE TO CREATE A SIMPLE
 *  HTTP SERVER AND LET ACCESS TO 4CHANNEL RELAY CONTROL SYSTEM 
 *
*/

#include <ESP8266WiFi.h>

#ifndef STASSID
#define STASSID "Your wifi id here"
#define STAPSK  "wifi password"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

WiFiServer server(80);

int OUTPUT_MODE_LOW = 1;
int OUTPUT_MODE_HIGH= 0; 


int PORT0=0,PORT1=1,PORT2=2,PORT3=3;

void setup() {
  Serial.begin(115200);
  
  /* PIN CONTROL */
  pinMode(PORT0, OUTPUT);
  pinMode(PORT1, OUTPUT);
  pinMode(PORT2, OUTPUT);
  pinMode(PORT3, OUTPUT);
 
  digitalWrite(PORT0, OUTPUT_MODE_LOW);
  digitalWrite(PORT1, OUTPUT_MODE_LOW);
  digitalWrite(PORT2, OUTPUT_MODE_LOW);
  digitalWrite(PORT3, OUTPUT_MODE_LOW);

/* WIFI CONNECTION BEGIN*/
  Serial.print(F("Connecting to "));
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println(F("Retrying:  "));
  }
  Serial.println(F("WiFi connected"));

  
  server.begin();
  Serial.println(F("Server started"));
  // Print the IP address
  Serial.println(WiFi.localIP());
}

void loop() {
 /* START WIFI CLIENT */
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  Serial.println(F("new client"));
  client.setTimeout(5000); // default is 1000

  String req = client.readStringUntil('\r');
  Serial.println(F("request: "));
  Serial.println(req);



/* MATCH THE REQUEST FOR CONTROL CENTER */
  int OUTPUT1,OUTPUT2,OUTPUT3,OUTPUT4;
 
  /* 1st*/
 if (req.indexOf(F("jb0"))){
  
  if (req.indexOf(F("/jb0/0")) != -1) {
    digitalWrite(PORT0,OUTPUT_MODE_LOW);
    OUTPUT1 = OUTPUT_MODE_LOW;
  } else if (req.indexOf(F("/jb0/1")) != -1) {
    digitalWrite(PORT0,OUTPUT_MODE_HIGH);
      OUTPUT1 = OUTPUT_MODE_HIGH;
  } 
}
 /* 2st*/
 else if(req.indexOf(F("jb1"))){
  
  if (req.indexOf(F("/jb1/0")) != -1) {
    digitalWrite(PORT1,OUTPUT_MODE_LOW);
     OUTPUT2 = OUTPUT_MODE_LOW;
  } else if (req.indexOf(F("/jb1/1")) != -1) {
    digitalWrite(PORT1,OUTPUT_MODE_HIGH);
     OUTPUT1 = OUTPUT_MODE_HIGH;
  } 
}
 /* 3rd*/
else if(req.indexOf(F("jb2"))){
  
  if (req.indexOf(F("/jb2/0")) != -1) {
    digitalWrite(PORT2,OUTPUT_MODE_LOW);
    OUTPUT3 = OUTPUT_MODE_LOW;
  } else if (req.indexOf(F("/jb2/1")) != -1) {
    digitalWrite(PORT2,OUTPUT_MODE_HIGH);
    OUTPUT3 = OUTPUT_MODE_HIGH;
  } 

} 
/* 4th*/
else if (req.indexOf(F("jb3"))){
  if (req.indexOf(F("/jb3/0")) != -1) {
    digitalWrite(PORT3,OUTPUT_MODE_LOW);
     OUTPUT4 = OUTPUT_MODE_LOW;
  } else if (req.indexOf(F("/jb3/1")) != -1) {
    digitalWrite(PORT3,OUTPUT_MODE_HIGH);
     OUTPUT4 = OUTPUT_MODE_HIGH;
  }

   }

  while (client.available()) {
     client.read();
  }

  // Send the response to the client
  // it is OK for multiple small client.print/write,
  // because nagle algorithm will group them into one single packet
 client.print(F("HTTP/1.1 200 OK"));
 

  
//
//  // The client will actually be *flushed* then disconnected
//  // when the function returns and 'client' object is destroyed (out-of-scope)
//  // flush = ensure written data are received by the other side
  Serial.println(F("Disconnecting from client"));
}
