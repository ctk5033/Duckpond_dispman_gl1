
#include "Egg.h"

#include "DuckData.h"
#include "Pond.h"
#include "Duckling.h"
#include "Animal.h"
#include "Duck.h"
#include "PopText.h"

  Egg::Egg(Pond* spond, Animal* smother, int sx, int sy) : Entity(spond, sx, sy)
  {

   color = DuckData::colorDuck;

   mother = smother;

   sprite = new Sprite(DuckData::imDuck, 0,0,16,16);

   aIdle = new AnimationData(0,2,0,2,5);
   aBreak = new AnimationData(1,2,3,2,5);



   hatchTimer = 10;

   fallY = ty;

   hatched = false;

   sprite->StartAnimation(aIdle);

   pond = spond;
  }

  Egg::~Egg()
  {
   delete aIdle;
   delete aBreak;
  }

  void Egg::Update()
  {
   if (sprite->IsCurrentAnimation(aBreak) && sprite->IsAnimationFinishedNext())
   {
    alive = false;
   }

   Entity::Update();
  }

  void Egg::OnTick()
  {
   Entity::OnTick();

   if (hatchTimer > 0)
   {
    pond->poptextList.Add(new PopText("HATCHING", x,y, pond->colorGround));
    hatchTimer--;
   }
   else
   {
    Hatch();
   }


  }

  void Egg::OnHitGround()
  {
   Break();
  }

  void Egg::Hatch()
  {
   hatched = true;
   if (!sprite->IsCurrentAnimation(aIdle)){return;}
   sprite->StartAnimation(aBreak);

   DuckData::wavHatch->Play();

   Duckling* d = new Duckling(pond, mother, tx, ty);
   pond->entList.Add(d);
   if (InWater()){d->dead = true;(dynamic_cast<Duck*>(mother))->AddScore(-10, this);}
   else
   {
   (dynamic_cast<Duck*>(mother))->AddScore(10, this);

    (dynamic_cast<Duck*>(mother))->ducklingList.Add(d);
   }

  }

  void Egg::Break()
  {
   DuckData::wavHatch->Play();
   if (!sprite->IsCurrentAnimation(aIdle)){return;}
   sprite->StartAnimation(aBreak);
   (dynamic_cast<Duck*>(mother))->AddScore(-10,this);

  }

  void Egg::Kill()
  {
   alive = false;
   (dynamic_cast<Duck*>(mother))->AddScore(-10,this);

 //  (dynamic_cast<Duck*>(mother))->AddScore(-10, this);
  }
