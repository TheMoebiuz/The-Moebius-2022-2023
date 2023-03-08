#include <SoftwareSerial.h>  //añadimos la libreria software serial para controlar el modulo bluetooth
SoftwareSerial bt(7, 8);

#define led1 3  //definimos los leds
#define led2 5
#define led3 6
#define led4 9
#define led5 10
#define led6 11


String lecparcial; //lectura parcial (las primeras lecturas que se hacen)
String lecfinal;   //lectura final (la lectura final de toda la cadena)
String piso;  //piso (basicamente el led que se tiene que activar)
String valor;  //valor led (que valor por PWM ma a adquirir el led)

char lec1byte; //Primera lectura que se ejecuta y que por cuestiones de el modulo bluetooth solo mide un byte

void setup() {
  bt.begin(9600); //inicializamos bt
  Serial.begin(9600); //inicializamos el puerto serial
  Serial.println("Comfandi Miraflores, The Moebius 2022-2023");  //...
  Serial.println("Version de codigo 1.1");

  pinMode(led1, OUTPUT); //inicializamos los leds
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);
}

void loop() {
  if (bt.available()) {  //if que se ejecuta si hay nuevos datos en el puerto serial
    lec1byte = bt.read();  //tengo que explicar esto?
    lecparcial = "";  //limpiamos todas las variables que van a ser utilizadas despues...
    lecfinal = "";
    piso = "";
    valor = "";

    while (lec1byte != 'f') { //while que se ejecuta mientras la lectura del puerto serial no sea "f"
      lec1byte = bt.read(); //actualizamos la variable que si no se traba
      lecparcial = lecparcial + String(lec1byte); //convertimos la lectura char en String y la vamos sumando para armar la cadena completa (mucho texto)
      //    Serial.println(lecparcial);  //depuracion no mas...
    }

    lecfinal = lecparcial;  //cuando ya se finalizo la cadena se le asigna el valor de dicha cadena a lecfinal
    //Serial.println(lecfinal); //depuracion...

    piso = lecfinal.substring(1, lecfinal.indexOf("."));  //sacamos un subtring para hayar piso
    //Serial.println(piso); //...

    valor = lecfinal.substring(lecfinal.indexOf(".") + 1, lecfinal.indexOf("f")); //otro substring para valor
    //Serial.println(valor); //._.

    switch (piso.toInt()) { //un switch para ejecutar los comandos en los leds y no voy a explicar nada mas
      case 1:
        analogWrite(led1, valor.toInt());
      //  Serial.println("led1");
        break;

      case 2:
        analogWrite(led2, valor.toInt());
        //Serial.println("led2");
        break;

      case 3:
        analogWrite(led3, valor.toInt());
        //Serial.println("led3");
        break;

      case 4:
        analogWrite(led4, valor.toInt());
        //Serial.println("led4");
        break;
    }
    //Serial.println(""); //para mejorar la depur...
  }
}
