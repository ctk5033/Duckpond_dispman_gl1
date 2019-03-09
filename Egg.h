
#ifndef EGG_H
#define EGG_H 1

#include "Entity.h"

class Animal;

class Egg : public Entity
{
 public:
  Egg(Pond* spond, Animal* smother, int sx, int sy);
  ~Egg();

  int hatchTimer;

  Animal* mother;

  void OnHitGround();


  bool hatched;

  AnimationData* aBreak;

  void Update();

  void OnTick();

  void Hatch();
  void Break();

  void Kill();

};


#endif
