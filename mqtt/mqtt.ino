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
#include <WiFi.h>
#include <PubSubClient.h>

#include <WiFiClientSecure.h>

WiFiClientSecure espClient;
PubSubClient client(espClient);

// Configure the name and password of the connected wifi and your MQTT Serve
// host.  配置所连接wifi的名称、密码以及你MQTT服务器域名
const char *ssid = "CSW-Guest";      // your network SSID (name of wifi network)
const char *password = "Critical98"; // your network password
const char *mqtt_server = "a1yj9lgdqxsds2-ats.iot.eu-west-2.amazonaws.com";

const char *test_root_ca =
    "-----BEGIN CERTIFICATE-----"
    "MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF"
    "ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6"
    "b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL"
    "MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv"
    "b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj"
    "ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM"
    "9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw"
    "IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6"
    "VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L"
    "93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm"
    "jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC"
    "AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA"
    "A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI"
    "U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs"
    "N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv"
    "o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU"
    "5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy"
    "rqXRfboQnoZsG4q5WTP468SQvvG5"
    "-----END CERTIFICATE-----";

// You can use x.509 client certificates if you want
const char *test_client_key =
    "-----BEGIN CERTIFICATE-----"
    "MIIDWjCCAkKgAwIBAgIVAIFuWtYDwa/K/5PTjAmjp/Oe0eZZMA0GCSqGSIb3DQEB"
    "CwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t"
    "IEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0yMjA4MDQxMzUx"
    "NTlaFw00OTEyMzEyMzU5NTlaMB4xHDAaBgNVBAMME0FXUyBJb1QgQ2VydGlmaWNh"
    "dGUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQCvyUMU22Hhpf9gCwcy"
    "0+8F75hw5PsjokG7TN7W7Nhz2OSnTjJpSzNuTDC1bY0py5n9kFEGJU3Ejv7MESEq"
    "K5gQNuDacqPtCjpTsJIYq8LXil4UOEuBB2juwash2IiLdkrEnwMnBhfwKlw+2znN"
    "BXoCnhL5QAbsI09NO1zosPTCP31NeODBDlcczmchJr7sMD9mahv97qwsqNTjImV2"
    "3dtDNqtQXL8h/oBmebIu2GBgRD+QgeN6xil4PUR9m0bX+yNHP0y/0FTWApWheeKp"
    "hSW/usUhMwvxGI67ok+1SHfd7N6SdcJ06KWK0thjmFVJFQjpp9yXOxZ/563oyNew"
    "0PYDAgMBAAGjYDBeMB8GA1UdIwQYMBaAFAYs8aerIJhJ5KXOPs+TNM4cKd08MB0G"
    "A1UdDgQWBBSyW5VD2PoQUngABgXlzB1McyeSVzAMBgNVHRMBAf8EAjAAMA4GA1Ud"
    "DwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEAYPRzqEpJGjkoxrD9utRpZIUN"
    "gsf++kQQov9Th8eJRtt71uXzWnrvBQpiLqei851+F3KZXLBpTwl6X8kuvzmbba+J"
    "3gx0Wrjsge3uNkVzs8neez0Y33zReD0oM7VGembqk34Quhlg3mAaMf2KaXZy2t5h"
    "xlTOfl8NQEJwbAxfGi0uYjm+5O7g9ntMjHYeHPbQ5JJZa7Nn845/VFvfxOWFUH+q"
    "PonHdEmR0aR9aooo8QHGFfchG24lCaatzh1zZmC/ZRexmvslbaPYcAUQIYIsOAyg"
    "7gX68i4j9BBfEKaR6CZe2tcdbobwlPsIFznS9bAWiuhaxUm5tOcAMEC/CKVUUg=="
    "-----END CERTIFICATE-----";

const char *test_client_cert =
    "-----BEGIN RSA PRIVATE KEY-----"
    "MIIEpAIBAAKCAQEAr8lDFNth4aX/YAsHMtPvBe+YcOT7I6JBu0ze1uzYc9jkp04y"
    "aUszbkwwtW2NKcuZ/ZBRBiVNxI7+zBEhKiuYEDbg2nKj7Qo6U7CSGKvC14peFDhL"
    "gQdo7sGrIdiIi3ZKxJ8DJwYX8CpcPts5zQV6Ap4S+UAG7CNPTTtc6LD0wj99TXjg"
    "wQ5XHM5nISa+7DA/Zmob/e6sLKjU4yJldt3bQzarUFy/If6AZnmyLthgYEQ/kIHj"
    "esYpeD1EfZtG1/sjRz9Mv9BU1gKVoXniqYUlv7rFITML8RiOu6JPtUh33ezeknXC"
    "dOilitLYY5hVSRUI6afclzsWf+et6MjXsND2AwIDAQABAoIBAQCdwZJpImUae73O"
    "tLb2H4rQGfEFyAm2NgSlkdweqBmtBcZWe2/0XN/AKbJA8BsSmj0NeTmtuUaskuQJ"
    "wYmw7cSfMJDkmqOQtHAZ8Ul7yJGom+3IWakxF7RNKRNq4YfRGQ0KneXXXLmY+Hsm"
    "kdmyrCqONMy0UYik3R9rIU5FKaHOvGu4qnIw1V/FfJMLBdM5XOXj5ypvy9NnQJiX"
    "OfTGxkbqWOrsP/AvnIOhvbPwGXCUi0gWTyul2HVIHfAEjLtTNe5acVYj8tdUxjJN"
    "8X56z1mi6pNYdUC5uwA8C0zyMFCMwkIRMNtcmCGIIAblDhrUF/Oo265gM7ujIvm+"
    "k4nJ+DLxAoGBAOX07GGdVQS9sQYZYCHgzusPf/aHtjCRwL8c8dMr0V9IDMVlgQSg"
    "q8da2nUwCRnQ6y87J5Xoi5i0ELlaY3b8YQkPfElddZ+MhQBQNJELq1sxhNjm+zP7"
    "oiUwEsBM3aEH6fGAKEsrg0EZDPLKrPeqyspte2+m7jU8Ga30zP1C5QwLAoGBAMOx"
    "ySWWWRY5H50tQcUj294zhezvMTIWvSs2L1XWFseVZl44FDXyn5kS/48c6kj8BCvz"
    "39v9Pfo3CfqKgc2IpOCH4K2fgSh3040/QHNjKR2xpzdcxWULi21MA68flWi5CWvC"
    "9pJtgNteyNAjdZRkFmw4DsdcWXxhUTS/gdspqwDpAoGAMd3/NNvth+2q6euu0Snz"
    "NT5TPZ8If1fcOJWKS4UBDmyNeHEenWZKWhz1qtwT3SlVFxT47KVVQHQr/EYBs9ff"
    "Ixvck/xUeZj7bqn1/E5PhqMib/cHGqrC6tWV+2Wv2i/hJ6HnGwYAnKlWCYCyKbM7"
    "7tH3JqtIlPrHhtXDbliHWykCgYAahZPPRksYmfFQ6ftJ7owz1yPFcr1mHnLQ0m0j"
    "4vn/Xp4bEtqaXSGIK2z7Rl3yOkWOd2TVecLWkHMHw5HH+0btLz0iCsYEaAkB0Zq4"
    "iK3f2l3hQO93vFLPI0g0icFECh/evPOR8MlP8c6hdszOqanoTMij+D4gf0f0MCg3"
    "PbRxUQKBgQCCJZh4n3BJMwSmTskSK4hdKfF5Uw70jOElHXo6w8NjSfwv7pYnL4g5"
    "jx0+uW6L1l+DYuq5Lxh/rTYxF1H0fNq0jhW2QA/WPQQuWVCKQXvdxWR992K55Z1S"
    "rKul+CoUzMuBP0vFjoNfS527R7bLz/jKWvgr67XuSIt6NYmQGLsHzQ=="
    "-----END RSA PRIVATE KEY-----";

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
    client.setServer(mqtt_server,
                     8883); // Sets the server details.  配置所连接的服务器
    client.setCallback(
        callback); // Sets the message callback function.  设置消息回调函数
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
    //定期调用此函数，以允许主机处理传入消息并保持与服务器的连接

    unsigned long now =
        millis(); // Obtain the host startup duration.  获取主机开机时长
    if (now - lastMsg > 2000)
    {
        lastMsg = now;
        ++value;
        snprintf(msg, MSG_BUFFER_SIZE, "hello world #%ld",
                 value); // Format to the specified string and store it in MSG.
                         // 格式化成指定字符串并存入msg中
        M5.Lcd.print("Publish message: ");
        M5.Lcd.println(msg);
        client.publish("M5Stack", msg); // Publishes a message to the specified
                                        // topic.  发送一条消息至指定话题
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
        WIFI_STA);              // Set the mode to WiFi station mode.  设置模式为WIFI站模式
    WiFi.begin(ssid, password); // Start Wifi connection.  开始wifi连接

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

    espClient.setCACert(test_root_ca);
    espClient.setCertificate(test_client_cert); // for client verification
    espClient.setPrivateKey(test_client_key);   // for client verification
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
    while (!client.connected())
    {
        M5.Lcd.print("Attempting MQTT connection...");
        // Create a random client ID.  创建一个随机的客户端ID
        char clientId[] = "Grupo3";

        // Attempt to connect.  尝试重新连接
        if (client.connect(clientId))
        {
            M5.Lcd.printf("\nSuccess\n");
            // Once connected, publish an announcement to the topic.
            // 一旦连接，发送一条消息至指定话题
            client.publish("$aws/things/Grupo3/shadow/name/Grupo3_shadow", "hello world");
            // ... and resubscribe.  重新订阅话题
            client.subscribe("$aws/things/Grupo3/shadow/name/Grupo3_shadow");
        }
        else
        {
            M5.Lcd.print("failed, rc=");
            M5.Lcd.print(client.state());
            M5.Lcd.println("try again in 5 seconds");
            delay(5000);
        }
    }
}
