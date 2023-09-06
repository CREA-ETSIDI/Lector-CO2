

void rtcSetup(){
  while (!rtc.begin()) {
      Serial.println(F("No se encontró RTC"));
      //while (1);
   }

   if (rtc.lostPower()) {
      rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
   }
   else {
     Serial.println("Iniciado correctamente");
   }
}
