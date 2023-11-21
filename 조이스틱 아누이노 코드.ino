#include <SoftwareSerial.h>
#include <AFMotor.h>
AF_DCMotor motor_L(1);            
AF_DCMotor motor_R(4); 
#define BT_RXD A5
#define BT_TXD A4
SoftwareSerial bluetooth(BT_RXD, BT_TXD);      
int x ,y;
bool rec_chk = false;
int i;
void setup() 
{
Serial.begin(9600);
bluetooth.begin(9600);
motor_L.setSpeed(200);             
motor_L.run(RELEASE);
motor_R.setSpeed(200);            
motor_R.run(RELEASE);
}
void loop() 
{
 if(bluetooth.available()>0)
 {   
     x = bluetooth.read();
     y = bluetooth.read();
     Serial.write(rec_data);
     rec_chk = true;
  }  
  if((x>=100&&x<=150) && (y>=100&&y<=150)
  {
     motor_L.run(RELEASE);
     motor_R.run(RELEASE);
  }
  else if(x<125&&y<125)
  {
    motor_L.setSpeed((200-y)/(126-x));
    motor_L.run(FORWARD);  
    motor_R.setSpeed(200-y);
    motor_R.run(FORWARD);
  }
  else if(x>125&&y<125)
  {
    motor_L.setSpeed(200-y);
    motor_L.run(FORWARD);  
    motor_R.setSpeed((200-y)/(x-124));
    motor_R.run(FORWARD);
  }
  else if(x<125&&y>125)
  {
    motor_L.setSpeed((y-50)/(126-x));
    motor_L.run(BACKWARD);  
    motor_R.setSpeed(y-50);
    motor_R.run(BACKWARD);
  }
  else if(x>125&&y>125)
  {
    motor_L.setSpeed(y-50);
    motor_L.run(BACKWARD);  
    motor_R.setSpeed((y-50)/(x-124));
    motor_R.run(BACKWARD);
  }
}
















