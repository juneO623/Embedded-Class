void setup() 
{

  Serial.begin(9600);

  Serial.println("haha");

  pinMode(9, OUTPUT);
  pinMode(13, OUTPUT);


}

int count = 0;
int count_100ms = 0;
int duty = 0;

int count2 = 0;
int count_100ms_count = 0;
int duty2 = 0;

void loop() 
{
  
//
//  for (int i=0; i<100; i++){
//    digitalWrite(13, HIGH);
//    delay(9);
//    digitalWrite(13, LOW);
//    delay(1);
//  }
//
//  for (int i=0; i<100; i++){
//    digitalWrite(13, HIGH);
//    delay(1);
//    digitalWrite(13, LOW);
//    delay(9);
//  }

// --------------------------------------

  if (count == 100){
    count = 0;
    digitalWrite(13, HIGH);
  }
  else if (count == duty){
    digitalWrite(13, LOW);
  }

// --------------------------------------

  if (count2 == 100){
    count2 = 0;
    digitalWrite(9, HIGH);
  }
  else if (count == duty2){
    digitalWrite(9, LOW);
  }
  
// --------------------------------------

  if (count_100ms == 100){
    count_100ms = 0;
    duty++;
    count_100ms_count++;
    if (duty == 100) duty = 0;
  }

  if (count_100ms_count == 1){
    count_100ms_count = 0;
    duty2++;
    if (duty2 == 200) duty2 = 0;
  }
  
// --------------------------------------
  count++;
  count_100ms++;
  count2++;
//  delay(1);
  delayMicroseconds(100);

}
