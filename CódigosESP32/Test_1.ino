#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

const char* ssid = "Pbn&tjd";
const char* password = "D27082014@!";

float Latitud = 40.465524;
float Longitud = -3.710935;

void setup() {
  Serial.begin(115200);
  Serial.println("Hola");
  delay(4000);

  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.println("Conectando a WiFi... "); //Serial.println(WiFi.status());
  }
  Serial.println("Conectado");
}
 
void loop() {

  int CO2 = 400+(rand()%601);
  
  if(WiFi.status() == WL_CONNECTED){
    std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure);

    //client->setFingerprint(fingerprint);
    // Or, if you happy to ignore the SSL certificate, then use the following line instead:
    client->setInsecure();

    HTTPClient https;

    Serial.print("[HTTPS] begin...\n");
    String url = "https://script.google.com/macros/s/AKfycbxGEx6UgPYs6joar7DV3kFgF1pYdWNvCYmUJalvka5aTdzlrcH7phicRMFwpb4Xd2F4zA/exec?Latitud=" + String(Latitud) + "&Longitud=" + String(Longitud) + "&CO2=" + String(CO2);
    //https://script.google.com/macros/s/AKfycbxGEx6UgPYs6joar7DV3kFgF1pYdWNvCYmUJalvka5aTdzlrcH7phicRMFwpb4Xd2F4zA/exec?Latitud=60&Longitud=-3&CO2=453
    if (https.begin(*client, url)) {  // HTTPS

      Serial.print("[HTTPS] GET...\n");
      // start connection and send HTTP header
      int httpCode = https.GET();

      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTPS] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = https.getString();
          Serial.println(payload);
        }
      } else {
        Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
      }

      https.end();
    } else {
      Serial.printf("[HTTPS] Unable to connect\n");
    }
  }

  Serial.println("Wait 10s before next round...");
  delay(2000);
}
