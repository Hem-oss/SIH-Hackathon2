#include <Servo.h>
const int trigPin = 3;
const int echoPin = 5;
const int trigPin2= 0;
const int echoPin2= 1;

long duration;
int distance;

long duration2;
int distance2;

int count,v=0;
String count_s ="";
Servo myServo;
Servo myServo2;

void setup() {
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 

  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT); 

  Serial.begin(9600);
  myServo.attach(7); 
  myServo2.attach(8);
}
void loop() {

  for(int i=0;i<=180;i+=20){
  myServo.write(i);
  myServo2.write(i);
  delay(30);
  distance = calculateDistance(trigPin, echoPin);
  distance2 = calculateDistance(trigPin2, echoPin2);
  Serial.print(i);
  Serial.print(",");
  Serial.print(distance);
  Serial.print(".");
  Serial.print(i);
  Serial.print(",");
  Serial.print(distance2);
  Serial.print(".");

  }
  count=Serial.read();
  Serial.println(" ");
  Serial.print("count = ");
  Serial.println(count);
  count=0;

  delay(5000);
  for(int i=180;i>=0;i-=20){
  myServo.write(i);
  myServo2.write(i);
  delay(30);
  distance = calculateDistance(trigPin, echoPin);
  distance2 = calculateDistance(trigPin2, echoPin2);
  Serial.print(i);
  Serial.print(",");
  Serial.print(distance);
  Serial.print(".");
  Serial.print(i);
  Serial.print(",");
  Serial.print(distance2);
  Serial.print(".");
 
  }
  
  while (Serial.available()>0) {
    count_s = Serial.readString();
      if(v!="e"){
      v = count_s.toInt();
    }
    else if (count == 'e') {
      Serial.println(v);
      v = 0;
    }}
  
  Serial.println(" ");
  Serial.print("count = ");
  Serial.println(count);
  count=0;
  delay(5000);
  
}



int calculateDistance(int tp, int ep){ 

  digitalWrite(tp, LOW); 
  delayMicroseconds(2);
  
  digitalWrite(tp, HIGH); 

  delayMicroseconds(10);
  digitalWrite(tp, LOW);

  duration = pulseIn(ep, HIGH);
 
  distance= duration*0.034/2;
  return distance;
}
