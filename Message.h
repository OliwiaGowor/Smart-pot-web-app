#ifndef MESSAGE
#define MESSAGE

#include <string>
#include "Gsender.h"

using namespace std;
int sendInfo(String mail, float humidity, String lightLvl, float distanceCm);
int sendInfoPump(String mail, String pumpState, float humidity);

#endif
