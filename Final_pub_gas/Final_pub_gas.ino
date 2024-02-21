#include <ESP8266WiFi.h>
#include <ThingSpeak.h>
#include <PubSubClient.h>
#include <WiFiClient.h>

long myChannelNumber = 2388619;
const char myWriteAPIKey[] = "1E75E0LVO3WFG5EN";

const char *mqtt_server = "192.168.43.35";
const char * mqtt_topic = "sensor/gas";

#define GAS_SENSOR_PIN      D4 
#define BUZZER_PIN          D5
#define LED                 D2

WiFiClient wific;
PubSubClient client(wific);

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
  Serial.begin(115200);
  Serial.flush();

  WiFi.begin("ABCD", "123456789");
  Serial.println("Connection to WiFi");
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(200);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi is connected successfully......!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  //GAS Sensor setup--------------------
  pinMode(GAS_SENSOR_PIN, INPUT);
  //BUZZER setup------------------------
  pinMode(BUZZER_PIN, OUTPUT);
  //LED setup---------------------------
  pinMode(LED, OUTPUT);
  //ThingSpeak setup--------------------
  ThingSpeak.begin(wific);
  client.setServer(mqtt_server, 1883);
  //Serial.println("MQTT connected successfully--------------");
}

void loop() {
  // put your main code here, to run repeatedly:
  if(!client.connected())
  {
    reconnect();
  }
  client.loop();

  int sensorValue = digitalRead(GAS_SENSOR_PIN);

  if (sensorValue == HIGH) {
    Serial.println("Gas detected!");
    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(LED, HIGH);
    delay(1000);
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(LED, LOW);
    delay(1000);
  }  
  else 
  {
    Serial.println("No gas detected");
  }

  ThingSpeak.writeField(myChannelNumber, 1, sensorValue, myWriteAPIKey);  //arg2: field no -1
  String payload = "{\"Gas value\":" + String(sensorValue)+ "}";
  client.publish(mqtt_topic, payload.c_str());
  delay(500);
}