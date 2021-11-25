#include <ESP32Servo.h>
#include "deneyap.h"
int xbir, x2, x3, ybir, y2, y3=0;
int ax1, ax2, ax3, ay1, ay2, ay3 = 90;
bool state=0; 
int button=0;
Servo altservo;
Servo ortakolservo;
Servo onservo;
Servo tutucuservo;
#define data1 D1    //Data pinlerinin adları yazılacak suanda calismiyor
#define data2 D2    //yer tutucu
#define data3 D3    //yer tutucu
#define data4 D4    //yer tutucu



const int generaldelay = 15; //genel gecikme
const int vSpeed = 100;// hız değiştirmek için
#define motorA1 D14 // L298N'in IN3 Girişi
#define motorA2 D12 // L298N'in IN1 Girişi
#define motorB1 D13 // L298N'in IN2 Girişi
#define motorB2 D15 // L298N'in IN4 Girişi
  
void setup() {//Setup
  //---- KUMANDA PİNLERİ VE SERİAL -----------
pinMode(A0, INPUT);pinMode(A1, INPUT);pinMode(A2, INPUT);pinMode(A3, INPUT);pinMode(A4, INPUT);pinMode(A5, INPUT);//analog pinler
pinMode(D0, INPUT_PULLUP);//button
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT); 
Serial.begin(115200);
  //----------------------------------------
//-----------SERVOLAR-----------

altservo.attach(data1);
ortakolservo.attach(data2);
onservo.attach(data3);
tutucuservo.attach(data4);
altservo.write(90);
ortakolservo.write(90);
onservo.write(90);
tutucuservo.write(90);
}



void stopmotor(){
digitalWrite(motorA1,0);
digitalWrite(motorA2,0);
digitalWrite(motorB1,0);
digitalWrite(motorB2,0);
//Serial.println("stop");//debug
}
void ilerle(){
digitalWrite(motorA1,vSpeed);
digitalWrite(motorA2,0);
digitalWrite(motorB1,vSpeed);
digitalWrite(motorB2,0); 
//Serial.println("ilerle");//debug
}
void geri(){
digitalWrite(motorA1,0);
digitalWrite(motorA2,vSpeed);
digitalWrite(motorB1,0);
digitalWrite(motorB2,vSpeed); 
//Serial.println("geri");//debug
}
void sol(){
digitalWrite(motorA1,vSpeed);
digitalWrite(motorA2,150);
digitalWrite(motorB1,0);
digitalWrite(motorB2,0);
//Serial.println("sol");//debug
}
void sag(){
digitalWrite(motorA1,0);
digitalWrite(motorA2,0);
digitalWrite(motorB1,vSpeed);
digitalWrite(motorB2,150);
//Serial.println("sag");//debug
}


void loop() {
  //------KONTROLLER-------
  xbir = analogRead(A0);//ileri 0 geri 4095
  ybir = analogRead(A1); //sol 4095 sag 0
  x2 = analogRead(A4);//kol yukari 0 asagi 4095
  y2 = analogRead(A5);//kol sag 0 sol 4095
  x3 = analogRead(A2);//kol ön asagi 0 yukari 4095
  y3 = analogRead(A3);//kol uc yukari 0 asagi 4095
  button = digitalRead(D0);//kiskac ac kapa
  //--------------------
  
//--------DEBUG---------
//Serial.println("----------");Serial.print("x1: ");Serial.println(xbir);Serial.print("y1: ");Serial.println(ybir);Serial.print("x2: ");Serial.println(x2);Serial.print("y2: ");Serial.println(y2);Serial.print("x3: ");Serial.println(x3);Serial.print("y3: ");Serial.println(y3);Serial.print("button: ");Serial.println(button);Serial.print("state: ");Serial.println(state);
//delay(200);
//----------------------
    if(button ==0){
      state =!state;
    delay(generaldelay);
    }
    
    if(xbir <300){
      ilerle();
      delay(generaldelay);
    }
    else if (xbir >2000){
      geri();
      delay(generaldelay);
    }
    if(ybir <300){
      sag();
      delay(generaldelay);
    }
    else if(ybir >2000);{
      sol();
      delay(generaldelay);
    }
    if(x2 <300){
     //kol yukari
      delay(generaldelay);
    }
    else if(x2 >2000){
      //kol asagi
      delay(generaldelay);
    }
    if(y2 <300){
      //kol sag
      delay(generaldelay);
    }
    else if(y2 >2000){
      //kol sol
      delay(generaldelay);
    }
    if(x3 <300){
      //
      delay(generaldelay);
    }
    else if(x3 >2000){
      //
      delay(generaldelay);
    }
    if(y3 <300){
      //
      delay(generaldelay);
    }
    else if(y3 >2000){
      //
      delay(generaldelay);
    }
    else{
      stopmotor();    
    }
}
/*
          YAPILMASI GEREKENLER
   1.Servo data pinlerinin girilmesi
   2.dc motor hareketlerinin kontrol edilmesi
   3.Servoların hareket kodunun yazılması
   4.test
   5.hata giderme
*/
