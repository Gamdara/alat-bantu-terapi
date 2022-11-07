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

    void print(){
      Serial.print(T.getCurrentPosition());
      Serial.print(" ");
      Serial.print(M.getCurrentPosition());
      Serial.print(" ");
      Serial.println(B.getCurrentPosition());
    }
};
