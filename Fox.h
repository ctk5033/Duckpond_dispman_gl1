

#ifndef FOX_H
#define FOX_H 1

#include "Animal.h"

class Fox : public Animal
{
 public:
  Fox(Pond* spond, int sx, int sy);
  ~Fox();

  int moveTimer;
  bool triggered;
  void OnTick();

  void Update();

  int eatingTimer;




};


#endif
