#include <AFMotor.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(A5, A4); // RX, TX
AF_DCMotor motor1(1);
AF_DCMotor motor2(4);
AF_DCMotor motor_L(1);
AF_DCMotor motor_R(4);

// 리모컨 조작 부분
String ms="";
int b;

// 자율주행 부분
int TrigPin = A0;        //초음파센서 출력핀(trig)과 입력핀(echo), 변수, 함수 선언
int EchoPin = A1;
long duration, distance;
int dL, dR;

int Lspeed = 115;        //좌측 모터 속도
int Rspeed = 400;        //우측 모터 속도

void Obstacle_Check();
void Distance_Measurement();
void Forward();
void Backward();
void Right();
void Left();
void Stop();

void setup() {
    //리모컨 조정 부분
    mySerial.begin(9600);
    motor1.setSpeed(200);
    motor2.setSpeed(400);
    //자율주행 부분
    motor_L.setSpeed(Lspeed);                   // 왼쪽 모터의 속도
    motor_L.run(RELEASE);
    motor_R.setSpeed(Rspeed);                   // 오른쪽 모터의 속도
    motor_R.run(RELEASE);
}

void loop() { // run over and over
    if (mySerial.available()) {
        
        ms=mySerial.readStringUntil('c');
        b=ms.toInt();

        if (b==1){

            motor1.run(RELEASE);

            motor2.run(FORWARD);
        }

        else if(b==2){

            motor1.run(FORWARD);

            motor2.run(FORWARD);
        }

        else if(b==3){

            motor1.run(FORWARD);

            motor2.run(RELEASE);
        }

        else if(b==4){

            motor1.run(BACKWARD);

            motor2.run(FORWARD);
        }

        else if(b==5){

            motor1.run(RELEASE);

            motor2.run(RELEASE);
        }
        
        else if(b==6){

            motor1.run(FORWARD);

            motor2.run(BACKWARD);
        }

        else if(b==7){

            motor1.run(RELEASE);

            motor2.run(BACKWARD);

        }
        
        else if(b==8){

            motor1.run(BACKWARD);

            motor2.run(BACKWARD);

        }

        else if(b==9){

            motor1.run(BACKWARD);

            motor2.run(RELEASE);
        }
        
        else if(b==10){
            
            motor1.run(FORWARD);
            motor2.run(FORWARD);
        }

        else if(b==11){
            
            Distance_Measurement();

            if(distance < 200) {
                Stop();
                Left();
                delay(250);
                Stop();
                Distance_Measurement();
                dL = distance;
                Right();
                delay(500);
                Stop();
                Distance_Measurement();
                dR = distance;

                if (dL > dR) {//좌회전
                    Left();
                    delay(500);
                    Stop();
                    Forward();
                }

                else {
                    Forward();
                }
            }
            
            else {
                Forward();
            }
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
  motor_L.setSpeed(Lspeed);  motor_R.setSpeed(Rspeed);
}
void Left() {
  motor_L.run(BACKWARD);  motor_R.run(FORWARD);
  motor_L.setSpeed(Lspeed);  motor_R.setSpeed(Rspeed);
}
void Stop() {
  motor_L.run(RELEASE);       motor_R.run(RELEASE);
  motor_L.setSpeed(0);  motor_R.setSpeed(0);
}