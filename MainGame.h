

#ifndef MAINGAME_H
#define MAINGAME_H 1

#include "MainSub.h"
#include "DuckData.h"


class Pond;
class Duck;
class Fox;

class MainGame : public MainSub
{
 public:
  MainGame(DuckData* sdata);
  ~MainGame();

  DuckData* duckData;
  Pond* pond;
  Duck* duck;

  Fox* foxL;
  Fox* foxR;

  int timer;

  int birdTimer;

  void AddFlyFish();

  void Start();

  void Update();
  void Draw();



  void HandleKeys();



};



#endif
