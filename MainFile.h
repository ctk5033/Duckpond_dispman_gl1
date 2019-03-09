#ifndef MAINFILE_H
#define MAINFILE_H 1

#include "GameEngine/GameEngine.h"
#include "GameEngine/Sprite.h"
#include "MainSub.h"

#define MAX_POINTFISH_TYPE 5


class MainFile
{
 public:

  static void Init();

  static void ReloadImages();

  static void Start();
  static void Update();
  static void Draw();
  static void HandleKeys();
  static void End();
  static void OnClickDown(float tx, float ty, int button);
  static void OnClickUp(float tx, float ty, int button);
  static void OnMouseMove(float tx, float ty, float dx, float dy);

  static int DrawSpecialCharacter(GList<KString> valList, float x, float y, bool calculateWidthOnly = false);

  // -- MainSub Management
  static GList<MainSub*> currentSub;

  static void StartSub(MainSub* startSub, bool useTransition = true, bool autoDelete = true);
  static void BackSub();
  static MainSub* GetCurrentSub();
  static MainSub* nextSub;

  static void StartTransition();
  static void UpdateTransition();
  static void DrawTransition();
  static bool IsTransitionOn();
  static bool IsTransitionSwitchTime();
  static int transitionTimer;


 private:
  static void FullSwitch(); // completely switches focus to the next sub


};


/*
class MainFile
{
 public:

  static void Init();

  static void ReloadImages();

  static void Start();
  static void Update();
  static void Draw();
  static void HandleKeys();
  static void End();
  static void OnClickDown(float tx, float ty, int button);
  static void OnClickUp(float tx, float ty, int button);
  static void OnMouseMove(float tx, float ty, float dx, float dy);


  static int DrawSpecialCharacter(GList<KString> valList, float x, float y, bool calculateWidthOnly = false);

  // -- MainSub Management
  static GList<MainSub*> currentSub;

  static void StartSub(MainSub* startSub);
  static void BackSub();
  static MainSub* GetCurrentSub();
  static MainSub* nextSub;

 private:
  static void FullSwitch(); // completely switches focus to the next sub


};


*/
#endif
