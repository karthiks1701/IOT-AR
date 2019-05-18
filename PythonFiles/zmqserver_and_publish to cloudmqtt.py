
import time
import zmq
import paho.mqtt.client as mqtt

context = zmq.Context()
socket = context.socket(zmq.REP)
socket.bind("tcp://*:5555")





def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))
    


def on_message(client, userdata, msg):
    print(msg.topic+" "+str(msg.payload))

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

client.username_pw_set("tgepnmwm", "ga7uomnLGGrq")
client.connect('m16.cloudmqtt.com', 15826)







while True:
    #  Wait for next request from client
    message = socket.recv()
    print("Received request: %s" % message)
    client.publish("topic",message)

    #  Do some 'work'.
    #  Try reducing sleep time to 0.01 to see how blazingly fast it communicates
    #  In the real world usage, you just need to replace time.sleep() with
    #  whatever work you want python to do, maybe a machine learning task?
    time.sleep(1)

    #  Send reply back to client
    #  In the real world usage, after you finish your work, send your output here
    socket.send(b"World")





