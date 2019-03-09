
#include "Animal.h"

#include "Pond.h"

#include "Plant.h"

#include "DuckData.h"

 Animal::Animal(Pond* spond, int sx, int sy) : Entity(spond, sx, sy)
 {
  aMove = NULL;
  pond = spond;

  aMoveGround = NULL;
  aMoveWater = NULL;
  aMoveAir = NULL;
  aMoveUnderWater = NULL;
  aIdleGround = NULL;
  aIdleWater = NULL;
  aIdleAir = NULL;
  aIdleUnderWater = NULL;

  playMoveAnimation = true;

  aEat = NULL;

  aDead = NULL;

  aMove = NULL;

  food = 0;
  maxFood = 5;
 }

 Animal::~Animal()
 {
  delete aMoveGround;
  delete aMoveWater;
  delete aMoveUnderWater;
  delete aMoveAir;
  delete aIdleGround;
  delete aIdleWater;
  delete aIdleAir;
  delete aIdleUnderWater;
  delete aEat;

 }

 void Animal::Update()
 {
   Entity::Update();

   UpdateAnimations();
 }

 void Animal::Draw()
 {
   Entity::Draw();
 }

 void Animal::UpdateAnimations()
 {

    if (OnGround()){aIdle = aIdleGround; aMove = aMoveGround;}
    else if (OnWater()){aIdle = aIdleWater; aMove = aMoveWater;}
    else if (InAir()){aIdle = aIdleAir; aMove = aMoveAir;}
    else if (InWater()){aIdle = aIdleUnderWater; aMove = aMoveUnderWater;}

 }

 void Animal::Eat()
 {
  if (!AtTarget()){return;}
  sprite->StartAnimation(aEat);


  GList<Entity*> entList = pond->GetEntsOnTile(tx, ty);
  for (int i = 0; i < entList.GetSize(); i++)
  {
   if (dynamic_cast<Plant*>(entList[i]))
   {
    DuckData::wavEat->Play();
    food = food + (dynamic_cast<Plant*>(entList[i]))->TakeBite();
    break;
   }
  }
 }


 bool Animal::MoveX(int dx)
 {
  if (sprite->IsCurrentAnimation(aEat)){return false;}

  if (Entity::MoveX(dx))
  {
   UpdateAnimations();
   if (aMove != NULL && playMoveAnimation){sprite->StartAnimation(aMove);}
   return true;
  }

  return false;
 }

 bool Animal::MoveY(int dy)
 {
  if (sprite->IsCurrentAnimation(aEat)){return false;}
  if (Entity::MoveY(dy))
  {
   UpdateAnimations();
   if (aMove != NULL && playMoveAnimation){sprite->StartAnimation(aMove);}

   return true;
  }

  return false;
 }
