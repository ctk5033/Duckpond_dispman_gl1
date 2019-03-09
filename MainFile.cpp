

#include "MainFile.h"
#include "GameEngine/GImage.h"
#include "GameEngine/Sprite.h"

#include "GameEngine/GSound.h"
#include "GameEngine/GMusic.h"

#include "GameEngine/GameDraw.h"

#include "MainSub.h"


#include "MainGame.h"

#include "GameEngine/GFont.h"

#include "MainMenu.h"








int MainFile::DrawSpecialCharacter(GList<KString> valList, float x, float y, bool calculateWidthOnly)
{


 return 35;
}

void MainFile::ReloadImages()
{
 GImage::ReloadImages();
}

void MainFile::Init()
{



 // game screen size, window size
 GameEngine::Init("Duck Pond", 1280/4,720/4,1024,768);

 // init data here
 DuckData::InitData();

}


void MainFile::Start()
{



 MainFile::StartSub(new MainMenu());

}

int MainFile::transitionTimer = 0;








void MainFile::Update()
{

 //GameEngine::colorMask = DogData::colorMask[DogData::curMask];

 if (IsTransitionOn())
 {
  UpdateTransition();

  if (nextSub != NULL && IsTransitionSwitchTime())
  {
   if (GetCurrentSub() != NULL){GetCurrentSub()->End();}
   MainFile::FullSwitch();
  }

 }
 else if (currentSub.GetSize() > 1)
 {
  for (int i = 0; i < currentSub.GetSize()-1; i++)
  {
   if (currentSub[i]->autoDelete){delete currentSub[i];}
   currentSub.Remove(i);
   i--;
  }
 }



 if (GetCurrentSub() != NULL)
 {

  GetCurrentSub()->Update();
  // Update Children Subs
  for (int i = 0; i < GetCurrentSub()->childList.GetSize(); i++)
  {
   if (GetCurrentSub()->childList[i]->IsActive()){GetCurrentSub()->childList[i]->Update();}
  }
 }

}


void MainFile::Draw()
{
 // Draw Main Sub
 if (GetCurrentSub() != NULL)
 {
  GetCurrentSub()->Draw();
 }

 if (IsTransitionOn())
 {
  DrawTransition();
 }

 if (GetCurrentSub() != NULL)
 {
  // Draw Children Subs
  for (int i = 0; i < GetCurrentSub()->childList.GetSize(); i++)
  {
   if (GetCurrentSub()->childList[i]->IsActive()){GetCurrentSub()->childList[i]->Draw();}
  }
 }


 /*GameEngine::SetColor(1,0,0);

 GameDraw::DrawText(KString("%d", currentSub.GetSize()),50,50);

 GameEngine::ResetColor();*/


}





// -------
// input
// -------


void MainFile::OnClickDown(float tx, float ty, int button)
{
 if (GetCurrentSub() == NULL){return;}
 // check first to see if the child subs are clicked
 for (int i = GetCurrentSub()->childList.GetSize()-1; i >= 0 ; i--)
 {
  if (GetCurrentSub()->childList[i]->IsActive() && GetCurrentSub()->childList[i]->PointCollide(tx,ty))
  {
   GetCurrentSub()->childList[i]->OnClickDown(tx,ty,button);
   return;
  }
 }

 GetCurrentSub()->OnClickDown(tx,ty,button);
}

void MainFile::OnClickUp(float tx, float ty, int button)
{
 if (GetCurrentSub() == NULL){return;}
 // check first to see if the child subs are clicked
 for (int i = GetCurrentSub()->childList.GetSize()-1; i >= 0 ; i--)
 {
  if (GetCurrentSub()->childList[i]->IsActive() && GetCurrentSub()->childList[i]->PointCollide(tx,ty))
  {
   GetCurrentSub()->childList[i]->OnClickUp(tx,ty,button);
   return;
  }
 }

 GetCurrentSub()->OnClickUp(tx,ty,button);
}

void MainFile::OnMouseMove(float tx, float ty, float dx, float dy)
{
 if (GetCurrentSub() == NULL){return;}
 // check first to see if the child subs are clicked
 for (int i = GetCurrentSub()->childList.GetSize()-1; i >= 0 ; i--)
 {
  if (GetCurrentSub()->childList[i]->IsActive() && GetCurrentSub()->childList[i]->PointCollide(tx,ty))
  {
   GetCurrentSub()->childList[i]->OnMouseMove(tx,ty,dx,dy);
   return;
  }
 }

 GetCurrentSub()->OnMouseMove(tx,ty, dx,dy);
}




void MainFile::HandleKeys()
{
 if (GetCurrentSub() == NULL){return;}
 GetCurrentSub()->HandleKeys();
}

void MainFile::End()
{

}






















// MAIN SUB MANAGER



GList<MainSub*> MainFile::currentSub;
MainSub* MainFile::nextSub = NULL;




MainSub* MainFile::GetCurrentSub()
{
 if (currentSub.GetSize() > 0)
 {
  return currentSub.GetLast();
 }

 return NULL;
}

void MainFile::StartSub(MainSub* startSub, bool useTransition, bool autoDelete)
{
 if (nextSub != NULL){return;}
 nextSub = startSub;


 startSub->autoDelete = autoDelete;

 if (useTransition)
 {
  StartTransition();
 }
 else
 {
  FullSwitch();
 }
}

void MainFile::FullSwitch()
{
 if (nextSub != NULL)
 {
  currentSub.Add(nextSub);
  nextSub->Start();
  nextSub = NULL;
 }
}

void MainFile::BackSub()
{
 delete currentSub.GetLast();
 currentSub.Remove(currentSub.GetSize()-1);
}



// ----------
// Transition
// ---------


void MainFile::StartTransition() // for other kinds of tansitions pass a transition class here
{
 transitionTimer = GameEngine::SCREEN_W*2;
}

void MainFile::UpdateTransition()
{
 if (IsTransitionOn())
 {
  transitionTimer = transitionTimer - 20;
 }
}

void MainFile::DrawTransition()
{
 GameEngine::SetColor(0,0,0);
 GameDraw::DrawBox(transitionTimer-GameEngine::SCREEN_W, 0, GameEngine::SCREEN_W, GameEngine::SCREEN_H);
 GameEngine::ResetColor();
}

bool MainFile::IsTransitionOn()
{
 if (transitionTimer > 0)
 {
  return true;
 }
 return false;
}

bool MainFile::IsTransitionSwitchTime()
{
 if (transitionTimer < GameEngine::SCREEN_W)
 {
  return true;
 }
 return false;
}


