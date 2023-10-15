#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <base64.h>

#define DATAPOINTS_PER_PACKAGE = 2
#define CONNECT_TRY_NUMBER = 10

//Importante no olvidar el '?' al final de la URL
#define URL_DATABASE "https://script.google.com/macros/s/AKfycbzT5snLwYcNbzv7GKdCBhrUBQ7yeD2EwnD5eYamqAOYxCa5uiCmZp9o31fWzZfXis_W3w/exec?"
                   //"https://script.google.com/macros/s/AKfycbzT5snLwYcNbzv7GKdCBhrUBQ7yeD2EwnD5eYamqAOYxCa5uiCmZp9o31fWzZfXis_W3w/exec"   

const char* ssid = "CREA_Hacklab";
const char* password = "CREA_Hacklab21";

unsigned long t_0 = millis();

unsigned int currentDataPoint = 1;
String dataString = "";

bool wifiInit()
{
  WiFi.begin(ssid, password);

  for(int i = 0; i < CONNECT_TRY_NUMBER; i++)
  {
    if(WiFi.status() == WL_CONNECTED)
    {
        Serial.println("Conectado");
        return true;
    }
    delay(500);
    Serial.println("Conectando a WiFi... "); //Serial.println(WiFi.status());
  }
  return false;
}

void enviarStringDeDatos(String datos)
{
  if(millis() < t_0 + 10000){
    Serial.println("Skipeando envío de datos");
    return;
  }

  if(!wifiInit()){
      return;
  }

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
        dataString = "";
        currentDataPoint = 1;
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
  WiFi.disconnect();
}

void addData(byte ID, String fecha,float temperatura, unsigned int presion, unsigned int pm1, unsigned int pm2, unsigned int pm4, unsigned int pm10, unsigned int co, unsigned int lpg, unsigned int ch4, unsigned int oh, unsigned int c6h6, unsigned int h2, float ruido, float luz){
  dataString += "id_";
  dataString += String(currentDataPoint);
  dataString += "=";
  dataString += String(ID);

  dataString += "&fecha_";
  dataString += String(currentDataPoint);
  dataString += "=";
  dataString += String(base64::encode(fecha));

  dataString += "&temperatura_";
  dataString += String(currentDataPoint);
  dataString += "=";
  dataString += String(temperatura);

  dataString += "&presion_";
  dataString += String(currentDataPoint);
  dataString += "=";
  dataString += String(presion);

  dataString += "&pm1_";
  dataString += String(currentDataPoint);
  dataString += "=";
  dataString += String(pm1);

  dataString += "&pm2_";
  dataString += String(currentDataPoint);
  dataString += "=";
  dataString += String(pm2);

  dataString += "&pm4_";
  dataString += String(currentDataPoint);
  dataString += "=";
  dataString += String(pm4);

  dataString += "&pm10";
  dataString += String(currentDataPoint);
  dataString += "=";
  dataString += String(pm10);

  dataString += "&co_";
  dataString += String(currentDataPoint);
  dataString += "=";
  dataString += String(co);

  dataString += "&lpg_";
  dataString += String(currentDataPoint);
  dataString += "=";
  dataString += String(lpg);

  dataString += "&ch4_";
  dataString += String(currentDataPoint);
  dataString += "=";
  dataString += String(ch4);

  dataString += "&oh_";
  dataString += String(currentDataPoint);
  dataString += "=";
  dataString += String(oh);

  dataString += "&c6h6_";
  dataString += String(currentDataPoint);
  dataString += "=";
  dataString += String(c6h6);

  dataString += "&h2_";
  dataString += String(currentDataPoint);
  dataString += "=";
  dataString += String(h2);

  dataString += "&ruido_";
  dataString += String(currentDataPoint);
  dataString += "=";
  dataString += String(ruido);

  dataString += "&luz_";
  dataString += String(currentDataPoint);
  dataString += "=";
  dataString += String(luz);

  if(currentDataPoint >= DATAPOINTS_PER_PACKAGE){
    enviarStringDeDatos(dataString); 
  }
  currentDataPoint++;
}
