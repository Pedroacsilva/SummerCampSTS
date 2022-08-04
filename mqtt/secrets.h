#include <pgmspace.h>

#define SECRET

const char ssid[] = "CSW-Guest";
const char pass[] = "Critical98";

#define THINGNAME "Group3"

int8_t TIME_ZONE = -5; // NYC(USA): -5 UTC
//#define USE_SUMMER_TIME_DST  //uncomment to use DST

const char MQTT_HOST[] = "a1yj9lgdqxsds2-ats.iot.eu-west-2.amazonaws.com";

// Obtain First CA certificate for Amazon AWS
// https://docs.aws.amazon.com/iot/latest/developerguide/managing-device-certs.html#server-authentication
// Copy contents from CA certificate here ▼
static const char cacert[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5
-----END CERTIFICATE-----
)EOF";

// Copy contents from XXXXXXXX-certificate.pem.crt here ▼
static const char client_cert[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
MIIEpAIBAAKCAQEAr8lDFNth4aX/YAsHMtPvBe+YcOT7I6JBu0ze1uzYc9jkp04y
aUszbkwwtW2NKcuZ/ZBRBiVNxI7+zBEhKiuYEDbg2nKj7Qo6U7CSGKvC14peFDhL
gQdo7sGrIdiIi3ZKxJ8DJwYX8CpcPts5zQV6Ap4S+UAG7CNPTTtc6LD0wj99TXjg
wQ5XHM5nISa+7DA/Zmob/e6sLKjU4yJldt3bQzarUFy/If6AZnmyLthgYEQ/kIHj
esYpeD1EfZtG1/sjRz9Mv9BU1gKVoXniqYUlv7rFITML8RiOu6JPtUh33ezeknXC
dOilitLYY5hVSRUI6afclzsWf+et6MjXsND2AwIDAQABAoIBAQCdwZJpImUae73O
tLb2H4rQGfEFyAm2NgSlkdweqBmtBcZWe2/0XN/AKbJA8BsSmj0NeTmtuUaskuQJ
wYmw7cSfMJDkmqOQtHAZ8Ul7yJGom+3IWakxF7RNKRNq4YfRGQ0KneXXXLmY+Hsm
kdmyrCqONMy0UYik3R9rIU5FKaHOvGu4qnIw1V/FfJMLBdM5XOXj5ypvy9NnQJiX
OfTGxkbqWOrsP/AvnIOhvbPwGXCUi0gWTyul2HVIHfAEjLtTNe5acVYj8tdUxjJN
8X56z1mi6pNYdUC5uwA8C0zyMFCMwkIRMNtcmCGIIAblDhrUF/Oo265gM7ujIvm+
k4nJ+DLxAoGBAOX07GGdVQS9sQYZYCHgzusPf/aHtjCRwL8c8dMr0V9IDMVlgQSg
q8da2nUwCRnQ6y87J5Xoi5i0ELlaY3b8YQkPfElddZ+MhQBQNJELq1sxhNjm+zP7
oiUwEsBM3aEH6fGAKEsrg0EZDPLKrPeqyspte2+m7jU8Ga30zP1C5QwLAoGBAMOx
ySWWWRY5H50tQcUj294zhezvMTIWvSs2L1XWFseVZl44FDXyn5kS/48c6kj8BCvz
39v9Pfo3CfqKgc2IpOCH4K2fgSh3040/QHNjKR2xpzdcxWULi21MA68flWi5CWvC
9pJtgNteyNAjdZRkFmw4DsdcWXxhUTS/gdspqwDpAoGAMd3/NNvth+2q6euu0Snz
NT5TPZ8If1fcOJWKS4UBDmyNeHEenWZKWhz1qtwT3SlVFxT47KVVQHQr/EYBs9ff
Ixvck/xUeZj7bqn1/E5PhqMib/cHGqrC6tWV+2Wv2i/hJ6HnGwYAnKlWCYCyKbM7
7tH3JqtIlPrHhtXDbliHWykCgYAahZPPRksYmfFQ6ftJ7owz1yPFcr1mHnLQ0m0j
4vn/Xp4bEtqaXSGIK2z7Rl3yOkWOd2TVecLWkHMHw5HH+0btLz0iCsYEaAkB0Zq4
iK3f2l3hQO93vFLPI0g0icFECh/evPOR8MlP8c6hdszOqanoTMij+D4gf0f0MCg3
PbRxUQKBgQCCJZh4n3BJMwSmTskSK4hdKfF5Uw70jOElHXo6w8NjSfwv7pYnL4g5
jx0+uW6L1l+DYuq5Lxh/rTYxF1H0fNq0jhW2QA/WPQQuWVCKQXvdxWR992K55Z1S
rKul+CoUzMuBP0vFjoNfS527R7bLz/jKWvgr67XuSIt6NYmQGLsHzQ==
-----END CERTIFICATE-----
)KEY";

// Copy contents from  XXXXXXXX-private.pem.key here ▼
static const char privkey[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
MIIDWjCCAkKgAwIBAgIVAIFuWtYDwa/K/5PTjAmjp/Oe0eZZMA0GCSqGSIb3DQEB
CwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t
IEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0yMjA4MDQxMzUx
NTlaFw00OTEyMzEyMzU5NTlaMB4xHDAaBgNVBAMME0FXUyBJb1QgQ2VydGlmaWNh
dGUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQCvyUMU22Hhpf9gCwcy
0+8F75hw5PsjokG7TN7W7Nhz2OSnTjJpSzNuTDC1bY0py5n9kFEGJU3Ejv7MESEq
K5gQNuDacqPtCjpTsJIYq8LXil4UOEuBB2juwash2IiLdkrEnwMnBhfwKlw+2znN
BXoCnhL5QAbsI09NO1zosPTCP31NeODBDlcczmchJr7sMD9mahv97qwsqNTjImV2
3dtDNqtQXL8h/oBmebIu2GBgRD+QgeN6xil4PUR9m0bX+yNHP0y/0FTWApWheeKp
hSW/usUhMwvxGI67ok+1SHfd7N6SdcJ06KWK0thjmFVJFQjpp9yXOxZ/563oyNew
0PYDAgMBAAGjYDBeMB8GA1UdIwQYMBaAFAYs8aerIJhJ5KXOPs+TNM4cKd08MB0G
A1UdDgQWBBSyW5VD2PoQUngABgXlzB1McyeSVzAMBgNVHRMBAf8EAjAAMA4GA1Ud
DwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEAYPRzqEpJGjkoxrD9utRpZIUN
gsf++kQQov9Th8eJRtt71uXzWnrvBQpiLqei851+F3KZXLBpTwl6X8kuvzmbba+J
3gx0Wrjsge3uNkVzs8neez0Y33zReD0oM7VGembqk34Quhlg3mAaMf2KaXZy2t5h
xlTOfl8NQEJwbAxfGi0uYjm+5O7g9ntMjHYeHPbQ5JJZa7Nn845/VFvfxOWFUH+q
PonHdEmR0aR9aooo8QHGFfchG24lCaatzh1zZmC/ZRexmvslbaPYcAUQIYIsOAyg
7gX68i4j9BBfEKaR6CZe2tcdbobwlPsIFznS9bAWiuhaxUm5tOcAMEC/CKVUUg==
-----END RSA PRIVATE KEY-----
)KEY";