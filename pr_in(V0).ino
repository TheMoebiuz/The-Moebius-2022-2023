#include <SoftwareSerial.h>
#define led1 4
#define led2 5

SoftwareSerial bt(10, 11);
char blu;
byte lec;
int bri;

void setup() {
  Serial.begin(9600);
  bt.begin(9600);
  Serial.println("ok");

  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);

  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
}

void loop() {
  blu = 0;
  lec = 0;
  if (bt.available()) {

    blu = bt.read();
    lec = String(blu).toInt();

    Serial.println(lec);

    if (lec == 1)//led 4
      digitalWrite(4, !digitalRead(4));

    if (lec == 2)// led 5
      digitalWrite(5, !digitalRead(5));

    //--------------------------------------------------------
    if (lec == 3) { //apaga todos los leds
      digitalWrite(4, LOW);
      digitalWrite(5, LOW);
    }
    //---------------------------------------------------------
    if (lec == 4) {  //lectura = 4 va subiendo el brilo de un led por PWM
      bri = bri + 10;

      if (bri > 255) //comprueba si el brillo es mayor de 255 y le aasigna el valor 255
        bri = 255;

      analogWrite(5, bri); // escribe en el led el brillo
    }
    //-----------------------------------------------------------
    if (lec == 5) { //le resta a brillo 10
      bri = bri - 10;

      if (bri < 0)
        bri = 0;

      analogWrite(5, bri);
      //---------------------------------------------------------
    }
    if (lec == 6) { //pone brillo a 0
      bri = 0;
      analogWrite(5, bri);
    }
  }
}
