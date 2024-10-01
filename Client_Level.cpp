#include <ESP8266WiFi.h>

const char *ssid = "YOUR_SSID";      // Your Wi-Fi SSID
const char *password = "YOUR_PASSWORD";  // Your Wi-Fi password
const char *serverIP = "192.168.209.234"; // Server IP address
const int serverPort = 80;           // Port the server is listening on

WiFiClient client;

void setup() {
  Serial.begin(115200);
  delay(10);

  // Connect to Wi-Fi
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

  // Connect to server
  Serial.print("Connecting to server: ");
  Serial.println(serverIP);
  if (!client.connect(serverIP, serverPort)) {
    Serial.println("Connection failed");
    return;
  }
  Serial.println("Connected to server");
}

void loop() {
  // Send a request to the server
  client.println("GET / HTTP/1.1");
  client.println("Host: 192.168.209.234"); // Server IP
  client.println("Connection: close");
  client.println();

  // Wait for the response
  while (client.connected() && !client.available()) {
    delay(1);
  }

  // Print the response
  while (client.available()) {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  Serial.println();
  Serial.println("Request sent");

  // Disconnect from the server
  client.stop();
  Serial.println("Disconnected from server");

  // Wait before sending the next request
  delay(5000);
}