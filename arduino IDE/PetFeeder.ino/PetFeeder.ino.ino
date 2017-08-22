#include <HX711.h>
#include <CytronWiFiClient.h>
#include <CytronWiFiShield.h>
#include <CytronWiFiServer.h>
#include <SoftwareSerial.h>
#include <SoftwareSerial.h>
#include <Servo.h>
#include "Arduino.h"

ESP8266Client server;
SoftwareSerial ESP8266(2, 3); //set ESP8266 RX pin = 5, and TX pin = 4
HX711 scale(A0, A1);    // parameter "gain" is ommited; the default value 128 is used by the library

String data;
String servera = "192.168.1.100"; 
String uri = "/arduino/add.php?"; 

#define SERV1 9
#define DEBUG true
ESP8266Client client;

Servo s1; //servo 1
int pos1 = 90; //servo 1 current position
int vel = 3; //servos' speed (100 -> 90º in 1 s)(1 -> 90º in 9 s)
int pos1max = 180; //servo 1 maximum position


//**************
// Arduino Setup
//**************
void setup()
{
  scale.set_scale(2280.f);// this value is obtained by calibrating the scale with known weights; see the README for details
  scale.tare();           // reset the scale to 0
  
  //attach and set servos' angles
  s1.attach(SERV1);
  s1.write(pos1max);
  
  //detach servos
  s1.detach();

  
  //start serial communication
  Serial.begin(9600);
  ESP8266.begin(9600);
  
  sendData("AT+RST\r\n", 2000, DEBUG); //reset module
  sendData("AT+CWMODE=1\r\n", 1000, DEBUG); //set station mode
  sendData("AT+CWJAP=\"kotakRiang\",\"BMaxCut3\"\r\n", 2000, DEBUG);   //connect wifi network
  while(!ESP8266.find("OK")) { //wait for connection
  } 
  sendData("AT+CIFSR\r\n", 1000, DEBUG); //show IP address
  sendData("AT+CIPMUX=1\r\n", 1000, DEBUG); //allow multiple connections
  sendData("AT+CIPSERVER=1,80\r\n", 1000, DEBUG); // start web server on port 80
}

//**********
// Main Loop
//**********
void loop()
{
  float a =scale.get_units();
 while (ESP8266.available())     //check if there is data available on ESP8266
  { 
    if (ESP8266.find("+IPD,")) //if there is a new command
    { 
      String msg;
      ESP8266.find("?");                           //run cursor until command is found
      msg = ESP8266.readStringUntil(' ');          //read the message
      String command = msg.substring(0, 3);    //command is informed in the first 3 characters "sr1"
      String valueStr = msg.substring(4);      //next 3 characters inform the desired angle
      int value = valueStr.toInt();            //convert to integer
      if (DEBUG) {
        Serial.println(command);
        Serial.println(value);
      }
      delay(100);
      //************
      // move servos
      //************
  
        //move servo1 to desired angle
      
      if(command == "sr1") {
         //limit input angle
         if (value >= pos1max) {
           value = pos1max;
         }
         s1.attach(SERV1); //attach servo
         while(pos1 != value) {
           if (pos1 < value) {
             pos1 += 1;
             s1.write(pos1);
             delay(100/vel);
             
           }
         }
         pos1 = 90;
         s1.detach(); //dettach
      }
        
  }
 }scale.power_up();
  
}


//********************
// Auxiliary functions
//********************

//send data to ESP8266
String sendData(String command, const int timeout, boolean debug)
{
  String response = "";
  ESP8266.print(command);
  long int time = millis();
  while ( (time + timeout) > millis())
  {
    while (ESP8266.available())
    {
      char c = ESP8266.read();
      response += c;
    }
  }
  if (debug)
  {
    Serial.print(response);
  }
  return response;
}

