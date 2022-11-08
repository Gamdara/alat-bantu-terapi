#include "Header.h"
#include "Kaki.h"

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

InterfacePanel Panel;

void moveKaki(CommandParameter& p){
  float sudutPaha = p.NextParameterAsInteger();
  float sudutBetis = p.NextParameterAsInteger();
  float sudutTelapak = p.NextParameterAsInteger();
  Serial.println(kakiPilihan);
  if(kakiPilihan == KANAN){
    kanan.move(sudutPaha, sudutBetis,sudutTelapak);
  }else{
    kiri.move(sudutPaha, sudutBetis, sudutTelapak);
  }
}

void moveGerakan(CommandParameter& p){
  for (int i = 0; i < listGerakan.Count(); i++)
  {
    if(kakiPilihan == KANAN){
      kanan.move(listGerakan[i].x,listGerakan[i].y,listGerakan[i].z);
    }else{
      kiri.move(listGerakan[i].x,listGerakan[i].y,listGerakan[i].z);
    }
  }
}

void setKakiPilihan(CommandParameter& p){
  kakiPilihan = p.NextParameterAsInteger();
}

void setKakiRotasi(CommandParameter& p){
  paha_rotation = p.NextParameterAsInteger();
  betis_rotation = p.NextParameterAsInteger();
  telapak_rotation = p.NextParameterAsInteger();
  if(paha_rotation == 0){
    paha_rotation = BELAKANG;
  }
  if(betis_rotation == 0){
    betis_rotation = BELAKANG;
  }
  if(telapak_rotation == 0){
    telapak_rotation = BELAKANG;
  }
}

void setSpeedAccel(CommandParameter& p){
  motor_speed = p.NextParameterAsInteger();
  motor_accel = p.NextParameterAsInteger();
}

void addGerakan(CommandParameter& p){
  int sudutPaha = p.NextParameterAsInteger();
  int sudutBetis = p.NextParameterAsInteger();
  int sudutTelapak = p.NextParameterAsInteger();
  vec3_t v = { sudutPaha , sudutBetis , sudutTelapak }; 
  listGerakan.Add(v);
  printGerakan();
}

void clearGerakan(CommandParameter& p){
  listGerakan.RemoveRange(0, listGerakan.Count());
}

void setupCommands(){
  SerialCmds.AddCommand(F("SetKakiPosisi"), moveKaki);
  SerialCmds.AddCommand(F("SetKakiPilihan"),setKakiPilihan);
  SerialCmds.AddCommand(F("SetRotasiKaki"), setKakiRotasi);
  SerialCmds.AddCommand(F("SetSpeedAccel"), setSpeedAccel);
  
  SerialCmds.AddCommand(F("MoveGerakan"),moveGerakan);
  SerialCmds.AddCommand(F("AddGerakan"), addGerakan);  
  SerialCmds.AddCommand(F("ClearGerakan"), clearGerakan);  

  Panel.SetListValue("PilihanKaki", kakiPilihan);
  Panel.SetListValue("PahaRotasi", paha_rotation);
  Panel.SetListValue("BetisRotasi", betis_rotation);
  Panel.SetListValue("TelapakRotasi", telapak_rotation);
  Panel.SetNumber("SpeedForm", motor_speed);
  Panel.SetNumber("AccelForm", motor_accel);
}

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
  Serial.println("Inisialisasi Selesai...");
}

void loop()
{ 
  SerialCmds.Process();
}
