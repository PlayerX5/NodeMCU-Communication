#include <ESP8266WiFi.h>

const char *ssid = "YOUR_SSID";      // Your Wi-Fi SSID
const char *password = "YOUR_PASSWORD";  // Your Wi-Fi password

void setup() {
  Serial.begin(115200);
  delay(10);

  // Connect to WiFi
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
  
  // Print the IP address of the NodeMCU
  Serial.println("Node IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Nothing to do here
}