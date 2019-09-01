#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include "MMA8452Q.h"
#include "WifiCredentials.h"

#define NTP_OFFSET   60 * 60      // Offset from UTC in seconds
#define NTP_INTERVAL 5 * 60 * 1000    // Refresh time (In miliseconds)
#define NTP_ADDRESS  "europe.pool.ntp.org"
#define INTERRUPT_PIN 13
#define LED_PIN 14

MMA8452Q accelerator;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, NTP_ADDRESS, NTP_OFFSET, NTP_INTERVAL);

volatile boolean interruptCaught = false;
byte state = LOW;

void ICACHE_RAM_ATTR tapInterrupt(){
  interruptCaught = true;
}


void setup() {
  Serial.begin(9600);
  Wire.begin();
  WiFi.begin(WifiSSID, WifiPASS);   //WiFi connection

  if (accelerator.begin() == false) {
//    Serial.println("MMA8452Q not Connected.");
    while (1);
  }

  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
    delay(500);
//    Serial.println("Waiting for connection");
  }
  
  timeClient.begin();

  pinMode(INTERRUPT_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), tapInterrupt, RISING);

//  pinMode(LED_PIN, OUTPUT);
//  digitalWrite(LED_PIN, state);

  // set up accelerator
/*
  accelerator.standby();
  accelerator.writeRegister(PULSE_CFG, 0x15); //55

  accelerator.writeRegister(PULSE_THSX, 0x04); //0x04  19
  accelerator.writeRegister(PULSE_THSY, 0x14); // 0x14  2A
  accelerator.writeRegister(PULSE_THSZ, 0x04);
  
  accelerator.writeRegister(PULSE_TMLT, 0x50);
  accelerator.writeRegister(PULSE_LTCY, 0xF0);
  //accelerator.writeRegister(PULSE_WIND, 0xFF);

  // enable pulse
  accelerator.writeRegister(CTRL_REG4, 0x08);
  accelerator.writeRegister(CTRL_REG5, 0x08);
  
  accelerator.active();
*/
}
/*
void printSRC(byte src) {
  if(src & 0b00010000)
    Serial.print("X");
  if(src & 0b00100000)
    Serial.print("Y");
  if(src & 0b01000000)
    Serial.print("Z");
  Serial.print("\n");
}
*/

void loop() {
  //delay(500);
  delay(50);
  timeClient.update();
  
  if(interruptCaught){
    if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
    
      StaticJsonDocument<300> JSONencoder;   //Declaring static JSON buffer
      //JsonObject& JSONencoder = JSONbuffer.createObject(); 
      
      JSONencoder["date"] = timeClient.getEpochTime(); //unsigned long
      char jsonBuffer[300];
      serializeJson(JSONencoder, jsonBuffer);

      WiFiClient client;
      HTTPClient http;    //Declare object of class HTTPClient
      
      http.begin(client, "http://192.168.0.100:3000/");      //Specify request destination
      http.addHeader("Content-Type", "application/json");
      
      //int httpCode = 
      http.POST(jsonBuffer);   //Send the request
      String payload = http.getString();                  //Get the response payload
      http.end();  //Close connection

//      state = !state;
//      digitalWrite(LED_PIN, state);
      
      interruptCaught = false;

    } 
//    else {
//      Serial.println("Error in WiFi connection");   
//    }
  }

/*
    // Sleep
  Serial.println("ESP8266 in sleep mode");
  ESP.deepSleep(sleepTimeS * 1000000);
*/

  /*
  if (accelerator.available()) {      // Wait for new data from accelerometer
    // Acceleration of x, y, and z directions in g units
    Serial.print(accelerator.getX());
    Serial.print("\t");
    Serial.print(accelerator.getY());
    Serial.print("\t");
    Serial.print(accelerator.getZ());
    Serial.println();
  }
  */

}
