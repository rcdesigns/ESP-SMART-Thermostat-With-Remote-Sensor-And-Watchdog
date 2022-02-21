/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp32-client-server-wi-fi/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

#include <WiFi.h>
#include <HTTPClient.h>
#include <Adafruit_Sensor.h>           // Adafruit sensor
#include <Adafruit_BMP280.h>           // For BME280 support
Adafruit_BMP280 tempsensor;                // I2C mode
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SensorAddress   0x76   

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


const char* ssid = "MyESP32AP";
const char* password = "testpassword";

//Your IP address or domain name with URL path
const char* serverNameTempVal = "http://192.168.4.1/temperature?name1=";
const char* serverNameBoostVal = "http://192.168.4.1/boost";

float Temperature = 0.0f;
float RawTemperature = 0.0f;
unsigned long previousMillis = 0;
const long interval = 15000; 
const int PushButton = 15;
int DisplayBoost = 0;
float TemperatureCalibrartion = 0.0f;

void setup() {
  Serial.begin(115200);

  delay(500);

  Serial.println("startup cpu freq: ");
  Serial.println(getCpuFrequencyMhz());
  setCpuFrequencyMhz(80);
  Serial.println("after setting - cpu freq: ");
  Serial.println(getCpuFrequencyMhz());

    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    //for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000);

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.println("Connecting...");
  display.display();
  
  WiFi.setAutoConnect(true);
  WiFi.setAutoReconnect(true);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
//  while(WiFi.status() != WL_CONNECTED) { 
//    delay(500);
//    Serial.print(".");
//  }
  uint32_t notConnectedCounter = 0;
  while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.print(".");
      notConnectedCounter++;
      if(notConnectedCounter > 120) { // Reset board if not connected after 5s
          Serial.println("Resetting due to Wifi not connecting...");
          ESP.restart();
      }
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  StartSensor();  
  pinMode(PushButton, INPUT_PULLUP);
}

void loop() {
  unsigned long currentMillis = millis();
  
  if(currentMillis - previousMillis >= interval) {
    ReadSensor();
    
     // Check WiFi connection status
    if(WiFi.status() == WL_CONNECTED ){ 
      String s1(serverNameTempVal);
      String s2(RawTemperature, 2);
      String s3 = s1 + s2;
      Serial.println("calling get with: " + s3);
      String response = httpGETRequest(s3.c_str());
      Serial.println("Temperature response (calibration value): " + response);
      float cal = response.toFloat();
      // if the response is duff, then toFloat should return 0, so ignore it
      // if the cal really is zero, then we'll be at zero anyway if we just restart
      if (cal != 0.0)
        TemperatureCalibrartion = cal;
    }
    else {
      Serial.println("WiFi Disconnected - trying to reconnect..");
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0, 10);
      display.println("Reconnecting...");
      display.display();
      delay(5000);
      WiFi.reconnect();
    }
    previousMillis = currentMillis;
  }

  int Push_button_state = digitalRead(PushButton);
  
  if (Push_button_state == LOW)
  {
    Serial.println("BOOST activated");
    // Check WiFi connection status
    if(WiFi.status() == WL_CONNECTED ){ 
      String response = httpGETRequest(serverNameBoostVal);
      Serial.println("Boost response: " + response);
      if (response == "boost activated")
      {
        DisplayBoost = 4;
        UpdateDisplay();
      }
        
    }
    delay(500);
  }
}

void StartSensor() {
  Wire.setClock(100000);                           // Slow down the SPI bus for some BME280 devices
  bool status = tempsensor.begin(SensorAddress);     // You can also pass a Wire library object like &Wire2, e.g. status = bme.begin(0x76, &Wire2);
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring, address and sensor ID!");
    Serial.print("SensorID is: 0x"); Serial.println(tempsensor.sensorID(), 16);
    Serial.print("       ID of 0xFF probably means a bad address, or a BMP 180 or BMP 085 or BMP280\n");
    Serial.print("  ID of 0x56-0x58 represents a BMP 280,\n");
    Serial.print("       ID of 0x60 represents a BME 280.\n");
  }
  else {
    Serial.println("Sensor started...");
  }
  delay(2000);                                   // Wait for sensor to start
}

void UpdateDisplay()
{
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(4);
  display.setCursor(0, 10);
  display.println(String(Temperature, 1));

  display.setTextSize(1);
  display.setCursor(95, 50);
  display.println(WiFiSignal());
  
  if (DisplayBoost > 0)
  {
    display.setTextSize(1);
    display.setCursor(0, 50);
    display.println("Wear a Jumper!");
    --DisplayBoost;
  }
  display.display(); 
}
void ReadSensor() {
  while (isnan(tempsensor.readTemperature())) { }  // Make sure there are no reading errors
  RawTemperature = tempsensor.readTemperature();    // Read the current temperature
  Temperature = RawTemperature + TemperatureCalibrartion;     

  Serial.println("Raw Sensor Temp: " + String(RawTemperature, 2) + ", Calibrated Temp: " + String(Temperature, 2));

  UpdateDisplay();
}

String httpGETRequest(const char* serverName) {
  WiFiClient client;
  HTTPClient http;
    
  // Your Domain name with URL path or IP address with path
  http.begin(client, serverName);

  
  // Send HTTP POST request
  int httpResponseCode = http.GET();
  
  String payload = "--"; 
  
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}
String WiFiSignal() {
  float Signal = WiFi.RSSI();
  Signal = 90 / 40.0 * Signal + 212.5; // From Signal = 100% @ -50dBm and Signal = 10% @ -90dBm and y = mx + c
  if (Signal > 100) Signal = 100;
  return " " + String(Signal, 0) + "%";
}
