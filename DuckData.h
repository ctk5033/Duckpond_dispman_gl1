
#ifndef DUCKDATA_H
#define DUCKDATA_H 1

#include "Player.h"
#include "MainFile.h"

class DuckData
{
 public:
  DuckData();
  ~DuckData();

  int score;
  Player* player;

  static GColor colorDuck;

  static GImage* imDuck;

  static GSound* wavStart;
  static GSound* wavDie;
  static GSound* wavPoints;
  static GSound* wavLosePoints;
  static GSound* wavStep;
  static GSound* wavHatch;
  static GSound* wavBite;
  static GSound* wavGrab;
  static GSound* wavDuckGrab;
  static GSound* wavEat;
  static GSound* wavLayEgg;
  static GSound* wavAir;

  static void InitData();


};

#endif
