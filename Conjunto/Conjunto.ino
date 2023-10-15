#include <Wire.h>
#include <SensirionCore.h>
#include <Arduino.h>
#include <SensirionI2CSen5x.h>
#include <Wire.h>
#include <Adafruit_BMP280.h>
#include <RTClib.h>
#include "Conexion.hpp"
#include <base64.h>

Adafruit_BMP280 bmp;

RTC_DS3231 rtc;
DateTime now;

void setup(){
  Serial.begin(115200);

  Serial.println("Iniciado");

  Serial.println("Iniciando RTC:");
  rtcSetup();
  Serial.println("RTC Iniciado");

  Serial.println();
  Serial.println("Iniciando BMP:");
  bmp280Setup();
  Serial.println("BMP Iniciado");

  Serial.println("Iniciando MQs");
  mqSetup();
  Serial.println("MQs Iniciados");

  Serial.println();
  Serial.println("Iniciando Sen50");
  sen50Setup();
  Serial.println("Sen50 Iniciado");

  Serial.println();
  //Serial.println("Iniciando WiFi:");
  //wifiInit();
  //Serial.println("WiFi Iniciado");

  Serial.println("Fin del Setup");
}

void loop(){
  Serial.println("Inicio del loop");

  //RTC
  DateTime now = rtc.now();
  Serial.println("");Serial.println("RTC");
  Serial.print(now.day()); Serial.print(" - "); Serial.print(now.hour()); Serial.print(":"); Serial.print(now.minute()); Serial.print(":"); Serial.println(now.second());
  Serial.println(getTimeString());
  
  //BMP280
  Serial.println("");Serial.println("BMP");
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

  //Microfono
  Serial.println(""); Serial.println("Micro");
  Serial.print("Ruido: "); Serial.println(get_Ruido());

  //Luz
  Serial.println(""); Serial.println("Luz");
  Serial.print("Lux: "); Serial.print(get_Lux()); Serial.println(" lux");

  addData(1, getTimeString(), bmp.readTemperature(), bmp.readPressure(), get_Pm1p0(), get_Pm2p5(), get_Pm4p0(), get_Pm10p0(), get_CO(), get_LPG(), get_CH4(), get_OH(), get_C6H6(), get_H2(), ruido(), get_Lux());
  //delay(30000);
}
