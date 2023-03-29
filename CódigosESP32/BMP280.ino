#include <Adafruit_BMP280.h>
#define SENSOR_T_P_ADDRESS (0x76) //BMP280 temperature and pressure sensor IC2 address
#define BAUD_RATE 9600
Adafruit_BMP280 sensor_T_P; //Temperature and pressure sensor, BMP280 (clone)

//reading temperature (ºC) ->  sensor_T_P.readTemperature();
//reading pressure (Pa)    ->  sensor_T_P.readPressure();

//Sets the default settings of the BMP280 settings
void setup_sensor_T_P()
{
  sensor_T_P.setSampling(MODE_NORMAL, SAMPLING_X16, SAMPLING_X16, FILTER_x16, STANDBY_MS_1);
}

//Return 0 if the sensor is not working, !0 if working
unsigned int status_sensor_T_P()
{
  sensor_T_P.begin(SENSOR_T_P_ADDRESS);
}

//Returns the IC2 address of the sensor
unsigned int address_sensor_T_P()
{
  sensor_T_P.sensorID();
}
