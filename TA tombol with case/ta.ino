const int motor1 = 4;
const int motor2 = 5;
const int motor3 = 7;
const int motor4 = 8; 
const int tombol = 10;
const int tombol2 = 11;

int  buttonState1;
int  buttonState2;
int i = 0;


void setup() {
 
  pinMode(tombol, INPUT);  
  pinMode(tombol2, INPUT);
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
  pinMode(motor3, OUTPUT);
  pinMode(motor4, OUTPUT);
  Serial.begin(9600);
  
}

void loop() {
  
  buttonState1 = digitalRead(tombol);
  if( buttonState1 == 1)
  {
    i++;
    delay(300);
  }
  buttonState2 = digitalRead(tombol2);
  if( buttonState2 == 1)
  {
    i--;
    delay(300);
  }
    switch (i)
    {
      case 0:
      digitalWrite(motor1, LOW);
      digitalWrite(motor2, LOW);
      digitalWrite(motor3, LOW);
      digitalWrite(motor4, LOW);
      break;
      
      case 1:
      digitalWrite(motor1,HIGH);
      digitalWrite(motor2,LOW);
      digitalWrite(motor3,HIGH);
      digitalWrite(motor4,LOW);
      delay(3000);

      digitalWrite(motor1,LOW);
      digitalWrite(motor2,LOW);
      digitalWrite(motor3,LOW);
      digitalWrite(motor4,LOW);
      delay(1000);

      digitalWrite(motor1,LOW);
      digitalWrite(motor2,HIGH);
      digitalWrite(motor3,LOW);
      digitalWrite(motor4,HIGH);
      delay(2000);

      digitalWrite(motor1,LOW);
      digitalWrite(motor2,LOW);
      digitalWrite(motor3,LOW);
      digitalWrite(motor4,LOW);
      delay(1000);
      break;
      
      case 2:
      digitalWrite(motor1,HIGH);
      digitalWrite(motor2,LOW);
      digitalWrite(motor3,HIGH);
      digitalWrite(motor4,LOW);
      delay(2000);

      digitalWrite(motor1,LOW);
      digitalWrite(motor2,HIGH);
      digitalWrite(motor3,LOW);
      digitalWrite(motor4,HIGH);
      delay(2000);
      break;

      default :
       if(i==-1 && i==3)
     {
       i=0;
     }
      break;
  
     }
     Serial.println(i);
   
     
  }
