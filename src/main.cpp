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

//VARIABLES NEXTION
String restan = "Restan";
int CantidadMov1 = 0;
int CantidadMov2 = 0;
int CantidadMov3 = 0;

NexPage INICIO    = NexPage(0, 0, "INICIO");
NexPage CALIBRANDO    = NexPage(1, 0, "CALIBRANDO");
NexPage MOVIENDO    = NexPage(2, 0, "MOVIENDO");

NexSlider SliderMov1 = NexSlider(0, 3, "SliderMov1"); //Page , ID, ObjName
NexSlider SliderMov2 = NexSlider(0, 4, "SliderMov2"); //Page , ID, ObjName
NexSlider SliderMov3 = NexSlider(0, 5, "SliderMov3"); //Page , ID, ObjName

NexText txtMov1 = NexText(0, 6, "txtMov1");
NexText txtMov2 = NexText(0, 7, "txtMov2");
NexText txtMov3 = NexText(0, 8, "txtMov3");

NexButton btnIniciar = NexButton(0, 2, "btnIniciar");

NexButton CheckMov1 = NexButton(2, 3, "CheckMov1");
NexButton CheckMov2 = NexButton(2, 4, "CheckMov2");
NexButton CheckMov3 = NexButton(2, 5, "CheckMov3");

NexText Mov1EnCurso = NexText(2, 6, "Mov1EnCurso");
NexText Mov2EnCurso = NexText(2, 7, "Mov2EnCurso");
NexText Mov3EnCurso = NexText(2, 8, "Mov3EnCurso");

NexButton btnComenzar = NexButton(2, 2, "btnComenzar");
NexButton btnRegresar = NexButton(2, 9, "btnRegresar");

NexTouch *nex_listen_list[] = 
{
    &INICIO,&CALIBRANDO,&MOVIENDO,//Paginas
    &SliderMov1,&SliderMov2,&SliderMov3,&btnIniciar,//Elementos PAGE 0
    &CheckMov1,&CheckMov2,&CheckMov3,&Mov1EnCurso,&Mov2EnCurso,//Elementos PAGE 2
    &Mov3EnCurso,&btnComenzar,&btnRegresar, //Elementos PAGE 2
    NULL
};

void SliderMov1PopCallback(void *ptr)
{
    uint32_t number = 0;
    char temp[10] = {0};
    SliderMov1.getValue(&number);
    utoa(number, temp, 10);
    txtMov1.setText(temp);
    CantidadMov1 = number;
}

void SliderMov2PopCallback(void *ptr)
{
    uint32_t number = 0;
    char temp[10] = {0};
    SliderMov2.getValue(&number);
    utoa(number, temp, 10);
    txtMov2.setText(temp);
    CantidadMov2 = number;
}

void SliderMov3PopCallback(void *ptr)
{
    uint32_t number = 0;
    char temp[10] = {0};
    SliderMov3.getValue(&number);
    utoa(number, temp, 10);
    txtMov3.setText(temp);
    CantidadMov3 = number;
}

void btnIniciarPopCallback(void *ptr)
{
    // CALIBRANDO.show();
     MOVIENDO.show();
    sendMovimientosToNextion();
   
}

void btnComenzarPopCallback(void *ptr)
{
    //En¨Progreso
}

void btnRegresarPopCallback(void *ptr)
{
    //En¨Progreso
}
void setup()
{
//Inicializar NEXTION
nexInit();
SliderMov1.attachPop(SliderMov1PopCallback, &SliderMov1);
SliderMov2.attachPop(SliderMov2PopCallback, &SliderMov2);
SliderMov3.attachPop(SliderMov3PopCallback, &SliderMov3);
btnIniciar.attachPop(btnIniciarPopCallback, &btnIniciar);
btnRegresar.attachPop(btnRegresarPopCallback, &btnRegresar);
btnComenzar.attachPop(btnComenzarPopCallback, &btnComenzar);
  
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

void sendMovimientosToNextion()
{
 String command = "Mov1EnCurso.txt=\""+restan+" "+String(CantidadMov1)+"\"";
  Serial.print(command);
  endNextionCommand();
}

void endNextionCommand()
{
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);
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