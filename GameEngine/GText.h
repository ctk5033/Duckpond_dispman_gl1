//
//  GText.h
//  GOGL5
//
//  Created by curt shark on 11/3/12.
//  Copyright (c) 2012 SharkArm. All rights reserved.
//

#ifndef GOGL5_GText_h
#define GOGL5_GText_h

#include "GFont.h"
#include "GList.h"

class GText
{

public:

    GText(KString stext);

	GText(KString stext, bool scentered) ;

	GText(KString stext, float sw, bool swrap, bool scentered);

    ~GText();


 void ConstructC(KString stext, float sw, bool swrap, bool scentered);

	KString text;
	bool centered;
	bool wrap;
	float w;
	int textW;
	GList<GText*> textWrap;


	void AddLine(KString line);


	KString GetText();
    void SetText(KString stext);

 int GetRows();

	bool IsCentered();

    bool IsWrap();

	void CalculateWidth();

	int GetTextWidth();

















	void SetupWrap();


};


#endif
