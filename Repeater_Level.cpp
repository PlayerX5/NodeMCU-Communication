#include <ESP8266WiFi.h>

const char *ssid = "YOUR_SSID";      // Your Wi-Fi SSID
const char *password = "YOUR_PASSWORD";  // Your Wi-Fi password
const int serverPort = 80;           // Port to listen on
const char *serverIP = "192.168.209.210"; // Server IP address

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

  // Connect to the server
  WiFiClient serverClient;
  Serial.print("Connecting to server: ");
  Serial.println(serverIP);
  if (!serverClient.connect(serverIP, serverPort)) {
    Serial.println("Connection to server failed");
    return;
  }
  Serial.println("Connected to server");

  // Forward the request to the server
  serverClient.print(request);

  // Wait for the response from the server
  while (serverClient.connected() && !serverClient.available()) {
    delay(1);
  }

  // Read and forward the response to the client
  const int bufferSize = 1024; // Adjust the buffer size as needed
  uint8_t buffer[bufferSize];
  size_t bytesRead;
  while ((bytesRead = serverClient.readBytes(buffer, bufferSize)) > 0) {
    client.write(buffer, bytesRead); // Forward response to client
  }
  Serial.println();
  Serial.println("Request forwarded");

  // Disconnect from the server
  serverClient.stop();
  Serial.println("Disconnected from server");

  // Close the connection with the client
  client.stop();
  Serial.println("Client disconnected");
}