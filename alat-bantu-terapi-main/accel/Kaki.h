#include "Motor.h"

class Kaki{
    public:
    Motor T;
    Motor M;
    Motor B;

    Kaki(){
    }
    
    Kaki(Motor T, Motor M,Motor B){
      this->T = T;
      this->M = M;
      this->B = B;
    }

    void runAuto(){
      while (
        (
          T.stepper.distanceToGo() != 0 ||
          M.stepper.distanceToGo() != 0 ||
          B.stepper.distanceToGo() != 0 
         ) && digitalRead(button)
      ){
        T.stepper.run();
        M.stepper.run();
        B.stepper.run();
      }
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
      //Jarak posisi skrng dgn posisi tujuan
      int selisihPaha = abs(T.mapSteps(T.getCurrentPosition()) - sudutPaha);
      int selisihBetis = abs(M.mapSteps(M.getCurrentPosition()) - sudutBetis);
      int selisihTelapak = abs(B.mapSteps(B.getCurrentPosition()) - sudutTelapak);
      
      //atur kecepatan setiap motor
      this->T.init(motor_speed, motor_accel);
      this->M.init(motor_speed * selisihBetis / selisihPaha, motor_accel * selisihBetis / selisihPaha);
      this->B.init(motor_speed * selisihTelapak / selisihPaha, motor_accel * selisihTelapak / selisihPaha);
      
      this->T.move(sudutPaha, rotasiPaha, ASYNC);  
      this->M.move(sudutBetis, rotasiBetis, ASYNC); 
      this->B.move(sudutTelapak, rotasiTelapak, ASYNC); 
      
    //memberi pulse sampai motor bergerak ke posisi tujuan
      this->run();
      this->print();
    }

    void moveAuto(float sudutPaha, float sudutBetis, float sudutTelapak, int rotasiPaha = paha_rotation, int rotasiBetis = betis_rotation, int rotasiTelapak = telapak_rotation){ 
      //Jarak posisi skrng dgn posisi tujuan
      int selisihPaha = abs(T.mapSteps(T.getCurrentPosition()) - sudutPaha);
      int selisihBetis = abs(M.mapSteps(M.getCurrentPosition()) - sudutBetis);
      int selisihTelapak = abs(B.mapSteps(B.getCurrentPosition()) - sudutTelapak);
      
      //atur kecepatan setiap motor
      this->T.init(motor_speed, motor_accel);
      this->M.init(motor_speed * selisihBetis / selisihPaha, motor_accel * selisihBetis / selisihPaha);
      this->B.init(motor_speed * selisihTelapak / selisihPaha, motor_accel * selisihTelapak / selisihPaha);
      
      this->T.move(sudutPaha, rotasiPaha, ASYNC);  
      this->M.move(sudutBetis, rotasiBetis, ASYNC); 
      this->B.move(sudutTelapak, rotasiTelapak, ASYNC); 
      
    //memberi pulse sampai motor bergerak ke posisi tujuan
      this->runAuto();
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
