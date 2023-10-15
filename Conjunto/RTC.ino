void rtcSetup(){
  while (!rtc.begin()) {
    Serial.println(F("No se encontró RTC"));
    //while (1);
    break;
  }
  
  if (rtc.lostPower()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  else {
    Serial.println("Iniciado correctamente");
  }
}

String getTimeString(){
  DateTime now = rtc.now();
  Serial.print(now.day()); Serial.print(" - "); Serial.print(now.hour()); Serial.print(":"); Serial.print(now.minute()); Serial.print(":"); Serial.println(now.second());

  String fecha = String(now.year()) + "/" + numberPad(now.month()) + "/" + numberPad(now.day()) + " " + numberPad(now.hour()) + ":" + numberPad(now.minute()) + ":" + numberPad(now.second());

  return fecha;
}

String numberPad(int number){
  if(number < 10){
    return "0" + String(number);
  }
  else{
    return String(number);
  }
}
