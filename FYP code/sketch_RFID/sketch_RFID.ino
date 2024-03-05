
#include <SPI.h> 
#include <RFID.h>
#include <Servo.h> 
#define ANSWERSIZE 5
#include <Wire.h> 
#include <Servo.h> 
#define SLAVE_ADDR 9
#include <LiquidCrystal_I2C.h>

#include <SoftwareSerial.h>

SoftwareSerial s(2,3);//rx,tx
LiquidCrystal_I2C lcd(0x27, 16, 2); //(rs,e,d4,d5,d6,d7)
//RFID
RFID rfid(10, 9);       //D10:pin of tag reader SDA. D9:pin of tag reader RST 
unsigned char status; 
unsigned char str[MAX_LEN]; //MAX_LEN is 16: size of the array 
String accessGranted [2] = {"88041591", "19612012715"};  //RFID serial numbers to grant access to
int accessGrantedSize = 2; 
//RFID
int Space2;
Servo myservo1;
Servo myservo2;
int ir_s1 = 8;
int ir_s2 = 9;
boolean execute = false;
int Total = 5;
boolean execute2 = false;

void setup() {
  // put your setup code here, to run once:
    Wire.begin();
  pinMode(13, OUTPUT);
  pinMode(ir_s1, INPUT);
  pinMode(ir_s2, INPUT);
  SPI.begin();            //Start SPI communication with reader
  rfid.init();            //initialization 
  Serial.begin(57600);// for Serial Monitor
  s.begin(115200);//for Seial Communication
  delay(1000);

  myservo1.attach(22); //Servo Attached to digital pin no 10
  myservo1.write(100);
  
  myservo2.attach(23); //Servo Attached to digital pin no 10
  myservo2.write(100);

  lcd.begin();  
  lcd.setCursor (0,0);
  lcd.print("  Car  Parking  ");
  lcd.setCursor (0,1);
  lcd.print("     System     ");
  delay (2000);
  lcd.clear();  


  Space2 = Total;
  Serial.println("Place card/tag near reader...");
}

void loop() {
  
//Logic Behind free slots update
 Wire.beginTransmission(SLAVE_ADDR);
  Wire.write(0);
  Wire.endTransmission();
   Wire.requestFrom(SLAVE_ADDR,ANSWERSIZE);
   String response = "";
  while (Wire.available()) {
      char b = Wire.read();
      response += b;
  } 
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
       if(checkAccess (temp)== true ){
    if(Space2>0){
      myservo1.write(200);
      delay(5000);
      myservo1.write(100); 
    
      Space2 = Space2-1;
      execute2=true;
      }

 if(Space2==0  ){
        lcd.setCursor (0,0);
        lcd.print(" Sorry not Space ");  
        lcd.setCursor (0,1);
        lcd.print("    Available    "); 
        delay (1000);
        lcd.clear();      
      }
    }
    } 
    rfid.selectTag(str); //Lock card to prevent a redundant read, removing the line will make the sketch read cards continually
  }
  rfid.halt();
   
if(response == "Hello"){
  if(Space2<5){
      myservo2.write(200);
     delay(5000);
     myservo2.write(100);
  Space2 = Space2 +1;
  
  Serial.println(Space2);
  }
  Serial.println(response);
  delay(4000);
  
 }  

   
lcd.setCursor (0,0);
lcd.print("Total Space: ");
lcd.print(Total);

lcd.setCursor (0,1);
lcd.print("Free Space: ");
lcd.print(Space2);


s.print(Space2); s.print("A"); //Sending Free slot Data to nodemcu with IndexofA
Serial.print(Space2); Serial.print("A");//print it on serial moniter
s.print("\n");
delay(1000);

}



boolean checkAccess (String temp)    //Function to check if an identified tag is registered to allow access
{
  boolean granted = false;
  for (int i=0; i <= (accessGrantedSize-1); i++)    //Runs through all tag ID numbers registered in the array
  {
    if(accessGranted[i] == temp)            //If a tag is found then open/close the lock
    {
      return true;
     
    }
  }
  if (granted == false)     //If the tag is not found
  {
    return false;
  }
}
