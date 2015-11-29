from pymongo import MongoClient
import paho.mqtt.client as mqtt
import json

mongo = MongoClient('192.168.128.35', 27017)


def on_connect(client, userdata, flags, respons_code):
    print('status {0}'.format(respons_code))
    client.subscribe('sensor')


def on_message(client, userdata, msg):
    print(msg.topic + ' ' + str(msg.payload))

    data = json.loads(msg.payload.decode('utf-8'))
    print(data)

    mongo.mori.Sensed.insert(data)

if __name__ == '__main__':
    client = mqtt.Client(protocol=mqtt.MQTTv311)

    client.on_connect = on_connect
    client.on_message = on_message

    client.username_pw_set(username='aggregator', password='aggregator')
    client.connect('m11.cloudmqtt.com', port=19539, keepalive=60)

    client.loop_forever()
