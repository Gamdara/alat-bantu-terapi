#include "Motor.h"

class Kaki{
    public:
    Motor T;
    Motor M;
    Motor B;
    
    Kaki(Motor T, Motor M,Motor B){
      this->T = T;
      this->M = M;
      this->B = B;
    }

    void run(){
      while (
        T.stepper.distanceToGo() != 0 ||
        M.stepper.distanceToGo() != 0 ||
        B.stepper.distanceToGo() != 0 
      ){
        T.stepper.run();
        M.stepper.run();
        B.stepper.run();
      }
    }

    void move(float sudutPaha, float sudutBetis, float sudutTelapak, int rotasiPaha = paha_rotation, int rotasiBetis = betis_rotation, int rotasiTelapak = telapak_rotation){ 
      //atur kecepatan setiap motor
      this->T.init(motor_speed, motor_accel);
      this->M.init(motor_speed * sudutBetis / sudutPaha, motor_accel * sudutBetis / sudutPaha);
      this->B.init(motor_speed * sudutTelapak / sudutPaha, motor_accel * sudutTelapak / sudutPaha);
      
      this->T.move(sudutPaha, paha_rotation, ASYNC);  
      this->M.move(sudutBetis, betis_rotation, ASYNC); 
      this->B.move(sudutTelapak, telapak_rotation, ASYNC); 
      
    //memberi pulse sampai motor bergerak ke posisi tujuan
      this->run();
      this->print();
    }
    
    void print(){
      Serial.print(T.getCurrentPosition());
      Serial.print(" ");
      Serial.print(M.getCurrentPosition());
      Serial.print(" ");
      Serial.println(B.getCurrentPosition());
    }


};
