#include "Message.h"

int sendInfo(String mail, float humidity, String lightLvl, float distanceCm) {

  String message = "<p>Informations:</p>";
  message = message + "<p>Humidity: ";
  message = message + String(humidity);
  message = message + "% </p>";
  message = message + "<p>Light level:";
  message = message + String(lightLvl);
  message = message + "</p>";
  message = message + "<p>Water level (cm from sensor): ";
  message = message + String(distanceCm);
  message = message + "cm";
  message = message + "</p>";

  Gsender *gsender = Gsender::Instance();  // Getting pointer to class instance
  gsender->Send(mail, message);
  return 0;
}

int sendInfoPump(String mail, String pumpState, float humidity) {

  String message = "<p>Informations:</p>";
  message = message + "<p>Pump state: ";
  message = message + String(pumpState);
  message = message + "</p>";
  message = message + "<p>Humidity:";
  message = message + String(humidity);
  message = message + "%";
  message = message + "</p>";

  Gsender *gsender = Gsender::Instance();  // Getting pointer to class instance
  gsender->Send(mail, message);
  return 0;
}
