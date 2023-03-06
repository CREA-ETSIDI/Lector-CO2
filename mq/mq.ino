//todos los #define de la parte de mq se va a meter después en un constructor (o como se llame)
//definicion de donde se conectan
#define pin_MQ2 A0
//#define MQ3 A1
//#define MQ4 A2
//#define MQ5 A3
//#define MQ6 A4
//#define MQ7 A5
//#define MQ8 A6
//#define MQ9 A7
//#define MQ135 A8


//Expresada en KiloOhmios (RESULTADOS DE CALIBRACIÓN)
float RC_MQ2 = 10;
//float RC_MQ3 = 10;
//float RC_MQ4 = 10;
//float RC_MQ5 = 10;
//float RC_MQ8 = 10;
//float RC_MQ9 = 10;
//float RC_MQ6 = 10;
//float RC_MQ7 = 10;
//float RC_MQ135 = 10;

class MQ{
  public:
  //Expresada en KiloOhmios
    float R;
    //variables randoms
    float MRPC; //muestras recogidas para la calibración
    float RAL; //resistencia del sensor en el aire limpio 
    
    MQ():R(10), MRPC(10), RAL(9.83){};
    
    //funciones
    float CalculoRMQ(int val);
    float CalibracionMQ (int pin);
    float LecturaMQ(int pin);
    virtual int PorcentajeMQ(float ratio, int id);
    int GetPorcentajeMQ(float ratio, float *curva);
  };
  
class MQ2:public MQ{     //mq2: lpg, CO, CH4
  public:
  //curvas
    float LPGCurva[3] = {2.3, 0.21, -0.47};
    float COCurva[3] = {2.3, 0.71, -0.28};
    float CH4Curva[3] = {2.3, 0.477, -0.41};
    enum GASES {GAS_LPG=0, GAS_CO, GAS_CH4};
    MQ2():MQ(){};
    
    //funciones
    int PorcentajeMQ(float ratio, int id);
  };
  
String readString;
MQ2 mq;

void setup() {
  Serial.begin(9600);
  //calibración de MQ (todos en teoría, habría q ir poniendolos para que fueran saliendo-pero not yet-)
  Serial.print("Calibrando el sensor MQ2 ");
  RC_MQ2 = mq.CalibracionMQ(pin_MQ2);
  Serial.println(RC_MQ2);
  /* RC_MQ3 = CalibracionMQ(MQ3);
    RC_MQ4 = CalibracionMQ(MQ4);
    RC_MQ5 = CalibracionMQ(MQ5);
    RC_MQ6 = CalibracionMQ(MQ6);
    RC_MQ7 = CalibracionMQ(MQ7);
    RC_MQ8 = CalibracionMQ(MQ8);
    RC_MQ9 = CalibracionMQ(MQ9);
    RC_MQ135 = CalibracionMQ(MQ135);*/
}

void loop() {
  //  while (Serial.available()) {
  //    delay(2);
  //    char c = Serial.read();
  //    readString += c;
  //    readString.toLowerCase();
  //    readString.trim();
  //  }
  Serial.print("LPG:");
  Serial.println(mq.PorcentajeMQ(mq.LecturaMQ(pin_MQ2) / RC_MQ2, mq.GAS_LPG) );
  Serial.print("CO:");
  Serial.println(mq.PorcentajeMQ(mq.LecturaMQ(pin_MQ2) / RC_MQ2, mq.GAS_CO) );
  Serial.print("CH4:");
  Serial.println(mq.PorcentajeMQ(mq.LecturaMQ(pin_MQ2) / RC_MQ2, mq.GAS_CH4) );
  readString = "";
}

float MQ::CalculoRMQ(int val) { //calculo de las resistencia del sensor
  return (((float)R * (1023 - val) / val));
}

float MQ::CalibracionMQ (int pin) { //funcion que calibra los MQ
  float valor = 0;
  for (int i = 0; i < MRPC; i++) { // toma una serie de medidas previas para ver si se está calibrando o no
    valor += CalculoRMQ(analogRead(pin));
    delay(50);
  }
  valor = valor / MRPC;
  valor = valor / RAL;

  return valor;
}

float MQ::LecturaMQ(int pin) {
  float valor = 0;
  for (int i = 0; i < MRPC; i++) { // toma una serie de medidas previas para ver si se está calibrando o no
    valor += CalculoRMQ(analogRead(pin));
    delay(50);
  }
  valor = valor / MRPC;
  return valor;
}
int MQ::PorcentajeMQ(float ratio, int id) { //para identificar el tipo de gas
  
}
int MQ::GetPorcentajeMQ(float ratio, float *curva) {
  return (pow(10, (((log(ratio) - curva[1]) / curva[2]) + curva[0])));
}
//

int MQ2::PorcentajeMQ(float ratio, int id) { //para identificar el tipo de gas
  if (id == GAS_LPG) {
    return GetPorcentajeMQ(ratio, LPGCurva);
  }
  if (id == GAS_CO) {
    return GetPorcentajeMQ(ratio, COCurva);
  }
  if (id == GAS_CH4) {
    return GetPorcentajeMQ(ratio, CH4Curva);
  }
  return 0;
}
