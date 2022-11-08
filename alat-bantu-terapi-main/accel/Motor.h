#define DEFAULT_SPEED 50
#define DEFAULT_ACCEL 20
#define ASYNC true
#define BLOCKING false
#define USEDEGREE true
#define USESTEP false

class Motor{
  public:
    AccelStepper stepper;
    int group = -1;

    Motor(){
    }
    
    Motor(int pul, int dir){
      stepper = AccelStepper(1, pul, dir); 
    }

    void init(int speed = DEFAULT_SPEED, int accel = DEFAULT_ACCEL){
      stepper.setSpeed(speed);
      stepper.setAcceleration(accel);
    }

    void move(int data,int dir = DEPAN,bool type = ASYNC,bool useDegree = true){
      if(type == ASYNC) moveAsyn(data, dir, useDegree );
      else moveBlocking(data, dir, useDegree );
    }

    void moveAsyn(int data,int dir = DEPAN, bool useDegree = true){
      if(useDegree) stepper.moveTo(mapDegree(data * this->group * dir));
      else stepper.moveTo(data * this->group * dir);
    }

    void moveBlocking(int data,int dir = DEPAN, bool useDegree = true){
      if(useDegree) stepper.runToNewPosition(mapDegree(data * this->group * dir));
      else stepper.runToNewPosition(data * this->group * dir);
    }

    int mapDegree(int deg){
      return map(deg, 0, 360, 0, STEPS_PER_ROTATION) * 30;
    }

    int getCurrentPosition(){
      return stepper.currentPosition();
    }
};
