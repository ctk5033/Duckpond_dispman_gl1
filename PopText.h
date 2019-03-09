
#ifndef POPTEXT_H
#define POPTEXT_H 1

#include "MainFile.h"

class PopText
{
 public:
  PopText(KString stext, float sx, float sy, GColor scolor);
  ~PopText();

  float x;
  float y;
  GColor color;
  KString text;
  int timer;

  int dir;

  void Draw();
  void Update();


  static void UpdateList(GList<PopText*>* ptList);
  static void DrawList(GList<PopText*>* ptList);

};


#endif
