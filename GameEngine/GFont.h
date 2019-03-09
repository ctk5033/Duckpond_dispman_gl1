//
//  GFont.h
//  GOGL5
//
//  Created by curt shark on 10/31/12.
//  Copyright (c) 2012 SharkArm. All rights reserved.
//

#ifndef __GOGL5__GFont__
#define __GOGL5__GFont__

#include <iostream>

#include "KString.h"

class GImage;


class Letter
{
public:
    Letter(){w=1;h=1;}
    Letter(int sw, int sh){w = sw; h = sh;}
    int w;
    int h;
};

class GFont
{
public:
	 static const int STARTING_CHAR = 32;
	 static const int SPACE_BLANKSPACE = 1;

  GFont(KString fontR, float sscale);
	~GFont();


	 GImage* image;
	 int tileW;
	 int tileH;
	 int tileCountX;
	 int tileCountY;
	 int leading;
	 int mainH;
	 float scale;
	 Letter* letterData;

	 int GetHeight();

	 int GetWSpace(char c);

	 int CalculateWidth(KString line);


};


#endif /* defined(__GOGL5__GFont__) */
