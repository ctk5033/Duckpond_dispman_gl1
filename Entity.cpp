
#include "Entity.h"
#include "Pond.h"

  Entity::Entity(Pond* spond, int sx, int sy)
  {

   pond = spond;
   sprite = NULL;

   aIdle = NULL;

   color.SetColor(1,1,1);

   speed = 3.0f;

   alive = true;
   dead = false;

   fly = false;
   floatWater = false;

   allowBoundsY = false;

   tx = sx;
   ty = sy;
   x = sx*Pond::TILE_W;
   y = sy*Pond::TILE_H;

   hitBox.SetBox(0,0,16,16);

   allowBoundsX = false;

   tickTime = 0;
   tickTimeMax = 20;

   grabbed = NULL;

   fallY = ty;
  }

  Entity::~Entity()
  {
   delete sprite;
  }


  void Entity::Kill()
  {
   alive = false;
  }


  void Entity::OnTick()
  {
   if (OnGround() || OnWaterGround())
   {

   }
   else
   {
    if (AtTarget() && !fly)
    {
     if (!(floatWater && OnWater()))
     {
      MoveY(1);
     }
    }
   }

   if (OnWater() && floatWater)
   {
    fallY = ty;
   }

   if (OnGround())
   {
    if (fallY != ty)
    {
     OnHitGround();
    }
   }

  }

  void Entity::OnHitGround()
  {

  }




  void Entity::Update()
  {

   tickTime++;
   if (tickTime >= tickTimeMax)
   {
    if (!grabbed){OnTick();}
    tickTime = 0;
   }

   float distToTarget = sqrt( (ty*Pond::TILE_H - y)*(ty*Pond::TILE_H - y) + (tx*Pond::TILE_W-x)*(tx*Pond::TILE_W-x));

   if (distToTarget <= speed)
   {
    x = tx*Pond::TILE_W;
    y = ty*Pond::TILE_H;
   }
   else
   {
    float angle = atan2(ty*Pond::TILE_H - y, tx*Pond::TILE_W-x);
    x = x + cos(angle)*speed;
    y = y + sin(angle)*speed;
   }



   if (sprite != NULL)
   {
    sprite->Update();

    if (!sprite->IsCurrentAnimation(aIdle) && sprite->IsAnimationFinished() && !dead && grabbed == NULL)
    {
     sprite->StartAnimation(aIdle);
    }

   }
  }

  void Entity::Draw()
  {
   if (sprite != NULL)
   {
    GameEngine::SetColor(color);
    sprite->x = x;
    sprite->y = y;
    sprite->Draw();
    GameEngine::SetColor(1,0,0,.5f);

    //GameDraw::DrawBox(x+hitBox.x, y + hitBox.y, hitBox.w, hitBox.h);
   }
  }



  bool Entity::AtTarget()
  {
    return x == tx*Pond::TILE_W && y == ty*Pond::TILE_H;

  }

  bool Entity::AtPosition(int px, int py, bool atTarget)
  {
   return (AtTarget() || !atTarget) && px == tx && py == ty;
  }


 bool Entity::MoveX(int dx)
 {
  if (InWater() && ((dx < 0 && tx == pond->bankLeftW) || (dx > 0 && tx == pond->w - pond->bankRightW - 1)) || tx <= 0 && dx < 0 && !allowBoundsX || tx > pond->w-2 && dx > 0 && !allowBoundsX )
  {
   sprite->pos = dx;
   return false;
  }


  tx = tx + dx;
  sprite->pos = dx;
  return true;
 }

 bool Entity::MoveY(int dy)
 {
  if (InWater() && ty >= pond->groundY + pond->waterH-1  && dy > 0 || OnGround() && dy > 0 || ty <= 2 && dy < 0 && !allowBoundsY)
  {
   return false;
  }



  ty = ty + dy;

  return true;

 }



  bool Entity::InWater()
  {
   if (tx >= pond->bankLeftW && tx < pond->w - pond->bankRightW && ty >= pond->groundY) {return true;}
   return false;
  }

  bool Entity::AboveWater()
  {
   if (tx >= pond->bankLeftW && tx < pond->w - pond->bankRightW && ty < pond->groundY) {return true;}
   return false;
  }


  bool Entity::OnWater()
  {
   if (tx >= pond->bankLeftW && tx < pond->w - pond->bankRightW && ty == pond->groundY-1) {return true;}
   return false;
  }

  bool Entity::InAir()
  {
   if (ty < pond->groundY-1){return true;}
   return false;
  }

  bool Entity::OnGround()
  {
   if ((tx < pond->bankLeftW || tx >= pond->w - pond->bankRightW) && ty == pond->groundY-1) {return true;}
   return false;
  }

  bool Entity::OnWaterGround()
  {
   if (tx >= pond->bankLeftW && tx < pond->w - pond->bankRightW && ty == pond->groundY + pond->waterH - 1) {return true;}
   return false;
  }


