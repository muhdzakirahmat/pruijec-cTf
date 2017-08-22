#include <CytronWiFiShield.h>
#include <CytronWiFiServer.h>
#include <SoftwareSerial.h>
#include <String.h>
#include <HX711.h>
#include <Servo.h> 

const char* ssid = "kotakRiang";
const char* pass = "BMaxCut3";
byte server1[] = {192 , 168 , 1 , 100};

HX711 scale(A1, A0); // DOUT, SCK                
ESP8266Server server(80);
ESP8266Client client;

float value = 0 ;




void setup() {
  Serial.begin(9600);
  scale.set_scale(2280.f); //// this value is obtained by calibrating the scale with known weights
  scale.tare();
  
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  if(!wifi.begin(2, 3))
    Serial.println(F("Error talking to shield"));
  Serial.println(wifi.firmwareVersion());
  Serial.print(F("Mode: "));Serial.println(wifi.getMode());// 1- station mode, 2- softap mode, 3- both
  Serial.println(F("Setup wifi config"));
  Serial.println(F("Start wifi connection"));
  if(!wifi.connectAP(ssid, pass))
    Serial.println(F("Error connecting to WiFi")); 
  Serial.print(F("Connected to: "));Serial.print(wifi.SSID());
  Serial.print(F(", "));Serial.println(wifi.RSSI());
  Serial.print(F("IP address: "));Serial.println(wifi.localIP());
  Serial.print(F("Status: "));Serial.println(wifi.status()); //2- wifi connected with ip, 3- got connection with servers or clients, 4- disconnect with clients or servers, 5- no wifi
  server.begin();
  espblink(100);

}


void loop() 
{
  long int a =scale.get_units();
  if (client.connect(server1,80)){
  Serial.println("connected");
    if (a < 2){
     client.print("GET /arduino/add.php?");
    client.print("value=");
    client.println(a);
    Serial.print("value = ");
    Serial.println(a);
      
    }
    else{
      client.print("GET /arduino/add.php?");
      client.print("value=");
    client.println(a+26);
    Serial.print("value = ");
    Serial.println(a+26);
    
    
      }
    
    
    client.stop();
  }
  scale.power_down(); // put the ADC in sleep mode
scale.power_up();
delay(2000);
}


void espblink(int time)
{
  for(int i = 0;i<12;i++)
  {
    wifi.digitalWrite(2,wifi.digitalRead(2)^1);
    delay(time);
  }
}

