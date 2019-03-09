

#ifndef PLANT_H
#define PLANT_H 1

#include "Entity.h"

class Plant : public Entity
{
 public:
  Plant(Pond* spond, int sx, int sy);
  ~Plant();

  void Update();
  void OnTick();

  int life;
  int respawn;

  int TakeBite();

};

#endif
