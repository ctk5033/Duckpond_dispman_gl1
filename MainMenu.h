

#ifndef MAINMENU_H
#define MAINMENU_H

#include "MainSub.h"
#include "Player.h"

class DuckData;
class Pond;

class MainMenu : public MainSub, public PlayerButton
{
 public:

 MainMenu();
 ~MainMenu();

 DuckData* data;

 bool started;

 Pond* pond;

 int phase;

 void Start();
 void Update();
 void Draw();

 void ButtonPress();

 void OnKeyEnter(Player* player);
 void ActivateA(Player* player);

 void HandleKeys();
};



#endif
