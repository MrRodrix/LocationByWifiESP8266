#include <ESP8266WiFi.h>
//#include <ESP8266HTTPClient.h>
#include <WifiLocation.h>


const String key = "AIzaSyANCTMJZQJl1K3Qi_l0jkijdw4xMN-vQNI";
const char* ssid = "DTEL_SOARES";
const char* passwd = "lidiane20";
const String servername = "www.googleapis.com/geolocation/v1";
WiFiClient cliente;
WifiLocation location(key);

void setup() {
  Serial.begin(9600);
  Serial.println("Location request data");
  // Connect to WPA/WPA2 network
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, passwd);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // wait 5 seconds for connection:
    Serial.println("Status = ");
    Serial.println(WiFi.status());
    delay(500);
  }
  Serial.println("Status = ");
  Serial.println(WiFi.status());
  Serial.println("Setup finalizado");
}
//HTTPClient http;

void loop() {
  Serial.println("STATUS WIFI: "+ String(WiFi.status()));
  Serial.println("Location request data");
  Serial.println(location.getSurroundingWiFiJson());

//  String serverPath = "google.com";
//  if (cliente.connect(serverPath, 443)){
//    Serial.println("connected");
//    cliente.println("GET /search?q=arduino HTTP/1.0");
//    cliente.println();
//  }
//  
  delay(10000);
}
