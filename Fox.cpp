
#include "Fox.h"
#include "DuckData.h"
#include "Pond.h"

#include "Duck.h"
#include "Duckling.h"
#include "Egg.h"

 Fox::Fox(Pond* spond, int sx, int sy) : Animal(spond, sx,sy)
 {

    color.SetColor(197,76,32);

    sprite = new Sprite(DuckData::imDuck, 0,0,23,16);

    aMoveGround  = new AnimationData(1,6,2,6,5);
    aMoveWater = new AnimationData(0,6,2,6,5);
    aMoveUnderWater = new AnimationData(0,6,2,6,5);
    aMoveAir = new AnimationData(0,6,2,6,5);
    aIdleGround = new AnimationData(0,6,0,6,5);
    aIdleWater = new AnimationData(0,6,0,6,5);
    aIdleUnderWater = new AnimationData(0,6,0,6,5);
    aIdleAir = new AnimationData(0,6,0,6,5);

    aEat = new AnimationData(3,6,4,6,5);

    aIdle = aIdleGround;
    aMove = aMoveGround;
    sprite->StartAnimation(aIdle);

    pond = spond;

    moveTimer = 0;

    allowBoundsX = true;

    triggered = false;

    hitBox.SetBox(2,6,18,10);

    speed = 1.0f;

    eatingTimer = 0;

    if (tx > pond->w/2){sprite->pos = -1;}


 }

 Fox::~Fox()
 {

 }

 void Fox::Update()
 {
  Animal::Update();


  if (eatingTimer > 0) {eatingTimer--;}
  else
  {
   aIdle = aIdleGround;
  }

  for (int i = 0; i < pond->entList.GetSize(); i++)
  {
      if (pond->entList[i]->alive && hitBox.BoxCollide(x,y, pond->entList[i]->hitBox, pond->entList[i]->x, pond->entList[i]->y) && (dynamic_cast<Duck*>(pond->entList[i]) || dynamic_cast<Duckling*>(pond->entList[i]) || dynamic_cast<Egg*>(pond->entList[i])))
      {
       pond->entList[i]->Kill();
       aIdle = aEat;
       sprite->StartAnimation(aEat);
       eatingTimer = 30;
       DuckData::wavBite->Play();
       break;
      }
  }
 }


 void Fox::OnTick()
 {
  if (eatingTimer > 0){return;}

  if (triggered)
  {
   moveTimer++;
   if (moveTimer > 1)
   {
    moveTimer = 0;
    MoveX(sprite->pos);
    if (sprite->pos == 1 && OnWater()){tx--; sprite->pos = -1;}
    else if (sprite->pos == -1 && OnWater()){tx++; sprite->pos = 1;}
   }

   if (tx < -1 || tx > pond->w)
   {
    triggered = false;
    if (x > pond->w/2){sprite->pos = -1;}
    else {sprite->pos = 1;}
   }
  }


 }
