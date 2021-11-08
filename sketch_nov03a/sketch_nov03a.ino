#include <ESP8266WiFi.h>
#include <WifiLocation.h>


const String key = "AIzaSyANCTMJZQJl1K3Qi_l0jkijdw4xMN-vQNI";
const char* ssid = "DTEL_SOARES";
const char* passwd = "lidiane20";
const String serverPath = "SERVER.COM.BR";
WiFiClient cliente;
WifiLocation location("fuckyou");

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
  String data = "{wifiAccessPoints: "+String(location.getSurroundingWiFiJson())+"}";
  if (cliente.connect(serverPath, 443)){
    Serial.println("Connected to server");
    cliente.println("POST /update-sensor HTTP/1.1");
    cliente.println("Host: " + serverPath);
    cliente.println("Content-Type: application/json");
    cliente.println(data);
    cliente.println();
  }
  while(cliente.available()){
    String line = cliente.readStringUntil('\r');
    Serial.print(line);
  }
  delay(10000);
}
