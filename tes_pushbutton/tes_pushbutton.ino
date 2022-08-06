const int LED_merah    = 4;                
const int LED_hijau    = 0;   
const int pbhijauGPI16 = 16;
const int pbmerahGPIO5 = 5;
int b   =0;
int a   =0;



void setup() {
  pinMode(pbhijauGPI16, INPUT);
  pinMode(pbmerahGPIO5, INPUT);
  pinMode(LED_merah, OUTPUT);
  pinMode(LED_hijau, OUTPUT); 
  digitalWrite(LED_merah, LOW); 
  digitalWrite(LED_hijau, LOW);
  
  Serial.begin(115200);
}


void loop() {
 int a = digitalRead(pbhijauGPI16); 
 int b = digitalRead(pbmerahGPIO5); 

 if (a==1)
   { 
   Serial.println("SEND CALL"); 
   delay(200); 
   }
 else if(b==1) 
  { 
   Serial.println("SEND I NEED HELP"); 
   delay(200); 
   }  
 }
