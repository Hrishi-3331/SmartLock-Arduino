/* SmartLock EDC Project
 *  Author: Hrishikesh Ugale 24/10/2018 6:20 pm
 */


//Constant Parameters
const int i1 = 9; //motor driver input
const int i2 = 5;//motor driver input
const int sound = 13;//Speaker pin
const int b1 = 2;
const int b2 = 3;
const int b3 = 4;
const int b4 = 6;
const int b5 = 7;
const int b6 = 8;
const int lock = 10; //lock button

//Changing variables
boolean state = false;
int bstate1 = 0;
int bstate2 = 0;
int bstate3 = 0;
int bstate4 = 0;
int bstate5 = 0;
int bstate6 = 0;
int bstatelock = 0;

const int pin[4] = {3, 1, 3, 5};//Default Password
int pinEntered[4] = {0,0,0,0};

int attempt = 0;


void setup() {
  pinMode(i1,OUTPUT);
  pinMode(i2,OUTPUT);
  pinMode(b1,INPUT);
  pinMode(b2,INPUT);
  pinMode(b3,INPUT);
  pinMode(b4,INPUT);
  pinMode(b5,INPUT);
  pinMode(b5,INPUT);
  pinMode(lock,INPUT);
  Serial.begin(9600);
}

void loop() {

while(Serial.available()>0)
{
char a = Serial.read();
Serial.println(a);

if (a == 'o'){
  
  if (state == true){
  state = unlock();
  Serial.println("Unlock Success");
  }
}

else if (a == 'l'){
  
  if (state == false){
  state = lockIt();
  Serial.println("Locked");
  }
}
/*else if(a == 'a')
{
  alarm();
}*/

else Serial.println("Unlock Failed");
}

bstate1 = digitalRead(b1);
bstate2 = digitalRead(b2);
bstate3 = digitalRead(b3);
bstate4 = digitalRead(b4);
bstate5 = digitalRead(b5);
bstate6 = digitalRead(b6);
bstatelock = digitalRead(lock);

if (bstate1 == HIGH && state==true){
  buzz();
  enter(1);
}

if (bstate2 == HIGH && state==true){
  buzz();
  enter(2);
}

if (bstate3 == HIGH && state==true){
  buzz();
  enter(3);
}

if (bstate4 == HIGH && state==true){
  buzz();
  enter(4);
}

if (bstate5 == HIGH && state==true){
  buzz();
  enter(5);
}

if (bstate6 == HIGH && state==true){
  buzz();
  enter(6);
}

if (lock == HIGH && state==true){
  if(state == false){
    state = lockIt();
  }
  else Serial.println("Already Locked");
}

}

boolean unlock(){
digitalWrite(i1,HIGH);
digitalWrite(i2,LOW);
delay(2500);
digitalWrite(i1,LOW);
digitalWrite(i2,LOW);
return false;
}

boolean lockIt(){
digitalWrite(i1,LOW);
digitalWrite(i2,HIGH);
delay(2500);
digitalWrite(i1,LOW);
digitalWrite(i2,LOW);
return true;
}

void alarm(){
  int i;
for (i=500; i<2000; i++){
  tone(sound, i);
}
while(i >1){
  tone(sound, i);
  i--;
}
}

void buzz(){
  tone(sound, 1500);
  delay(500);
}

void enter(int y){
  int z = attempt;
  
  switch(z){
    case 0:
    {
      pinEntered[0] = y;
      attempt++;
      break;
    }

    case 1:
    {
      pinEntered[1] = y;
      attempt++;
      break;
    }

    case 2:
    {
      pinEntered[2] = y;
      attempt++;
      break;
    }

    case 3:
    {
      pinEntered[3] = y;
      attempt = 0;
      checkPin();
    }
  }
}

void checkPin(){
  int p = 0;
  boolean match = true;
  for (p = 0;p<4; p++){
  if (pinEntered[p] != pin[p])
    match = false;
    break;
  }

  action(match);
}

void action (boolean key){
  int h;
  if(key){
    state = unlock();
    for(h=0;h<4;h++){
      pinEntered[h] = 0;
    }
    Serial.println("UNLOCK SUCCESS");
  }
  else{
    for(h=0;h<4;h++){
      pinEntered[h] = 0;
    }
    Serial.println("UNLOCK FAILED");
  }
}




