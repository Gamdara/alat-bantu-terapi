#include "Header.h"
#include "KakiController.h"

Kaki kanan{
  Motor(13,12),
  Motor(11,10), 
  Motor(9,8) 
};

Kaki kiri{
  Motor(7,6),
  Motor(5,4), 
  Motor(3,2) 
};
void movementDefault();

void setup()
{  
  Serial.begin(9600);
  Serial.println("mulai");
  Serial.println("Inisialisasi...");
  setupCommands();
//inisiasi semua motor, defaultnya speed 50, accel 20
  kanan.T.init(DEFAULT_SPEED, DEFAULT_ACCEL);
  kanan.M.init(DEFAULT_SPEED, DEFAULT_ACCEL);
  kanan.B.init(DEFAULT_SPEED, DEFAULT_ACCEL);
  
  kiri.T.init(DEFAULT_SPEED, DEFAULT_ACCEL);
  kiri.M.init(DEFAULT_SPEED, DEFAULT_ACCEL);
  kiri.B.init(DEFAULT_SPEED, DEFAULT_ACCEL);
  megunoLink.setKaki(kanan, kiri);

  pinMode(button, INPUT);
  Serial.println("Inisialisasi Selesai...");
}

void loop()
{ 
  if(digitalRead(button)){
    movementDefault();
  }
  SerialCmds.Process();
}

void movementDefault(){
    paha_rotation = DEPAN;
    betis_rotation = BELAKANG;
    telapak_rotation = BELAKANG;
    
    kanan.moveAuto(0,0,0);
    kanan.moveAuto(35, 30, 13);
    kanan.moveAuto(35, 0, 0);
    kanan.moveAuto(35, 30, 13);
    kanan.moveAuto(0,0,0);
    delay(5000);
    kiri.moveAuto(0,0,0);
    kiri.moveAuto(35, 30, 13);
    kiri.moveAuto(35, 0, 0);
    kiri.moveAuto(35, 30, 13);
    kiri.moveAuto(0,0,0);
    delay(5000);
}
