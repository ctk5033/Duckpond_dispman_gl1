

#include "GameEngine.h"
#include "../MainFile.h"
#include "GameDraw.h"




 #include  "bcm_host.h"

int GameEngine::SCREEN_W = 800;
int GameEngine::SCREEN_H = 600;
int GameEngine::WINDOW_W = 800;
int GameEngine::WINDOW_H = 600;

bool GameEngine::gameOn = true;


float GameEngine::GlobalScale = 1.0f;
float GameEngine::ScreenShiftX = 0;
float GameEngine::ScreenShiftY = 0;

GList<KString> GameEngine::paramList;

float GameEngine::FPS = 50.0f;

GFont* GameEngine::curFont = NULL;

GColor GameEngine::color;
GColor GameEngine::colorMask;

int GameEngine::key[256];

int GameEngine::mouseX = 0;
int GameEngine::mouseY = 0;
int GameEngine::lastMouseX = 0;
int GameEngine::lastMouseY = 0;
bool GameEngine::mouseButtonDown[MAX_MOUSE_BUTTONS];

float GameEngine::frameLimit = 60.0f;

std::string GameEngine::mainDir = "";
std::string GameEngine::outDir = ".";

GFont* GameEngine::defaultFont = NULL;
GImage* GameEngine::defaultFontIm = NULL;

Uint32 GameEngine::flags = 0;

int GameEngine::joyCount = 8;

float GameEngine::GetFPS()
{
 return frameLimit;
}

void GameEngine::Init(KString name, int w, int h, int windowW, int windowH, int fullScreen)
{
   bcm_host_init();


   // ---





  if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
  {
   GameEngine::Message(SDL_GetError());
  }


  std::cout << "HI there!";
 // std::cout << SDL_GetNumVideoDisplays();

  /*if (SDLNet_Init() < 0)
  {


  }*/



  srand(SDL_GetTicks());

  SCREEN_W = w; // game screen size
  SCREEN_H = h;

  WINDOW_W = windowW; // actual window size (will adjust)
  WINDOW_H = windowH;

  float scaleW = GameEngine::GetWidth()*1.0f/GameEngine::SCREEN_W;
  float scaleH = GameEngine::GetHeight()*1.0f/GameEngine::SCREEN_H;

  if (scaleW > scaleH){GlobalScale = scaleH;} else {GlobalScale = scaleW;}

  atexit(SDL_Quit);



 // SDL_WM_SetCaption( name.str.c_str(), NULL );

  //| SDL_FULLSCREEN

  flags = SDL_OPENGL ;


  // fullscreen -1 means it is chosen by the parameters, 0 = no full screen, 1 = fullscreen

  bool fScreen = true;
  if (fullScreen == -1 && paramList.Contains(KString("-f")) || fullScreen == 1)
  {
   fScreen = true;
   //flags = flags | SDL_FULLSCREEN;
  }

   //SDL_SetVideoMode(WINDOW_W,WINDOW_H,32, flags );

  SetVideo(fScreen, false);



  int audio_rate = 44100;
  Uint16 audio_format = AUDIO_S16SYS; // 16-bit stereo
  int audio_channels = 2;
  int audio_buffers = 2048;

  if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers))
  {
   GameEngine::MessageBox("Could Not Open SDL_Mixer!");
  }




  for (int i = 0; i < 256; i++)
  {
   key[i] = 0;
  }

  for (int i = 0; i < MAX_MOUSE_BUTTONS; i++)
  {
   mouseButtonDown[i] = false;
  }

 // defaultFontIm = new GImage(KString("data/font/codFont.png"));
  defaultFont = new GFont( "data/font/codfont.cff", 1.0f);
  SetFont(defaultFont);

  InitJoystick();


}





void GameEngine::SetVideo(bool fullScreen, bool reloadImages)
{




   Uint32 flags = GameEngine::flags;

   if (fullScreen){flags = flags | SDL_FULLSCREEN;}

     const SDL_VideoInfo* videoInfo = SDL_GetVideoInfo ();

  int systemX = videoInfo->current_w ;
  int systemY = videoInfo->current_h ;
  Uint8 bpp = videoInfo->vfmt->BitsPerPixel ;

  WINDOW_W = systemX;
  WINDOW_H = systemY;


  SDL_SetVideoMode(systemX, systemY, bpp, flags );
/*

      EGLDisplay eglDpy = eglGetDisplay(EGL_DEFAULT_DISPLAY);

    EGLint major, minor;

  eglInitialize(eglDpy, &major, &minor);

  // 2. Select an appropriate configuration
  EGLint numConfigs;
  EGLConfig eglCfg;

  eglChooseConfig(eglDpy, configAttribs, &eglCfg, 1, &numConfigs);

  // 3. Create a surface
  EGLSurface eglSurf = eglCreatePbufferSurface(eglDpy, eglCfg,
                                               pbufferAttribs);

  // 4. Bind the API
  eglBindAPI(EGL_OPENGL_API);

  // 5. Create a context and make it current
  EGLContext eglCtx = eglCreateContext(eglDpy, eglCfg, EGL_NO_CONTEXT,
                                       NULL);

  eglMakeCurrent(eglDpy, eglSurf, eglSurf, eglCtx);
*/


   glEnable(GL_TEXTURE_2D);
	 glShadeModel(GL_SMOOTH);
  glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	 glClearDepth(1.0f);
	 glEnable(GL_DEPTH_TEST);
	 glDepthFunc(GL_LEQUAL);
  glDisable(GL_DEPTH_TEST);
	 glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);

  glViewport(0,0,WINDOW_W,WINDOW_H);
 	glMatrixMode(GL_PROJECTION);
 	glLoadIdentity();


 	gluPerspective(45.0f,(GLfloat)SCREEN_W/(GLfloat)SCREEN_H,0.1f,100.0f);

 	glMatrixMode(GL_MODELVIEW);
 	glLoadIdentity();

 	 if (reloadImages){MainFile::ReloadImages();}

}


void GameEngine::ForceClose()
{
 gameOn = false;
 //SDL_Quit();
}


int GameEngine::GetWidth()
{
 return WINDOW_W;
}
int GameEngine::GetHeight()
{
 return WINDOW_H;
}




void GameEngine::SetFont(GFont* sFont)
{
 curFont = sFont;
}




void GameEngine::Start()
{
 MainFile::Start();
}



void GameEngine::Update()
{
 Uint8 mouseState = SDL_GetMouseState(&mouseX, &mouseY);

 mouseX = mouseX/GameEngine::GlobalScale;
 mouseY = mouseY/GameEngine::GlobalScale;


 if (recordTime > 0)
 {
  GameEngine::ScreenShot(KString("record/%s%d.bmp", recordName.c_str(), recordTime));
  recordTime++;
 }


 SDL_JoystickUpdate();
 GameDraw::ShakeUpdate();

 MainFile::Update();

 // -----------
 // mouse
 // -----------

 if (lastMouseX != mouseX || lastMouseY != mouseY)
 {
  MainFile::OnMouseMove(mouseX, mouseY, mouseX - lastMouseX, mouseY - lastMouseY);
 }
 lastMouseX = mouseX;
 lastMouseY = mouseY;

 for (int i = 1; i < 1+MAX_MOUSE_BUTTONS; i++)
 {
  if (mouseState & SDL_BUTTON(i))
  {
   if (!mouseButtonDown[i-1])
   {
    mouseButtonDown[i-1] = true;
    MainFile::OnClickDown(mouseX, mouseY, i-1);
   }
   //::MessageBox(0,KString("BUTTON: %d", i).str.c_str(),0,0);
  }
  else
  {
   if (mouseButtonDown[i-1])
   {
    mouseButtonDown[i-1] = false;
    MainFile::OnClickUp(mouseX, mouseY, i-1);
   }
  }
 }

}



void GameEngine::Draw()
{
 glClear(GL_COLOR_BUFFER_BIT);

 glPushMatrix();

 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 glOrtho(0.0f,WINDOW_W,WINDOW_H,0.0f,-1000.0f,1000.0f);

 MainFile::Draw();


 GameDraw::SetShiftZ(1000);
    // Clip edges to keep ratio the same
    if (GlobalScale*GameEngine::SCREEN_W < GameEngine::GetWidth())
    {
        ScreenShiftX = (int)((GameEngine::GetWidth()-GlobalScale*GameEngine::SCREEN_W)/2);
        GameEngine::SetColor(0,0,0);
        GameDraw::DrawGlobalBox(GlobalScale*GameEngine::SCREEN_W + ScreenShiftX, 0, ScreenShiftX+10, GameEngine::GetHeight());
        GameDraw::DrawGlobalBox(0, 0, ScreenShiftX, GameEngine::GetHeight());
        GameEngine::ResetColor();
    }
    else {ScreenShiftX = 0;}
    if (GlobalScale*GameEngine::SCREEN_H < GameEngine::GetHeight())
    {
        ScreenShiftY = (int)((GameEngine::GetHeight()-GlobalScale*GameEngine::SCREEN_H)/2);
        GameEngine::SetColor(0,0,0);
        GameDraw::DrawGlobalBox(0, GlobalScale*GameEngine::SCREEN_H + ScreenShiftY, GameEngine::GetWidth(), ScreenShiftY+10);
        GameDraw::DrawGlobalBox(0, 0, GameEngine::GetWidth(), ScreenShiftY);
        GameEngine::ResetColor();
    }
    else {ScreenShiftY = 0;}

    GameDraw::SetShiftZ(0);


 glPopMatrix();

 SDL_GL_SwapBuffers();
}



void GameEngine::HandleKeys()
{
 MainFile::HandleKeys();


}

void GameEngine::End()
{
 MainFile::End();

 //SDLNet_Quit();
}




void GameEngine::SetColor(GColor scolor)
{
 color = scolor;
 color.Multiply(colorMask.r,colorMask.g,colorMask.b);
 glColor4f(color.r, color.g, color.b, color.a);
}
void GameEngine::SetColor(float sr, float sg, float sb, float sa)
{
 SetColor(GColor(sr,sg,sb,sa));
}
void GameEngine::SetColor(float sr, float sg, float sb)
{
 SetColor(GColor(sr,sg,sb));
}

void GameEngine::SetColor255(int sr, int sg, int sb, int sa)
{
  SetColor((sr*1.0f/255), (sg*1.0f/255), (sb*1.0f/255),(sa*1.0f/255));
}


void GameEngine::ResetColor()
{
 SetColor(1.0f,1.0f,1.0f);
}


void GameEngine::MessageBox(KString msg)
{
// ::MessageBox(0,msg.c_str(), 0,0);
}

int GameEngine::GetKey(int k)
{
 return key[k];
}

void GameEngine::Message(KString str)
{
 std::cout << str.str.c_str() << "\n";
}

void GameEngine::Message(int i)
{
 std::cout << i << "\n";

}


float GameEngine::GetMilliTime()
{
   return 1;
}

float GameEngine::Random()
{



    return (rand()*1.0f/(RAND_MAX-1));
}

int GameEngine::RandomFull()
{
 return rand();
}

int GameEngine::Random(int i)
{
 return (int)(Random()*i);
}

void GameEngine::Finish()
{
 gameOn = false;
}





int GameEngine::DiceRoll(KString roll)
{
     if (!roll.Contains('+') && !roll.Contains('d'))
     {
      return std::atoi(roll.str.c_str());
     }

     int mult = 1;
     if (roll[0] == '_') // negates entire roll
     {
      roll.Remove(0);
      mult = -1;
     }

     GList<KString> splitList = roll.Split('+');
     int total = 0;
     for (int i = 0; i < splitList.GetSize(); i++)
     {
      if (splitList[i].Contains('d'))
      {
       GList<KString> rList = splitList[i].Split('d');
       int n = atoi(rList[0].c_str());
       for (int k = 0; k < n; k++)
       {
        int r = atoi(rList[1].c_str());
        total = total + ((rand()%r)+1);
       }

      }
      else
      {
       total = total + atoi(splitList[i].c_str());
      }
     }

  return total*mult;
}


GList<SDL_Joystick*> GameEngine::joystickList;

void GameEngine::InitJoystick()
{
 int j = SDL_NumJoysticks();

 for (int i = 0; i < j; i++)
 {
  joystickList.Add(SDL_JoystickOpen(i));
 }

}

int GameEngine::JoystickX(int i)
{
 if (i >= joystickList.GetSize()){return 0;}
 int jPos = SDL_JoystickGetAxis(joystickList[i], 0);

 if (jPos > 10000){return 1;}
 if (jPos < -10000){return -1;}
 return 0;
}
int GameEngine::JoystickY(int i)
{
 if (i >= joystickList.GetSize()){return 0;}
 int jPos = SDL_JoystickGetAxis(joystickList[i], 1);

 if (jPos > 10000){return 1;}
 if (jPos < -10000){return -1;}
 return 0;
}

int GameEngine::JoystickButton(int i, int b)
{
 if (i >= joystickList.GetSize()){return 0;}
 return SDL_JoystickGetButton(joystickList[i], b);
}



KString GameEngine::recordName = "";
int GameEngine::recordTime = -1;
void GameEngine::StartRecord(KString filename)
{
 recordTime = 10000;
 recordName = filename;
}
void GameEngine::EndRecord()
{
 recordTime = -1;
}



void GameEngine::ScreenShot(KString filename)
{
    Uint32 rmask, gmask, bmask, amask;

   #if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
    #else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
    #endif


 int recordX = 0;
 int recordY = 0;
 int recordW = WINDOW_W;
 int recordH = WINDOW_H;


 SDL_Surface* text = SDL_CreateRGBSurface(SDL_SWSURFACE, recordW, recordH, 32, rmask, gmask, bmask, amask);
 SDL_FillRect(text, NULL, SDL_MapRGBA(text->format, 0, 0, 0,0));


 glReadPixels(recordX, recordY,recordW,recordH,GL_RGBA, GL_UNSIGNED_BYTE, text->pixels);

  for (int y = 0; y < text->h/2; y++)
  {
   for (int x = 0; x < text->w; x++)
   {
    int pix1 = y*(text->pitch/sizeof(unsigned int)) + x;
    int pix2 = ((text->h-y-1))*(text->pitch/sizeof(unsigned int)) + x;

    unsigned int pix = ((unsigned int*)text->pixels)[pix1];
    ((unsigned int*)text->pixels)[pix1] = ((unsigned int*)text->pixels)[pix2];
    ((unsigned int*)text->pixels)[pix2] = pix;


   }
  }

 SDL_SaveBMP(text, filename.c_str());
 SDL_FreeSurface(text);

}











