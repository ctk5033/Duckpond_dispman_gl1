#ifndef ANIMAL_H
#define ANIMAL_H 1


#include "Entity.h"

class Animal : public Entity
{
 public:
  Animal(Pond* spond, int sx, int sy);

  ~Animal();

  AnimationData* aMove;
  AnimationData* aMoveGround;
  AnimationData* aMoveWater;
  AnimationData* aMoveUnderWater;
  AnimationData* aMoveAir;
  AnimationData* aIdleGround;
  AnimationData* aIdleWater;
  AnimationData* aIdleUnderWater;
  AnimationData* aIdleAir;

  AnimationData* aEat;

  AnimationData* aDead;

   int food;
   int maxFood;

   bool playMoveAnimation;

  void Update();

  void Draw();

  void Eat();

  void UpdateAnimations();

  bool MoveX(int dx);
  bool MoveY(int dy);



};


#endif
