### MQTT based coal mining monitoring using RaspberryPi

__Description :)__

  Now I decided to make my project with the help of NodeMCU and RaspberryPi in which I used two NodeMCU(ESP8266) in which I connected Temperature and Humidity sensor(DHT11 sensor) on one NodeMCU and on other NodeMCU I connected gas sensor(MQ2 sensor). And both NodeMCU going to publish both of the sensor data on MQTT broker here my MQTT broker is RaspberryPi.
  From both NodeMCU I send all sensor data on ThingSpeak for storage data. And NodeMCU also connected with LED and BUZZER if sensor data out from threshold value then buzzer and LED gonna to on. 

__Installation :)__

For NodeMCU all installation and all required settings:-

  1.To upload program on NodeMCU microcontroller we have to install Arduino IDE from which we can easly upload our code on NodeMCU.
    Arduino IDE also provide there are many importances in built libarary we can install any libarary as our requirnment on Arduino 
    IDE itself.
