
#include <Wire.h>
#include "RTClib.h"



// RTC_DS1307 rtc;
RTC_DS3231 rtc;

void setup() {
   Serial.begin(9600);
   delay(1000);
//
   if (!rtc.begin()) {
      Serial.println(F("No se encontró RTC"));
      while (1);
   }

   if (rtc.lostPower()) {
      rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
   }
   else {
     Serial.println("Iniciado correctamente");
   }
}
void loop () {
 DateTime now = rtc.now();
 
 Serial.print(now.day());
 Serial.print('/');
 Serial.print(now.month());
 Serial.print('/');
 Serial.print(now.year());
 Serial.print(" ");
 Serial.print(now.hour());
 Serial.print(':');
 Serial.print(now.minute());
 Serial.print(':');
 Serial.print(now.second());
 Serial.println();
 delay(3000);
}
