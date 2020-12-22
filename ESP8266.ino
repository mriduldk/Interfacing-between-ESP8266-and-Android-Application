/*
 *  This sketch demonstrates how to set up a simple HTTP-like server.
 *  The server will set a GPIO pin depending on the request
 *    http://server_ip/led/0 will set the GPIO2 low,
 *    http://server_ip/led/1 will set the GPIO2 high
 *  server_ip is the IP address of the ESP8266 module, will be 
 *  printed to Serial when the module is connected.
 */

#include <ESP8266WiFi.h>

const char* ssid = "ssid";
const char* password = "pass";

// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);
int ledPin = 13;

void setup() {
  Serial.begin(115200);
  delay(10);

  // prepare GPIO2
  //pinMode(ledPin, OUTPUT);
  //digitalWrite(ledPin, 0);
  
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());
}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
  
  // Read the first line of the request
  String req = client.readStringUntil('\r');
  // Data from phone can be stored in Req variable
  Serial.println(req);
  client.flush();
  

 Serial.println("Got request..");
 client.flush();

   // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one

  // send value to android 
  client.print("5.6 PH");
 

  Serial.println("Client disonnected...");
  // The client will actually be disconnected 
  // when the function returns and 'client' object is detroyed
}
