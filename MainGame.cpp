
#include "MainGame.h"
#include "Pond.h"
#include "Duck.h"
#include "Fly.h"
#include "Plant.h"
#include "Fish.h"
#include "Fox.h"
#include "Hawk.h"


  MainGame::MainGame(DuckData* sdata)
  {
   duckData = sdata;
   pond = new Pond();

   duck = new Duck(pond, duckData->player, 10,pond->groundY-1);


  // pond->entList.Add(new Fly(pond, 5,2));

  // pond->entList.Add(new Fish(pond, 7,8));

   AddFlyFish();
   AddFlyFish();

   pond->entList.Add(new Plant(pond, 3, pond->groundY-1));
   pond->entList.Add(new Plant(pond, pond->w-4, pond->groundY-1));
   pond->entList.Add(new Plant(pond, pond->w-2, pond->groundY-1));
   pond->entList.Add(new Plant(pond, 1, pond->groundY-1));



  // pond->entList.Add(new Plant(pond, 6, pond->groundY+pond->waterH-1));
  // pond->entList.Add(new Plant(pond, pond->w-7, pond->groundY+pond->waterH-1));

   pond->entList.Add(duck);

   foxL = new Fox(pond, -2,pond->groundY-1);
   foxR = new Fox(pond, pond->w,pond->groundY-1);

   pond->entList.Add(foxL);
   pond->entList.Add(foxR);




   timer = 0;

   birdTimer = 200;



  }

  MainGame::~MainGame()
  {

  }

  void MainGame::Start()
  {

  }

  void MainGame::Update()
  {
   pond->Update();

   if (GameEngine::RandomFull()%50 == 0)
   {
    if (GameEngine::RandomFull()%2 == 0 || foxR->triggered ){foxL->triggered = true;}
    else {foxR->triggered = true;}
   }
   if (birdTimer  == 0)
   {
    if (GameEngine::RandomFull()%2 == 0 ){pond->entList.Add(new Hawk(pond, -1,2));}
    else {pond->entList.Add(new Hawk(pond, pond->w,2));}
    birdTimer = 500;// GameEngine::RandomFull()%200+
   }
   birdTimer--;

   if (timer%500 == 0)
   {
    AddFlyFish();
   }
   timer++;

  }

  void MainGame::Draw()
  {
   pond->Draw();

   GameEngine::SetColor(1,0,0);
  // GameDraw::DrawText(KString("IW: %d OW: %d OG: %d IA: %d OWG: %d", duck->InWater(), duck->OnWater(), duck->OnGround(), duck->InAir(), duck->OnWaterGround()), 10, 10);
   GameEngine::ResetColor();

   GameEngine::SetColor(DuckData::colorDuck);

   KString foodText = "FOOD: ";
   for (int i = 0; i < duck->maxFood; i++)
   {
    if (i <= duck->food){foodText.Add("f");} else {foodText.Add("g");}
   }
   GameDraw::DrawText(foodText,1,11);
   GameDraw::DrawText(KString("SCORE: %d", duck->score), 1, 1);

    KString airText = "AIR: ";
   for (int i = 0; i < 5; i++)
   {
    if (i <= duck->air){airText.Add("f");} else {airText.Add("g");}
   }
   GameDraw::DrawText(airText,1,21);


   GameEngine::ResetColor();

   if (!duck->alive)
   {
    GameEngine::SetColor(pond->colorGround);
    GameDraw::DrawText("GAME OVER!", GameEngine::SCREEN_W/2, 10, true);
    GameDraw::DrawText("YOU DIED!", GameEngine::SCREEN_W/2, 20, true);

    GameDraw::DrawText(KString("SCORE: %d", duck->score), GameEngine::SCREEN_W/2, 50, true);
    GameDraw::DrawText(KString("PRESS Z TO QUACK ANOTHER DAY!"), GameEngine::SCREEN_W/2, 60, true);
    GameEngine::ResetColor();

   }

  }

  void MainGame::AddFlyFish()
  {
   if (pond->entList.GetSize() > 20){return;}
   if (GameEngine::RandomFull()%2 == 0)
    {
     int spawnY = 3 + GameEngine::RandomFull()%(pond->groundY-3);
     int spawnX = 1 + GameEngine::RandomFull()%(pond->w-2);
     pond->entList.Add(new Fly(pond, spawnX, spawnY));
    }
    else
    {
     int spawnY = pond->groundY + GameEngine::RandomFull()%(pond->waterH);
     int spawnX = pond->bankLeftW + GameEngine::RandomFull()%(pond->w-pond->bankRightW - pond->bankLeftW-1);
     pond->entList.Add(new Fish(pond, spawnX, spawnY));
    }

  }

  void MainGame::HandleKeys()
  {
   duckData->player->HandleKeys();
  }

