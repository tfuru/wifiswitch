#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define FIREBASE_HOST "wifiswitch-dev.firebaseio.com"
#define FIREBASE_AUTH "vLsS7UB5Vag2v4dm10wqvLxrRSBprMTlMHg5ssz3"
#define WIFI_SSID "tukuddo-guest-2.4"
#define WIFI_PASSWORD "monotukuddo"

#define LED 2

void setup() {
  Serial.begin(9600);
  
  pinMode(LED,OUTPUT);
  digitalWrite(LED,0);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  if(Firebase.getInt("LEDStatus")){
    digitalWrite(LED,HIGH);
  }
  else{
    digitalWrite(LED,LOW);
  }
}
