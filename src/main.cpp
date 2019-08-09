#include <Arduino.h>
#include "Nextion.h"

////////////////////////////////////////////
////////////////////////////////////////////
////VARIABLES PARA NANO TWO (PRINCIPAL)//
// NANO PIN 5 - PUENTE H ONE - LPWM (D- MICRO USB)
// NANO PIN 6 - PUENTE H ONE - RPWM (D+ MICRO USB)
// NANO PIN 7 - CONEXION NANO UNO
// NANO PIN 8 - CONEXION NEXTION
// NANO PIN 9 - RELAY 1
// NANO PIN 10 - RELAY 2
// NANO PIN 11 - RELAY 3
// NANO PIN 12 - RELAY 4
// NANO PIN A2 - SENSOR M2 (D+ MICRO USB)
// NANO PIN A3 - SENSOR M3 (D+ MICRO USB)
// NANO PIN A4 (SDA) - SENSOR M1 (SDA)
// NANO PIN A5 (SCL) - SENSOR M1 (SCL)

//METODO PARA ENCENDER M1
//Orden = 1 OFF + 2 ON + 3 OFF + 4 OFF (VERIFICADO)

//METODO PARA ENCENDER M2
//Orden = 1 ON + 2 OFF + 3 OFF + 4 OFF (VERIFICADO)

//METODO PARA ENCENDER M3
//Orden = 1 OFF + 2 OFF + 3 ON + 4 ON (VERIFICADO)

int LPWMPuenteHOutput = 5;
int RPWMPuenteHOutput = 6;
int conexionArdOutput = 7;
int conexionNexOutput = 8;
int relay1Output = 9;
int relay2Output = 10;
int relay3Output = 11;
int relay4Output = 12;
int sensorM2INPUT = A2;
int sensorM3INPUT = A3;


NexSlider SliderMov1 = NexSlider(0, 3, "SliderMov1"); //Page , ID, ObjName
NexSlider SliderMov2 = NexSlider(0, 4, "SliderMov2"); //Page , ID, ObjName
NexSlider SliderMov3 = NexSlider(0, 5, "SliderMov3"); //Page , ID, ObjName
NexNumber txtMov1 = NexNumber(0, 6, "txtMov1");
NexNumber txtMov2 = NexNumber(0, 7, "txtMov2");
NexNumber txtMov3 = NexNumber(0, 8, "txtMov3");

NexTouch *nex_listen_list[] = 
{
    &SliderMov1,&SliderMov2,&SliderMov3,&txtMov1,&txtMov2,&txtMov3,
    NULL
};

void SliderMov1PopCallback(void *ptr)
{
    uint32_t number = 0;
    char temp[10] = {0};
    SliderMov1.getValue(&number);
    utoa(number, temp, 10);
    txtMov1.setText(temp);
}

void SliderMov2PopCallback(void *ptr)
{
    uint32_t number = 0;
    char temp[10] = {0};
    SliderMov2.getValue(&number);
    utoa(number, temp, 10);
    txtMov2.setText(temp);
}

void SliderMov3PopCallback(void *ptr)
{
    uint32_t number = 0;
    char temp[10] = {0};
    SliderMov3.getValue(&number);
    utoa(number, temp, 10);
    txtMov3.setText(temp);
}
void setup()
{

//
  
Serial.begin(9600);
pinMode(LPWMPuenteHOutput, OUTPUT);
pinMode(RPWMPuenteHOutput, OUTPUT);
pinMode(conexionArdOutput, OUTPUT);
pinMode(conexionNexOutput, OUTPUT);
pinMode(relay1Output, OUTPUT);
pinMode(relay2Output, OUTPUT);
pinMode(relay3Output, OUTPUT);
pinMode(relay4Output, OUTPUT);
pinMode(sensorM2INPUT, INPUT);
pinMode(sensorM3INPUT, INPUT);


}

void loop()
{

nexLoop(nex_listen_list);

}

void apagarMotores(){
    digitalWrite(relay1Output, LOW);
    digitalWrite(relay2Output, LOW);
    digitalWrite(relay3Output, LOW);
    digitalWrite(relay4Output, LOW);
    delay(100);
}

void metodoEncenderM1(){
//Orden = 1 OFF + 2 ON + 3 OFF + 4 OFF (VERIFICADO)
    apagarMotores();
    digitalWrite(relay1Output, LOW);
    digitalWrite(relay2Output, HIGH);
    digitalWrite(relay3Output, LOW);
    digitalWrite(relay4Output, LOW);

}

void metodoEncenderM2(){
//Orden = 1 ON + 2 OFF + 3 OFF + 4 OFF (VERIFICADO)
    apagarMotores();
    digitalWrite(relay1Output, HIGH);
    digitalWrite(relay2Output, LOW);
    digitalWrite(relay3Output, LOW);
    digitalWrite(relay4Output, LOW);

}

void metodoEncenderM3(){
//METODO PARA ENCENDER M3
//Orden = 1 OFF + 2 OFF + 3 ON + 4 ON (VERIFICADO)
    apagarMotores();
    digitalWrite(relay1Output, LOW);
    digitalWrite(relay2Output, LOW);
    digitalWrite(relay3Output, HIGH);
    digitalWrite(relay4Output, HIGH);
}



void comunicarArduinoToArduino(){
  digitalWrite(conexionNexOutput, LOW);
  delay(50);
  digitalWrite(conexionArdOutput, HIGH);

}

void comunicarArduinoToNextion(){
  digitalWrite(conexionArdOutput, LOW);
  delay(50);
  digitalWrite(conexionNexOutput, HIGH);

}