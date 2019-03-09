

#include "MainSub.h"







MainSub::~MainSub()
{

}



MainSub::MainSub()
{
 x = 0;
 y = 0;
 w = GameEngine::SCREEN_W;
 h = GameEngine::SCREEN_H;
 active = true;
 originalX = x;
 originalY = y;

 targetX = x;
 targetY = y;

 speed = 5.0f;
 maxSpeed = 15.0f;

 autoDelete = true;
}

MainSub::MainSub(int sx, int sy,int sw, int sh)
{
 x = sx;
 y = sy;
 w = sw;
 h = sh;
 originalX = x;
 originalY = y;
 active = true;

 targetX = x;
 targetY = y;

 speed = 5.0f;
 maxSpeed = 15.0f;
}

void MainSub::Start()
{

}



void MainSub::SetPosition(int sx, int sy)
{
 x = sx;
 y = sy;
}

void MainSub::SetTarget(int sx, int sy)
{
 targetX = sx;
 targetY = sy;
}

void MainSub::MoveTowardTarget(bool smooth)
{

   float xDist = (x - targetX);
   float yDist = (y - targetY);
   float angle = atan2(yDist,xDist)+PI;
   float speed = sqrt(xDist*xDist+yDist*yDist)/this->speed;



   if (speed > maxSpeed){speed = maxSpeed;}

   int endRange = 2;

   if (!smooth)
   {
    speed = maxSpeed;
    endRange = speed;
   }

   if (fabs(x - targetX) <= endRange){ x = targetX;}
   else {x = x + cos(angle)*speed;}

   if (fabs(y - targetY) <= endRange){ y = targetY;}
   else {y = y + sin(angle)*speed;}


}

bool MainSub::AtTarget()
{
 return (x == targetX && y == targetY);
}

bool MainSub::AtOriginal()
{
 return (x == originalX && y == originalY);
}



void MainSub::Update()
{

}

void MainSub::Draw()
{

}

void MainSub::TopDraw()
{

}

void MainSub::HandleKeys()
{

}

void MainSub::OnClickDown(int tx, int ty, int button)
{

}

void MainSub::OnClickUp(int tx, int ty, int button)
{

}

void MainSub::OnClickUpOffScreen(int tx, int ty, int button, MainSub* onScreen)
{

}

void MainSub::OnClickDownOffScreen(int tx, int ty, int button, MainSub* onScreen)
{

}


void MainSub::OnMouseMove(int tx, int ty, float dx, float dy)
{


}

void MainSub::End()
{

}




void MainSub::AddChild(MainSub* child)
{
 childList.Add(child);
 child->Start();
}

void MainSub::AddChildUnder(MainSub* child, MainSub* other)
{
 for (int i = 0; i < childList.GetSize(); i++)
 {
  if (childList[i] == other)
  {
   childList.AddAt(i, child);
   child->Start();
   return;
  }
 }
}

void MainSub::RemoveChild(MainSub* child)
{
 childList.RemoveElement(child);
}


bool MainSub::PointCollide(int tx, int ty)
{
 return (tx >= x && tx <= x + w && ty >= y && ty <= y + h);
}

bool MainSub::IsActive()
{
 return active;
}





