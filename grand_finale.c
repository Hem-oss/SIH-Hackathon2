#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
char Incoming_value = 0;
const int trigPin = 3;
const int echoPin = 5;
long duration;
int distance;
int count;
Servo myServo;
 char val; // Data received from the serial port
#define red1 1
#define green1 2
#define red2 4
#define green2 8
#define SS_PIN 6
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup()
{
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  pinMode(2,OUTPUT);
  Serial.println("Put your card to the reader...");
  Serial.println();
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  //Serial.begin(9600);
  myServo.attach(7); 

}
void loop()
{            
  //Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    //delay(10000);
        for(int i=0;i<=180;i++){
        myServo.write(i);
        delay(30);
        distance = calculateDistance();
        Serial.print(i);
        Serial.print(",");
        Serial.print(distance);
        Serial.print(".");
        }
        
         if (Serial.available()) 
         { // If data is available to read,
           val = Serial.read(); // read it and store it in val
         }
         if (val == '1') 
         { // If 1 was received then lane 2 has more density
            Serial.print("Lane 2");
            Serial.println();
            digitalWrite(green1,LOW);
            digitalWrite(red2,LOW);
            digitalWrite(green2,HIGH);
            digitalWrite(red1,HIGH);
            delay(6000); //max amt given - actually given 45s
            digitalWrite(green1,HIGH);
            digitalWrite(red2,HIGH);
            digitalWrite(green2,LOW);
            digitalWrite(red1,LOW);
            delay(3000);
            
         } else {
            Serial.print("Lane 1");
            Serial.println();
            digitalWrite(green2,LOW);
            digitalWrite(red1,LOW);
            digitalWrite(green1,HIGH);
            digitalWrite(red2,HIGH);
            delay(6000); //max amt given - actually given 45s
            digitalWrite(green2,HIGH);
            digitalWrite(red1,HIGH);
            digitalWrite(green1,LOW);
            digitalWrite(red2,LOW);
            delay(3000);
           }
      
        delay(10000);
        for(int i=180;i>=0;i--){
        myServo.write(i);
        delay(30);
        distance = calculateDistance();
        Serial.print(i);
        Serial.print(",");
        Serial.print(distance);
        Serial.print(".");
        }
        if (Serial.available()) 
         { // If data is available to read,
           val = Serial.read(); // read it and store it in val
         }
         if (val == '0') 
         { // If 1 was received then lane 2 has more density
            Serial.print("Lane 2");
            Serial.println();
            digitalWrite(green1,LOW);
            digitalWrite(red2,LOW);
            digitalWrite(green2,HIGH);
            digitalWrite(red1,HIGH);
            delay(6000); //max amt given - actually given 45s
            digitalWrite(green1,HIGH);
            digitalWrite(red2,HIGH);
            digitalWrite(green2,LOW);
            digitalWrite(red1,LOW);
            delay(3000);
            
         } else {
            Serial.print("Lane 1");
            Serial.println();
            digitalWrite(green2,LOW);
            digitalWrite(red1,LOW);
            digitalWrite(green1,HIGH);
            digitalWrite(red2,HIGH);
            delay(6000); //max amt given - actually given 45s
            digitalWrite(green2,HIGH);
            digitalWrite(red1,HIGH);
            digitalWrite(green1,LOW);
            digitalWrite(red2,LOW);
            delay(3000);
          }
      
        delay(10000);
  }
  
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :  ");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  //delay(5000);
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "5A A7 5B 19")//amb; assuming ambulance is in lane 1
  {//led code
    Serial.print("Emergency Vehicle Approaching.... Green Light ON");
    Serial.println();
    digitalWrite(green2,LOW);
    digitalWrite(red1,LOW);
    digitalWrite(green1,HIGH);
    digitalWrite(red2,HIGH);
    delay(6000); //max amt given
    digitalWrite(green2,HIGH);
    digitalWrite(red1,HIGH);
    digitalWrite(green1,LOW);
    digitalWrite(red2,LOW);
    delay(3000);
  }
  else{
    if (content.substring(1) == "AA 83 20 86")//vip; assuming vip in lane 1
  {//led code
    Serial.print("VIP Vehicle Approaching.....Green Light ON ");
    Serial.println();
    digitalWrite(green2,LOW);
    digitalWrite(red1,LOW);
    digitalWrite(green1,HIGH);
    digitalWrite(red2,HIGH);
    delay(6000); //max amtc -1000  given
    digitalWrite(green2,HIGH);
    digitalWrite(red1,HIGH);
    digitalWrite(green1,LOW);
    digitalWrite(red2,LOW);
    delay(3000);
  }
  }
  }

int calculateDistance(){ 
      
        digitalWrite(trigPin, LOW); 
        delayMicroseconds(2);
      
        digitalWrite(trigPin, HIGH); 
        delayMicroseconds(10);
        digitalWrite(trigPin, LOW);
        duration = pulseIn(echoPin, HIGH); 
        distance= duration*0.034/2;
        return distance;
      }
