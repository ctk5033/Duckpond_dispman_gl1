
#ifndef MAINSUB_H
#define MAINSUB_H 1

#include "GameEngine/GameEngine.h"

class MainSub
{
public:

  MainSub();
  MainSub(int sx, int sy, int sw, int sh);

  virtual ~MainSub();

  float x;  // window position
  float y;
  int w;
  int h;

  float speed;
  float maxSpeed;

  int originalX;
  int originalY;

  int targetX;
  int targetY;

  bool active;
  bool IsActive();

  GList<MainSub*> childList;

  void AddChild(MainSub* child);
  void AddChildUnder(MainSub* child, MainSub* other);
  void RemoveChild(MainSub* child);

  void SetPosition(int sx, int sy);
  void SetTarget(int sx, int sy);
  void MoveTowardTarget(bool smooth = true);
  bool AtTarget();
  bool AtOriginal();

  bool autoDelete;

  virtual void Start();
  virtual void Update();
  virtual void TopDraw();
  virtual void Draw();
  virtual void HandleKeys();
  virtual void OnClickDown(int tx, int ty, int button);
  virtual void OnClickUp(int tx, int ty, int button);
  virtual void OnClickUpOffScreen(int tx, int ty, int button, MainSub* onScreen);
  virtual void OnClickDownOffScreen(int tx, int ty, int button, MainSub* onScreen);
  virtual void OnMouseMove(int tx, int ty, float dx, float dy);
  virtual void End();



  virtual bool PointCollide(int tx, int ty);




};


#endif
