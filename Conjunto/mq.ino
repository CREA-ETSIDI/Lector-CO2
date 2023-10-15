//definicion de donde se conectan
#define pin_MQ2 26
#define pin_MQ3 33
#define pin_MQ4 35
//#define pin_MQ5 A3
//#define pin_MQ6 35
#define pin_MQ7 35
#define pin_MQ8 34
#define pin_MQ9 25
//#define pin_MQ135 A8


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
//MQ6 mq6;
MQ7 mq7;
MQ8 mq8;
MQ9 mq9;
//MQ135 mq135;

void mqSetup(){
  pinMode(27, OUTPUT);
  pinMode(14, OUTPUT);
  
  digitalWrite(27,HIGH);
  digitalWrite(14,HIGH);
  
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
//  Serial.print("Calibrando el sensor MQ6 ");
//  RC_MQ6 = mq6.CalibracionMQ(pin_MQ6);
//  Serial.println(RC_MQ6);
  //
  Serial.print("Calibrando el sensor MQ7 ");
  RC_MQ7 = mq7.CalibracionMQ(pin_MQ7);
  Serial.println(RC_MQ7);
  //
  Serial.print("Calibrando el sensor MQ8 ");
  RC_MQ8 = mq8.CalibracionMQ(pin_MQ8);
  Serial.println(RC_MQ8);
  //
  Serial.print("Calibrando el sensor MQ9 ");
  RC_MQ9 = mq9.CalibracionMQ(pin_MQ9);
  Serial.println(RC_MQ9);
    //
//  Serial.print("Calibrando el sensor MQ135");
//  RC_MQ135 = mq135.CalibracionMQ(pin_MQ135);
//  Serial.println(RC_MQ135);
}

//-------------------------------------------------

float MQ::CalculoRMQ(int val) { //calculo de las resistencia del sensor
  return (((float)R * (1023 - val) / val));
}

float MQ::CalibracionMQ (int pin) { //funcion que calibra los MQ
  float valor = 0;
  for (int i = 0; i < MRPC; i++) { // toma una serie de medidas previas para ver si se está calibrando o no
    valor += CalculoRMQ(analogRead(pin)/6.06);
    delay(50);
  }
  valor = valor / MRPC;
  valor = valor / RAL;

  return valor;
}

float MQ::LecturaMQ(int pin) {
  float valor = 0;
  for (int i = 0; i < MRPC; i++) {
    #ifdef _ARDUINO_
    valor += CalculoRMQ(analogRead(pin));
    #else
    valor += CalculoRMQ(analogRead(pin)/6.06);
    #endif
    delay(50);
  }
  valor = valor / MRPC;
  Serial.print("Lectura analogica media: "); Serial.println(valor);
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

//D14 ON
//D27 ON
float get_CO(){
  float mq2_co = 0;//mq2.PorcentajeMQ(mq2.LecturaMQ(pin_MQ2) / RC_MQ2, mq2.GAS_CO);
  float mq7_co = mq7.PorcentajeMQ(mq7.LecturaMQ(pin_MQ7) / RC_MQ7, mq7.GAS_CO);
  float mq9_co = 0;//mq9.PorcentajeMQ(mq9.LecturaMQ(pin_MQ9) / RC_MQ9, mq9.GAS_CO);

  return (mq2_co+mq7_co+mq9_co)/3.0;
}

//D14 ON
//D27 ON
float get_LPG(){
  float mq2_LPG = 0;//mq2.PorcentajeMQ(mq2.LecturaMQ(pin_MQ2) / RC_MQ2, mq2.GAS_LPG);
  float mq4_LPG = mq4.PorcentajeMQ(mq4.LecturaMQ(pin_MQ4) / RC_MQ4, mq4.GAS_LPG);
  //float mq6_LPG = mq6.PorcentajeMQ(mq6.LecturaMQ(pin_MQ6) / RC_MQ6, mq6.GAS_LPG);
  float mq9_LPG = 0;//mq9.PorcentajeMQ(mq9.LecturaMQ(pin_MQ9) / RC_MQ9, mq9.GAS_LPG);

  return (mq2_LPG + mq4_LPG + mq9_LPG)/3.0; 
}

//D14 ON
//D27 ON
float get_CH4(){
  float mq2_CH4 = 0;//mq2.PorcentajeMQ(mq2.LecturaMQ(pin_MQ2) / RC_MQ2, mq2.GAS_CH4);
  float mq4_CH4 = mq4.PorcentajeMQ(mq4.LecturaMQ(pin_MQ4) / RC_MQ4, mq4.GAS_CH4);
  //float mq6_CH4 = mq6.PorcentajeMQ(mq6.LecturaMQ(pin_MQ6) / RC_MQ6, mq6.GAS_CH4);
  float mq9_CH4 = 0;//mq9.PorcentajeMQ(mq9.LecturaMQ(pin_MQ9) / RC_MQ9, mq9.GAS_CH4);

  return (mq2_CH4 + mq4_CH4 + mq9_CH4)/3.0;
}

//D27 ON
float get_OH(){
  float mq3_OH = mq3.PorcentajeMQ(mq3.LecturaMQ(pin_MQ3) / RC_MQ3, mq3.GAS_OH);

  return (mq3_OH)/1.0;
}

//D27 ON
float get_C6H6(){
  float mq3_C6H6 = mq3.PorcentajeMQ(mq3.LecturaMQ(pin_MQ3) / RC_MQ3, mq3.GAS_C6H6);

  return (mq3_C6H6)/1.0;
}

//D14 ON
float get_H2(){
  float mq4_H2 = mq4.PorcentajeMQ(mq4.LecturaMQ(pin_MQ4) / RC_MQ4, mq4.GAS_H2);
  //float mq6_H2 = mq6.PorcentajeMQ(mq6.LecturaMQ(pin_MQ6) / RC_MQ6, mq6.GAS_H2);
  float mq8_H2 = mq8.PorcentajeMQ(mq8.LecturaMQ(pin_MQ8) / RC_MQ8, mq8.GAS_H2);

  return mq8_H2;
}
