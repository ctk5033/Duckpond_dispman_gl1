
#include "Duck.h"

#include "DuckData.h"

#include "Duckling.h"

#include "Egg.h"
#include "Pond.h"

#include "Fly.h"
#include "Fish.h"

#include "PopText.h"

#include "MainGame.h"

Duck::Duck(Pond* spond, Player* splayer, int sx, int sy) : Animal(spond, sx, sy)
{
 player = splayer;
 player->playerButtonList.Add(this);



 color = DuckData::colorDuck;



 sprite = new Sprite(DuckData::imDuck, 0,0,16,16);

 aMoveGround  = new AnimationData(1,0,2,0,5);
 aMoveWater = new AnimationData(3,0,4,0,5);
 aMoveUnderWater = new AnimationData(0,1,3,1,5);
 aMoveAir = new AnimationData(6,0,7,0,5);
 aIdleGround = new AnimationData(0,0,0,0,5);
 aIdleWater = new AnimationData(3,0,3,0,5);
 aIdleUnderWater = new AnimationData(0,1,3,1,5);
 aIdleAir = new AnimationData(6,0,7,0,5);

 aEat = new AnimationData(4,2,5,2,5);

 aIdle = aIdleGround;
 aMove = aMoveGround;

 hitBox.SetBox(4,11,8,3);

 score = 0;

 air = 5;
 airTimer = 0;


 sprite->StartAnimation(aIdle);

 pond = spond;

 hold = NULL;

 fly = true;

 food = -1;

 eggTimer = -1;

 scoreTimer = 0;

}

Duck::~Duck()
{
 player->playerButtonList.RemoveElement(this);
}

void Duck::AddScore(int s, Entity* ent)
{
 if (!alive || s < 0){return;}
 score = score + s;
 pond->DispScore(s, ent->x, ent->y);
}

void Duck::Update()
{
 Animal::Update();


 if (hold != NULL)
 {
  hold->tickTime =  0;
  if (sprite->pos == 1) { hold->x = x - 4;}
  else {hold->x = x + 5;}

  if (sprite->IsCurrentAnimation(aIdleWater) || sprite->IsCurrentAnimation(aMoveWater)){hold->y = y - 5;}
  else {hold->y = y - 7;}
  hold->tx = tx;
  hold->ty = ty;
  hold->fallY = ty;
 }

 GList<Entity*> entList = pond->GetEntsOnTile(tx, ty);
 for (int i = 0; i < entList.GetSize(); i++)
 {
  if (dynamic_cast<Fly*>(entList[i]) || dynamic_cast<Fish*>(entList[i]))
  {
   entList[i]->alive = false;
   DuckData::wavEat->Play();
   food = food + 1;
   break;
  }
 }

 if (food >= maxFood-1)
 {
  if (eggTimer == -1){eggTimer = 2;}
  food = food - maxFood;
 }




}

void Duck::Draw()
{
 Animal::Draw();
}


void Duck::Kill()
{
 Animal::Kill();
 DuckData::wavDie->Play();
}


void Duck::LayEgg()
{
 DuckData::wavLayEgg->Play();

 pond->entList.Add(new Egg(pond, this, tx,ty));
}


void Duck::ActivateA(Player* player)
{
 if (!alive)
 {
  DuckData::wavStart->Play();
  MainFile::StartSub(new MainGame(new DuckData()));

  return;
 }

 Entity* oldHold = hold;
 hold = NULL;
 GList<Entity*> entList = pond->GetEntsOnTile(tx, ty);
 for (int i = 0; i < entList.GetSize(); i++)
 {
  if (oldHold != entList[i] && (dynamic_cast<Egg*>(entList[i]) || dynamic_cast<Duckling*>(entList[i])))
  {
   hold = entList[i];
   DuckData::wavDuckGrab->Play();
   break;
  }
 }

}

void Duck::OnTick()
{
 if (eggTimer > 0){eggTimer--;}
 else if (eggTimer == 0){eggTimer = -1; LayEgg();}


 scoreTimer++;
 if (scoreTimer >= 10)
 {
  for (int i = 0; i < ducklingList.GetSize(); i++)
  {
   AddScore(5*(i+1), ducklingList[i]);
  }
  scoreTimer = 0;
 }

 airTimer++;
 if (airTimer > 1)
 {
  if (InWater())
  {
   air--;
   DuckData::wavAir->Play();
   pond->poptextList.Add(new PopText("AIR -1", x,y, pond->colorGround));
  }
  else {air++;}
  if (air > 5){air = 5;}
  else if (air < 0){alive = false;}

  airTimer = 0;
 }

}

void Duck::ActivateB(Player* player)
{
 //LayEgg();

}

void Duck::OnKeyUp(Player* player)
{
 if (!AtTarget()){return;}
 if (MoveY(-1)){DuckData::wavStep->Play();}
}

void Duck::OnKeyDown(Player* player)
{
 if (!AtTarget()){return;}

 if (OnGround()){Eat();}
 else
 {
  if (MoveY(1)){DuckData::wavStep->Play();}
 }

}

void Duck::OnKeyLeft(Player* player)
{
 if (!AtTarget()){return;}
 if (MoveX(-1)){DuckData::wavStep->Play();}
}

void Duck::OnKeyRight(Player* player)
{
 if (!AtTarget()){return;}
 //GameEngine::MessageBox("RIGHT!");
 if (MoveX(1)){DuckData::wavStep->Play();}
}

void Duck::OnKeyEnter(Player* player)
{

}
