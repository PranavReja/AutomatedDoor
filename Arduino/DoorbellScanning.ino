/*
PINOUT:
RC522 MODULE   Uno/Nano   MEGA
SDA             D10       D9
SCK             D13       D52
MOSI            D11       D51
MISO            D12       D50
IRQ             N/A       N/A
GND             GND       GND
RST             D9        D8x
3.3V            3.3V      3.3V
*/

/* Include the standard Arduino SPI library */
#include <SPI.h>
/* Include the RFID library */
#include <RFID.h>

#include <Stepper.h>

/* Define the DIO used for the SDA (SS) and RST (reset) pins. */
#define SDA_DIO 10
#define RESET_DIO 9
#define dirPin 6
#define stepPin 7

#define stepsPerRevolution 200
/* Create an instance of the RFID library */
RFID RC522(SDA_DIO, RESET_DIO);

int buzzerPin = 8;

// Registry of allowed card numbers (replace with your actual card numbers)
const byte allowedCards[][4] = {
  {0x12, 0xDE, 0xD6, 0x34,},
  {0x47, 0xE5, 0xA5, 0x7B,},
  {0x24, 0x7C, 0xE7, 0x50,},
  {0xA1, 0x1C, 0x15, 0xFC,},
  {0x99, 0x38, 0x1F, 0xE9,}
  

  // ... more card numbers ...
};

int numAllowedCards = sizeof(allowedCards) / sizeof(allowedCards[0]);

const int doorbellpin = 2;  // Define the button pin

const int ledPin = 3; // Define LED pin
int photoPin = A0;


bool compareArrays(const byte array1[], const byte array2[], int len) {
  for (int i = 0; i < len; i++) {
    if (array1[i] != array2[i]) {
      return false;
    }
  }
  return true;
}

String incomingByte = "hello"; // for incoming serial data

void setup() {
  Serial.begin(9600);
  /* Enable the SPI interface */
  SPI.begin();
  /* Initialise the RFID reader */
  RC522.init();

  pinMode(buzzerPin, OUTPUT);
  pinMode(doorbellpin, INPUT_PULLUP);  // Set button pin as input with pullup
  pinMode(ledPin, OUTPUT); // Set pin 3 as output
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
}


void loop() {
  int i;
  int light = analogRead(photoPin);
  delay(100);

  if (Serial.available() > 0) {
    incomingByte = Serial.readString();
    incomingByte.trim();
    Serial.println(incomingByte);
    if (incomingByte == "open"){
      tone(buzzerPin, 1000, 500);  // Play a setup mode tone
      digitalWrite(ledPin, HIGH);   // Turn the LED on
      delay(1000);                  // Wait for 1 second
      digitalWrite(ledPin, LOW);    // Turn the LED off
      delay(100); 

      digitalWrite(dirPin, LOW);
      for (int i = 0; i < 5 * stepsPerRevolution; i++) {
    // These four lines result in 1 step:
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(1000);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(1000);
      }
      delay(1000);
      digitalWrite(dirPin, HIGH);
      for (int i = 0; i < 5 * stepsPerRevolution; i++) {
    // These four lines result in 1 step:
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(1000);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(1000);
      }
      delay(1000);
    Serial.flush();  
    delay(1000);
    }   
    } 
    
    else if (light < 3){
        Serial.println("DoorBell!");
        tone(buzzerPin, 1000, 500);  // Play a setup mode tone
        digitalWrite(ledPin, HIGH);   // Turn the LED on
        delay(1000);                  // Wait for 1 second
        digitalWrite(ledPin, LOW);    // Turn the LED off
        delay(1000);   
          
    }
    else{
    
      // Normal card scanning logic
      if (RC522.isCard()) {
        RC522.readCardSerial();

        bool cardFound = false;
        int cardIndex = 0;
        for (int i = 0; i < numAllowedCards; i++) {
          if (compareArrays(allowedCards[i], RC522.serNum, 4)) {
            cardFound = true;
            cardIndex = i + 1;
          // Perform actions for a valid card
            Serial.println(cardIndex);
            tone(buzzerPin, 1500, 500); // Play a success tone
            digitalWrite(ledPin, HIGH);   // Turn the LED on
            delay(1000);                  // Wait for 1 second
            digitalWrite(ledPin, LOW);    // Turn the LED off
            delay(100); 

            digitalWrite(dirPin, LOW);
            for (int i = 0; i < 5 * stepsPerRevolution; i++) {
          // These four lines result in 1 step:
              digitalWrite(stepPin, HIGH);
              delayMicroseconds(1000);
              digitalWrite(stepPin, LOW);
              delayMicroseconds(1000);
              
            }
            delay(1000);
            digitalWrite(dirPin, HIGH);
            for (int i = 0; i < 5 * stepsPerRevolution; i++) {
          // These four lines result in 1 step:
              digitalWrite(stepPin, HIGH);
              delayMicroseconds(1000);
              digitalWrite(stepPin, LOW);
              delayMicroseconds(1000);
            }
            break;
        }
      }

      if (!cardFound) {
        Serial.println("Access denied!");
        tone(buzzerPin, 500, 500); // Play an error tone
        delay(2000);
      }
        }
    }
  }
