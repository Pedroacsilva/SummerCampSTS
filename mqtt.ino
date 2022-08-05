/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with M5StickC-Plus sample source code
*                          配套  M5StickC-Plus 示例源代码
* Visit for more information: https://docs.m5stack.com/en/core/m5stickc_plus
* 获取更多资料请访问: https://docs.m5stack.com/zh_CN/core/m5stickc_plus
*
* Describe: MQTT.
* Date: 2021/11/5
*******************************************************************************
*/
#include "M5StickCPlus.h"
#include "secrets.h"

#include <WiFi.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>

WiFiClientSecure espClient;
PubSubClient client(espClient);

unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE (50)
char msg[MSG_BUFFER_SIZE];
int value = 0;

void setupWifi();
void callback(char *topic, byte *payload, unsigned int length);
void reConnect();

void setup()
{
    M5.begin();
    M5.Lcd.setRotation(3);
    setupWifi();
    setupCredentials();
    M5.begin();
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setTextSize(2);
    
    pinMode(10, OUTPUT);

    client.setServer(mqtt_server, 8883); // Sets the server details.

    client.setCallback(callback); // Sets the message callback function.
}

void loop() {
  M5.update();
  ledSwitch();

  
}

void ledSwitch(){
  if(M5.BtnA.wasReleased()){
    digitalWrite(10,LOW);
    if (client.connected() || client.connect(THINGNAME)){
      client.publish("$aws/things/grupo3/shadow/update",
        "{\"state\": {\"desired\": {\"led\": 1}}}");
    }
  }
  else if (M5.BtnA.wasReleasefor(700)) {
    digitalWrite(10,HIGH);
    if (client.connected() || client.connect(THINGNAME)){
      client.publish("$aws/things/grupo3/shadow/update",
        "{\"state\": {\"desired\": {\"led\": 0}}}");
    }
  }
  }
}

bool ledState(){
  if(digitalRead(10) == 0){
    M5.Lcd.print("On\n");
    return true; 
  }
  else{
    M5.Lcd.print("Off\n");
    return false;
  }
    
}

void setupWifi()
{
    delay(10);
    M5.Lcd.printf("Connecting to %s", ssid);
    WiFi.mode(
        WIFI_STA);              // Set the mode to WiFi station mode.
    WiFi.begin(ssid, password); // Start Wifi connection.

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        M5.Lcd.print(".");
    }
    M5.Lcd.printf("\nSuccess\n");
}

void setupCredentials()
{
    delay(10);
    M5.Lcd.printf("Setting credentials...");

    espClient.setCACert(cacert);
    espClient.setCertificate(client_cert); // for client verification
    espClient.setPrivateKey(privkey);      // for client verification
}

void callback(char *topic, byte *payload, unsigned int length)
{
    M5.Lcd.print("Message arrived [");
    M5.Lcd.print(topic);
    M5.Lcd.print("] ");
    for (int i = 0; i < length; i++)
    {
        M5.Lcd.print((char)payload[i]);
    }
    M5.Lcd.println();
}
void reConnect()
{
    M5.Lcd.print("Attempting MQTT connection...");

    if (client.connect(THINGNAME))
    {
        M5.Lcd.printf("\nSuccess\n");


        client.subscribe("$aws/things/grupo3/shadow/update");
    }
    else
    {
        M5.Lcd.print("failed, rc= ");
        M5.Lcd.print(client.state());
        M5.Lcd.println(", try again in 5 seconds");
        delay(5000);
    }
    delay(10000);
    // }
}
