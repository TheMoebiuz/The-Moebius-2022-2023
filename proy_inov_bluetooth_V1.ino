#include <SoftwareSerial.h>
SoftwareSerial mBT (10, 11);

#define l201 4
#define l202 5

String lBT;
byte Cu;
String Pwms;
String ps;
int p;
int Pwm;

void setup() {
  Serial.begin(9600);
  Serial.println("ok");
  mBT.begin(9600);
  mBT.println("bt:ok");

  pinMode(l201, OUTPUT);
  pinMode(l202, OUTPUT);

}

void loop() {
  lBT = "0";
  Cu = 0;
  Pwm = 0;
  p = 0;

  if (mBT.available()) {
    Serial.println(mBT.read());
    lBT = mBT.read();
    if (lBT.length() == 1) {
      Cu = String(lBT).toInt();

      switch (Cu) {
        case 1:
          digitalWrite(l201, !digitalRead(l201));
          break;

        case 2:
          digitalWrite(l202, !digitalRead(l202));
          break;

        case 3:
          digitalWrite(l201, LOW);
          digitalWrite(l202, LOW);
          break;
      }
    }

    if (lBT.length() > 3) {
      ps = lBT.substring(1, 1);
      Pwms = lBT.substring(3);

      p = String(ps).toInt();
      p = String(Pwms).toInt();


      switch (p) {

        case 1:
          analogWrite(l201, Pwm);
          break;

        case 2:
          analogWrite(l202, Pwm);
          break;
      }
    }
  }
}
