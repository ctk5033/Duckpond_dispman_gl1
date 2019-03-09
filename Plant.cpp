
#include "Plant.h"
#include "DuckData.h"

Plant::Plant(Pond* spond, int sx, int sy) : Entity(spond, sx, sy)
{
 respawn = 0;
 life = 3;

 color = GColor(1,109,27);

 sprite = new Sprite(DuckData::imDuck, 0,0,16,16);

 aIdle = new AnimationData(7,1,7,1,5);

 sprite->StartAnimation(aIdle);



}

Plant::~Plant()
{

}

void Plant::Update()
{
 Entity::Update();

 aIdle->sF = 4 + life;
 aIdle->eF = 4 + life;
 sprite->StartAnimation(aIdle);
}

void Plant::OnTick()
{
 Entity::OnTick();

 respawn++;
 if (life > 0 && respawn >= 10 || life == 0 && respawn >= 35)
 {
  life++;
  respawn = 0;
 }
 if (life >= 3){life = 3; respawn = 0;}
}


int Plant::TakeBite()
{
 if (life > 0)
 {
  life = life - 1;
  return 1;
 }

 return 0;

}



