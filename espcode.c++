#include <WiFi.h>
#include <WebSocketsServer.h>
#include <string>
#include <stdio.h>
#include <ESP32Servo.h>


#define TRIG_PIN  27 
#define ECHO_PIN  26 
#define LED_PIN   25
#define DISTANCE_THRESHOLD 119 
#include "DHT.h"


/*
#define DHTPIN 13
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
*/
float duration_us, distance_cm;

const int servoPin = 18;
int buzzerPin = 12;

Servo servo;

const char *name = "espServer";
const char *passwd = "criftw";
IPAddress mainIP(192, 168, 1, 16);
WebSocketsServer webSocket = WebSocketsServer(81);

void elevate(int a){
  servo.write(a);
}

float readTemp(){
  //readd temperature from sensors
  Serial.print(distance_cm);
  Serial.println(" cm");
}

float readWaterLevel(){
  //function that reads water level data from sensors
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration_us = pulseIn(ECHO_PIN, HIGH);
  distance_cm = 0.017 * duration_us;
}

void onWebSocketEvent(uint8_t num, WStype_t type, uint8_t * msg, size_t length) {
    if (type ==  WStype_TEXT){
        Serial.println(msg);
        //elevate(*((int*)(msg)));
    }

    if (type == WStype_DISCONNECTED){
      //connection led off
      digitalWrite(LED_PIN,0);
    }

    if (type == WStype_CONNECTED){
      //connection led on
      digitalWrite(LED_PIN,1);
    }
}

void setup() {
  Serial.begin(115200);
  servo.attach(servoPin, 500, 2400);

  WiFi.softAP(name,passwd);
  WiFi.softAPConfig(mainIP,mainIP, IPAddress(255, 255, 255, 0));

  pinMode(TRIG_PIN, OUTPUT); 
  pinMode(ECHO_PIN, INPUT);  
  pinMode(LED_PIN, OUTPUT);  
  pinMode(buzzerPin, OUTPUT);

  //dht.begin();
  Serial.println("espServer on");
}
int pos = 0;

void loop() {
  webSocket.loop();
  /*webSocket.broadcastTXT("t_"+readTemp());
  webSocket.broadcastTXT("w_"+readWaterLevel());*/
  webSocket.broadcastTXT("wii");
  delay(500);
}
