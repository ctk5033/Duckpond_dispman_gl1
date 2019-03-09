


#include "Sprite.h"
#include "GameDraw.h"

Sprite::Sprite(GImage* simage, float sx, float sy, int sw, int sh)
{
 image = simage;
 x = sx;
 y = sy;
 frameW = sw;
 frameH = sh;

  if (frameW == -1) {frameW = image->w;}
 if (frameH == -1) {frameH = image->h;}

 StartAnimation(0, 0, 0, 0, 0);
 animationOn = false;

 pos = 1;
 posY = 1;

 scale = 1.0f;

 hide = false;

 curAnimation = NULL;

 startFrame = 0;
 startLayer = 0;
 curFrame = 0;
 curLayer = 0;
 maxFrame = 0;
 maxLayer = 0;

 forward = true;

 looping = true;
 stopAtEnd = false;
 active = true;

 rot = 0.0f;

 rotPointX = frameW /2;
 rotPointY = frameH /2;

 animationDelay = 0;
 curDelay = 0;

 scaleX = 1.0f;
 scaleY = 1.0f;

}





void Sprite::Update()
{

 if (animationOn)
 {
  curDelay++;
  if (curDelay >= animationDelay)
  {
   curDelay = 0;
   if (forward)
   {
    curFrame++;
    if ((curFrame >= image->w / frameW) || (curFrame > maxFrame && curLayer == maxLayer))
    {
     curFrame = 0;
     curLayer++;
    }
    if ((curLayer > maxLayer))
    {
     curLayer = startLayer;
     curFrame = startFrame;
     if (!looping)
     {
      if (stopAtEnd)
      {
       stopAtEnd = false;
       StartStaticAnimation(maxFrame, maxLayer, maxFrame, maxLayer, curDelay);
      }
      else
      {
       active = false;
       SetAnimation(false);
      }
     }
    }
   }
   else
   {
    curFrame--;
    if ((curFrame < 0) || (curFrame < startFrame))
    {

     curFrame = image->w / frameW - 1;
     curLayer--;
    }
    if ((curLayer < startLayer))
    {
     curLayer = maxLayer;
     curFrame = maxFrame;
     if (!looping)
     {
      if (stopAtEnd)
      {
       stopAtEnd = false;
       StartStaticAnimation(startFrame, startLayer, startFrame, startLayer,
        curDelay);
      }
      else
      {
       active = false;
       SetAnimation(false);
      }
     }
    }

   }

  }
 }

}




void Sprite::Draw()
{
 if (active && !hide)
 {
  GameDraw::DrawImagePart(image, (int) x, (int) y, frameW * curFrame, frameH
   * curLayer, frameW, frameH, rot, scale*scaleX, scale*scaleY,  rotPointX,  rotPointY, pos, posY);
 }
}








void Sprite::SetAnimation(bool t)
{
 animationOn = t;
}





void Sprite::StartStaticAnimation(int sFrame, int sLayer, int mFrame,int mLayer, int sDelay)
{
 startFrame = sFrame;
 startLayer = sLayer;
 curFrame = sFrame;
 curLayer = sLayer;
 maxFrame = mFrame;
 maxLayer = mLayer;
 animationDelay = sDelay;
 curDelay = 0;
 animationOn = false;
 active = true;
 curAnimation = NULL;
}

void Sprite::StartAnimation(AnimationData* data)
{

 StartAnimation(data->sF, data->sL, data->eF, data->eL, data->delay);
 curAnimation = data;
}

void Sprite::StartAnimation(int sFrame, int sLayer, int mFrame, int mLayer,int sDelay)
{
 startFrame = sFrame;
 startLayer = sLayer;
 curFrame = sFrame;
 curLayer = sLayer;
 maxFrame = mFrame;
 maxLayer = mLayer;
 animationDelay = sDelay;
 curDelay = 0;
 animationOn = true;
 active = true;
 looping = true;
 forward = true;
}


void Sprite::StartAnimationPlayOnce(int sFrame, int sLayer, int mFrame,int mLayer, int sDelay)
{
 startFrame = sFrame;
 startLayer = sLayer;
 curFrame = sFrame;
 curLayer = sLayer;
 maxFrame = mFrame;
 maxLayer = mLayer;
 animationDelay = sDelay;
 curDelay = 0;
 animationOn = true;
 active = true;
 looping = false;
 forward = true;
 stopAtEnd = false;

}

void Sprite::StartAnimationPlayOnceStop(int sFrame, int sLayer, int mFrame, int mLayer, int sDelay)
{
 startFrame = sFrame;
 startLayer = sLayer;
 curFrame = sFrame;
 curLayer = sLayer;
 maxFrame = mFrame;
 maxLayer = mLayer;
 animationDelay = sDelay;
 curDelay = 0;
 animationOn = true;
 active = true;
 looping = false;
 forward = true;
 stopAtEnd = true;

}

bool Sprite::IsAnimationFinishedNext()
{
 if (forward){return curFrame == maxFrame && curLayer == maxLayer && curDelay >= animationDelay-2;}
 else { return curFrame == startFrame && curLayer == startLayer && curDelay >= animationDelay-2;}
}

bool Sprite::OnFrameEnter(int sF, int sL)
{
 return curFrame == sF && curLayer == sL && curDelay == 0;
}

bool Sprite::IsAnimationFinished()
{
 bool r = false;
 if (forward){r = curFrame == maxFrame && curLayer == maxLayer && curDelay >= animationDelay-1;}
 else { r = curFrame == startFrame && curLayer == startLayer && curDelay >= animationDelay-1;}
 return r;
}

bool Sprite::IsCurrentAnimation(AnimationData* a)
{

 return a == curAnimation;
}

void Sprite::StartReverse()
{
 forward = false;
 curFrame = maxFrame;
 curLayer = maxLayer;
}

void Sprite::SetReverse()
{
 forward = false;
}
