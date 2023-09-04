#include <LiquidCrystal_I2C.h>
#include <string>
//define sound speed in cm/uS
#define SOUND_SPEED 0.034

#include <WiFi.h>
#include <WiFiClient.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "Gsender.h"
#include "Message.h"
#include "index.h"  //Web page header file

// Global variables and constants
#pragma region Globals
AsyncWebServer server(80);      // Create AsyncWebServer object on port 80
const char *ssid = "PLAY_Swiatlowodowy_6078";        // WIFI network name
const char *password = "cWrNuM8ThU";  // WIFI network password
uint8_t connection_state = 0;           // Connected to WIFI or not
uint16_t reconnect_interval = 10000;    // If not connected wait time to try again
const char* PARAM_INPUT_VALUE = "value";
const char* PARAM_INPUT_STATE = "state";
int minHumidity = 30;
long duration;
LiquidCrystal_I2C lcd(0x3F, 16, 2);
int counter = 0;
int counterAwayMode = 0;
bool awayMode = false;
bool pumpOn = false;
int awayModeInterval = 120000;
#pragma endregion Globals
 
// Replaces placeholder section in the web page
String processor(const String& var){
  if(var == "AWAYMODEPLACEHOLDER"){
    String data = "";
    data += "<p>Away mode: <label class=\"switch\"><input type=\"checkbox\" id=\"auto-mode\" onChange=\"toggleAwayMode(this)\" " + String(awayMode ? "checked" : "") + "/><span class=\"slider round\"></span></label></p><br>";
    data += "<p>Frequency(s): <input id=\"awayModeValue\" type=\"text\" oninput=\"this.value = this.value.replace(/[^0-9.]/g, '').replace(/(\..*)\./g, '$1');\" value=" + String(awayModeInterval) + " /></p>"; 
    return data;
  } else if(var == "PUMPPLACEHOLDER"){
    return "<label class=\"switch\"><input type=\"checkbox\" id=\"toggle-pump\" onChange=\"togglePump(this)\" " + String(pumpOn ? "checked" : "") + "/><span class=\"slider round\"></span></label><br>";
  } else if (var == "SETHUMIDITYPLACEHOLDER") {
    return "<div id=\"setHumidity\"><input type=\"range\" id=\"minHumidityValue\" min=\"0\" max=\"100\" value=" + String(minHumidity) + " oninput=\"this.nextElementSibling.value = this.value\" onChange=\"setMinHumidity()\" /><output>"  + String(minHumidity) + "</output></div>"; 
  } 
  return String();
}

// Function to check humidity and control pump
void checkHumidity() {
  int counterHum = 5;
  if (((4095 - analogRead(A2)) / 28) < minHumidity) {
    float humidity = ((4095 - analogRead(A2)) / 28);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Pompa: ON");
    lcd.setCursor(0, 1);
    lcd.print("Wilgotnosc:");

    while (((4095 - analogRead(A2)) / 28) < minHumidity) {
      pumpOn = true;
      digitalWrite(D13, HIGH);
      lcd.setCursor(11, 1);
      lcd.print((4095 - analogRead(A2)) / 28);
      if (counterHum == 5) {
        sendInfoPump("smiw.kowalski@interia.pl", "Pompa: ON", humidity);
        counterHum = 0;
      }
      counterHum ++;
      delay(1000);
    }  pumpOn = false;
  digitalWrite(D13, LOW);
  }

}

// Function to read light level and return the value
String getLight() {
  if (analogRead(A3) > 2680) {
    return ("Ciemno");
  } else if (analogRead(A3) > 1340) {
    return ("Srednie");
  } else {
    return ("Jasno");
  }
}

//Function to read and return distance value
float getDistance() {
  // Clears the trigPin
  digitalWrite(D6, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(D6, HIGH);
  delayMicroseconds(10);
  digitalWrite(D6, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(D7, HIGH);
  // Calculate the distance
  return (duration * SOUND_SPEED / 2);
}

void handleAwayMode(float humidity, String lightLvl, float distanceCm) {      
  //Check if enough time passed to send the notification again
  if(awayMode) {
    counterAwayMode++;
    if(counterAwayMode == awayModeInterval) {
      sendInfo("smiw.kowalski@interia.pl", humidity, lightLvl, distanceCm);
      counterAwayMode = 0;
    }
  } 
}

// Function to establish a WiFi connection
uint8_t WiFiConnect(const char *nSSID = nullptr, const char *nPassword = nullptr) {
  static uint16_t attempt = 0;
  lcd.setCursor(0, 0);
  lcd.print("Connecting to:");
  if (nSSID) {
    WiFi.begin(nSSID, nPassword);
    lcd.setCursor(0, 1);
    lcd.println(nSSID);
  } else {
    WiFi.begin(ssid, password);
    lcd.setCursor(0, 1);
    lcd.println(ssid);
  }
  delay(1000);
  lcd.clear();

  uint8_t i = 0;
  while (WiFi.status() != WL_CONNECTED && i++ < 50) {
    delay(200);
    Serial.print(".");
  }
  ++attempt;
  Serial.println("");

  if (i == 51) {
    lcd.setCursor(0, 0);
    lcd.print("Connect TIMEOUT on attempt: ");
    lcd.setCursor(0, 1);
    lcd.print("on attempt: " + String(attempt));
    delay(1000);
    if (attempt % 2 == 0)
      lcd.setCursor(0, 0);
      lcd.print("Check SSID and");
      lcd.setCursor(0, 1);
      lcd.print("Password or if");
      delay(1000);
      lcd.setCursor(0, 0);
      lcd.print("access point");
      lcd.setCursor(0, 1);
      lcd.print("available ");
      delay(1000);  
    return false;
  }
  lcd.setCursor(0, 0);
  lcd.println("Connected!      ");
  lcd.setCursor(0, 1);
  lcd.print("IP: " + String(WiFi.localIP()));
  Serial.println(WiFi.localIP());
  delay(2000);
  return true;
}

// Function to wait for WiFi connection
void Awaits() {
  uint32_t ts = millis();
  int counter = 0;
  while (!connection_state && counter < 1000) {
    delay(50);
    if (millis() > (ts + reconnect_interval) && !connection_state) {
      connection_state = WiFiConnect();
      ts = millis();
    }
    counter++;
  }
}

void setup() {
  Serial.begin(57600);
  pinMode(D13, OUTPUT);  //water pump
  pinMode(D6, OUTPUT);   // Sets the trigPin as an Output
  pinMode(D7, INPUT);    // Sets the echoPin as an Input
  lcd.init();
  lcd.backlight();

  connection_state = WiFiConnect();
  if (!connection_state)  // if not connected to WIFI
    Awaits();             // constantly trying to connect

  if(connection_state) {
    Gsender *gsender = Gsender::Instance();  // Getting pointer to class instance
    String subject = "ESP monitorowanie roslin";
    gsender->Subject(subject);
    if (gsender->Send("smiw.kowalski@interia.pl", "Setup test")) {
      Serial.println("Message send.");
    } else {
      Serial.print("Error sending message: ");
      Serial.println(gsender->getError());
    }

    // Handle Web Server
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send_P(200, "text/html", MAIN_page, processor);
    });

    // Send a GET request to <ESP_IP>/awayMode?state=<inputMessage2>
    server.on("/awayMode", HTTP_GET, [] (AsyncWebServerRequest *request) {
      // GET input1 value on <ESP_IP>/awayMode?state=<inputMessage2>
      String inputMessage1;
      if (request->hasParam(PARAM_INPUT_STATE)) {
        inputMessage1 = request->getParam(PARAM_INPUT_STATE)->value();
        if(inputMessage1 == "1") {
          awayMode = true;
          counterAwayMode = 0;
        } else if(inputMessage1 == "0") {
          awayMode = false;
          counterAwayMode = 0;
        }
      }
      request->send(200, "text/plain", "OK");
    });

    // Send a GET request to <ESP_IP>/awayModeInterval?value=<inputMessage1>
    server.on("/awayModeInterval", HTTP_GET, [] (AsyncWebServerRequest *request) {
      // GET input1 value on <ESP_IP>/awayModeInterval?value=<inputMessage1>
      if (request->hasParam(PARAM_INPUT_VALUE)) {
        awayModeInterval = (request->getParam(PARAM_INPUT_VALUE)->value()).toInt() / 4; //because program loop is 4 seconds
        counterAwayMode = 0;
      }
      request->send(200, "text/plain", "OK");
    });

    // Send a GET request to <ESP_IP>/pump?state=<inputMessage1>
    server.on("/pump", HTTP_GET, [] (AsyncWebServerRequest *request) {
      String inputMessage1;
      // GET input1 value on <ESP_IP>/pump?state=<inputMessage1>
      if (request->hasParam(PARAM_INPUT_STATE)) {
        inputMessage1 = request->getParam(PARAM_INPUT_STATE)->value();
        if(inputMessage1 == "1") {
          pumpOn = true;
          digitalWrite(D13, HIGH);
        } else if(inputMessage1 == "0") {
          pumpOn = false;
          digitalWrite(D13, LOW);
        }
      }
      request->send(200, "text/plain", "OK");
    });

    // Send a GET request to <ESP_IP>/setHumidity?value=<inputMessage1>
    server.on("/setHumidity", HTTP_GET, [] (AsyncWebServerRequest *request) {
      // GET input1 value on <ESP_IP>/etHumidity?value=<inputMessage1>
      if (request->hasParam(PARAM_INPUT_VALUE)) {
        minHumidity = (request->getParam(PARAM_INPUT_VALUE)->value()).toInt();
      }
      request->send(200, "text/plain", "OK");
    });

    // Send a POST request to <ESP_IP>/lightLvl
    server.on("/lightLvl", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send_P(200, "text/plain", getLight().c_str());
    });
    // Send a POST request to <ESP_IP>/humidity
    server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send_P(200, "text/plain", String((4095 - analogRead(A2)) / 28).c_str());
    });
    // Send a POST request to <ESP_IP>/distance
    server.on("/distance", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send_P(200, "text/plain", String(getDistance()).c_str());
    });
    
    server.begin();                  //Start server
    Serial.println("HTTP server started");
  }
}

void loop() {
  checkHumidity();
  
  //First part of informations displayed on LCD
  lcd.setCursor(0, 0);
  lcd.print("Swiatlo:");
  lcd.setCursor(8, 0);
  String lightLvl = getLight();
  lcd.print(lightLvl);
  
  lcd.setCursor(0, 1);
  lcd.print("Wilgotnosc:");
  lcd.setCursor(11, 1);
  float humidity = ((4095 - analogRead(A2)) / 28);
  lcd.print(humidity);
  delay(2000);

  //Second part of informations displayed on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Woda:");
  lcd.setCursor(5, 0);
  float distanceCm = getDistance();
  lcd.print(distanceCm);
  lcd.setCursor(11, 0);
  lcd.print("cm");
  lcd.setCursor(0, 1);
  lcd.print("(od czujnika)");

  handleAwayMode(humidity, lightLvl, distanceCm);

  delay(2000);
}
