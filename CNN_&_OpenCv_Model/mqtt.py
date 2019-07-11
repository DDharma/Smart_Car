import paho.mqtt.client as mqtt #import the client1
class MqttConnector:
	def __init__(self, host, port):
		self.host = host
		self.port = port
		self.client = mqtt.Client("P1")
		self.client.connect(host,port)

	def sendMsg(self,topic,msg):
		self.client.publish(topic,msg)

