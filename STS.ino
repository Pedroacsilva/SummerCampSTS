#include "M5StickCPlus.h"

void setup() {
  M5.begin();
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(2);

  pinMode(10, OUTPUT);
  
}

void loop() {
  M5.update();

  ledSwitch();
}

void ledSwitch(){
  if(M5.BtnA.wasReleased()){
    digitalWrite(10,LOW);
    ledState();
  }
  else if (M5.BtnA.wasReleasefor(700)) {
    digitalWrite(10,HIGH);
    ledState();
  }
}

bool ledState(){
  if(digitalRead(10) == 0){
    M5.Lcd.print("On\n");
    return true; 
  }
  else{
    M5.Lcd.print("Off\n");
    return false;
  }
    
}
