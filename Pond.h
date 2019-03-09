

#ifndef POND_H
#define POND_W

#include "MainFile.h"

class Entity;
class PopText;

class Pond
{
 public:

  static int TILE_W;
  static int TILE_H;

  Pond();
  ~Pond();

  int bankLeftW;
  int bankRightW;

  int groundY;
  int waterH;

  int w;
  int h;

  GList<Entity*> entList;

  GList<PopText*> poptextList;
  void DispScore(int d, int dx, int dy);

  GColor colorBkg;
  GColor colorGround;
  GColor colorPond;
  GColor colorPond2;

  void Update();
  void Draw();


  GList<Entity*> GetEntsOnTile(int tx, int ty);


};


#endif

