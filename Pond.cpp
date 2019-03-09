

#include "Pond.h"
#include "Entity.h"
#include "Duck.h"

#include "PopText.h"

int Pond::TILE_W = 16;
int Pond::TILE_H = 16;


 Pond::Pond()
 {
  bankLeftW = 5;
  bankRightW = 5;
  colorBkg.SetColor(243,207,180);
  colorGround.SetColor(150,76,23);
  colorPond.SetColor(139,173,213);
  colorPond2.SetColor(89,150,222);
  groundY = 6;
  waterH = 4;
  w = GameEngine::SCREEN_W/TILE_W;
  h = GameEngine::SCREEN_H/TILE_H;
 }

 Pond::~Pond()
 {


 }


 void Pond::DispScore(int d, int dx, int dy)
 {
 // GameEngine::MessageBox(KString("score:%d", d));
 KString k = KString("%d", d);
 if (d > 0){k = KString("+%d", d);}
  poptextList.Add(new PopText(k, dx, dy, colorGround));
 }



  void Pond::Update()
  {
   for (int i = 0; i < entList.GetSize(); i++)
   {
    entList[i]->Update();

    if (!entList[i]->alive)
    {
     if (!dynamic_cast<Duck*>(entList[i])){delete entList[i];}
     entList.Remove(i);
     i--;
    }
   }

   PopText::UpdateList(&poptextList);

  }

  void Pond::Draw()
  {
   GameEngine::SetColor(colorBkg);
   GameDraw::DrawBox(0,0,GameEngine::SCREEN_W, GameEngine::SCREEN_H);

   GameEngine::SetColor(colorGround);
   GameDraw::DrawBox(0, groundY*TILE_H, bankLeftW*TILE_W, 1);
   GameDraw::DrawBox(GameEngine::SCREEN_W-bankRightW*TILE_W, groundY*TILE_H, bankRightW*TILE_W, 1);
   // pond boarder
   GameDraw::DrawBox(bankLeftW*TILE_W-1, groundY*TILE_H, GameEngine::SCREEN_W - bankLeftW*TILE_W - bankRightW*TILE_W + 2, waterH*TILE_H + 1);

   GameEngine::SetColor(colorPond);
   GameDraw::DrawBox(bankLeftW*TILE_W, groundY*TILE_H, GameEngine::SCREEN_W - bankLeftW*TILE_W - bankRightW*TILE_W, waterH*TILE_H);
   GameEngine::SetColor(colorPond2);
   GameDraw::DrawBox(bankLeftW*TILE_W, groundY*TILE_H, GameEngine::SCREEN_W - bankLeftW*TILE_W - bankRightW*TILE_W, 1);

   GameEngine::ResetColor();

   for (int i = 0; i < entList.GetSize(); i++)
   {
    entList[i]->Draw();
   }

   PopText::DrawList(&poptextList);

  }


  GList<Entity*> Pond::GetEntsOnTile(int tx, int ty)
  {
   GList<Entity*> tileEntList;

   for (int i = 0; i < entList.GetSize(); i++)
   {
    if (entList[i]->AtPosition(tx,ty))
    {
     tileEntList.Add(entList[i]);
    }
   }

   return tileEntList;

  }
