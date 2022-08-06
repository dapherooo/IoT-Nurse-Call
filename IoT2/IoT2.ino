#include <EEPROM.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <ESP8266WiFi.h>


// Connect to the WiFi
const char* ssid = "IoT";
const char* password = "skripsi2021";
// Connect to the MQTT Broker
const char* mqtt_server = "11.11.1.2";
const char* mqtt_username ="";
const char* mqtt_password = "";
const char* clientID = "ESP8266Client";


// this constant won't change:
const int buttonPin1 = 16;    // the pin that the pushbutton is attached to
const int buttonPin2 = 5;    // the pin that the pushbutton is attached to
const int LED_merah  = 4;                
const int LED_hijau  = 0;  


// Variables will change:
int buttonPushCounter1 = 0;   // counter for the number of button presses
int buttonState1 = 0;         // current state of the button
int lastButtonState1 = 0;     // previous state of the button

int buttonPushCounter2 = 0;   // counter for the number of button presses
int buttonState2 = 0;         // current state of the button
int lastButtonState2 = 0;     // previous state of the button



WiFiClient espClient;
PubSubClient client(espClient);


void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.println("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(clientID, mqtt_username, mqtt_password)) {
      Serial.println("Connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}



void setup()
{
  {

    client.setServer(mqtt_server, 1883);
    //client.setCallback(callback);

    // initialize the button pin as a input:
    pinMode(buttonPin1, INPUT_PULLUP);
    pinMode(buttonPin2, INPUT_PULLUP);
    pinMode(LED_merah, OUTPUT);
    pinMode(LED_hijau, OUTPUT); 
    digitalWrite(LED_merah, LOW); 
    digitalWrite(LED_hijau, LOW);


    // initialize serial communication:
    Serial.begin(9600);
  }

// Connect to WiFinetwork
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    //Serial.begin(9600);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  //Serial.begin(9600);
  // Start the server
  // server.begin();
  // Serial.println("Server started");
  //Serial.begin(9600);
  // Print the IP address
  Serial.print("Local IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {

  // read the pushbutton input pin1:
  buttonState1 = digitalRead(buttonPin1);

  // compare the buttonState to its previous state
  if (buttonState1 != lastButtonState1) {
    // if the state has changed, increment the counter
    if (buttonState1 == HIGH) {
      client.publish("ESP8266/Input1", "CALL THE NURSE"); //
      // if the current state is HIGH then the button
      // went from off to on:
    } else {
      // if the current state is LOW then the button
      // went from on to off:
      client.publish("ESP8266/Input1", "ON"); //
    }
    // Delay a little bit to avoid bouncing
    delay(100);
  }
  // save the current state as the last state,
  //for next time through the loop
  lastButtonState1 = buttonState1;



  // read the pushbutton input pin2:
  buttonState2 = digitalRead(buttonPin2);

  // compare the buttonState to its previous state
  if (buttonState2 != lastButtonState2) {
    // if the state has changed, increment the counter
    if (buttonState2 == HIGH) {
      client.publish("ESP8266/Input2", "URGENT FAST RESPON"); //
      // if the current state is HIGH then the button
      // went from off to on:
    } else {
      // if the current state is LOW then the button
      // went from on to off:
      client.publish("ESP8266/Input2", "ON"); //
    }
    // Delay a little bit to avoid bouncing
    delay(100);
  }
  // save the current state as the last state,
  //for next time through the loop
  lastButtonState2 = buttonState2;
 
  {
      if (!client.connected()) {
      reconnect();
    }
    client.loop();
  }
}
