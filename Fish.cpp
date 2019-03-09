
#include "Fish.h"
#include "Pond.h"
#include "DuckData.h"

Fish::Fish(Pond* spond, int sx, int sy) : Animal(pond, sx, sy)
{
 color.SetColor(0,0,0);
 sprite = new Sprite(DuckData::imDuck, 0,0,16,16);
 aMoveGround  = new AnimationData(0,5,7,5,5);
 aMoveWater = new AnimationData(0,5,7,5,5);
 aMoveUnderWater = new AnimationData(0,5,7,5,5);
 aMoveAir = new AnimationData(0,5,7,5,5);
 aIdleGround = new AnimationData(0,5,7,5,5);
 aIdleWater = new AnimationData(0,5,7,5,5);
 aIdleUnderWater = new AnimationData(0,5,7,5,5);
 aIdleAir = new AnimationData(0,5,7,5,5);

 aIdle = aIdleGround;
 aMove = aMoveGround;

 moveTimer = 0;

 playMoveAnimation = false;

 sprite->StartAnimation(aIdle);

 sprite->curFrame = GameEngine::RandomFull()%8;

 pond = spond;

}

Fish::~Fish()
{

}

void Fish::OnTick()
{
 Animal::OnTick();

  moveTimer++;
 if (moveTimer%5 == 0)
 {
  int r = GameEngine::RandomFull()%4;
  if (r == 0 && ty > pond->waterH+1){MoveY(-1);}
  else if (r ==  1){MoveX(1);}
  else if (r ==  2 ){MoveY(1);}
  else if (r ==  3 ){MoveX(-1);}

 }
}
