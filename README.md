# Smart pot
  The system is designed to control soil moisture in a pot and the light intensity near the plant using appropriate sensors. When the soil moisture drops below a specified level, a small water pump will be activated. The system also includes a distance sensor, which should be placed above the water tank to determine the water level. Current parameters and information about plant watering is displayed in a web application, on the display, and sent to the user as email notifications.



## Components Used
* Microcontroller: FireBeetle ESP32-E
* Display: Philips PCF8574 LCD 2x16 with I2C converter LCM1602
* Battery: 18650 Li-Ion XTAR with a capacity of 2200 mAh and a nominal voltage of 3.7V
* Soil Moisture Sensor: MOD-01588
* Light Intensity Sensor: Resistor-based LDR – Okystar
* Distance Sensor: Ultrasonic HC-SR04
* Water Pump: Small submersible water pump powered by 3V – 6V
* Bipolar NPN Transistor: 2N2222A
* Resistor: 2.2k Ohm



## Schematic
![SCHEMATIC](https://github.com/OliwiaGowor/Smart-pot-web-app/assets/72342415/ed9fe84f-5cba-413c-98f7-92ccb403ef84)



## Instalation
### Configure Arduion IDE for FireBeetle 2 ESP32-E
First you need to install Arduino IDE. Next it is required to install ESP32 board in Arduino IDE for using FireBeetle 2 ESP32-E for the first time.

* Open Arduino IDE, click File-Preferences, as shown below
![image](https://github.com/OliwiaGowor/Smart-pot-web-app/assets/72342415/23ac7048-1b06-4b63-a42d-8f8d6e2f720c)
* Click the icon circled in red in the Preferences window.
![image](https://github.com/OliwiaGowor/Smart-pot-web-app/assets/72342415/53b26287-15f2-4a8d-8b07-7ee14ce2ec84)
* Add the json URL below to the newly-popped up window. There should be one URL for each line.
[https://espressif.github.io/arduino-esp32/package_esp32_index.json](https://espressif.github.io/arduino-esp32/package_esp32_index.json)
​ Click OK then.
![image](https://github.com/OliwiaGowor/Smart-pot-web-app/assets/72342415/357ee3f7-005d-489b-84b6-08dfdf1d5093)
* Download SDK. Click Tools->Board>Boards Manager.
![image](https://github.com/OliwiaGowor/Smart-pot-web-app/assets/72342415/49ce0ee3-3eac-4c08-879b-4e3aea22223e)
* Enter "ESP32" in the search bar, then the SDK for DFRobot ESP32 Boards will appear automatically. Click install now.
![image](https://github.com/OliwiaGowor/Smart-pot-web-app/assets/72342415/56cc96c7-acbe-4f11-950e-639b7c7514cc)
* When the SDK installation completes, the word "installed" will appear at the position marked in red below. Close the window.
![image](https://github.com/OliwiaGowor/Smart-pot-web-app/assets/72342415/b07c3a94-0f3a-4196-baa0-70eeb99ea7c5)
* Select FireBeetle 2 ESP32-E development board. Click Tools-->Board-->DFRobot ESP32 Arduino-->FireBeetle ESP32-E, as shown below.
![image](https://github.com/OliwiaGowor/Smart-pot-web-app/assets/72342415/6976ef26-54f3-49e8-a2d8-7c723e796c53)
* After that, connect your FireBeetle 2 ESP32-E to your computer. Here, a port COM4 comes out after the connection, indicating that it is the port for FireBeetle 2 ESP32-E. Select it as the way shown below.
![image](https://github.com/OliwiaGowor/Smart-pot-web-app/assets/72342415/40fe87ac-3fbc-4011-93d0-865a38816013)
* Now, the FireBeetle 2 ESP32-E is configured in Arduino IDE and it's ready to go.

## Uploading the code to the microcontroller
* Download the code from GitHub and open it using the IDE.
* Connect the device to the computer via USB.
* In the device tab, select the appropriate version for the FireBeetle 2 ESP32-E device.
  ![image](https://github.com/OliwiaGowor/Smart-pot-web-app/assets/72342415/b3403e9f-c20f-45ee-adc0-f5364be18b91)

* Click the "upload to device" option and enjoy a working system.
![image](https://github.com/OliwiaGowor/Smart-pot-web-app/assets/72342415/6b5ac361-45c4-4480-80fe-8628e8078aeb)



## Software
  The program code is written in C++ and uses HTML, CSS, and JavaScript for the web part. It is divided into six files:


### Gsender.h
  This is a header file that contains the declaration of the Gsender class.


### Gsender.cpp
  This code defines the Gsender class, which allows sending email messages using the SMTP protocol. Here are the key parts of the code:
* The static method  ```Instance()``` creates an instance of the Gsender class and returns a pointer to it. It uses the Singleton pattern to ensure that only one instance of the Gsender class exists.
* The ```Subject(const char* subject)``` method sets the email subject. It removes the previous subject (if it existed) and allocates memory for the new subject.
* The ```AwaitSMTPResponse(WiFiClientSecure &client, const String &resp, uint16_t timeOut)```  method waits for an SMTP server response. It checks if the client receives a response from the server within the specified time. If the time limit is exceeded, it returns false.
* The ```getLastResponce()``` method returns the last received SMTP server response.
* The ```getError()``` method returns the current error (if any) as a pointer to a constant character array.
* The ```Send(const String &to, const String &message)``` method is the main method for sending email messages. It establishes a connection with the SMTP server, authenticates, sets message headers, sends the message content, and closes the connection.


### Message.h
  This is a header file that contains the declarations of the ```sendInfo()``` and ```sendInfoPump()``` functions.


### Message.cpp
  This code contains two functions, ```sendInfo()``` and ```sendInfoPump()```, which send information via email. Here's a description of the most important parts of the code:
* The ```sendInfo()```function takes an email address, humidity, light level, and distance from a sensor as parameters. It creates a character string message to which information about humidity, light level, and distance is added. Then, an object of the Gsender class is created, and the  ```Send()``` function is called to send the email with the data.
* The ```sendInfoPump()``` function takes an email address, the state of the water pump (on/off), and humidity as parameters. Similar to the ```sendInfo()``` function, it creates a character string message to which information about the water pump state and humidity is added. Then, an object of the Gsender class is created, and the ```Send()``` function is called to send the email with the data.

Both functions use the Gsender class, whose instance is obtained through the ```Instance()``` method. The Gsender class likely implements the functionality of sending email messages.

### index.h
 This is a header file containing the declaration of the web page, written using HTML, CSS, and JavaScript as a character array. It includes the content of the web page in the form of a "raw literal" (starting with R"rawliteral( and ending with )rawliteral") so that all characters inside the string are treated literally without the need for escapes (backslashes). There are several JavaScript functions defined in the <script> tag, which execute on the browser side:
* ```togglePump(element)``` and ```toggleAwayMode(element)``` are functions that use XMLHttpRequest to send HTTP GET requests to the appropriate paths (/pump?state=1 or /pump?state=0, /awayMode?state=1 or /awayMode?state=0) depending on the state of the passed element (e.g., a checkbox). By sending such requests, you can turn the water pump or "away mode" on and off.
* ```setAwayModeInterval()``` and ```setMinHumidity()``` functions use XMLHttpRequest to send HTTP GET requests to the appropriate path (/setHumidity?value=<value>) with values obtained from certain elements on the page. This allows you to set parameters such as the "away mode" interval or minimum humidity.
* Three intervals (```setInterval(...)```) are JavaScript code snippets that regularly (every 2000 ms) send HTTP GET requests to different paths (/lightLvl, /humidity, /distance) to update the content of relevant elements on the page, such as light level, humidity, or distance.

### smartPot.ino
  This code is the main program for the ESP microcontroller. Here are the most important parts of the code:
* The defined constant ```SOUND_SPEED``` represents the speed of sound in centimeters per microsecond.
* Global variables, such as ```ssid``` and ```password``` (storing the WiFi network name and password), ```connection_state``` (storing the connection status), and ```reconnect_interval``` określa czas oczekiwania przed kolejną próbą połączenia z siecią WiFi. Innymi zmiennymi globalnymi są prędkość dźwięku (```SOUND_SPEED```), input parameters (```PARAM_INPUT_VALUE```, ```PARAM_INPUT_STATE```), minimum humidity (```minHumidity```), ultrasonic sensor signal duration in microseconds (```duration```), program intervals (```counter```), a variable (```awayMode```)that defines whether "away mode" is activated, and an interval (in milliseconds) for "away mode" (```awayModeInterval```).
* An initialized object of the ```LiquidCrystal_I2C``` class for handling the LCD display.
* An initialized object of the ```AsyncWebServer``` class named server listening on port 80, enabling the handling of HTTP requests from web browsers.
* The ```checkHumidity()``` function checks the humidity level. If it's too low, it turns on the water pump and displays information on the LCD display. It also periodically sends water pump information.
* The ```getLight()``` function reads the light level and returns the corresponding value (dark, medium, bright).
* The ```getDistance()``` function measures distance using ultrasonic sensors and returns the result in centimeters.
* The ```displayLight()``` function displays the light level on the LCD display and returns the value as a character string.
* The ```processor()``` function substitutes placeholders in the HTML code of the web page. It inserts dynamic data such as the "away mode" status, light level, humidity, distance, water pump state, and current minimum humidity.
* The ```handleAwayMode()``` function manages the "away mode" by sending notifications based on the set interval.
* The ```WiFiConnect()``` function establishes a WiFi connection based on the provided SSID and password. If not provided, it uses default values.
* The ```Awaits()``` o function waits for a WiFi connection, retrying to connect at intervals if not already connected.
* In the  ```setup()``` function, various settings are initialized, such as serial communication, input/output pins, and WiFi connection. Then, an instance of Gsender (a class for sending email messages) is created, and a test message is sent. It also configures endpoints to handle different HTTP requests.
* The ```loop()``` function contains the main program loop. It checks plant parameters (humidity, light level, distance from the sensor) and displays them on the LCD screen. It also handles the "away mode."
The code also uses helper functions like ```sendInfoPump()``` and ```sendInfo()``` to send email messages with information about the water pump and plant parameters.



## Operation
### Device
  The system is user-friendly and can operate with minimal user intervention for a limited period of time, determined by the capacity of the water container in use and, in the event of a power outage, the capacity and charge level of the battery. To ensure proper operation of the system, make sure all parts are correctly connected. Then, insert the soil moisture sensor and the silicone tube from the pump into the soil in the plant pot, and immerse the pump itself in the water container for plant watering. Directly above the water container, mount the distance sensor. Position the light intensity sensor to monitor sunlight without obstructions (avoid placing it under objects that may block light access, e.g., under a windowsill). To access the web application for remote control of the device and to receive email notifications, prepare a device that provides internet connectivity via Wi-Fi. Fill in the network name, password, and email address details in the program code. Then, plug the device into the power source and the battery basket. If everything is correctly connected, the LCD display will light up, showing the internet connection status and IP address, which should be entered in a web browser, along with the current parameters. An email notification will be sent about the device activation, followed by periodic notifications with current parameters or notifications of the water pump activation.

### Web Application
  The web application allows users to control the device and monitor its current status from any web browser. This function requires the device to be connected to the same Wi-Fi network as the microcontroller. The address is the device's IP address, displayed on the LCD screen during startup. The application allows users to enable or disable the "away mode," which sends email notifications about the plant's current status. Users can also set the notification frequency. Another function is the ability to manually turn the water pump on and off. To switch to manual water pump control, set the minimum humidity level to 0. The application displays sensor parameters in real-time. A slider is implemented to set the minimum soil humidity level at which the watering module is activated.

