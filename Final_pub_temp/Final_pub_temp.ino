#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <WiFiClient.h>
#include "DHT.h"
#include <ThingSpeak.h>

const char *ssid = "ABCD";
const char *password = "123456789";

const char *mqtt_server = "192.168.43.91";
const char * mqtt_topic = "sensor/temp";

DHT dht(D4, DHT11);
#define BUZZER_PIN     D5
#define LED            D2

WiFiClient wific;
PubSubClient client(wific);

long channel_no = 2388610;
const char *APIkey = "4A9WPGDKQZISBK1L";

// void setup_wifi()
// {
//   delay(10);
//   Serial.println();
//   Serial.print("Connecting to ");
//   Serial.println(ssid);
//   WiFi.mode(WIFI_STA);
//   WiFi.begin(ssid, password);

//   while(WiFi.status() != WL_CONNECTED)
//   {
//     delay(500);
//     Serial.print(".");
//   }
//   Serial.println();
//   Serial.println("WiFi is connected successfully.....!");
//   Serial.println(WiFi.localIP());
// }

void reconnect()
{
  while(!client.connected())
  {
    Serial.println("Attempting MQTT connection..."); 
    if(client.connect("ESP8266Client"))
    {
      Serial.println("Successfully connected MQTT broker......");
    }

    else 
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}


void setup() {
  // put your setup code here, to run once:
  dht.begin();
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED, OUTPUT);
  Serial.begin(115200);
  Serial.flush();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi");
    
    while(WiFi.status() != WL_CONNECTED) 
    {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("WiFi connected successfully-------------");
  //setup_wifi();
  ThingSpeak.begin(wific);
  client.setServer(mqtt_server, 1883);
  //client.setCallback(callback);
  Serial.println("MQTT connected successfully--------------");
}

void loop() {
  // put your main code here, to run repeatedly:
  if(!client.connected())
  {
    reconnect();
  }
  client.loop();
  // float humi = dht.readHumidity();
  // float temp = dht.readTemperature();
  float humi = rand() % 50;
  float temp = rand()% 50;
  if(isnan(humi) || isnan(temp))
  {
        Serial.println("Failed to read data from DHT sensor");
  }
  Serial.println("Temperature in celcius:  ");
  Serial.print(temp);
  Serial.println();
  Serial.println("Humidity: ");
  Serial.print(humi);
  if(humi > 60.00 || temp > 32.00)
  {
    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(LED, HIGH);
    delay(2000);
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(LED, LOW);
  }
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(LED, LOW);

  ThingSpeak.writeField(channel_no, 1, humi, APIkey);
  ThingSpeak.writeField(channel_no, 2, temp, APIkey);
  String payload = "{\"Humidity\":" + String(humi) + ",\"Temperature\":" + String(temp) + "}";
  client.publish(mqtt_topic, payload.c_str());
  delay(5000);
}
