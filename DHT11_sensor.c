#include <DHT.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <PubSubClient.h>

const char *ssid = "Realme";
const char *password = "9608862022";

const char *mqtt_broker = "192.168.43.35";
unsigned int port = 1883;
const char *mqtt_topic = "topic/temp_humi";

WiFiClient wific;
PubSubClient mqttClient(wific);

// DHT sensor
#define DHTPIN       2
#define DHTTYPE      DHT11
DHT dht(DHTPIN, DHTTYPE);

// BUZZER & LED
#define BUZZER       D5
#define LED          D2

void setup() {
    Serial.begin(115200);
    Serial.flush();

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.println("Connecting to WiFi");
    
    while(WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }

    Serial.println("WiFi connected successfully....");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    mqttClient.setServer(mqtt_broker, port);
}

void loop() {
    if (!mqttClient.connected()) {
        reconnect();
    }

    float humidity = dht.readHumidity();  // Fixed: Corrected the method name
    float temperature = dht.readTemperature();

    if (isnan(humidity) || isnan(temperature)) {
        Serial.println("Failed to read from DHT sensor!");
        delay(2000);
        return;
    }

    // Print sensor data
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.print(" %\tTemperature: ");
    Serial.print(temperature);
    Serial.println(" C");

    String payload = "{\"humidity\":" + String(humidity) + ",\"temperature\":" + String(temperature) + "}";
    mqttClient.publish(mqtt_topic, payload.c_str());

    delay(5000);
}

void reconnect() {
    while (!mqttClient.connected()) {
        Serial.println("Attempting MQTT connection...");

        if (mqttClient.connect("ESP8266Client")) {
            Serial.println("Successfully connected to MQTT broker");
        } else {
            Serial.print("Failed, rc= ");
            Serial.print(mqttClient.state());
            Serial.println(" Retrying in 5 seconds...");

            delay(5000);
        }
    }
}
