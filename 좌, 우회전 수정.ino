/*
 Name:		Sketch3.ino
 Created:	2023-11-06 오후 5:09:54
 Author:	augus
*/

#include <SoftwareSerial.h>
#include <AFMotor.h>
AF_DCMotor motor_L(1);
AF_DCMotor motor_R(3);

#define BT_RXD A5
#define BT_TXD A4
SoftwareSerial bluetooth(BT_RXD, BT_TXD);

char rec_data;
bool rec_chk = false;

int i;
int j;
int Lspeed = 228;
int Rspeed = 255;

//초음파센서 출력핀(trig)과 입력핀(echo) 설정
int trigPin = A0;
int echoPin = A1;

void setup() {
    Serial.begin(9600);              // PC와의 시리얼 통신속도
    bluetooth.begin(9600);            // 스마트폰 블루투스 통신속도
    Serial.println("Eduino Smart Car Start!");

    pinMode(echoPin, INPUT);   // echoPin 입력
    pinMode(trigPin, OUTPUT);  // trigPin 출력

    // turn on motor
    motor_L.setSpeed(Lspeed);              // 왼쪽 모터의 속도   
    motor_L.run(RELEASE);
    motor_R.setSpeed(Rspeed);              // 오른쪽 모터의 속도   
    motor_R.run(RELEASE);
}


void loop() {

    if (bluetooth.available()) {         // 블루투스 명령 수신
        rec_data = bluetooth.read();
        Serial.write(rec_data);
        rec_chk = true; 
    }

    if (rec_data == 'g') {  // 전진, go
        motor_L.run(FORWARD);  motor_R.run(FORWARD);
    }
    else if (rec_data == 'b') { // 후진, back
        motor_L.run(BACKWARD);  motor_R.run(BACKWARD);
    }
    else if (rec_data == 'l') { // 좌회전, Go Left
        motor_L.run(FORWARD);  motor_R.run(FORWARD);// 수정했음
        motor_L.setSpeed(Lspeed * 0.5);  motor_R.setSpeed(Rspeed);// 수정했음
    }
    else if (rec_data == 'r') { // 우회전, Go Right
        motor_L.run(FORWARD);  motor_R.run(FORWARD);// 수정했음
        motor_L.setSpeed(Lspeed);  motor_R.setSpeed(Rspeed * 0.5);//수정했음
    }
    else if (rec_data == 'q') { // 제자리 회전, Left Rotation
        motor_L.run(BACKWARD);   motor_R.run(FORWARD);
    }
    else if (rec_data == 'w') { // 제자리 회전, Right Rotation
        motor_L.run(FORWARD);   motor_R.run(BACKWARD);
    }
    else if (rec_data == 's') { // Stop 
        motor_L.run(RELEASE);       motor_R.run(RELEASE);
    }


    if (rec_data == 'f') {       // 정지
        if (rec_chk == true) {
            for (i = 250; i >= 0; i = i - 20) {
                motor_L.setSpeed(i);  motor_R.setSpeed(i);
                delay(10);
            }

        }
    }


}


//#include <SoftwareSerial.h>
//#include <AFMotor.h>
//
//AF_DCMotor motor_L(1);
//AF_DCMotor motor_R(3);
//
//#define BT_RXD A5
//#define BT_TXD A4
//SoftwareSerial bluetooth(BT_RXD, BT_TXD);
//
//char rec_data;
//bool rec_chk = false;
//
//int Lspeed = 228;
//int Rspeed = 255;
//
//void setup() {
//    Serial.begin(9600);
//    bluetooth.begin(9600);
//    Serial.println("Eduino Smart Car Start!");
//
//    motor_L.setSpeed(Lspeed);
//    motor_L.run(RELEASE);
//    motor_R.setSpeed(Rspeed);
//    motor_R.run(RELEASE);
//}
//
//void loop() {
//    if (bluetooth.available()) {
//        rec_data = bluetooth.read();
//        Serial.write(rec_data);
//        rec_chk = true;
//
//        // 모터를 블루투스 신호에 따라 작동합니다.
//        if (rec_data == 'g') {
//            motor_L.run(FORWARD);
//            motor_R.run(FORWARD);
//        }
//        else if (rec_data == 'b') {
//            motor_L.run(BACKWARD);
//            motor_R.run(BACKWARD);
//        }
//        else if (rec_data == 'l') {
//            motor_L.run(RELEASE);
//            motor_R.run(FORWARD);
//        }
//        else if (rec_data == 'r') {
//            motor_L.run(FORWARD);
//            motor_R.run(RELEASE);
//        }
//        else if (rec_data == 'q') {
//            motor_L.run(BACKWARD);
//            motor_R.run(FORWARD);
//        }
//        else if (rec_data == 'w') {
//            motor_L.run(FORWARD);
//            motor_R.run(BACKWARD);
//        }
//        else if (rec_data == 's') {
//            motor_L.run(RELEASE);
//            motor_R.run(RELEASE);
//        }
//    }
//    else {
//        // 블루투스 신호를 받지 않을 때 모터를 정지시킵니다.
//        motor_L.run(RELEASE);
//        motor_R.run(RELEASE);
//    }
//
//    if (rec_data == 'f') {
//        if (rec_chk == true) {
//            for (int i = 250; i >= 0; i -= 20) {
//                motor_L.setSpeed(i);
//                motor_R.setSpeed(i);
//                delay(10);
//            }
//        }
//    }
//}
