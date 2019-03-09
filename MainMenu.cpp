

#include "MainMenu.h"
#include "DuckData.h"
#include "Pond.h"
#include "MainGame.h"
#include "Plant.h"
#include "Duck.h"
#include "Duckling.h"


 MainMenu::MainMenu()
 {
   data = new DuckData();

   data->player->playerButtonList.Add(this);

   started = false;

   pond = new Pond();

   phase = 0;
 }

 MainMenu::~MainMenu()
 {
  delete data;
 }

 void MainMenu::Start()
 {
   pond->entList.Add(new Plant(pond, 3, pond->groundY-1));
   pond->entList.Add(new Plant(pond, pond->w-4, pond->groundY-1));
   pond->entList.Add(new Plant(pond, pond->w-2, pond->groundY-1));
   pond->entList.Add(new Plant(pond, 1, pond->groundY-1));

   Duck* duck = new Duck(pond, data->player, 11,pond->groundY-1);

   pond->entList.Add(duck);
   duck->MoveX(1);

   pond->entList.Add(new Duckling(pond, duck, 10,pond->groundY-1));
   pond->entList.GetLast()->MoveX(1);
   pond->entList.Add(new Duckling(pond, duck, 9,pond->groundY-1));
   pond->entList.GetLast()->MoveX(1);
   pond->entList.Add(new Duckling(pond, duck, 8,pond->groundY-1));
   pond->entList.GetLast()->MoveX(1);

 }

 void MainMenu::Update()
 {

 }

 void MainMenu::Draw()
 {
  pond->Draw();

  GameEngine::SetColor(pond->colorGround);

  if (phase == 1)
  {
   GameEngine::SetColor(0,0,0,.75f);
   GameDraw::DrawBox(0,0,GameEngine::SCREEN_W, GameEngine::SCREEN_H);

   GameEngine::SetColor(pond->colorPond2);
   GameDraw::DrawText("HOW TO PLAY:", GameEngine::SCREEN_W/2, 10, true);
   GameDraw::DrawText("SURVIVE AND RAISE DUCKLINGS IN THE DANGEROUS POND", GameEngine::SCREEN_W/2, 30, true);

   GameDraw::DrawText("PRESS Z TO PICK UP AN EGG OR DUCKLING", GameEngine::SCREEN_W/2, 40, true);
   GameDraw::DrawText("PRESS DOWN NEAR PLANTS TO EAT THEM", GameEngine::SCREEN_W/2, 50, true);
   GameDraw::DrawText("RUN INTO FISH OR INSECTS TO EAT THEM", GameEngine::SCREEN_W/2, 60, true);
   GameDraw::DrawText("EAT 5 TIMES TO LAY AN EGG", GameEngine::SCREEN_W/2, 70, true);
   GameDraw::DrawText("KEEP DUCKLINGS ALIVE TO GAIN POINTS", GameEngine::SCREEN_W/2, 80, true);
   GameDraw::DrawText("WATCH OUT FOR PREDATORS!", GameEngine::SCREEN_W/2, 90, true);

   GameDraw::DrawText("PRESS Z TO START", GameEngine::SCREEN_W/2, 110, true);



  }
  else if (phase == 0)
  {
   GameEngine::SetColor(pond->colorGround);
   GameDraw::DrawText("DUCK POND", GameEngine::SCREEN_W/2, 10, true);
   GameEngine::SetColor(pond->colorPond2);
   GameDraw::DrawText("A GAME BY SHARKARM CURT", GameEngine::SCREEN_W/2, 20, true);

   GameEngine::SetColor(pond->colorGround);
   GameDraw::DrawText("PRESS Z TO GET QUAKIN!", GameEngine::SCREEN_W/2, 165, true);
  }



 }

 void MainMenu::ButtonPress()
 {
  if (started){return;}

  if (phase == 1)
  {
   started = true;
   DuckData::wavStart->Play();
   MainFile::StartSub(new MainGame(new DuckData()));
  }

  phase++;
  if (phase == 1){DuckData::wavStep->Play();}

 }

 void MainMenu::OnKeyEnter(Player* player)
 {
  ButtonPress();
 }

 void MainMenu::ActivateA(Player* player)
 {
  ButtonPress();
 }

 void MainMenu::HandleKeys()
 {
  data->player->HandleKeys();
 }
