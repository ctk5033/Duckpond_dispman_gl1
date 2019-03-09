
#include "Duckling.h"

#include "DuckData.h"
#include "Duck.h"
#include "Pond.h"

Duckling::Duckling(Pond* spond, Animal* smother, int sx, int sy) : Animal(spond, sx, sy)
{
 mother = smother;

 color = mother->color;

 sprite = new Sprite(DuckData::imDuck, 0,0,16,16);

 aMoveGround  = new AnimationData(1,3,2,3,5);
 aMoveWater = new AnimationData(3,3,4,3,5);
 aMoveUnderWater = new AnimationData(3,3,4,3,5);
 aMoveAir = new AnimationData(3,3,4,3,5);
 aIdleGround = new AnimationData(0,3,0,3,5);
 aIdleWater = new AnimationData(3,3,3,3,5);
 aIdleUnderWater = new AnimationData(3,3,3,3,5);
 aIdleAir = new AnimationData(3,3,3,3,5);

 aDead = new AnimationData(5,3,5,3,5);

 aIdle = aIdleGround;
 aMove = aMoveGround;



 floatWater = true;

 hitBox.SetBox(6,12,3,3);


 sprite->StartAnimation(aIdle);

 tickTimeMax = 10;

}

Duckling::~Duckling()
{

}

void Duckling::Update()
{
 Animal::Update();

 if (OnGround()){speed = 1.0f;}else {speed = 3.0f;}

 if (dead)
 {
  if (!sprite->IsCurrentAnimation(aDead)){sprite->StartAnimation(aDead);}
 }




}

void Duckling::OnTick()
{


 if (InWater()){ty = ty - 1;}


 Animal::OnTick();

 if (InAir() || dead){return;}

 if (!mother->InWater() || true)
 {
  if (tx < mother->tx)
  {
   GList<Entity*> entList = pond->GetEntsOnTile(tx+1, ty);
   for (int i = 0; i < entList.GetSize(); i++)
   {
    if (dynamic_cast<Duckling*>(entList[i]) && !entList[i]->dead || entList[i] == mother){return;}
   }
   MoveX(1);

  }
  else if (tx > mother->tx)
  {
   GList<Entity*> entList = pond->GetEntsOnTile(tx-1, ty);
   for (int i = 0; i < entList.GetSize(); i++)
   {
    if (dynamic_cast<Duckling*>(entList[i]) && !entList[i]->dead || entList[i] == mother){return;}
   }
   MoveX(-1);

  }
 }

}


void Duckling::Kill()
{

 (dynamic_cast<Duck*>(mother))->ducklingList.RemoveElement(this);
 if (alive && !dead){(dynamic_cast<Duck*>(mother))->AddScore(-10, this);}
 alive = false;

}
