#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9         
#define SS_PIN          6         

MFRC522 mfrc522(SS_PIN, RST_PIN);  

void setup() {
	Serial.begin(9600);		// Initialize serial communications with the PC
	while (!Serial);		// Do nothing if no serial port is opened
	SPI.begin();			// Init SPI bus
	mfrc522.PCD_Init();		// Init MFRC522
	delay(4);				// Optional delay
	mfrc522.PCD_DumpVersionToSerial();	// Show details of PCD - MFRC522 Card Reader details
	Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
}

void loop() {
	// Reset the loop if no new card present on the sensor/reader.
	if ( ! mfrc522.PICC_IsNewCardPresent()) {
		return;
	}
  
	if ( ! mfrc522.PICC_ReadCardSerial()) {
		return;
	}
	mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
}
