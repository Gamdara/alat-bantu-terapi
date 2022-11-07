#include <AccelStepper.h>
#include <Math.h>

#define KANAN 1
#define KIRI -1
#define BELAKANG -1
#define DEPAN 1

#define MOTOR_LIST {'RT','RM','RB','LT','LM','LB'}

#define STEPS_PER_ROTATION 800

#define TINGGI_SELURUH 92.5
#define PANJANG_PAHA 41
#define PANJANG_BETIS 41
#define PANJANG_TELAPAK 24.7
#define TINGGI_MATAKAKI 10.5


float getSudutTelapak(float sudutPaha, float sudutBetis){
  float tinggiPaha = PANJANG_PAHA * cos(sudutPaha * PI / 180.0);
  float tinggiBetis = PANJANG_BETIS * cos(sudutBetis * PI / 180.0);
  float tinggiTelapak = TINGGI_SELURUH - tinggiPaha - tinggiBetis;
    
  float sudutTelapak =  90 - (acos( (tinggiTelapak / PANJANG_TELAPAK + TINGGI_MATAKAKI) * PI / 180.0 ) * 180/PI);
  Serial.print("Telapak : ");
  Serial.println(sudutTelapak );
  return sudutTelapak ; 
}
