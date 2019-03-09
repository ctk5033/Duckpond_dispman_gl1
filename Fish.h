
#ifndef FISH_H
#define FISH_H 1

#include "Animal.h"

class Fish : public Animal
{
public:
  Fish(Pond* spond, int sx, int sy);
  ~Fish();

  void OnTick();

  int moveTimer;
};

#endif
