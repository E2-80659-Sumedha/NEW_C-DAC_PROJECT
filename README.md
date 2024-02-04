## MQTT based coal mining monitoring using RaspberryPi

### Description

 Now I decided to do my project using NodeMCU and RaspberryPi, where I used two NodeMCUs (ESP8266), in which I connected the temperature and humidity sensor (DHT11 sensor) to one NodeMCU and to the other NodeMCU I connected the gas sensor (sensor MQ2). And here both NodeMCU publish both sensor data with MQTT broker, my MQTT broker is RaspberryPi.
 From both NodeMCUs I send all sensor data into ThingSpeak for data storage. And NodeMCU is also connected with LED and BUZZER, when the sensor data exceeds the threshold value, the buzzer and LED will light up.

### Installation for NodeMCU

For NodeMCU all installation and all required settings:-

  __NodeMCU :)__

  The NodeMCU(Node MicroController Unit) is an open-source software and hardware development enviornment built around an inexpensive System-on-Chip(SoC) called the ESP8266.

  __Arduino IDE :)__

  - The open-source Arduino Software(IDE) makes it easy to write and upload it to the board. This software can be used with any Arduino board. 

  - To upload program on NodeMCU microcontroller we have to Download IDE from this link __[Arduino IDE](https://www.arduino.cc/en/software)__ on your system from which we can easily upload  our code on NodeMCU.

  - Add NdeMCU Library to the IDE 
    + The IDE needs to know details about the NodeMCU module.

    + This information is available in a configuration file which will be added to the IDE.

    + Select the **File->Preferences**

    + This will open up a new window, where we set the IDE to point to the configuration file.

    + In the field "**Additional Boards Manager URLs:**" enter **http://arduino.esp8266.com/stable/package_esp8266com_index.json**

    + Select the **OK** button at the bottom of the window when the link address is entered.

  - Selecting the NodeMCU Board driver
    + Navigate to the Boards Manager from the
      
    + Tools Board -> Boards Manager menu option
      
    + A new options windows will appear
      
    + From the Boards Manager window, enter esp8266 in the
        search bar
      
    + This will display the new ESP8266 driver as supplied by the ESP8266 Community. At the bottom of the options box, select
    the version to be setup (select the most recent version)

    + Now select Install to complete the installation of the driver
      which will take a few seconds to download and install

    + Select Close to complete the installation

  - Selecting Board Version
    + Now from the Tools -> Board menu, the dropdown list will contain many different hardware board

    + Scroll down and select the NodeMCU 1.0 (ESP-12E Module)

  - Defining The Communication Port
    + The communications port must be defined to allow the Arduino IDE to communicate with the NodeMCU. Connect your PC by a USB cable to the NodeMCU.

    + After connection, the PC will provide power to the NodeMCU. The communication port used will vary by system.

    + To determine which communications port has been selected on your system, select the Tools -> Port menu option.

    + The options list will present the available COM ports. For our example, our NodeMCU added COM6 and will be selected by clicking on COM6.

    + The Board selection, are several NodeMCU
    settings. These include CPU Frequency, Flash Size, andalso Upload Speed. If Upload Speed is not set to 115200,select the speed of 115200 from the options from that item.       The speed of 115200 is the optimum transfer rate which is used to transfer data to and from the NodeMCU.

  - Library to install for this project
    + **Adafruit ESp8266**: a collcetion of example codes for ESP8266 chipset.

    + **DHT**: Sample code for DHT11 and DHT22 sensor.(In this project I used DHT11).

    + **PubSubClient**: MQTT messaging library for ESP8266.

    + **ThingSpeak**: To interface Wifi devices with ThingSpeak server to send and read data.

### Installation for Rapsberry Pi

+ Installing OS on Raspberry Pi
   - With the help of card reader or PenDrive plug my SDcard on my computer system and going to [Raspberry Pi.org/documentation](https://www.raspberrypi.com/documentation/)from here I downloaded OS Imager and did all setup of my Raspberry pi whichever I required to making our project.

+ Installing Python3 on Raspberry Pi
   - Open Raspberry Pi dekstop on computer and open Raspberry Pi terminal enter command :
     >> sudo apt-get install idle

+ Installing MQTT broker on Raspberry Pi
  - Open Raspberry Pi terminal and enter command
     * Run the following command to upgrade and update your system:
       >> sudo apt update && sudo apt upgrade
       
     * To install the Mosquitto Broker:
       >> apt-get install -y mosquitto mosquitto-clients

     * To make Mosquitto auto start when the Raspberry Pi boots:  
       >> sudo systemctl enable mosquitto.service

     * Now, test the installation by running the following command:
       >> mosquitto -v

+ Installing all neccessary Libraries
     * To install MQTT library in python
       >> sudo pip3 install paho.mqtt

     * To install requests library in python3
       >> sudo pip3 install requests

           

