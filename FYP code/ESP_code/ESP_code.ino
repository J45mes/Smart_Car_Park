#include <ESP8266WiFi.h>

#include <SoftwareSerial.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

SoftwareSerial s(D6,D5);


#define WIFI_SSID "kingballball_2.4g"                                               //WiFi SSID to which you want NodeMCU to connect
#define WIFI_PASSWORD "90152788881971043021896341"         
const char* host = "192.168.100.18";
//Password of your wifi network 

int8_t indexOfA;

char c;
String Space;
String Num; 
String dataIn;
String postVariable = "space=";
int firebaseSpace;

int val=0;

void setup() {

  s.begin(115200);
  Serial.begin(57600);

  Serial.println("Serial communication started\n\n"); 
           
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                     //try to connect with wifi
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);


  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());                                            //print local IP address
  
delay(1000);
}

void loop() { 
  
  while(s.available()>0){
      c = s.read();

      if(c=='/n') {break;}
      else        {dataIn+=c;}
    }
  if(c='/n'){
    
    indexOfA = dataIn.indexOf("A");
  
    Space = dataIn.substring(0, indexOfA);
    //Parse_the_data();
    
    Serial.println("Available Space is = " + Space);
    
    Serial.println("========================");
    c=0;
    dataIn="";
    }

  delay(1000);

Serial.print("connecting to ");
    Serial.println(host);

     WiFiClient client;
    const int httpPort = 80;
    if (!client.connect(host, httpPort)) {
        Serial.println("connection failed");
        return;
    }else{
         Serial.println("success!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
      }

 String postData = postVariable + Space;


  if (client.connect(host, 80)) {
    client.println("POST /PhpProject10/Car_park.php HTTP/1.1");
    client.println("Host: 127.0.0.1");
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.print("Content-Length: ");
    client.println(postData.length());
    client.println();
   client.print(postData);
    //Serial.print("Yeah");
  }

  if (client.connected()) {
    client.stop();
  }
 
  Serial.println(postData);
  
  
  delay(3000);

// Firebase Error Handling ************************************************
 

}
// the setup function runs once when you press reset or power the board
