#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>

//Importante no olvidar el '?' al final de la URL
#define URL_DATABASE "https://script.google.com/macros/s/AKfycbzT5snLwYcNbzv7GKdCBhrUBQ7yeD2EwnD5eYamqAOYxCa5uiCmZp9o31fWzZfXis_W3w/exec?"

const char* ssid = "CREA_Hacklab";
const char* password = "CREA_Hacklab21";

void wifiInit(){
  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.println("Conectando a WiFi... "); //Serial.println(WiFi.status());
  }
  Serial.println("Conectado");
}

void enviarStringDeDatos(String datos)
{
  HTTPClient http;
  WiFiClientSecure client;

  client.setInsecure();

  String url = URL_DATABASE + datos;

  if (http.begin(client, url)) //Iniciar conexión
  {
    Serial.print("[HTTP] GET...\n");
    int httpCode = http.GET();  // Realizar petición

    if (httpCode > 0) {
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);

      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
        String payload = http.getString();  // Obtener respuesta
        Serial.println(payload);  // Mostrar respuesta por serial
      }
    }
    else {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  }
  else {
    Serial.printf("[HTTP} Unable to connect\n");
  }

  delay(30000);
}
