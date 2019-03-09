
#ifndef DUCKLING_H
#define DUCKLING_H 1

#include "Animal.h"

class Duckling : public Animal
{
 public:
  Duckling(Pond* spond, Animal* smother, int sx, int sy);
  ~Duckling();

  Animal* mother;

  void Update();
  void OnTick();

  void Kill();



};



#endif
