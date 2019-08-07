#include <Arduino.h>
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
int comunicacionArdOutput = 7;
int comunicacionNexOutput = 8;
int relay1Output = 9;
int relay2Output = 10;
int relay3Output = 11;
int relay4Output = 12;
int sensorM2INPUT = A2;
int sensorM3INPUT = A3;

//NUEVO
//jaja
void setup()
{
Serial.begin(9600);

pinMode(LPWMPuenteHOutput, OUTPUT);
pinMode(RPWMPuenteHOutput, OUTPUT);
pinMode(comunicacionArdOutput, OUTPUT);
pinMode(comunicacionNexOutput, OUTPUT);
pinMode(relay1Output, OUTPUT);
pinMode(relay2Output, OUTPUT);
pinMode(relay3Output, OUTPUT);
pinMode(relay4Output, OUTPUT);
pinMode(sensorM2INPUT, INPUT);
pinMode(sensorM3INPUT, INPUT);


}

void loop()
{



}