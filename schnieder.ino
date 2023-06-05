#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "YOUR_SSID"; //Put name of your notwork
const char* password = "YOUR_PASSWORD"; //Put modem password

//const char* serverUrl = "http://your_web_server.com/endpoint";

const int pressure_Pin = A0; // ANALOG PIN
int pressure_Value= 0; // Initial signal 
int pressure_Value_in_bar = 0; // Initial Value
const float min_pressure = 0.0; // Data sheet's specification 
const float max_pressure = 25.0; // Data sheet's specification
const int min_ADC_Value = 0; // Minimum value of Analog to direct conversion
const int max_ADC_Value = 4095; // Maximale value of Analog to direct conversion

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  
  Serial.println("Connected to WiFi");

  pinMode(pressure_Pin, INPUT);
}

void loop() {
  float pressure_Value = analogRead(pressure_Pin)// Tension value of our sensor
  pressure_Value_in_bar = map(pressureValue, min_ADC_Value, max_ADC_Value, min_pressure, max_pressure); // Conversion of tension to pressure
  
  // Send value to web server
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    
    String pressure_data = "The pressure indicates" + String(pressure_Value_in_bar) + " bar";
    
    http.begin(serverUrl);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    int httpCode = http.POST(pressure_data);
    
    if (httpCode > 0) {
      String response = http.getString();
      Serial.println(response);
    } else {
      Serial.println("Error sending data to server");
    }
    
    http.end();
  }
  
  delay(1000);
}
