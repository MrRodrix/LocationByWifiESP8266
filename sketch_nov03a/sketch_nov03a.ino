#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WifiLocation.h>


const String key = "AIzaSyANCTMJZQJl1K3Qi_l0jkijdw4xMN-vQNI";
const char* ssid = "DTEL_SOARES";
const char* passwd = "lidiane20";
const String serverPath = "http://onde-circular.herokuapp.com/wifi";
WiFiClient cliente;
WifiLocation location(key);
HTTPClient http;

void connect_wifi(){
  // Connect on wifi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, passwd);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // wait 5 seconds for connection:
    Serial.print("Status = ");
    Serial.println(WiFi.status());
    delay(500);
  }
  Serial.print("End\n Status = ");
  Serial.println(WiFi.status());
}

void setup() {
  Serial.begin(9600);
  connect_wifi();
}

void loop() {
  if (WiFi.status() != WL_CONNECTED){
    connect_wifi();
  }
  Serial.println("STATUS WIFI: "+ String(WiFi.status()));
  Serial.println("Location request data");
  Serial.println(location.getSurroundingWiFiJson());
  String data = "{\"wifiAccessPoints\": "+String(location.getSurroundingWiFiJson())+"}";
  http.begin(cliente, serverPath);
  // If you need an HTTP request with a content type: application/json, use the following:
  http.addHeader("Content-Type", "application/json");
  // JSON data to send with HTTP POST            
  // Send HTTP POST request
  int httpResponseCode = http.POST(data);
  Serial.print("HTTP Response code: ");
  Serial.println(httpResponseCode);
    
  // Free resources
  http.end();
  delay(10000);
}
