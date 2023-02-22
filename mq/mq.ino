//todos los #define de la parte de mq se va a meter después en un constructor (o como se llame)
//definicion de donde se conectan
#define MQ2 A0
//#define MQ3 A1
//#define MQ4 A2
//#define MQ5 A3
//#define MQ6 A4
//#define MQ7 A5
//#define MQ8 A6
//#define MQ9 A7
//#define MQ135 A8

//Expresada en KiloOhmios
#define R2 10
//#define R3 10
//#define R4 10
//#define R5 10
//#define R6 10
//#define R7 10
//#define R8 10
//#define R9 10
//#define R135 10

//nombre de los gases que puede captar el sensor
#define GAS_LPG 0
#define GAS_CO 1

float LPGCurva[3] = {2.3, 0.21, -0.47};
float COCurva[3] = {1, 1, 1};

//variables randoms
#define MRPC 10 //muestras recogidas para la calibración
#define RAL 9.83 //resistencia del sensor en el aire limpio 

//Expresada en KiloOhmios (RESULTADOS DE CALIBRACIÓN)
float RC_MQ2 = 10;
//float RC_MQ3 = 10;
//float RC_MQ4 = 10;
//float RC_MQ5 = 10;
//float RC_MQ6 = 10;
//float RC_MQ7 = 10;
//float RC_MQ8 = 10;
//float RC_MQ9 = 10;
//float RC_MQ135 = 10;

String readString;

void setup() {
  Serial.begin(9600);
  //calibración de MQ (todos en teoría, habría q ir poniendolos para que fueran saliendo-pero not yet-)
  Serial.println("Calibrando el sensor MQ2 "); 
  RC_MQ2 = CalibracionMQ(MQ2);
  Serial.println(RC_MQ2);
 /* RC_MQ3 = CalibracionMQ(MQ3);
  RC_MQ4 = CalibracionMQ(MQ4);
  RC_MQ5 = CalibracionMQ(MQ5);
  RC_MQ6 = CalibracionMQ(MQ6);
  RC_MQ7 = CalibracionMQ(MQ7);
  RC_MQ8 = CalibracionMQ(MQ8);
  RC_MQ9 = CalibracionMQ(MQ9);*/
//  Resultados_Calibracion_MQ135 = CalibracionMQ(MQ135);
}

void loop() {
  while (Serial.available()) {
    delay(2);
    char c = Serial.read();
    readString += c;
    readString.toLowerCase();
    readString.trim();
  }
  if (readString == "lpg")
    Serial.println(PorcentajeMQ(LecturaMQ(MQ2) / RC_MQ2, GAS_LPG) );
//  else if (readString == "co")
//    Serial.println(PorcentajeMQ(LecturaMQ(MQ2) / RC_MQ2, GAS_CO) );
//  readString = "";
}

float CalculoRMQ(int val) { //calculo de las resistencia del sensor
  return (((float)R2 * (1023 - val) / val));
}

float CalibracionMQ (int pin) { //funcion que calibra los MQ
  float valor = 0;
  for (int i = 0; i < MRPC; i++) { // toma una serie de medidas previas para ver si se está calibrando o no
    valor += CalculoRMQ(analogRead(pin));
    delay(50);
  }
  valor = valor / MRPC;
  valor = valor / RAL;

  return valor;
}

float LecturaMQ(int pin) {
  float valor = 0;
  for (int i = 0; i < MRPC; i++) { // toma una serie de medidas previas para ver si se está calibrando o no
    valor += CalculoRMQ(analogRead(pin));
    delay(50);
  }
  valor = valor / MRPC;
  return valor;
}
int PorcentajeMQ(float ratio, int id) { //para identificar el tipo de gas
  if (id = GAS_LPG) {
    return GetPorcentajeMQ(ratio, LPGCurva);
  }
  if (id == GAS_CO) {
    return GetPorcentajeMQ(ratio, COCurva);
  }

  return 0;
}
int GetPorcentajeMQ(float ratio, float *curva) {
  return (pow(10, (((log(ratio) - curva[1]) / curva[2]) + curva[0])));
}
