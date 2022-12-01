
int servo_port = 7;
int freq = 20000; // 20 milliseconds (50Hz)
int minPulse = 600;   // 600 microseconds
int maxPulse = 2400;  // 2400 microseconds

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.setTimeout(100);
  pinMode(5, OUTPUT);
  pinMode(3, OUTPUT);
  digitalWrite(servo_port, LOW);
}

String str;
void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available())
  {
    str = Serial.readString();
    if (str == "1"){  
      digitalWrite(5, HIGH);
    } else if (str == "2"){
      digitalWrite(5, LOW);
    } else if (str == "3"){
      digitalWrite(3, HIGH);
    } else if (str == "4"){
      digitalWrite(3, LOW);
    } else if (str == "5"){
      for (int i=0; i<=180; i++){
        setServo(i);
      }
    } else if (str == "6"){
      for (int i=180; i>=0; i--){
        setServo(i);
      }
    }
  }
  
}

void setServo(int degree){
  int hTime = 0;
  int lTime = 0;

  if (degree < 0) degree = 0;
  if (degree > 180) degree = 180;

  hTime = (int)(minPulse + ((maxPulse-minPulse) / 180.0 * degree));
  lTime = freq - hTime;

  digitalWrite(servo_port, HIGH);
  delayMicroseconds(hTime);
  digitalWrite(servo_port, LOW);
  delayMicroseconds(lTime);
}
