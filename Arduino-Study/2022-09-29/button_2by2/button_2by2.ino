void setup() {

  Serial.begin(9600);

  pinMode(12, INPUT);
  pinMode(6, INPUT);
  digitalWrite(12, HIGH);
  digitalWrite(6, HIGH);

  // col
  pinMode(3, OUTPUT);
  pinMode(11, OUTPUT);

}

char flag_row1 = 0;
char flag_row2 = 0;
int row_port[2] = {12, 6};
char row_flag[2][2] = {{0,0}, {0,0}};
int col_port[2] = {3, 11};

void loop() {

  for (int j=0; j<2; j++)
  {
    // 1. all column off
    for (int i=0; i<2; i++)
    {
      digitalWrite(col_port[i], LOW);
    }
    
    // 2. Col HIGH
    digitalWrite(col_port[j], HIGH);
  // ---------------------------------------------
   // ROW
    for (int i=0; i<2; i++)
    {
      int row = digitalRead(row_port[i]);
      if (row == 0 && row_flag[i][j] == 0)
      {
        row_flag[i][j] = 1;
        Serial.println("button " + String(i*2+j) + " down");
      }
      else if (row == 1 && row_flag[i][j] == 1)
      {
        row_flag[i][j] = 0;
        Serial.println("button " + String(i*2+j) + " up");
      }    
    }    
  }
  

  

//// ---------------------------------------
//  // ROW 1
//  int row1 = digitalRead(3);
//  if (row1 == 1 && flag_row1 == 0)
//  {
//    flag_row1 = 1;
//    Serial.println("button 1 down");
//  }
//  else if (row1 == 0 && flag_row1 == 1)
//  {
//    flag_row1 = 0;
//    Serial.println("button 1 up");
//  }
//// ---------------------------------------
//  // Row 2
//  int row2 = digitalRead(11);
//  if (row2 == 1 && flag_row2 == 0)
//  {
//    flag_row2 = 1;
//    Serial.println("button 3 down");
//  }
//  else if (row2 == 0 && flag_row2 == 1)
//  {
//    flag_row2 = 0;
//    Serial.println("button 3 up");
//  }

  delay(10);
  
}
