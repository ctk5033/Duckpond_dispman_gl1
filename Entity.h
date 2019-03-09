
#ifndef ENTITY_H
#define ENTITY_H 1

#include "MainFile.h"

class Pond;

class Entity
{
 public:

  Entity(Pond* spond, int sx, int sy);
  virtual ~Entity();


  Sprite* sprite;
  Pond* pond;

  float x;
  float y;
  int tx;
  int ty;

  bool alive;
  bool dead;

  int tickTime;
  int tickTimeMax;

  int fallY;

  bool allowBoundsX; // allow out of bounds for x
  bool allowBoundsY;

  bool AtTarget();
  bool AtPosition(int px, int py, bool atTarget = false);

  float speed;

  GColor color;

  GBox hitBox;

  bool fly;
  bool floatWater;

  Entity* grabbed;

  AnimationData* aIdle;

  virtual void Update();
  virtual void Draw();

  virtual void OnTick();

  virtual void OnHitGround();

  virtual void Kill();

  bool InWater();
  bool OnWater();
  bool InAir();
  bool AboveWater();
  bool OnGround();
  bool OnWaterGround();


  virtual bool MoveX(int dx);
  virtual bool MoveY(int dy);






};

#endif
