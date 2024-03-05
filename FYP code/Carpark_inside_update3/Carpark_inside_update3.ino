
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);
const int trigPin = 12;
const int echoPin = 13;
#define LED1 11
long duration;
int distance;
#define ir_car1 2
#define ir_car2 4
#define ir_car3 5
#define ir_car4 8
#define ir_car5 10
#define ir_car6 9

int S1=0, S2=0, S3=0, S4=0, S5=0, S6=0;
int slot1 = 3;  
int slot2 = 3; 
int slot = 6;  
void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(LED1, OUTPUT);
  Serial.begin(9600);
  pinMode(ir_car1, INPUT);
pinMode(ir_car2, INPUT);
pinMode(ir_car3, INPUT);
pinMode(ir_car4, INPUT);
pinMode(ir_car5, INPUT);
pinMode(ir_car6, INPUT);


lcd.begin();  
lcd.setCursor (0,1);
lcd.print("    Car  parking  ");
lcd.setCursor (0,2);
lcd.print("       System     ");
delay (2000);
lcd.clear();   

Read_Sensor();
  

}

void loop() {
   digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Read_Sensor();
 slot1 =3;
 slot2 =3;
 S1=0, S2=0, S3=0, S4=0, S5=0, S6=0;
Read_Sensor();
int total_1 = S1+S2+S3;
int total_2 = S4+S5+S6;
slot1 = slot1-total_1; 
slot2 = slot2-total_2;
lcd.setCursor (0,0);
lcd.print("Pink:"); 
lcd.print(slot2);
lcd.setCursor (10,0);
lcd.print("Green:"); 
lcd.print(slot1);

lcd.setCursor (0,1);
if(S4==1){lcd.print("S4:Fill ");}
     else{lcd.print("S4:Empty");}

lcd.setCursor (0,2);
if(S5==1){lcd.print("S5:Fill ");}
     else{lcd.print("S5:Empty");}

lcd.setCursor (0,3);
if(S6==1){lcd.print("S6:Fill ");}
     else{lcd.print("S6:Empty");}

lcd.setCursor (10,1);
if(S1==1){lcd.print("S1:Fill ");}
     else{lcd.print("S1:Empty");}

 lcd.setCursor (10,2);
if(S2==1){lcd.print("S2:Fill ");}
     else{lcd.print("S2:Empty");}

lcd.setCursor (10,3);
if(S3==1){lcd.print("S3:Fill ");}
     else{lcd.print("S3:Empty");}






delay(1);
  if (distance <= 3){
    digitalWrite(LED1, HIGH);
    Serial.println("close");
    delay(1000);
    
    }
    else{
      
      digitalWrite(LED1, LOW);
      
      }
      
  

}
void Read_Sensor(){
S1=0, S2=0, S3=0, S4=0, S5=0, S6=0;

if(digitalRead(ir_car1) == 0){S1=1;}
if(digitalRead(ir_car2) == 0){S2=1;}
if(digitalRead(ir_car3) == 0){S3=1;}
if(digitalRead(ir_car4) == 0){S4=1;}
if(digitalRead(ir_car5) == 0){S5=1;}
if(digitalRead(ir_car6) == 0){S6=1;}  
}
