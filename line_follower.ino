
int left1 = 4, left2 = 13, right1 = 7, right2 = 8, enable1 = 3, enable2 = 10;

int x, y, z, frontSensor;
int xO = 1, yO = 0, zO = 1;

int counter = 1;

int speedR = 145, speedL = 131;
int speedRH = 85, speedLH = 72;
float rs = speedR, ls = speedL;

bool isTurning;

void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  
  pinMode(left1, OUTPUT);
  pinMode(left2, OUTPUT);
  pinMode(right1, OUTPUT);
  pinMode(right2, OUTPUT);
  pinMode(enable1, OUTPUT);
  pinMode(enable2, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  x = digitalRead(A2);
  y = digitalRead(A1);
  z = digitalRead(A0);

  frontSensor = digitalRead(A3);
  Serial.println(frontSensor);

  if(frontSensor == 0){

    if (x == 0 && y == 0 && z == 0) { //all black
      if (!(xO == 0 && yO == 0 && zO == 0))
        chalteRaho();
      else stopIt();
    }
    if (x == 0 && y == 0 && z == 1) {
      goRight();
    }
    //  if(x==0 && y==1 && z==0){
    //    stopIt();
    //  }
    if (x == 0 && y == 1 && z == 1) {
      goRight();
    }
    if (x == 1 && y == 0 && z == 0) {
      goLeft();
    }
    if (x == 1 && y == 0 && z == 1) {
      chalteRaho();
    }
    if (x == 1 && y == 1 && z == 0) {
      goLeft();
    }
    if (x == 1 && y == 1 && z == 1) { //all white
      chalteRaho();
    }
    
  }else followArc();
  
  xO = x;
  yO = y;
  zO = z;
}


void setDefault() {
  rs = speedR, ls = speedL;
  isTurning = false;
  digitalWrite(left1, HIGH);
  digitalWrite(left2, LOW);
  digitalWrite(right1, HIGH);
  digitalWrite(right2, LOW);
}

void setHalf() {
  rs = speedRH, ls = speedLH;
  isTurning = false;
}

void chalteRaho() {
  if(!isTurning){
    setDefault();
  }
    
  analogWrite(enable2, ls);
  analogWrite(enable1, rs);
}
void goLeft() {
  if(!isTurning){
    setHalf();
  }
  digitalWrite(left1, LOW);
  digitalWrite(left2, HIGH);
  digitalWrite(right1, HIGH);
  digitalWrite(right2, LOW);
  analogWrite(enable1, ls);
  analogWrite(enable2, rs);
}


void goRight() {
  if(!isTurning){
    setHalf();
  }
  digitalWrite(left1, HIGH);
  digitalWrite(left2, LOW);
  digitalWrite(right1, LOW);
  digitalWrite(right2, HIGH);
  analogWrite(enable2, rs);
  analogWrite(enable1, ls);
}

void uTurn() {
  analogWrite(enable2, 5);
  analogWrite(enable1, 200);
}

void stopIt() {
  analogWrite(enable1, 0);
  analogWrite(enable2, 0);
}

void followArc() {

  int x, y, z;
  // Make it rotate
  if(counter == 1){
    analogWrite(enable2, 205);
    analogWrite(enable1, 0);
    delay(450);
  }else if(counter == 2){
    analogWrite(enable2, 205);
    analogWrite(enable1, 0);
    delay(450);
  }else if(counter == 3){
    analogWrite(enable2, 240);
    analogWrite(enable1, 0);
    delay(400);
  }

  if(counter != 3){    
    while(!(x == 1 && y == 1 && z == 1)){
      x = digitalRead(A2);
      y = digitalRead(A1);
      z = digitalRead(A0);
  
      analogWrite(enable2, rs);
      analogWrite(enable1, ls);
    }
  }
  
  int r = 11;

  if(counter == 2)
    r =8;

  //float r =60;
  rs = 52.3 * (log(r)), ls = 254;

  do{
    x = digitalRead(A2);
    y = digitalRead(A1);
    z = digitalRead(A0);

    analogWrite(enable2, rs-15);
    analogWrite(enable1, ls-18);
  }while(x == 1 && y == 1 && z == 1);

  isTurning = false;

  analogWrite(enable2, 0);
  analogWrite(enable1, 20);
  delay(300);

  if(counter == 2){
    do{
      x = digitalRead(A2);
      y = digitalRead(A1);
      z = digitalRead(A0);
      
      analogWrite(enable1, 0);
      analogWrite(enable2, 80); 
    }while(!(x == 1 && y == 0 && z == 1));  
  }else if(counter == 3){
    analogWrite(enable2,220);
    analogWrite(enable1, 0);
    delay(450);
  }else{
    analogWrite(enable2,220);
    analogWrite(enable1, 0);
    delay(400);
  }

  analogWrite(enable2, 0);
  analogWrite(enable1, 0);
  delay(500);

  counter = counter + 1;

}
  

  //isTurning = true;
