# import mqtt module
import paho.mqtt.client as mqtt
import utils.database as db

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
    print("Recieved msg : " + str(message.payload) + "on topic: " + str(message.topic))
    # print(f"Recieved msg : \"{message.payload}\"on topic \"{message.topic}\"")

    if message.topic == "sensor/temp":
        temp = float(message.payload)
        print(f"Temperature = {temp}")
        query = f"insert into Temperature(value) values({temp});"
    
    elif message.topic == "sensor/humi":
        humi = float(message.payload)
        print(f"Humidity = {humi}")
        query = f"insert into Humidity(value) values({humi});"

    else:   
        gas = float(message.payload)
        print(f"Gas = {gas}")
        query = f"insert into Gas(value) values({gas});"

    db.execute_query(query)

# register our callback functions with our client instance
mqttc.on_connect = on_connect
mqttc.on_message = on_message

# connect with broker
host = "localhost"
mqttc.connect(host)

# run forever loop to keep subscriber alive
mqttc.loop_forever()