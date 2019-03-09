
#ifndef HAWK_H
#define HAWK_H 1

#include "Animal.h"

class Hawk : public Animal
{
 public:
  Hawk(Pond* spond, int sx, int sy);
  ~Hawk();

  float waver;
  float waverSpeed;
  float waverAmp;

  int dive;
  Entity* grab;

  int moveTimerMax;


  void OnTick();
  void Update();
  void Draw();
  int moveTimer;
};



#endif
