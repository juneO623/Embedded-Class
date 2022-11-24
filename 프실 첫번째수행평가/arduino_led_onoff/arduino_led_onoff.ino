#include <string.h>

int led1 = 5;
int led2 = 3;

void setup(){
  Serial.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
}

void loop(){

  if (Serial.available() > 0){
    Serial.setTimeout(100);
    String res = Serial.readString();

    if (res != ""){
      if (res == "1ON "){
        digitalWrite(led1, HIGH);  
      } else if (res == "1OFF"){
        digitalWrite(led1, LOW);
      } else if (res == "2ON "){
        digitalWrite(led2, HIGH);
      } else if (res == "2OFF"){
        digitalWrite(led2, LOW);
      }
    }
  }
}
