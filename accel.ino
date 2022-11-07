#include "Header.h"
#include "Kaki.h"
#include "Button.h"
#include "LCD.h"

#define SPEED 50
#define ACCEL 20


Kaki kanan{
  //motor kiri atas
  Motor(12,11, KIRI),
  //motor kiri tengah
  Motor(10,9, KIRI),
  //motor kiri bawah  
  Motor(8,7, KIRI) 
};

void setup()
{  
  Serial.begin(9600);
  Serial.println("mulai");
  Serial.print(getSudutTelapak(45, 37.5));
//inisiasi semua motor, defaultnya speed 50, accel 20
//  kanan.T.init(DEFAULT_SPEED, DEFAULT_ACCEL);
//  kanan.M.init(DEFAULT_SPEED, DEFAULT_ACCEL);
//  kanan.B.init(DEFAULT_SPEED, DEFAULT_ACCEL);

  kanan.T.init(50, 20);
  kanan.M.init(50, 20);
  kanan.B.init(20, 20);

//  kanan.B.move(10, DEPAN, BLOCKING);  
//  kanan.M.move(15, DEPAN, BLOCKING);  
//  kanan.T.move(20, BELAKANG, BLOCKING);   
}

void loop()
{
//ke posisi naik
  kanan.T.init(SPEED, ACCEL);
  kanan.M.init(SPEED * 37.5 / 45, ACCEL * 37.5 / 45);
  kanan.B.init(SPEED * 15 / 45, ACCEL * 15 / 45);
  
  kanan.T.move(45, DEPAN, ASYNC);  //bergerak 60 derajat ke depan
  kanan.M.move(37.5, BELAKANG, ASYNC); //bergerak 60 derajat ke belakang
  kanan.B.move(15, BELAKANG, ASYNC); //bergerak 60 derajat ke belakang
  
////memberi pulse sampai motor bergerak ke posisi tujuan
  kanan.run();
  kanan.print();
  delay(5000);

//ke posisi awal
  kanan.T.move(0, DEPAN, ASYNC, USESTEP);      //bergerak ke posisi 0 step (posisi awal)
  kanan.M.move(0, BELAKANG, ASYNC, USESTEP); //bergerak ke posisi 0 step (posisi awal)
  kanan.B.move(0, BELAKANG, ASYNC, USESTEP); //bergerak ke posisi 0 step (posisi awal)

  //memberi pulse sampai motor bergerak ke posisi tujuan
  kanan.run();  
  kanan.print();
  delay(5000);

  
}
