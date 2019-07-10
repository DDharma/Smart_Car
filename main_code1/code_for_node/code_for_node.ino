 #include <ESP8266WiFi.h>
#include <PubSubClient.h>
#define LED D0
const char* ssid = "Shivangi";
const char* password = "AN720000";
const char* mqtt_server = "192.168.137.1";
int DL1 = D1;
int DL2 = D2;
int DR1 = D3;
int DR2 = D4;

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {

  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    //Serial.print(i);
    Serial.print((char)payload[i]);
  }
  Serial.println();
  controller((char)payload[0]);
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "OpenCV-Automated_Bot";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      client.subscribe("control");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(DL1, OUTPUT);
  pinMode(DL2, OUTPUT);
  pinMode(DR1, OUTPUT);
  pinMode(DR2, OUTPUT);
  digitalWrite (DL1, HIGH);
  digitalWrite (DL2, LOW);
  digitalWrite (DR1, HIGH);
  digitalWrite (DR2, LOW);
  analogWrite(D6,650);
  analogWrite(D7,650);
  
  Serial.println("Hi!, I am Arduino,\ncurrently setting up plz wait!!");
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}


void controller(char command) {
  Serial.println("Command");
  Serial.println(command);
  if (command == 'F') {
    Serial.println("Forward");
    digitalWrite (DL1, HIGH);
    digitalWrite (DL2, LOW);
    digitalWrite (DR1, HIGH);
    digitalWrite (DR2, LOW);
  }
  else if (command == 'R') {
    Serial.println("Right");
    digitalWrite (DL1, HIGH);
    digitalWrite (DL2, LOW);
    delay(1000);
    digitalWrite (DR1, LOW);
    digitalWrite (DR2, HIGH);
    delay(1000);

  }
  else if (command == 'L') {
    Serial.println("Left");
    digitalWrite (DL1, LOW);
    digitalWrite (DL2, HIGH);
    delay(1000);
    digitalWrite (DR1, HIGH);
    digitalWrite (DR2, LOW);
    delay(1000);
  }
  
  else if (command == 'S') {
    Serial.println("Stop");
    digitalWrite (DL1, LOW);
    digitalWrite (DL2, LOW);
    digitalWrite (DR1, LOW);
    digitalWrite (DR2, LOW);

  }
  else if (command == 'N') {
    Serial.println("NaN");
    digitalWrite (DL1, HIGH);
    digitalWrite (DL2, LOW);
    digitalWrite (DR1, HIGH);
    digitalWrite (DR2, LOW);

  }
}
