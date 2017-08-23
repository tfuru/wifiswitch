#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define FIREBASE_HOST "wifiswitch-dev.firebaseio.com"
#define FIREBASE_AUTH "vLsS7UB5Vag2v4dm10wqvLxrRSBprMTlMHg5ssz3"
#define WIFI_SSID "tukuddo-guest-2.4"
#define WIFI_PASSWORD "monotukuddo"

#define LED 4
#define SW 0

void setup() {
  Serial.begin(115200);

  //LED初期化
  pinMode(LED,OUTPUT);
  digitalWrite(LED,LOW);
  
  //スイッチを入力として初期化
  pinMode(SW,INPUT);
  
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
  //Firebaseとの接続でエラー
  if (Firebase.failed()) {
    Serial.print("setting /number failed:");
    Serial.println(Firebase.error());
    return;
  }
  
  //データベースの状態をみてLED点灯
  if(Firebase.getBool("led") == true){
    Serial.println("LED ON");
    digitalWrite(LED,HIGH);
  }
  else{
    Serial.println("LED OFF");
    digitalWrite(LED,LOW);
  }

  //スイッチ状態をみて Firebase に書き込む
  if(digitalRead(SW) == LOW){
    Serial.println("SW ON");
    Firebase.setBool("btn", true);
    delay(1000);
  }
  else{
    Serial.println("SW OFF");
    Firebase.setBool("btn", false);
  }
}
