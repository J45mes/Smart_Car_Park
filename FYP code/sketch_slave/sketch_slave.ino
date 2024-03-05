
 
// Include Arduino Wire library for I2C
#include <Wire.h>
#include <RFID.h> 
#include <SPI.h> 
// Define Slave I2C Address
#define SLAVE_ADDR 9
unsigned char status; 
unsigned char str[MAX_LEN]; 
// Define Slave answer size
#define ANSWERSIZE 5
RFID rfid(10, 9);    
// Define string with response to Master
String answer = "Hello";

void setup() {
   SPI.begin();            //Start SPI communication with reader
  rfid.init(); 


  // Initialize I2C communications as Slave
  Wire.begin(SLAVE_ADDR);
  
  // Function to run when data requested from master
  Wire.onRequest(requestEvent); 
  
  // Function to run when data received from master
  Wire.onReceive(receiveEvent);
  
  // Setup Serial Monitor 
  Serial.begin(57600);
  Serial.println("I2C Slave Demonstration");
}
 
void receiveEvent() {
 
  // Read while data received
  while (0 < Wire.available()) {
    byte x = Wire.read();
  }
  
  // Print to Serial Monitor
  
}
 
void requestEvent() {
 Serial.println("Requesst");
  // Setup byte variable in the correct size
  byte response[ANSWERSIZE];
  
  // Format answer as array
  for (byte i=0;i<ANSWERSIZE;i++) {
    response[i] = (byte)answer.charAt(i);
  }
  
  // Send response back to Master
 if (rfid.findCard(PICC_REQIDL, str) == MI_OK)   //Wait for a tag to be placed near the reader
  { 
    Serial.println("Card found"); 
    String temp = "";                             //Temporary variable to store the read RFID number
    if (rfid.anticoll(str) == MI_OK)              //Anti-collision detection, read tag serial number 
    { 
      Serial.println("The card's ID number is : "); 
      for (int i = 0; i < 4; i++)                 //Record and display the tag serial number 
      { 
        temp = temp + (0x0F & (str[i] >> 4)); 
        temp = temp + (0x0F & str[i]); 
      } 
      Serial.println (temp);
           //Check if the identified tag is an allowed to open tag
     Wire.write(response,sizeof(response)); 
    rfid.selectTag(str); //Lock card to prevent a redundant read, removing the line will make the sketch read cards continually
  }
  rfid.halt();
  // Print to Serial Monitor
  
}
}
 
void loop() {
 
  // Time delay in loop
  delay(50);
}
