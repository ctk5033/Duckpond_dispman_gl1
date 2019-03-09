#ifndef GAMEENGINE_H
#define GAMEENGINE_H 1



#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>


#include <math.h>
#include <iostream>

#include "GTypes.h"
#include "GFont.h"
#include "KString.h"
#include <fstream>
#include "GList.h"
#include "GameDraw.h"
#include "TextPrint.h"
#include "GMap.h"
#include "GScript.h"

#include "GSound.h"
#include "GMusic.h"

#include "GPair.h"

#include "Sprite.h"


#define PI 3.14159265359f

#define TRUE 1
#define FALSE 0

#define BOOL bool

#define KEY_LEFT SDLK_LEFT
#define KEY_RIGHT SDLK_RIGHT
#define KEY_UP SDLK_UP
#define KEY_DOWN SDLK_DOWN
#define KEY_ENTER SDLK_RETURN
#define KEY_ESCAPE SDLK_ESCAPE

#define MAX_MOUSE_BUTTONS 3

#define GAMEENGINE_READ_FILE_MAX 10


class GImage;

class GameEngine
{
 public:
  static void Init(KString name, int w, int h, int windowW, int windowH, int fullScreen = -1);

  static void Start();
  static void Draw();
  static void Update();
  static void End();
  static void HandleKeys();

  static void SetColor(GColor scolor);
  static void SetColor(float sr, float sg, float sb, float sa);
  static void SetColor(float sr, float sg, float sb);
  static void SetColor255(int sr, int sg, int sb, int sa = 255);
  static void ResetColor();

  static void MessageBox(KString msg);

  static float GlobalScale;
  static float ScreenShiftX;
  static float ScreenShiftY;

  static int SCREEN_W;
  static int SCREEN_H;
  static int WINDOW_W;
  static int WINDOW_H;

  static int mouseX;
  static int mouseY;
  static int lastMouseX;
  static int lastMouseY;
  static bool mouseButtonDown[MAX_MOUSE_BUTTONS];

  static const int MOUSE_LEFT = 0;
  static const int MOUSE_WHEEL = 1;
  static const int  MOUSE_RIGHT = 2;



  static GFont* curFont;
  static GFont* defaultFont;
  static GImage* defaultFontIm;

  static GList<KString> paramList;

  static void SetFont(GFont* sFont);

  static int GetWidth(); // get window w
  static int GetHeight();

  static float FPS;
  static float frameLimit;
  static float GetFPS();

  static int key[256]; // keyboard key states
  static int GetKey(int k);

  static GColor color;
  static GColor colorMask;

  static void Message(KString str);
  static void Message(int i);

  static float Random();
  static int Random(int i);
  static int RandomFull();

  static float GetMilliTime();

  static int DiceRoll(KString roll);

  static void Finish();


  static void ForceClose();

  static bool gameOn;

  static void SetVideo(bool fullscreen, bool reloadImages = true);

  static Uint32 flags;

  static int joyCount;


  // joysticks

  static GList<SDL_Joystick*> joystickList;
  static void InitJoystick();
  static int JoystickX(int i);
  static int JoystickY(int i);
  static int JoystickButton(int i, int b);


  // screenshot
  static void ScreenShot(KString filename);
  static KString recordName;
  static int recordTime;
  static void StartRecord(KString filename);
  static void EndRecord();


   // read file

    static std::string mainDir;
    static std::string outDir;


    static std::ifstream readFile[GAMEENGINE_READ_FILE_MAX]; // read file stack for reading multiple files at the same time
    static int curReadFile;
    static bool OpenReadFile(KString filename, bool resouceFile = true);
    static void CloseReadFile();
    static KString ReadNextString();
    static KString ReadNextLine();
    static GList<KString> ReadNextLineSplit(char splitChar);
    static bool HasNextLine();
    static int ReadNextInt();

    static std::ofstream writeFile;
    static void OpenWriteFile(KString filename, bool append = false);
    static void WriteFile(int d);
    static void WriteFile(KString str);
    static void CloseWriteFile();

    static void CopyFile(std::string source, std::string dest);


    static KString ToLowerCase(KString data);
    static KString ToUpperCase(KString data);

    static std::string ToLowerCase(std::string data);
    static std::string ToUpperCase(std::string data);
	   static GList<std::string> Split(std::string split, char c);








};





#endif
