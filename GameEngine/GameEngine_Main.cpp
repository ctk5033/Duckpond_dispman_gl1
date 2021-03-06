

#include "GameEngine.h"
#include "../MainFile.h"
#include <cstdlib>

Uint32 bfps = 1.0f;
Uint32 efps = 1.0f;



int main( int argc, char** args)
{
  freopen( "CON", "wt", stdout );
  freopen( "CON", "wt", stderr );



  for (int i = 0; i < argc; i++)
  {
   GameEngine::Message(args[i]);
   GameEngine::paramList.Add(KString(args[i]));
  }

  MainFile::Init();

  GameEngine::Start();

  SDL_Event event;

  atexit(SDL_Quit);
  atexit(Mix_CloseAudio);
  atexit(Mix_Quit);

  GameEngine::gameOn = true;

  long startTime = SDL_GetTicks();


    long frameHoldTime = SDL_GetTicks();
     int frames = 0;

  while (GameEngine::gameOn )
  {

   bfps = SDL_GetTicks();

  // int

frames++;
  if (bfps - frameHoldTime >= 3000)
  {
   GameEngine::FPS = frames/3;

   //GameEngine::OpenWriteFile("fps", true);
   //GameEngine::WriteFile(KString("fps:%f\n", GameEngine::FPS));
   //GameEngine::CloseReadFile();
   std::cout << "FPS " << GameEngine::FPS  << std::endl;


        frames = 0;
        frameHoldTime = SDL_GetTicks();


  }



   if ((bfps-efps)*GameEngine::frameLimit  >= 1000.0)
   {

    /*if (bfps-efps != 0)
    {
     GameEngine::FPS = 1000.0f/((bfps-efps));
    }
    else {GameEngine::FPS = 0;}*/

    efps = bfps;

    GameEngine::Update();
    GameEngine::HandleKeys();









   while ( SDL_PollEvent(&event) )
   {

    if ( event.type == SDL_QUIT || event.key.keysym.sym ==  KEY_ESCAPE || (event.key.keysym.sym == SDLK_F4 && (event.key.keysym.mod == KMOD_LALT || event.key.keysym.mod == KMOD_RALT) ))
    {
     GameEngine::gameOn = false;
     break;
    }



    static bool delR = false;
    static bool delS = false;
    if ((event.key.keysym.mod == KMOD_LALT || event.key.keysym.mod == KMOD_RALT) && event.key.keysym.sym ==  'g')
    {
     if (delR)
     {
      if (GameEngine::recordTime < 0)
      {
     //  GameEngine::StartRecord("record");
      }
      else {GameEngine::EndRecord();}
      delR = false;
     }
    }
    else {delR = true;}

    if ((event.key.keysym.mod == KMOD_LALT || event.key.keysym.mod == KMOD_RALT) && event.key.keysym.sym ==  's')
    {
     if (delS)
     {
      //GameEngine::ScreenShot(KString("record/screenshot_%d.bmp", rand()%90000));
      delS = false;
     }
    }
    else {delS = true;}

    if ((event.key.keysym.mod == KMOD_LALT || event.key.keysym.mod == KMOD_RALT) && event.key.keysym.sym ==  'f')
    {
     GameEngine::SetVideo(true);
    }
    if ((event.key.keysym.mod == KMOD_LALT || event.key.keysym.mod == KMOD_RALT) && event.key.keysym.sym ==  'w')
    {
     GameEngine::SetVideo(false);
    }

    if (event.type == SDL_KEYDOWN)
    {
     GameEngine::key[event.key.keysym.sym] = 1;
    }
    if (event.type == SDL_KEYUP)
    {
     GameEngine::key[event.key.keysym.sym] = 0;
    }

    }

    GameEngine::Draw();


    //SDL_Delay(1); //Delay / pause
   }




    if (SDL_GetTicks() - startTime > 10000)
    {
    // GameEngine::gameOn = false;
   //  break;
    }


  }


  GameEngine::End();

  SDL_Delay(1);

  Mix_CloseAudio();
  Mix_Quit();
  SDL_Quit();


  return 0;
}
