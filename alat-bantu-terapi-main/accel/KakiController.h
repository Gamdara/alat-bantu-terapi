#include "Kaki.h"

InterfacePanel Panel;
CommandHandler<> SerialCmds;
List<vec3_t> listGerakan; 

void moveKaki(CommandParameter& p);
void moveGerakan();
void setKakiPilihan(CommandParameter& p);
void setKakiRotasi(CommandParameter& p);
void setKakiRotasiVariabel(int rPaha, int rBetis, int rTelapak);
void setSpeedAccel(CommandParameter& p);
void addGerakan(CommandParameter& p);
void clearGerakan();
void printGerakan();

class KakiController{
  public:
    Kaki kanan;
    Kaki kiri;

  KakiController(){};
  KakiController(Kaki kanan, Kaki kiri){
    this->kanan = kanan;
    this->kiri = kiri;
  }

 void setKaki(Kaki kanan, Kaki kiri){
    this->kanan = kanan;
    this->kiri = kiri;
  }
};

KakiController megunoLink;

void setupCommands(){
  SerialCmds.AddCommand(F("SetKakiPosisi"), moveKaki);
  SerialCmds.AddCommand(F("SetKakiPilihan"),setKakiPilihan);
  SerialCmds.AddCommand(F("SetRotasiKaki"), setKakiRotasi);
  SerialCmds.AddCommand(F("SetSpeedAccel"), setSpeedAccel);
  
  SerialCmds.AddCommand(F("MoveGerakan"),moveGerakan);
  SerialCmds.AddCommand(F("AddGerakan"), addGerakan); 
  SerialCmds.AddCommand(F("ClearGerakan"), clearGerakan); 
  SerialCmds.AddCommand(F("PrintGerakan"), printGerakan); 

  Panel.SetListValue("PilihanKaki", kakiPilihan);
  Panel.SetListValue("PahaRotasi", paha_rotation);
  Panel.SetListValue("BetisRotasi", betis_rotation);
  Panel.SetListValue("TelapakRotasi", telapak_rotation);
  Panel.SetNumber("SpeedForm", motor_speed);
  Panel.SetNumber("AccelForm", motor_accel);
  Panel.SetText("CountSavedMove",listGerakan.Count());
}

void moveKaki(CommandParameter& p){
  float sudutPaha = p.NextParameterAsInteger();
  float sudutBetis = p.NextParameterAsInteger();
  float sudutTelapak = p.NextParameterAsInteger();
  Serial.println(kakiPilihan);
  if(kakiPilihan == KANAN){
    megunoLink.kanan.move(sudutPaha, sudutBetis,sudutTelapak);
  }else{
    megunoLink.kiri.move(sudutPaha, sudutBetis, sudutTelapak);
  }
}

void moveGerakan(){
  for (int i = 0; i < listGerakan.Count(); i++)
  {
    if(kakiPilihan == KANAN){
      megunoLink.kanan.move(listGerakan[i].x,listGerakan[i].y,listGerakan[i].z, DEPAN, DEPAN, DEPAN);
    }else{
      megunoLink.kiri.move(listGerakan[i].x,listGerakan[i].y,listGerakan[i].z, DEPAN, DEPAN, DEPAN);
    }
  }
}

void setKakiPilihan(CommandParameter& p){
  kakiPilihan = p.NextParameterAsInteger();
}

void setKakiRotasi(CommandParameter& p){
  int rPaha = p.NextParameterAsInteger();
  int rBetis = p.NextParameterAsInteger();
  int rTelapak = p.NextParameterAsInteger();
  setKakiRotasiVariabel(rPaha, rBetis, rTelapak);
}

void setKakiRotasiVariabel(int rPaha, int rBetis, int rTelapak){
  paha_rotation = rPaha;
  betis_rotation = rBetis;
  telapak_rotation = rTelapak;
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
  float sudutPaha = p.NextParameterAsInteger();
  float sudutBetis = p.NextParameterAsInteger();
  float sudutTelapak = p.NextParameterAsInteger();
  
  int rotasiPaha = p.NextParameterAsInteger();
  int rotasiBetis = p.NextParameterAsInteger();
  int rotasiTelapak = p.NextParameterAsInteger();
  
  if(rotasiPaha != 1){sudutPaha *= -1;}
  if(rotasiBetis != 1){sudutBetis *= -1;}
  if(rotasiTelapak != 1){sudutTelapak *= -1;}
  
  vec3_t v = { sudutPaha , sudutBetis , sudutTelapak }; 
  listGerakan.Add(v);
  printGerakan();
  Panel.SetText("CountSavedMove",listGerakan.Count());
}

void clearGerakan(){
  listGerakan.Clear();
  Panel.SetText("CountSavedMove",listGerakan.Count());
}

void printGerakan(){
  Serial.println("Gerakan");
  for (int i = 0; i < listGerakan.Count(); i++)
  {
    Serial.print(listGerakan[i].x);
    Serial.print(" ");
    Serial.print(listGerakan[i].y);
    Serial.print(" ");
    Serial.println(listGerakan[i].z);
  }
}
