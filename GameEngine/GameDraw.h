//
//  GameDraw.h
//  GOGL4
//
//  Created by curt shark on 10/25/12.
//  Copyright (c) 2012 SharkArm. All rights reserved.
//

#ifndef __GOGL4__GameDraw__
#define __GOGL4__GameDraw__

#include <iostream>

#include "GImage.h"
#include "GText.h"

#include <string>

class GameDraw
{
public:

    static void DrawBox(float sx, float sy, float sw, float sh, float rot = 0.0f, float scale = 1.0f, bool global = false, int rX = -1, int rY = -1);
    static void DrawGlobalBox(float x, float y, float w, float h);

    static void DrawImage(GImage* image, float x, float y);
    static void DrawImage(GImage* image, float x, float y, float rot, float scale);
    static void DrawImagePart(GImage* image, float x, float y, int sx, int sy, int sw, int sh, float rot = 0.0f, float scaleX = 1.0f, float scaleY = 1.0f, int rX = -1, int rY = -1, int posX = 1, int posY = 1, bool ignoreRotScale = false);

    static int DrawText(KString stext, float x, float y, bool center = false, int underLine = -1);
    static void DrawText(GText* text, float x, float y);

    static int DrawSpecialCharacter(GList<KString> valList, float x, float y, bool calculateWidthOnly = false);

    // Z Shift
    static float shiftZ;
    static float rotY;
    static float shiftZ2;
    static void SetShiftZ(float sz);
	   static void SetShiftZ2(float sz);
	   static void SetRotY(float rY);

    static GLuint lastTexture;


    // Screen Shake
    static float ShakeTimer;
	static float ShakeX;
	static float ShakeY;
	static float ShakeCounter;
	static float ShakeAmpX;
	static float ShakeAmpY;
	static float ShakeSpeed;

	static void Shake(float ampX, float ampY, float speed, float dur);
    static void ShakeUpdate();
};

#endif /* defined(__GOGL4__GameDraw__) */
