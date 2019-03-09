
#ifndef DUCK_H
#define DUCK_H 1

#include "Animal.h"
#include "Player.h"

class Duckling;

class Duck : public Animal, public PlayerButton
{
 public:
  Duck(Pond* spond, Player* splayer, int sx, int sy);
  ~Duck();

  Player* player;


  void Update();
  void Draw();

  Entity* hold;

  int eggTimer;

  void OnTick();

  void Kill();

  void AddScore(int s, Entity* ent);
  int score;

  int scoreTimer;

  int air;
  int airTimer;

  GList<Duckling*> ducklingList;


  void LayEgg();

  void ActivateA(Player* player);
  void ActivateB(Player* player);
  void OnKeyUp(Player* player);
  void OnKeyDown(Player* player);
  void OnKeyLeft(Player* player);
  void OnKeyRight(Player* player);
  void OnKeyEnter(Player* player);


};


#endif
