#include <SoftwareSerial.h>
#include <AFMotor.h>
AF_DCMotor motor_L(1);
AF_DCMotor motor_R(4);

int Lspeed = 170;        //좌측 모터 속도
int Rspeed = 200;        //우측 모터 속도

int TrigPin = A0;        //초음파센서 출력핀(trig)과 입력핀(echo), 변수, 함수 선언
int EchoPin = A1;
long duration, distance;
int dL, dR;

void Obstacle_Check();
void Distance_Measurement();
void Forward();
void Backward();
void Right();
void Left();
void Stop();

void setup() {
  Serial.begin(9600);                         // PC와의 시리얼 통신속도
  Serial.println("Eduino Smart Car Start!");

  pinMode(EchoPin, INPUT);                    // EchoPin 입력
  pinMode(TrigPin, OUTPUT);                   // TrigPin 출력

  motor_L.setSpeed(Lspeed);                   // 왼쪽 모터의 속도
  motor_L.run(RELEASE);
  motor_R.setSpeed(Rspeed);                   // 오른쪽 모터의 속도
  motor_R.run(RELEASE);
}

void loop() 
{
{
Distance_Measurement();
if(distance < 300)
{
  Stop();
  Left();
  delay(500);
  Stop();
  Distance_Measurement();
  dL = distance;
  Right();
  delay(1000);
  Distance_Measurement();
  dR = distance;
  if (dL > dR) //좌회전
  {
    Left();
    delay(1500);
    Stop();
    Forward();
  }
  else
  {
    Right();
    delay(500);
    Stop();
    Forward();
  }
}
else 
{
  Forward();
}
}
}
////////거리감지///////////
void Distance_Measurement() {
  digitalWrite(TrigPin, LOW);
  delay(2);
  digitalWrite(TrigPin, HIGH);       // trigPin에서 초음파 발생(echoPin도 HIGH)
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);
  duration = pulseIn(EchoPin, HIGH); // echoPin 이 HIGH를 유지한 시간을 저장 한다.
  distance = ((float)(340 * duration) / 1000) / 2;
  delay(50);
}

///////////모터 제어 함수////////////
void Forward() {
  motor_L.run(FORWARD);  motor_R.run(FORWARD);
  motor_L.setSpeed(Lspeed);  motor_R.setSpeed(Rspeed);
}
void Backward() {
  motor_L.run(BACKWARD);  motor_R.run(BACKWARD);
  motor_L.setSpeed(Lspeed);  motor_R.setSpeed(Rspeed);
}
void Right() {
  motor_L.run(FORWARD);  motor_R.run(BACKWARD);
  motor_L.setSpeed(Lspeed);  motor_R.setSpeed(Rspeed*0.5);
}
void Left() {
  motor_L.run(BACKWARD);  motor_R.run(FORWARD);
  motor_L.setSpeed(Lspeed*0.5);  motor_R.setSpeed(Rspeed);
}
void Stop() {
  motor_L.run(RELEASE);       motor_R.run(RELEASE);
  motor_L.setSpeed(0);  motor_R.setSpeed(0);
}
