#include <PubSubClient.h>
#include <ESP8266WiFi.h>

const char* ssid = "IoT";
const char* password = "skripsi2021";
const char* mqtt_server = "11.11.1.2";

WiFiClient espClient;
PubSubClient client(espClient);

const int LED_merah    = 4;                
const int LED_hijau    = 0;   
const int pbhijauGPI16 = 16;
const int pbmerahGPIO5 = 5;
int b   =0;
int a   =0;

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  randomSeed(micros());
  Serial.println("");
  Serial.print("WiFi connected - ESP IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");  
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  pinMode(pbhijauGPI16, INPUT);
  pinMode(pbmerahGPIO5, INPUT);
  pinMode(LED_merah, OUTPUT);
  pinMode(LED_hijau, OUTPUT); 
  digitalWrite(LED_merah, LOW); 
  digitalWrite(LED_hijau, LOW);
  
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  
}


void loop() {
  if (!client.connected()) {
    reconnect();
  }
  if(!client.loop())
    client.connect("ESP8266Client");
 int a = digitalRead(pbhijauGPI16); 
 int b = digitalRead(pbmerahGPIO5); 
 static char CALL[7];
 static char URGENT[7];
 if (a==1)
   { 
   Serial.println("SEND CALL"); 
   client.publish("/esp8266/pushbuttonhijau",CALL);
   delay(200); 
   }
 else if(b==1) 
  { 
   Serial.println("SEND I NEED HELP"); 
   client.publish("/esp8266/pushbuttonmerah",URGENT);
   delay(200); 
   }  
 }
