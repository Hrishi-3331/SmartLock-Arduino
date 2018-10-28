const int sound = 13;//Speaker pin
const int b1 = 2;
const int b2 = 3;
const int b3 = 4;
const int b4 = 6;
const int b5 = 7;
const int b6 = 8;
const int b0 = 11;
const int b789 = 12;
const int lock = 10;
const int i1 = 9; //motor driver input
const int i2 = 5;//motor driver input

boolean state = true;
//Changing variables
int bstate0 = 0;
int bstate1 = 0;
int bstate2 = 0;
int bstate3 = 0;
int bstate4 = 0;
int bstate5 = 0;
int bstate6 = 0;
int bstate789 = 0;
int bstatelock = 0;

const int pin[4] = {3, 1, 3, 5};//Default Password
int pinEntered[4] = {0,0,0,0};


int index = 0;
int iat = 0;

void setup() {
  pinMode(i1,OUTPUT);
  pinMode(i2,OUTPUT);
  pinMode(b0,INPUT);
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
 unlock();
 Serial.println("Unlock Success");
}

else 
if (a == 'l'){
  lockit();
  Serial.println("Locked");
}

else 
if(a == 'a')
{
  alarm();
}


else Serial.println("Unlock Failed");
}
    
bstate0 = digitalRead(b0);
bstate1 = digitalRead(b1);
bstate2 = digitalRead(b2);
bstate3 = digitalRead(b3);
bstate4 = digitalRead(b4);
bstate5 = digitalRead(b5);
bstate6 = digitalRead(b6);
bstate789 = digitalRead(b789);
bstatelock = digitalRead(lock);
if(index == 4){
checkPin();
  resetArray();
  index = 0;
}

if (iat == 3){
  Serial.println("Theft alert");
  alarm();
  iat = 0;
}

if (bstate0 == HIGH){
buzz();
store(0);
}

if (bstate1 == HIGH){
buzz();
store(1);
}

if (bstate2 == HIGH){
buzz();
store(2);
}

if (bstate3 == HIGH){
buzz();
store(3);
}

if (bstate4 == HIGH){
buzz();
store(4);
}

if (bstate5 == HIGH){
buzz();
store(5);
}

if (bstate6 == HIGH){
buzz();
store(6);
}

if (bstate789 == HIGH){
buzz();
}

if (bstatelock == HIGH){
buzz();
lockit();
}

}

void buzz(){
  tone(sound, 1500);
  delay(150);
  noTone(sound);
}

void store(int num) {
  pinEntered[index] = num;
  index++;
}

void checkPin(){
  if (pin[0] == pinEntered[0] && pin[1] == pinEntered[1])
  {
    if (pin[2] == pinEntered[2] && pin[3] == pinEntered[3])
    unlock();

    else{
    Serial.println("Incorrect Pin");
    iat++;
    beep();
    }
  }

  else{
    Serial.println("Incorrect Pin");
    iat++;
    beep();
  }
}

void resetArray(){
  int temp=0;
  for(temp=0;temp<4;temp++){
    pinEntered[temp]=0;
  }
}

void unlock(){
  if(state == true){
digitalWrite(i1,HIGH);
digitalWrite(i2,LOW);
delay(500);
digitalWrite(i1,LOW);
digitalWrite(i2,LOW);
iat = 0;
state = false;
}
else
{
  Serial.println("Already unloced");
}
}

void lockit(){
  if(state == false){
digitalWrite(i2,HIGH);
digitalWrite(i1,LOW);
delay(500);
digitalWrite(i1,LOW);
digitalWrite(i2,LOW);
state = true;
}
else
{
  Serial.println("lready locked");
}
}

void alarm(){
  int i; 
  int myVar = 0;
  while(myVar < 30000){
for (i=500; i<2000; i++){
  tone(sound, i);
  myVar++;
}
  }
  noTone(sound);
}


void beep(){
  int temp2=0;
  while (temp2< 3){
    tone(sound,500);
    delay(250);
    noTone(sound);
    delay(250);
    temp2++;
  }
}

