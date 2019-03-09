
#ifndef FLY_H
#define FLY_H 1

#include "Animal.h"

class Fly : public Animal
{
public:
  Fly(Pond* spond, int sx, int sy);
  ~Fly();

  void OnTick();

  int moveTimer;

};

#endif
