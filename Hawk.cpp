

#include "Hawk.h"
#include "DuckData.h"
#include "Pond.h"
#include "Duck.h"
#include "Duckling.h"

Hawk::Hawk(Pond* spond, int sx, int sy) : Animal(spond, sx,sy)
{
    color.SetColor(145,67,199);

    sprite = new Sprite(DuckData::imDuck, 0,0,19,16);

    aMoveGround  = new AnimationData(0,7,2,7,5);
    aMoveWater = new AnimationData(0,7,2,7,5);
    aMoveUnderWater = new AnimationData(0,7,2,7,5);
    aMoveAir = new AnimationData(0,7,2,7,5);
    aIdleGround = new AnimationData(0,7,2,7,5);
    aIdleWater = new AnimationData(0,7,2,7,5);
    aIdleUnderWater = new AnimationData(0,7,2,7,5);
    aIdleAir = new AnimationData(0,7,2,7,5);

    aEat = new AnimationData(0,7,2,7,5);

    aIdle = aIdleGround;
    aMove = aMoveGround;
    sprite->StartAnimation(aIdle);

    pond = spond;

    moveTimer = 0;

    allowBoundsX = true;

    allowBoundsY = true;

    waver = 0;
    waverAmp = 2.0f;
    waverSpeed = PI/80;

    speed = 1.0f;
    sprite->pos = 1;
    if (tx > pond->w/2){sprite->pos = -1;}

    playMoveAnimation = false;

    dive = 0;
    grab = NULL;

    moveTimerMax = 2;
}

Hawk::~Hawk()
{

}

void Hawk::Update()
{
 Animal::Update();
 waver = waver + waverSpeed;

 if (grab)
 {
  grab->ty = 0;
  grab->tx = 0;

  if (sprite->pos == 1)
  {
   grab->x = x + 9 - 8;
  }
  else
  {
   grab->x = x + 9 - 8;
  }

  grab->y = y + 16 - 4 - 8;
  if (dynamic_cast<Duckling*>(grab))
  {
   grab->y = y + 16 - 4 - 14;
  }
 }

 if (dive == 0) //&& AboveWater())
 {
   for (int i = 0; i < pond->entList.GetSize(); i++)
    {
     if ( (pond->entList[i]->AboveWater() || pond->entList[i]->InAir()) && pond->entList[i]->tx == tx && (dynamic_cast<Duck*>(pond->entList[i]) || dynamic_cast<Duckling*>(pond->entList[i])))
     {

      dive = 1;
      moveTimerMax = 0;
      speed = 2.0f;

      break;
     }
    }

 }
 if (!grab  && alive)
 {
  for (int i = 0; i < pond->entList.GetSize(); i++)
     {
      if ( pond->entList[i]->grabbed == NULL && hitBox.BoxCollide(x,y, pond->entList[i]->hitBox, pond->entList[i]->x, pond->entList[i]->y) && (dynamic_cast<Duck*>(pond->entList[i]) || dynamic_cast<Duckling*>(pond->entList[i])))
      {
       grab = pond->entList[i];
       pond->entList[i]->grabbed = this;
       dive = -1;
       break;
      }
     }
 }

 if (tx < -5 || tx > pond->w + 5)
 {
  alive = false;
 }

}

void Hawk::Draw()
{
    GameEngine::SetColor(color);
    sprite->x = x;
    sprite->y = y + waverAmp*sin(waver);
    sprite->Draw();

    //GameDraw::DrawText(KString("%d",dive), x+30, y);
}

void Hawk::OnTick()
{
 if (moveTimer >= moveTimerMax)
 {
  if (dive == 0)
  {

    MoveX(sprite->pos);


  }
  else if (dive == 1)
  {
   MoveY(1);
   if (OnWater() || OnGround())
   {
    dive = -1;
   }
  /* if (OnWater())
   {
    GList<Entity*> entList = pond->GetEntsOnTile(tx, ty);
    for (int i = 0; i < entList.GetSize(); i++)
    {
     if ((dynamic_cast<Duck*>(entList[i]) || dynamic_cast<Duckling*>(entList[i])) && entList[i]->tx == tx && entList[i]->ty == ty)
     {
      grab = entList[i];
      entList[i]->grabbed = this;
      break;
     }
    }
    dive = -1;
   }*/
  }
  else if (dive == -1)
  {
   MoveY(-1);
   if (ty == 2 && !grab)
   {
    dive = 0;
    moveTimerMax = 2;
    speed = 1.0f;
   }
  }


  moveTimer = 0;
 }

 moveTimer++;


 if (ty < -1)
 {
  if (grab != NULL){grab->Kill(); grab = NULL;}
  alive = false;
 }
}
