#define Trig_R 13
#define Echo_R 12

#define Trig_L 8
#define Echo_L 9

unsigned int distance_L;
unsigned int time_L;

unsigned int distance_R;
unsigned int time_R;

#define ENA_L 5
#define INL 10
#define INR 2
#define ENA_R 6


float kp = 25;
float ki = 0;
float kd = 10;

float error = 0, lastError = 0;
float P ,I , D, PIDvalue ;

int baseSpeed = 100;
int leftSpeed , rightSpeed;

void setup() {

  pinMode(Trig_R,OUTPUT);
  pinMode(Echo_R,INPUT);

  pinMode(Trig_L,OUTPUT);
  pinMode(Echo_L,INPUT);

  pinMode(ENA_L,OUTPUT);
  pinMode(INL,OUTPUT);
  pinMode(INR,OUTPUT);

  pinMode(ENA_R,OUTPUT);
  

  Serial.begin(9600);

}

void loop() {
  digitalWrite(Trig_R , LOW);
  delayMicroseconds(2);
  digitalWrite(Trig_R , HIGH);
  delayMicroseconds(2);
  time_R =pulseIn(Echo_R ,HIGH);
  distance_R = (time_R/29)/2;
  Serial.print("Right_distance  ");
  Serial.println(distance_R);
  delay(100);

  digitalWrite(Trig_L , LOW);
  delayMicroseconds(2);
  digitalWrite(Trig_L , HIGH);
  delayMicroseconds(2);
  time_L =pulseIn(Echo_L ,HIGH);
  distance_L = (time_L/29)/2;
  Serial.print("Left_distance  ");
  Serial.println(distance_L);
  delay(100);

  if((distance_R<4)&&(distance_L<4)){
    digitalWrite(INL,LOW);
    digitalWrite(INR,LOW);
    delay(100);
    }

  else if((distance_R<15)||(distance_L<15)){
    digitalWrite(INL,HIGH);
    digitalWrite(INR,HIGH);
    if(distance_R>distance_L)error = 1;
    else error =-1;
    P = error;
    I += error;
    D = error - lastError;
    PIDvalue = (kp * P) + (ki * I) + (kd * D);
    lastError = error;
    leftSpeed = baseSpeed - PIDvalue;
    rightSpeed = baseSpeed + PIDvalue;

    leftSpeed = constrain(leftSpeed , 40, 255);
    rightSpeed = constrain(rightSpeed , 40, 255);

    analogWrite(ENA_L, leftSpeed);
    analogWrite(ENA_R, rightSpeed);
    delay(200);
  }
  else{
    digitalWrite(INL,LOW);
    digitalWrite(INR,LOW);
    delay(100);
    
  }


}
