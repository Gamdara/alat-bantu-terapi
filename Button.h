
#define MAX_STATE 5
#define MIN_STATE 0

class Button{
  public:
    int pin;
    int state;
    
    Button (int pin){
      this->pin = pin;
      this->state = MIN_STATE;
    }

    void init(){
      pinMode(this->pin, INPUT);
    }

    int readButton(){
      return digitalRead(pin);    
    }

    void incState(){
      if(this->state == MAX_STATE) this->state = MIN_STATE;
      else this->state++;
    }

    void decState(){
      if(this->state == MIN_STATE) this->state = MAX_STATE;
      else this->state--;
    }
};
