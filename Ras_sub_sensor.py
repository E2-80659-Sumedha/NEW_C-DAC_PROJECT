# import mqtt module
import paho.mqtt.client as mqtt

# create instance of Client class (creating mqtt client)
mqttc = mqtt.Client("Subscriber")

# define all required callbacks
def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Subscriber is connected successfully")
        # subscribe for topic
        topic = "sensor/+"
        mqttc.subscribe(topic)
    else:
        print(f"Publisher is not connected Error code : {rc}")

def on_message(client, userdata, message):
    print("Recieved msg : " + str(message.payload) + "on topic" + str(message.topic))
    temp = float(message.payload)
    print(f"Temperature = {temp}")
    # print(f"Recieved msg : \"{message.payload}\"on topic \"{message.topic}\"")

# register our callback functions with our client instance
mqttc.on_connect = on_connect
mqttc.on_message = on_message

# connect with broker
host = "localhost"
mqttc.connect(host)

# run forever loop to keep subscriber alive
mqttc.loop_forever()