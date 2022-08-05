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

    client.setServer(mqtt_server, 8883); // Sets the server details.  配置所连接的服务器

    client.setCallback(callback); // Sets the message callback function.  设置消息回调函数
}

void loop()
{
    if (!client.connected())
    {
        reConnect();
    }
    client.loop(); // This function is called periodically to allow clients to
                   // process incoming messages and maintain connections to the
                   // server.

    unsigned long now =
        millis(); // Obtain the host startup duration.
    if (now - lastMsg > 2000)
    {
        lastMsg = now;
        ++value;
        snprintf(msg, MSG_BUFFER_SIZE, "hello world #%ld",
                 value); // Format to the specified string and store it in MSG.
        M5.Lcd.print("Publish message: ");
        M5.Lcd.println(msg);
        client.publish("M5Stack", msg); // Publishes a message to the specified
                                        // topic.
        if (value % 7 == 0)
        {
            M5.Lcd.fillScreen(BLACK);
            M5.Lcd.setCursor(0, 0);
        }
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
    //     while (!client.connected())
    //     {
    M5.Lcd.print("Attempting MQTT connection...");

    if (client.connect(THINGNAME))
    {
        M5.Lcd.printf("\nSuccess\n");
        client.publish("$aws/things/grupo3/shadow/update",
                       "{\"state\": {\"desired\": {\"led\": 1}}}");

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
