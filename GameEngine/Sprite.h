#ifndef SPRITE_H
#define SPRITE_H 1

#include "GameEngine.h"
#include "GImage.h"

class AnimationData
{
 public:
		int sF;
		int sL;
		int eF;
		int eL;
		int delay;

  AnimationData()
  {
   sF = 0; sL = 0; eF = 0; eL = 0; delay = 0;
  }

		AnimationData(int ssF, int ssL, int seF, int seL, int sdelay)
		{
			sF = ssF;
			sL = ssL;
			eF = seF;
			eL = seL;
			delay = sdelay;
		}

  void SetData(int ssF, int ssL, int seF, int seL, int sdelay)
		{
			sF = ssF;
			sL = ssL;
			eF = seF;
			eL = seL;
			delay = sdelay;
		}

  bool IsAnimation(AnimationData* a)
  {
   if (sF == a->sF && sL == a->sL && eF == a->eF && eL == a->eL && delay == a->delay)
   {
    return true;
   }
   return false;
  }

};

class Sprite
{
 public:





	 Sprite(GImage* simage, float sx, float sy, int sw, int sh);




	GImage* image;
	float x;
	float y;

	int frameW;
	int frameH;

	int startFrame;
	int startLayer;

	int curFrame;
	int curLayer;

	int maxFrame;
	int maxLayer;

	int rotPointX;
	int rotPointY;

	float scaleX;
	float scaleY;

 bool forward;

	int pos;
	int posY;

	bool hide;

	float rot;

	int animationDelay;
	int curDelay;

	bool animationOn;
	float scale;
	bool looping;
	bool active;
	bool stopAtEnd;

	AnimationData* curAnimation;

 void Update();


	void SetAnimation(bool t);


	void Draw();

	void StartStaticAnimation(int sFrame, int sLayer, int mFrame,int mLayer, int sDelay);


	void StartAnimation(AnimationData* data);



	// USE STARTREVERSE FUNCTION FOR A REVERSED






	bool IsAnimationFinishedNext();

	bool OnFrameEnter(int sF, int sL);

	bool IsAnimationFinished();

	bool IsCurrentAnimation(AnimationData* a);

	void StartReverse();

	void SetReverse();

 private:
  	void StartAnimation(int sFrame, int sLayer, int mFrame, int mLayer,int sDelay);
   void StartAnimationPlayOnceStop(int sFrame, int sLayer, int mFrame,int mLayer, int sDelay);
   void StartAnimationPlayOnce(int sFrame, int sLayer, int mFrame,int mLayer, int sDelay);


};

#endif
