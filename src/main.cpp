#include <Arduino.h>
#include <SoftwareSerial.h>

#define lAZUL   5
#define lVERDE  6
#define lVERM   7
#define bREC    8

SoftwareSerial moduloSerial(2, 3); // RX, TX

int numLed = 0;
byte resposta;
//String resposta = "";

void setup() {

  Serial.begin(115200);
  moduloSerial.begin(38400);

  pinMode(lAZUL, OUTPUT);
  pinMode(lVERDE, OUTPUT);
  pinMode(lVERM, OUTPUT);
  pinMode(bREC, INPUT_PULLUP);

  Serial.println("Set compact mode...");
  delay(2000);
  moduloSerial.write(0xAA);
  moduloSerial.write(0x37);
  // Serial.println("Set baudrate...");
  // delay(2000);
  // moduloSerial.write(0xAA);
  // moduloSerial.write(0x35);
  Serial.println("Waiting mode...");
  delay(2000);
  moduloSerial.write(0xAA);
  moduloSerial.write(byte(0x00));

}

void loop() {

  if(!digitalRead(bREC)) {
    while (!digitalRead(bREC));
    delay(100);
    Serial.println("Button pressed!");
    Serial.println("Comandos apagados...");
    delay(2000);
    moduloSerial.write(0xAA);
    moduloSerial.write(0x04);
    Serial.println("Gravacao grupo 1");
    delay(2000);
    moduloSerial.write(0xAA);
    moduloSerial.write(0x11);
  }
  while (moduloSerial.available()) {
    //resposta = moduloSerial.readString();
    resposta = moduloSerial.read();
    Serial.print("0x");
    Serial.println(resposta, HEX);
    if (resposta == 0x46) {
      Serial.println("Grupo 1 finalizado");
      Serial.println("Gravacao grupo 2");
      delay(100);
      moduloSerial.write(0xAA);
      moduloSerial.write(0x12);
    }
    if (resposta == 0x47) {
      Serial.println("Grupo 2 finalizado");
      Serial.println("Gravacao grupo 3");
      delay(100);
      moduloSerial.write(0xAA);
      moduloSerial.write(0x13);
    }
    if (resposta == 0x48) {
      Serial.println("Grupo 3 finalizado");
      Serial.println("importando grupo 1 fale agora");
      delay(100);
      moduloSerial.write(0xAA);
      moduloSerial.write(0x21);
    }
    if (resposta == 0x11) {
      Serial.println("Grupo 3 finalizado");
      Serial.println("importando grupo 1 fale agora");
      delay(100);
      moduloSerial.write(0xAA);
      moduloSerial.write(0x21);
    }
  }

  // if(!digitalRead(bREC)) {
  //   if (numLed > 3) {
  //     numLed = 0;
  //   }
  //   switch (numLed)
  //   {
  //     case 0:
  //       digitalWrite(lAZUL, LOW);
  //       digitalWrite(lVERDE, LOW);
  //       digitalWrite(lVERM, LOW);
  //       break;
  //     case 1:
  //       digitalWrite(lAZUL, HIGH);
  //       digitalWrite(lVERDE, LOW);
  //       digitalWrite(lVERM, LOW);
  //       break;
  //     case 2:
  //       digitalWrite(lAZUL, LOW);
  //       digitalWrite(lVERDE, HIGH);
  //       digitalWrite(lVERM, LOW);
  //       break;
  //     case 3:
  //       digitalWrite(lAZUL, LOW);
  //       digitalWrite(lVERDE, LOW);
  //       digitalWrite(lVERM, HIGH);
  //       break;
  //   }
  //   numLed++;
  //   while (!digitalRead(bREC));
  //   delay(100);
  // }
}
