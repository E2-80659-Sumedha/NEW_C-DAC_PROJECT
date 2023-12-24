#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <PubSubClient.h>

const char *ssid = "Realme";
const char *password = "9608862022";

const char *mqtt_broker = "0.0.0.0";
unsigned int port = 1883;
const char *mqtt_topic = "topic/gas";

WiFiClient wific;
PubSubClient mqttClient(wific);

// MQ2 gas sensor
#define GAS_SENSOR_PIN A0  // Use A0 for analog input

// BUZZER & LED
#define BUZZER       D5
#define LED          D2

// Threshold value to determine gas presence (adjust according to your needs)
const int GAS_THRESHOLD = 500;

void setup() {
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

    Serial.println("WiFi connected successfully....");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    mqttClient.setServer(mqtt_broker, port);
}

void loop() {
    if (!mqttClient.connected())
    {
        reconnect();
    }

    int gas_value = analogRead(GAS_SENSOR_PIN);

    // Print sensor data
    Serial.print("Gas value (analog): ");
    Serial.println(gas_value);

    // Convert analog value to digital (1 if above threshold, 0 otherwise)
    int digital_gas_value = (gas_value > GAS_THRESHOLD) ? 1 : 0;
    
    Serial.print("Digital Gas value: ");
    Serial.println(digital_gas_value);

    String payload = "{\"DigitalGasValue\":" + String(digital_gas_value) + "}";
    mqttClient.publish(mqtt_topic, payload.c_str());

    delay(5000);
}

void reconnect() {
    while (!mqttClient.connected()) {
        Serial.println("Attempting MQTT connection...");

        if (mqttClient.connect("ESP8266Client")) {
            Serial.println("Successfully connected to MQTT broker");
        }
        
        else {
            Serial.print("Failed, rc= ");
            Serial.print(mqttClient.state());
            Serial.println(" Retrying in 5 seconds...");

            delay(5000);
        }
    }
}
