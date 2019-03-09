

#include "Fly.h"
#include "DuckData.h"

Fly::Fly(Pond* spond, int sx, int sy) : Animal(pond, sx, sy)
{
 color.SetColor(0,0,0);
 sprite = new Sprite(DuckData::imDuck, 0,0,16,16);
 aMoveGround  = new AnimationData(0,4,7,4,5);
 aMoveWater = new AnimationData(0,4,7,4,5);
 aMoveUnderWater = new AnimationData(0,4,7,4,5);
 aMoveAir = new AnimationData(0,4,7,4,5);
 aIdleGround = new AnimationData(0,4,7,4,5);
 aIdleWater = new AnimationData(0,4,7,4,5);
 aIdleUnderWater = new AnimationData(0,4,7,4,5);
 aIdleAir = new AnimationData(0,4,7,4,5);

 aIdle = aIdleGround;
 aMove = aMoveGround;

 moveTimer = 0;

 playMoveAnimation = false;


 sprite->StartAnimation(aIdle);

 sprite->curFrame = GameEngine::RandomFull()%8;

 pond = spond;

 fly = true;
}

Fly::~Fly()
{

}

void Fly::OnTick()
{
 Animal::OnTick();


 moveTimer++;
 if (moveTimer%5 == 0)
 {
  int r = GameEngine::RandomFull()%4;
  if (r == 0){MoveY(-1);}
  else if (r ==  1){MoveX(1);}
  else if (r ==  2 && !OnWater()){MoveY(1);}
  else if (r ==  3 ){MoveX(-1);}

 }

}
