#include <SPI.h>
#include <MFRC522.h>
char Incoming_value = 0;
 
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

}
void loop()
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "5A A7 5B 19")
  {
    Serial.print("Green Light ON");
    Serial.println();
    digitalWrite(2,HIGH);
    delay(3000);
    digitalWrite(2,LOW);
 
  }
 
 else   {
    Serial.println("Unauthorized");
 
  }
}
