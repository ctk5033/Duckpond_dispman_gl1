
#ifndef PLAYER_H
#define PLAYER_H 1

#include "MainFile.h"







class Player;

class PlayerButton
{
 public:
  PlayerButton()
  {

  }
  virtual ~PlayerButton(){}

  virtual void ActivateA(Player* player){}
  virtual void ActivateB(Player* player){}
  virtual void OnKeyUp(Player* player){}
  virtual void OnKeyDown(Player* player){}
  virtual void OnKeyLeft(Player* player){}
  virtual void OnKeyRight(Player* player){}
  virtual void OnKeyEnter(Player* player){}



};

class Player
{
 public:
  Player(int snum);
  ~Player();


  int num;







  bool inGame;

  void Update();





  void HandleKeys();

  void SetKeys(int u, int d, int l, int r, int a, int b, int e);



  int keyUp;
  int keyDown;
  int keyLeft;
  int keyRight;

  int joyButtonA;
  int joyButtonB;
  int joyButtonEnter;

  int keyA;
  int keyB;
  int keyEnter;

  bool KeyLeft();
  bool KeyRight();
  bool KeyUp();
  bool KeyDown();
  bool KeyA();
  bool KeyB();
  bool KeyEnter();

  void OnKeyA();
  void OnKeyB();
  void OnKeyUp();
  void OnKeyDown();
  void OnKeyLeft();
  void OnKeyRight();
  void OnKeyEnter();

  bool delKeyA;
  bool delKeyB;
  bool delKeyLeft;
  bool delKeyRight;
  bool delKeyUp;
  bool delKeyDown;
  bool delKeyEnter;

  GList<PlayerButton*> playerButtonList;




};


#endif




