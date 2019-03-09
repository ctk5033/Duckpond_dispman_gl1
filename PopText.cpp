
#include "PopText.h"





  PopText::PopText(KString stext, float sx, float sy, GColor scolor)
  {
   x = sx;
   y = sy;
   text = stext;
   color = scolor;
   timer = 30;
   dir = -1;

   if(sy < 0)
   {
    y = -10;
    dir = 1;
   }
  }

  PopText::~PopText()
  {

  }



  void PopText::Draw()
  {

   GameEngine::SetColor(color);
   GameDraw::DrawText(text,  x,  y, true);
   GameEngine::ResetColor();
  }

  void PopText::Update()
  {
   y = y + .5f*dir;
   timer--;
  }


  void PopText::UpdateList(GList<PopText*>* ptList)
  {
   for (int i = 0; i < ptList->GetSize(); i++)
   {
    ptList->Get(i)->Update();
    if (ptList->Get(i)->timer <= 0)
    {
     delete ptList->Get(i);
     ptList->Remove(i);
     i--;
    }
   }
  }

  void PopText::DrawList(GList<PopText*>* ptList)
  {
   for (int i = 0; i < ptList->GetSize(); i++)
   {
    ptList->Get(i)->Draw();
   }
  }
