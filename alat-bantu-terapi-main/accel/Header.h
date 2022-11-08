#include <MegunoLink.h>
#include <CommandHandler.h>
#include <ArduinoTimer.h>
#include <AccelStepper.h>
#include <vector_type.h>
#include <Math.h>
#include "ListLib.h"

#define KANAN 1
#define KIRI 0
#define BELAKANG -1
#define DEPAN 1

#define MOTOR_LIST {'RT','RM','RB','LT','LM','LB'}

#define STEPS_PER_ROTATION 800

#define TINGGI_SELURUH 92.5
#define PANJANG_PAHA 41
#define PANJANG_BETIS 41
#define PANJANG_TELAPAK 24.7
#define TINGGI_MATAKAKI 10.5

int kakiPilihan = KANAN;
int paha_rotation = DEPAN;
int betis_rotation = BELAKANG;
int telapak_rotation = BELAKANG;
int motor_speed = 50;
int motor_accel = 20;

List<vec3_t> listGerakan; 

CommandHandler<> SerialCmds;

float getSudutTelapak(float sudutPaha, float sudutBetis){
  float tinggiPaha = PANJANG_PAHA * cos(sudutPaha * PI / 180.0);
  float tinggiBetis = PANJANG_BETIS * cos(sudutBetis * PI / 180.0);
  float tinggiTelapak = TINGGI_SELURUH - tinggiPaha - tinggiBetis;
    
  float sudutTelapak =  90 - (acos( (tinggiTelapak / PANJANG_TELAPAK + TINGGI_MATAKAKI) * PI / 180.0 ) * 180/PI);
  Serial.print("Telapak : ");
  Serial.println(sudutTelapak );
  if(sudutTelapak > 30){
    sudutTelapak = 15;
  }
  return sudutTelapak ; 
}

void printGerakan(){
  Serial.println("Gerakan");
  for (int i = 0; i < listGerakan.Count(); i++)
  {
    Serial.print(listGerakan[i].x);
    Serial.print(" ");
    Serial.print(listGerakan[i].y);
    Serial.print(" ");
    Serial.print(listGerakan[i].z);
  }
}
