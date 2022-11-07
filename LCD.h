#include <LiquidCrystal.h>

class LCD{
  public:
    int rs;
    int en;
    int d4;
    int d5;
    int d6;
    int d7;
    int row;
    int col;
    LiquidCrystal *lcd = NULL;
    
    LCD(int rs,int en,int d4,int d5,int d6,int d7, int row, int col){
      this->rs = rs;
      this->en = en;
      this->d4 = d4;
      this->d5 = d5;
      this->d6 = d6;
      this->d7 = d7;
      this->row = row;
      this->col = col;
    }

    void init(){
      this->lcd = &LiquidCrystal(this->rs, this->en, this->d4, this->d5, this->d6, this->d7);
      this->lcd->begin(this->col,this->row);
    }

    void print(String msg){
       this->lcd->print(msg);
    }

    
};
