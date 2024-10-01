#include <ESP8266WiFi.h>

const char *ssid = "YOUR_SSID";      // Your Wi-Fi SSID
const char *password = "YOUR_PASSWORD";  // Your Wi-Fi password
const int serverPort = 80;           // Port to listen on

WiFiServer server(serverPort);

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

  // Start the server
  server.begin();
  Serial.println("Server started");
}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Wait until the client sends some data
  Serial.println("New client connected");
  while (!client.available()) {
    delay(1);
  }

  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  // Send a response to the client
  client.println("Hey Sathwik");
  client.println("Content-Type: text/html");
  client.println(""); // Blank line
  client.println("<h1>Hello from NodeMCU 1!</h1>");

  // The client will be disconnected after the response is sent
  delay(1);
  Serial.println("Client disconnected");
}