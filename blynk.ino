/*FINAL YEAR PROJECT - 
TITlE: DEVELOPMENT OF A PORTABLE INCUBATOR FOR DETECTION OF COLIFORM USING IOT 
BY: OLONISAKIN DAVID AKOLADE 18CK024244 AND OGUIBE FAVOUR OZIOMA 18CK024232
EEE SET2023 #18TH SET            
SUPERVISOR: DR. OMORUYI OSEMWINGIE */

//Global declarations//
//Including necessary libraries
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "DHT.h"

//Blynk and wifi details
#define BLYNK_TEMPLATE_ID "TMPLiD4_oZ2g"
#define BLYNK_TEMPLATE_NAME "COLIFORM DETECTION"
#define BLYNK_AUTH_TOKEN "O_Y7eWj-zfD9Y49K4kdOTx3ueyJIut6y"
#define BLYNK_PRINT Serial
//Wifi credentials and assignments
char auth[] = BLYNK_AUTH_TOKEN; 
char ssid[] = "Coliform";
char password[] = "bacteria";
unsigned long startTime;
BlynkTimer timer;
LiquidCrystal_I2C lcd(0x27 ,20,4); //20x4 lcd dinmsplay
// initialize DHT sensor
#define DHTPIN 5
#define DHTTYPE DHT11  
DHT dht(DHTPIN, DHTTYPE);
float temperature, humidity;
//setting sensor pins  to the Esp32
  int ldrA = 33 ;
  int ldrB = 35;
  int ldrC = 34;
  int relayPin = 32; 
//Functions
  void sendSensor(){ 
   float humidity = dht.readHumidity();
   float temperature = dht.readTemperature();
   int ldr1 = analogRead(ldrA);
   int ldr1_value = map(ldr1, 600, 0, 0 ,100);
   int ldr2 = analogRead(ldrB);
   int ldr2_value = map(ldr2, 2200, 0 , 0, 100);
   int ldr3 = analogRead(ldrC); 
   int ldr3_value = map(ldr3, 670, 0 , 0, 100);
   Blynk.virtualWrite(V2, ldr1_value);
   Blynk.virtualWrite(V3, ldr2_value);
   Blynk.virtualWrite(V4, ldr3_value);
   Blynk.virtualWrite(V6, humidity);
   Blynk.virtualWrite(V5, temperature);
  }
  void updateLedBlynk(){
   int status = digitalRead(relayPin);
   if (status == LOW)
   {
     Blynk.virtualWrite(V1, HIGH);
   }
   else
   {
     Blynk.virtualWrite(V1, LOW);
   }
  }

void setup(){
 //initialize serial communication at 115200 bit/s
  Serial.begin(115200);
  Serial.println("System is ON, Coliform Test");
  delay(2000);
  lcd.begin();  //initialize LCD
  dht.begin();  // initialize DHT sensor
  startTime = millis(); // record the current time in milliseconds
  pinMode(relayPin, OUTPUT);
  pinMode(DHTPIN, INPUT);
  // Display startup messages on LCD
  lcd.setCursor(0,2);
  lcd.print("PROJECT TOPIC:");
  delay(2500);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("DEVELOPMENT OF A");
  lcd.setCursor(0,1);
  lcd.print("PORTABLE INCUBATOR");
  lcd.setCursor(0,2);
  lcd.print("FOR DETECTION OF"); 
  lcd.setCursor(0,3);
  lcd.print("COLIFORM USING IOT");     
  delay(4000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("BY");
  lcd.setCursor(0,1);
  lcd.print("OLONISAKIN DAVID");
  lcd.setCursor(0,2);
  lcd.print("AND");
  lcd.setCursor(0,3);
  lcd.print("OGUIBE FAVOUR");
  delay(4000);
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("LOADING ....");
  delay(2000);
  lcd.setCursor(0,1);
  lcd.print("Connecting....");
  delay(2000);
  lcd.clear();
  //Setting up Blynk Application 
  Blynk.begin(auth, ssid, password);
  // Setting interval to send data to Blynk Cloud to 1000ms. It means that data will be sent every second
  timer.setInterval(1000L, sendSensor);
  timer.setInterval(1000L, updateLedBlynk);  
}

void loop() {
  Blynk.run();
  timer.run();//Initiates blynkTimer
    //Getting LDR readings
   int ldr1 = analogRead(ldrA);
   int ldr1_value = map(ldr1, 600, 0, 0 ,100);
   int ldr2 = analogRead(ldrB);
   int ldr2_value = map(ldr2, 2200, 0 , 0, 100);
   int ldr3 = analogRead(ldrC); 
   int ldr3_value = map(ldr3, 670, 0 , 0, 100);
  //Visualize on LDR values on serial monitor
  Serial.print("ldr1 value: ");
  Serial.println(ldr1_value);
  Serial.print("ldr2 value: ");
  Serial.println(ldr2_value);
  Serial.print("ldr3 value: ");
  Serial.println(ldr3_value);
  unsigned long uptime = millis() - startTime;
  int seconds = (uptime / 1000) % 60; // extract the seconds from the uptime
  int minutes = (uptime / (1000 * 60)) % 60; // extract the minutes from the uptime
  int hours = (uptime / (1000 * 60 * 60)) % 24; // extract the hours from the uptime
  lcd.setCursor(0,1);
  lcd.print("Coliform Test");
  lcd.setCursor(0, 2); // set the cursor to the top right corner
  lcd.print("Time: "); // print the label
  lcd.print(hours); // print the number of hours
  lcd.print("h ");
  lcd.print(minutes); // print the number of minutes
  lcd.print("m ");
  lcd.print(seconds); // print the number of seconds
  lcd.print("s");
  delay(4000) ;
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("Rechecking...."); 
  delay(3000);
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("Checking Status");   
  lcd.setCursor(0,2);
  lcd.print("in the incubator");
  delay(3000);
  sendSensor();
  updateLedBlynk();
  //UPTIME - CONDITION
  if(uptime % 20 == 0){
  lcd.setCursor(0,0);
  lcd.print("PROJECT TOPIC:");
  delay(2500);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("DEVELOPMENT OF A");
  lcd.setCursor(0,1);
  lcd.print("PORTABLE INCUBATOR");
  lcd.setCursor(0,2); 
  lcd.print("FOR DETECTION OF"); 
  lcd.setCursor(0,3);
  lcd.print("COLIFORM USING IOT");     
  delay(4000);
}
//<<<<Checking beakers if coliform bacteria is present or not>>>>>>>>>>>//
if (ldr1_value < 66) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Beaker 1");
  lcd.setCursor(0, 1);
  lcd.print("Possible Absence");
  lcd.setCursor(0, 2);
  lcd.print("of Coliform");
  lcd.setCursor(0,3);
  lcd.print("Resistance: " + String(ldr1_value));
  delay(3000);
 }
else{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Beaker 1");
  lcd.setCursor(0, 1);
  lcd.print("Possible Presence");
  lcd.setCursor(0, 2);
  lcd.print("of Coliform");
  lcd.setCursor(0,3);
  lcd.print("Resistance: " + String(ldr1_value));
  delay(3000);
}
lcd.clear(); // clear the LCD after displaying the status of beaker 1
if(ldr2_value < 28){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Beaker 2");
  lcd.setCursor(0, 1);
  lcd.print("Possible Absence");
  lcd.setCursor(0, 2);
  lcd.print("of Coliform");
  lcd.setCursor(0,3);
  lcd.print("Resistance: " + String(ldr2_value));
  delay(3000);
}
else{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Beaker 2");
  lcd.setCursor(0, 1);
  lcd.print("Possible Presence");
  lcd.setCursor(0, 2);
  lcd.print("of Coliform");
  lcd.setCursor(0,3);
  lcd.print("Resistance: " + String(ldr2_value));
  delay(3000);
}
lcd.clear(); // clear the LCD after displaying the status of beaker 2

if(ldr3_value < 59){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Beaker 3");
  lcd.setCursor(0, 1);
  lcd.print("Possible Absence");
  lcd.setCursor(0, 2);
  lcd.print("of Coliform");
  lcd.setCursor(0,3);
  lcd.print("Resistance: " + String(ldr3_value));
  delay(2000);
}
else{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Beaker 3");
  lcd.setCursor(0, 1);
  lcd.print("Possible Presence");
  lcd.setCursor(0, 2);
  lcd.print("of Coliform");
  lcd.setCursor(0,3);
  lcd.print("Resistance: " + String(ldr3_value));
  delay(2000); 
}
lcd.clear(); // clear the LCD after displaying the status of beaker 2
//DHT22 sensor
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  //<<<<<<<<<<<<<<<<<CONDITIONAL STATEMENTS>>>>>>>>>>>>>>>>>>>>>>
  // checking if reading from sensor was successful
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  // check if temperature is within desired range
  //normally closed logic
  if(temperature > 37.0){
    digitalWrite(relayPin, HIGH); //Turn off Heater
    Serial.println("Heating pad is OFF");
    lcd.setCursor(0,0);
    lcd.print("Heating pad:");
    lcd.setCursor(0,1);
    lcd.print("is OFF");
    lcd.setCursor(0, 2);
    lcd.print("Temperature:" + String(temperature) + "°C");
    lcd.setCursor(0, 3);
    lcd.print("Humidity:" + String(humidity) + "%");
    delay(3000); 
    lcd.clear();
  }
  else if (temperature < 35.0) {
    digitalWrite(relayPin, LOW); //Turn on Heater
    Serial.println("Heating pad is ON");
    lcd.setCursor(0,0);
    lcd.print("Heating pad:");
    lcd.setCursor(0,1);
    lcd.print("is ON");
    lcd.setCursor(0,2);
    lcd.print("Temperature:" + String(temperature) + "°C");
    lcd.setCursor(0, 3);
    lcd.print("Humidity:" + String(humidity) + "%");
    delay(3000); 
    lcd.clear();
  }
  
  else{
    Serial.println(F("Temperature within range."));
    lcd.setCursor(0,0);
    lcd.print("Optimal Temperature");
    lcd.setCursor(0,1);
    lcd.print("Temperature:" + String(temperature) + "°C");
    lcd.setCursor(0, 2);
    lcd.print("Humidity:" + String(humidity) + "%");
    delay(3000); 
    lcd.clear(); 
  }
//DHT22 Live temperature on Serial MOnitor
  Serial.print("temperature: ");
  Serial.println(temperature);
  Serial.print("humidity: ") ;
  Serial.println(humidity);
//condition when 16hour is reached
  if(uptime == 57600000){
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("INCUBATION PROCESS");
    lcd.setCursor(3, 2);
    lcd.print("COMPLETE");
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print(".FINAL RESULTS.");
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("Please Wait..");
    delay(3000);
    //Printing out final result of project analysis
    //drawing conclusion from the 16hour test
    //Check LDR1 value
    switch (ldr1_value < 66) {
      case true:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Beaker 1");
        lcd.setCursor(0, 1);
        lcd.print("Coliform ABSENT");
        lcd.setCursor(0, 2);
        lcd.print("Water is Safe");
        lcd.setCursor(0, 3);
        lcd.print("To Drink");  
        delay(3000);   
        lcd.clear(); 
        break;
      case false:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Beaker 1");
        lcd.setCursor(0, 1);
        lcd.print("Coliform PRESENT");
        lcd.setCursor(0, 2);
        lcd.print("Water is Unsafe");
        lcd.setCursor(0, 3);
        lcd.print("Don't Drink!!"); 
        delay(3000);
        lcd.clear();
        break;
    }

    // Check LDR2 value
    switch (ldr2_value < 28) {
      case true:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Beaker 2");
        lcd.setCursor(0, 1);
        lcd.print("Coliform ABSENT");
        lcd.setCursor(0, 2);
        lcd.print("Water is Safe");
        lcd.setCursor(0, 3);
        lcd.print("To Drink");
        delay(3000); 
        lcd.clear(); 
        break;
      case false:
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Beaker 2");
        lcd.setCursor(0, 1);
        lcd.print("Coliform PRESENT");
        lcd.setCursor(0, 2);
        lcd.print("Water is Unsafe");
        lcd.setCursor(0, 3);
        lcd.print("Don't Drink");
        delay(3000);  
        lcd.clear();
        break;
    }

  // Check LDR3 value
  switch (ldr3_value < 59) {
    case true:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Beaker 3");
      lcd.setCursor(0, 1);
      lcd.print("Coliform ABSENT");
      lcd.setCursor(0, 2);
      lcd.print("Water is Safe");
      lcd.setCursor(0, 3);
      lcd.print("To Drink");
      delay(3000);  
      lcd.clear();
      break;
    case false:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Beaker 3");
      lcd.setCursor(0, 1);
      lcd.print("Coliform PRESENT");
      lcd.setCursor(0, 2);
      lcd.print("Water is Unsafe");
      lcd.setCursor(0, 3);
      lcd.print("Don't Drink");
      delay(3000);  
      lcd.clear();
      break;
  }
  }
}