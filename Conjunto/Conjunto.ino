#include <Wire.h>
#include "RTClib.h"
#include <SensirionCore.h>
#include <Arduino.h>
#include <SensirionI2CSen5x.h>
#include <Wire.h>
#include <Adafruit_BMP280.h>

RTC_DS3231 rtc;
DateTime now = rtc.now();

Adafruit_BMP280 bmp;

void setup(){
  Serial.begin(115200);

  Serial.println("Iniciado");
  
  mqSetup();
  rtcSetup();
  sen50Setup();

  Serial.println("Fin del Setup");
}

void loop(){
  Serial.println("Inicio del loop");
  //RTC
  Serial.println("");Serial.println("RTC");
  now = rtc.now();
  Serial.print(now.day()); Serial.print(" "); Serial.print(now.hour()); Serial.print(" "); Serial.print(now.minute()); Serial.print(" "); Serial.println(now.second());

  //BMP280
  Serial.println("");Serial.println("RTC");
  Serial.print("Temperatura: "); Serial.println(bmp.readTemperature());
  Serial.print("Presión: "); Serial.println(bmp.readPressure());
  
  //MQs
  Serial.println("");Serial.println("MQs");
  Serial.print("CO: "); Serial.println(get_CO());
  Serial.print("LPG: "); Serial.println(get_LPG());
  Serial.print("CH4: "); Serial.println(get_CH4());
  Serial.print("OH: "); Serial.println(get_OH());
  Serial.print("C6H6: "); Serial.println(get_C6H6());
  Serial.print("H2: "); Serial.println(get_H2());

  //Sen50
  Serial.println("");Serial.println("sen50");
  Serial.print("PM 10: "); Serial.println(get_Pm10p0());
  Serial.print("PM 4: "); Serial.println(get_Pm4p0());
  Serial.print("PM 2.5: "); Serial.println(get_Pm2p5());
  Serial.print("PM 1: "); Serial.println(get_Pm1p0());

  delay(2000);
}
