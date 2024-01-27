
#define IN_1   D1   // Right Connector motor
#define IN_2   D2
#define IN_3   D3   // Left Connector motor
#define IN_4   D4


#define S1     D6
#define S2     D7

int speedCar = 400; //0-1024

void setup()
{
  // Debug console
  Serial.begin(9600);

  pinMode(IN_1,OUTPUT);
  pinMode(IN_2,OUTPUT);
  pinMode(IN_3,OUTPUT);
  pinMode(IN_4,OUTPUT);

  pinMode(S1,INPUT);
  pinMode(S2,INPUT);
  
  digitalWrite(IN_1,LOW);
  digitalWrite(IN_2,LOW);
  digitalWrite(IN_3,LOW);
  digitalWrite(IN_4,LOW);
}

void goAhead(){ 

      digitalWrite(IN_1, LOW);
      analogWrite(IN_2, speedCar);

      digitalWrite(IN_3, LOW);
      analogWrite(IN_4, speedCar);

  }

void goRight(){ 

      analogWrite(IN_1, speedCar);
      digitalWrite(IN_2, LOW);

      digitalWrite(IN_3, LOW);
      analogWrite(IN_4, speedCar);
  }

void goLeft(){

      digitalWrite(IN_1, LOW);
      analogWrite(IN_2, speedCar);

      analogWrite(IN_3, speedCar);
      digitalWrite(IN_4, LOW);
  }

void stopRobot(){  

      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, LOW);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, LOW);
 }

void loop()
{
  // if(digitalRead(switch)==HIGH)
  // {
    Serial.print("Line Follower Mode");
    if(digitalRead(S1)==LOW  && digitalRead(S2)==LOW)
    {
      goAhead();
    }
    if(digitalRead(S1)==HIGH  && digitalRead(S2)==LOW)
    {
      goRight();
    }
    if(digitalRead(S1)==LOW  && digitalRead(S2)==HIGH)
    {
      goLeft();
    }
    if(digitalRead(S1)==HIGH  && digitalRead(S2)==HIGH)
    {
      stopRobot();
    }
  // }

}