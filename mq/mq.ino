
//definicion de donde se conectan
#define pin_MQ2 A0
#define pin_MQ3 A1
#define pin_MQ4 A2
#define pin_MQ5 A3
#define pin_MQ6 A4
#define pin_MQ7 A5
#define pin_MQ8 A6
#define pin_MQ9 A7
#define pin_MQ135 A8


//Expresada en KiloOhmios (RESULTADOS DE CALIBRACIÓN)
float RC_MQ2 = 10;
float RC_MQ3 = 10;
float RC_MQ4 = 10;
float RC_MQ5 = 10;
float RC_MQ8 = 10;
float RC_MQ9 = 10;
float RC_MQ6 = 10;
float RC_MQ7 = 10;
float RC_MQ135 = 10;

class MQ {
  public:
    //Expresada en KiloOhmios
    float R;
    //variables randoms
    float MRPC; //muestras recogidas para la calibración
    float RAL; //resistencia del sensor en el aire limpio

    MQ(): R(10), MRPC(10), RAL(9.83) {};

    //funciones
    float CalculoRMQ(int val);
    float CalibracionMQ (int pin);
    float LecturaMQ(int pin);
    virtual int PorcentajeMQ(float ratio, int id);
    int GetPorcentajeMQ(float ratio, float *curva);
};

class MQ2: public MQ {   //mq2: lpg, CO, CH4 //ESTE YA FUNCIONA
  public:
    //curvas
    float LPGCurva[3] = {2.3, 0.36, -0.47};
    float COCurva[3] = {2.3, 0.71, -0.28};
    float CH4Curva[3] = {2.3, 0.477, -0.41};
    enum GASES {GAS_LPG = 0, GAS_CO, GAS_CH4};
    MQ2(): MQ() {};

    //funciones
    int PorcentajeMQ(float ratio, int id);
};
class MQ3: public MQ {   //mq3: alcohol(OH), benceno(C6H6) //ESTE YA FUNCIONA (tal vez habria que calibrarlo un poco)
  public:
    //curvas
    float OHCurva[3] = { -1, 0.34, -0.56};
    float C6H6Curva[3] = { -1, 0.61, -0.33};
    enum GASES {GAS_OH = 0, GAS_C6H6};
    MQ3(): MQ() {};

    //funciones
    int PorcentajeMQ(float ratio, int id);
};
class MQ4: public MQ {   //mq4: lpg, metano, hidrogeno //ESTE YA FUNCIONA
  public:
    //curvas
    float LPGCurva[3] = {2.3, 0.43, -0.34};
    float CH4Curva[3] = {2.3, 0.255, -0.34};
    float H2Curva[3] = {2.3, 0.59, -0.19};
    enum GASES {GAS_LPG = 0, GAS_CH4, GAS_H2};
    MQ4(): MQ() {};

    //funciones
    int PorcentajeMQ(float ratio, int id);
};
//  class MQ5:public MQ{     //mq5:
//  public:
//  //curvas
//    float LPGCurva[3] = {2.3, 0.43, -0.72};
//    float CH4Curva[3] = {2.3, 0.477, -0.05};
//    float H2Curva[3] = {2.3, 0.71, -0.33};
//    enum GASES {GAS_LPG=0, GAS_CH4, GAS_H2};
//    MQ4():MQ(){};
//
//    //funciones
//    int PorcentajeMQ(float ratio, int id);
//  };
class MQ6: public MQ {   //mq6: lpg, metano, hidrogeno
  public:
    //curvas
    float LPGCurva[3] = {2.3, 0.3, -0.39};
    float CH4Curva[3] = {2.3, 0.176, -0.435};
    float H2Curva[3] = {2.3, 0.778, -0.2};
    enum GASES {GAS_LPG = 0, GAS_CH4, GAS_H2};
    MQ6(): MQ() {};

    //funciones
    int PorcentajeMQ(float ratio, int id);
};
class MQ7: public MQ {   //mq7: hidrogeno, co
  public:
    //curvas
    float H2Curva[3] = {1.69, 0.11, -0.124};
    float COCurva[3] = {1.69, 0.176, -0.6};
    enum GASES {GAS_H2 = 0, GAS_CO};
    MQ7(): MQ() {};

    //funciones
    int PorcentajeMQ(float ratio, int id);
};
class MQ8: public MQ {   //mq8: hidrogeno
  public:
    //curvas
    float H2Curva[3] = {2, -0.6, 0.648};
    enum GASES {GAS_H2 = 0};
    MQ8(): MQ() {};

    //funciones
    int PorcentajeMQ(float ratio, int id);
};
class MQ9: public MQ {   //mq9: co, lpg,ch4
  public:
    //curvas
    float COCurva[3] = {2.3,0.255, -1.117};
    float LPGCurva[3] = {2.3, 0.33, -0.64};
    float CH4Curva[3] = {2.3, 0.49, -0.455};
    enum GASES {GAS_CO = 0, GAS_LPG, GAS_CH4};
    MQ9(): MQ() {};

    //funciones
    int PorcentajeMQ(float ratio, int id);
};
//   class MQ135:public MQ{     //mq135:
//  public:
//  //curvas
//    float LPGCurva[3] = {2.3, 0.43, -0.72};
//    float CH4Curva[3] = {2.3, 0.477, -0.05};
//    float H2Curva[3] = {2.3, 0.71, -0.33};
//    enum GASES {GAS_LPG=0, GAS_CH4, GAS_H2};
//    MQ135():MQ(){};
//
//    //funciones
//    int PorcentajeMQ(float ratio, int id);
//  };
String readString;
MQ2 mq2;
MQ3 mq3;
MQ4 mq4;
//MQ5 mq5;
MQ6 mq6;
MQ7 mq7;
MQ8 mq8;
MQ9 mq9;
//MQ135 mq135;
void setup() {
  Serial.begin(9600);
  //calibración de MQ (todos en teoría, habría q ir poniendolos para que fueran saliendo-pero not yet-)
  Serial.print("Calibrando el sensor MQ2 ");
  RC_MQ2 = mq2.CalibracionMQ(pin_MQ2);
  Serial.println(RC_MQ2);
  //
  Serial.print("Calibrando el sensor MQ3 ");
  RC_MQ3 = mq3.CalibracionMQ(pin_MQ3);
  Serial.println(RC_MQ3);
  //
  Serial.print("Calibrando el sensor MQ4 ");
  RC_MQ4 = mq4.CalibracionMQ(pin_MQ4);
  Serial.println(RC_MQ4);
  //
//  Serial.print("Calibrando el sensor MQ5 ");
//  RC_MQ5 = mq5.CalibracionMQ(pin_MQ5);
//  Serial.println(RC_MQ5);
  //
  Serial.print("Calibrando el sensor MQ6 ");
  RC_MQ6 = mq6.CalibracionMQ(pin_MQ6);
  Serial.println(RC_MQ6);
  //
  Serial.print("Calibrando el sensor MQ7 ");
  RC_MQ7 = mq7.CalibracionMQ(pin_MQ7);
  Serial.println(RC_MQ7);
  //
  Serial.print("Calibrando el sensor MQ8");
  RC_MQ8 = mq8.CalibracionMQ(pin_MQ8);
  Serial.println(RC_MQ8);
  //
  Serial.print("Calibrando el sensor MQ9");
  RC_MQ9 = mq9.CalibracionMQ(pin_MQ9);
  Serial.println(RC_MQ9);
    //
//  Serial.print("Calibrando el sensor MQ135");
//  RC_MQ135 = mq135.CalibracionMQ(pin_MQ135);
//  Serial.println(RC_MQ135);
}

void loop() {
  Serial.print("LPG:");
  Serial.println(mq2.PorcentajeMQ(mq2.LecturaMQ(pin_MQ2) / RC_MQ2, mq2.GAS_LPG) );
  Serial.print("CO:");
  Serial.println(mq2.PorcentajeMQ(mq2.LecturaMQ(pin_MQ2) / RC_MQ2, mq2.GAS_CO) );
  Serial.print("CH4:");
  Serial.println(mq2.PorcentajeMQ(mq2.LecturaMQ(pin_MQ2) / RC_MQ2, mq2.GAS_CH4) );
  readString = "";
  //
  Serial.print("Alcohol:");
  Serial.println(mq3.PorcentajeMQ(mq3.LecturaMQ(pin_MQ3) / RC_MQ3, mq3.GAS_OH) );
  Serial.print("Benceno:");
  Serial.println(mq3.PorcentajeMQ(mq3.LecturaMQ(pin_MQ3) / RC_MQ3, mq3.GAS_C6H6) );
  readString = "";
  //
  Serial.print("LPG:");
  Serial.println(mq4.PorcentajeMQ(mq4.LecturaMQ(pin_MQ4) / RC_MQ4, mq4.GAS_LPG) );
  Serial.print("CH4:");
  Serial.println(mq4.PorcentajeMQ(mq4.LecturaMQ(pin_MQ4) / RC_MQ4, mq4.GAS_CH4) );
  Serial.print("H2:");
  Serial.println(mq4.PorcentajeMQ(mq4.LecturaMQ(pin_MQ4) / RC_MQ4, mq4.GAS_H2) );
  readString = "";
  //
   Serial.print("LPG:");
  Serial.println(mq6.PorcentajeMQ(mq6.LecturaMQ(pin_MQ6) / RC_MQ6, mq6.GAS_LPG) );
  Serial.print("CH4:");
  Serial.println(mq6.PorcentajeMQ(mq6.LecturaMQ(pin_MQ6) / RC_MQ6, mq6.GAS_CH4) );
  Serial.print("H2:");
  Serial.println(mq6.PorcentajeMQ(mq6.LecturaMQ(pin_MQ6) / RC_MQ6, mq6.GAS_H2) );
  readString = "";
  //
   Serial.print("H2:");
  Serial.println(mq7.PorcentajeMQ(mq7.LecturaMQ(pin_MQ7) / RC_MQ7, mq7.GAS_H2) );
  Serial.print("CO:");
  Serial.println(mq7.PorcentajeMQ(mq7.LecturaMQ(pin_MQ7) / RC_MQ7, mq7.GAS_CO) );
  readString = "";
  //
  Serial.print("H2:");
  Serial.println(mq8.PorcentajeMQ(mq8.LecturaMQ(pin_MQ8) / RC_MQ8, mq8.GAS_H2) );
  //
   Serial.print("CO:");
  Serial.println(mq9.PorcentajeMQ(mq9.LecturaMQ(pin_MQ9) / RC_MQ9, mq9.GAS_CO) );
  Serial.print("LPG:");
  Serial.println(mq9.PorcentajeMQ(mq9.LecturaMQ(pin_MQ9) / RC_MQ9, mq9.GAS_LPG) );
  Serial.print("CH4:");
  Serial.println(mq9.PorcentajeMQ(mq9.LecturaMQ(pin_MQ9) / RC_MQ9, mq9.GAS_CH4) );
  readString = "";
  //
  //
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
int MQ3::PorcentajeMQ(float ratio, int id) { //para identificar el tipo de gas
  if (id == GAS_OH) {
    return GetPorcentajeMQ(ratio, OHCurva);
  }
  if (id == GAS_C6H6) {
    return GetPorcentajeMQ(ratio, C6H6Curva);
  }
  return 0;
}
int MQ4::PorcentajeMQ(float ratio, int id) { //para identificar el tipo de gas
  if (id == GAS_LPG) {
    return GetPorcentajeMQ(ratio, LPGCurva);
  }
  if (id == GAS_CH4) {
    return GetPorcentajeMQ(ratio, CH4Curva);
  }
  if (id == GAS_H2) {
    return GetPorcentajeMQ(ratio, H2Curva);
  }
  return 0;
}
//int MQ5::PorcentajeMQ(float ratio, int id) { //para identificar el tipo de gas
//  if (id == GAS_LPG) {
//    return GetPorcentajeMQ(ratio, LPGCurva);
//  }
//  if (id == GAS_CH4) {
//    return GetPorcentajeMQ(ratio, CH4Curva);
//  }
//  if (id == GAS_H2) {
//    return GetPorcentajeMQ(ratio, H2Curva);
//  }
//  return 0;
//}
int MQ6::PorcentajeMQ(float ratio, int id) { //para identificar el tipo de gas
  if (id == GAS_LPG) {
    return GetPorcentajeMQ(ratio, LPGCurva);
  }
  if (id == GAS_CH4) {
    return GetPorcentajeMQ(ratio, CH4Curva);
  }
  if (id == GAS_H2) {
    return GetPorcentajeMQ(ratio, H2Curva);
  }
  return 0;
}
int MQ7::PorcentajeMQ(float ratio, int id) { //para identificar el tipo de gas
  if (id == GAS_H2) {
    return GetPorcentajeMQ(ratio, H2Curva);
  }
  if (id == GAS_CO) {
    return GetPorcentajeMQ(ratio, COCurva);
  }
  return 0;
}
int MQ8::PorcentajeMQ(float ratio, int id) { //para identificar el tipo de gas
  if (id == GAS_H2) {
    return GetPorcentajeMQ(ratio, H2Curva);
  }
  return 0;
}
int MQ9::PorcentajeMQ(float ratio, int id) { //para identificar el tipo de gas
  if (id == GAS_CO) {
    return GetPorcentajeMQ(ratio, COCurva);
  }
  if (id == GAS_LPG) {
    return GetPorcentajeMQ(ratio, LPGCurva);
  }
  if (id == GAS_CH4) {
    return GetPorcentajeMQ(ratio, CH4Curva);
  }
  return 0;
}
//int MQ135::PorcentajeMQ(float ratio, int id) { //para identificar el tipo de gas
//  if (id == GAS_LPG) {
//    return GetPorcentajeMQ(ratio, LPGCurva);
//  }
//  if (id == GAS_CH4) {
//    return GetPorcentajeMQ(ratio, CH4Curva);
//  }
//  if (id == GAS_H2) {
//    return GetPorcentajeMQ(ratio, H2Curva);
//  }
//  return 0;
//}
