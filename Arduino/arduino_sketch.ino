#include <WiFiS3.h>
#include <ArduinoHttpClient.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
// Include the necessary libraries for WiFi, HTTP client, and NTP

// Define the WiFi credentials
char ssid[] = "JAC-TALENTI";
char pass[] = "Jac2020%";

// AWS API Gateway endpoint
char serverAddress[] = "iz4elvjg0b.execute-api.us-east-1.amazonaws.com";
int port = 443;
String endpointPath = "/prod/misure"; // Path to the API endpoint
String user = "giulio";

WiFiSSLClient wifi;
HttpClient client = HttpClient(wifi, serverAddress, port);

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 0, 60000);

// Pin for the piezo buzzer
const int piezoPin = 9;

void setup() {
  Serial.begin(9600);
  delay(1000);

  pinMode(piezoPin, OUTPUT);

  WiFi.begin(ssid, pass);
  Serial.print("Connessione WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnesso!");

  tone(piezoPin, 2000);
  delay(300);
  noTone(piezoPin);
  delay(100);
  tone(piezoPin, 1500);
  delay(300);
  noTone(piezoPin);

  timeClient.begin();
  timeClient.update();
}

String getTimestamp() {
  timeClient.update();
  unsigned long epochTime = timeClient.getEpochTime();

  int hour = (epochTime  % 86400L) / 3600;
  int minute = (epochTime % 3600) / 60;
  int second = epochTime % 60;

  char buf[25];
  snprintf(buf, sizeof(buf), "2025-07-11T%02d:%02d:%02dZ", hour, minute, second);
  return String(buf);
}

void loop() {
    // Read the light sensor value and send it to the AWS API Gateway
  int lightValue = analogRead(A0);
  String timestamp = getTimestamp();

  String json = "{\"misurazione\": " + String(lightValue) +
                ", \"timestamp\": \"" + timestamp + "\"" +
                ", \"user\": \"" + user + "\"}";

  Serial.println("Invio: " + json);

  client.post(endpointPath, "application/json", json);

  int status = client.responseStatusCode();
  String response = client.responseBody();

  Serial.print("Status: ");
  Serial.println(status);
  Serial.print("Response: ");
  Serial.println(response);

  tone(piezoPin, 1000);
  delay(200);
  noTone(piezoPin);

  delay(4800);
}