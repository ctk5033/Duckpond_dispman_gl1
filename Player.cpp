
#include "Player.h"





  Player::Player(int snum)
  {
   num = snum;


   SetKeys(0, 0, 0, 0, 0,0, 0);

   joyButtonA = 1;
   joyButtonB = 2;
   joyButtonEnter = 9;

   delKeyA = true;
   delKeyB = true;
   delKeyLeft = true;
   delKeyRight = true;
   delKeyUp = true;
   delKeyDown = true;
   delKeyEnter = true;


   inGame = false;




  }


  Player::~Player()
  {

  }





  void Player::SetKeys(int u, int d, int l, int r, int a, int b, int e)
  {
   keyUp = u;
   keyDown = d;
   keyLeft = l;
   keyRight = r;

   keyA = a;
   keyB = b;
   keyEnter = e;
  }

  void Player::OnKeyA()
  {
   for (int i = 0; i < playerButtonList.GetSize(); i++)
   {
    playerButtonList[i]->ActivateA(this);
   }
  }

  void Player::OnKeyB()
  {
   for (int i = 0; i < playerButtonList.GetSize(); i++)
   {
    playerButtonList[i]->ActivateB(this);
   }
  }

  void Player::OnKeyUp()
  {
   for (int i = 0; i < playerButtonList.GetSize(); i++)
   {
    playerButtonList[i]->OnKeyUp(this);
   }
  }

  void Player::OnKeyDown()
  {
    for (int i = 0; i < playerButtonList.GetSize(); i++)
   {
    playerButtonList[i]->OnKeyDown(this);
   }
  }

  void Player::OnKeyLeft()
  {
   for (int i = 0; i < playerButtonList.GetSize(); i++)
   {
    playerButtonList[i]->OnKeyLeft(this);
   }
  }

  void Player::OnKeyRight()
  {

   for (int i = 0; i < playerButtonList.GetSize(); i++)
   {
    playerButtonList[i]->OnKeyRight(this);
   }
  }

  void Player::OnKeyEnter()
  {
   for (int i = 0; i < playerButtonList.GetSize(); i++)
   {
    playerButtonList[i]->OnKeyEnter(this);
   }
  }




  void Player::Update()
  {


  }






  void Player::HandleKeys()
  {
   if (KeyUp())
   {
    if (!delKeyUp) {delKeyUp = true; OnKeyUp();}
   }
   else {delKeyUp = false;}

   if (KeyDown())
   {
    if (!delKeyDown) {delKeyDown = true; OnKeyDown();}
   }
   else {delKeyDown = false;}


   if (KeyLeft())
   {
    if (!delKeyLeft) {delKeyLeft = true; OnKeyLeft();}
   }
   else {delKeyLeft = false;}

   if (KeyRight())
   {
    if (!delKeyRight) {delKeyRight = true; OnKeyRight();}
   }
   else {delKeyRight = false;}


   if (KeyA())
   {
    if (!delKeyA) {delKeyA = true; OnKeyA();}
   }
   else {delKeyA = false;}

   if (KeyB())
   {
    if (!delKeyB) {delKeyB = true; OnKeyB();}
   }
   else {delKeyB = false;}

   if (KeyEnter())
   {
    if (!delKeyEnter) {delKeyEnter = true; OnKeyEnter();}
   }
   else {delKeyEnter = false;}
   }


  bool Player::KeyLeft()
  {
   return GameEngine::GetKey(keyLeft) || GameEngine::JoystickX(num) == -1;
  }

  bool Player::KeyRight()
  {

   return GameEngine::GetKey(keyRight) || GameEngine::JoystickX(num) == 1;
  }

  bool Player::KeyUp()
  {
   return GameEngine::GetKey(keyUp) || GameEngine::JoystickY(num) == -1;
  }

  bool Player::KeyDown()
  {
   return GameEngine::GetKey(keyDown) || GameEngine::JoystickY(num) == 1;
  }

  bool Player::KeyA()
  {
   return GameEngine::GetKey(keyA) || GameEngine::JoystickButton(num, joyButtonA);
  }

  bool Player::KeyB()
  {
   return GameEngine::GetKey(keyB) || GameEngine::JoystickButton(num, joyButtonB) || GameEngine::JoystickButton(num, 2);
  }

  bool Player::KeyEnter()
  {
   return GameEngine::GetKey(keyEnter) || GameEngine::JoystickButton(num, joyButtonEnter);
  }
