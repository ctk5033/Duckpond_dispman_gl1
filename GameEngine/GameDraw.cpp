
#include "GameDraw.h"
#include "GameEngine.h"
#include "GFont.h"
#include <string>

#include "../MainFile.h"


#include "GameEngine.h"


GLuint GameDraw::lastTexture = 999;


// Z Shift
float GameDraw::shiftZ = 0;
float GameDraw::shiftZ2 = 0;
float GameDraw::rotY = 0;


// Screen Shake
float GameDraw::ShakeX = 0;
float GameDraw::ShakeY = 0;
float GameDraw::ShakeTimer = 0;

float GameDraw::ShakeCounter = 0;
float GameDraw::ShakeAmpX = 0;
float GameDraw::ShakeAmpY = 0;
float GameDraw::ShakeSpeed = 0;



/*void GameDraw::DrawBox(float sx, float sy, float sw, float sh,float rot, float scale, bool global)
{
    GameEngine::drawCommandList.Add(new GC_DrawBox(sx,sy,sw,sh,rot,scale,global));

}*/

void GameDraw::DrawGlobalBox(float x, float y, float w, float h)
{
  /*  x = (x - GameEngine::ScreenShiftX - ShakeX)/GameEngine::GlobalScale;
    y = (y - GameEngine::ScreenShiftY - ShakeY)/GameEngine::GlobalScale;
    w = (w/GameEngine::GlobalScale);
    h = (h/GameEngine::GlobalScale);*/
    DrawBox(x, y, w, h,0,1, true);
}


void GameDraw::DrawBox(float x, float y, float sw, float sh,float rot, float scale, bool global, int rX, int rY)
{
    static const GLfloat squareVertices[] = {
        .5f, -.5f, 0,            // Top left
        -.5f, -.5f, 0,            // Bottom left
        -.5f, .5f, 0,            // Bottom right
        .5f, .5f, 0,             // Top right
    };



    float W = (sw*GameEngine::GlobalScale*scale);
    float H = (int)(sh*GameEngine::GlobalScale*scale);

    float X = (x*GameEngine::GlobalScale + GameEngine::ScreenShiftX + ShakeX);//(-y +GameEngine::WINDOW_H-sh*scale)*GameEngine::GlobalScale + GameEngine::ScreenShiftY + ShakeX;
    float Y = (y*GameEngine::GlobalScale + GameEngine::ScreenShiftY + ShakeY); // convertion of coordinates from top right to top left

    if (global)
    {
        H = sh;
        W = sw;
        X = x;
        Y = y;

        /*W = sw;
        H = sh;
        X = x;
        Y = y;*/
    }

    if (rX == -1 && rY == -1)
    {
        rX = 0;
        rY = 0;
    }
    else
    {
       rX = (int)(rX*GameEngine::GlobalScale - W/2);
       rY = (int)((rY)*GameEngine::GlobalScale - H/2);
    }


    shiftZ = 0;
    shiftZ2 = 0;
    //if (!global && (X + W < 0 || X > GameEngine::SCREEN_W || Y + H < 0 || Y > GameEngine::SCREEN_W)) {return;}
    glPushMatrix();
    //glLoadIdentity();
    glTranslatef(X + W/2,Y + H/2,shiftZ);

    glTranslatef(rX,rY,0);
    glRotatef(rot,0,0,1);
    glRotatef(rotY, 0, 1.0f, 0.0f);
    glTranslatef(-rX,-rY,0);
    glScalef(W, H, 1.0f);
    glTranslatef(0, 0, shiftZ2);




    glDisable(GL_TEXTURE_2D);
	   glVertexPointer(3, GL_FLOAT, 0, squareVertices);
    glEnableClientState(GL_VERTEX_ARRAY);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    glPopMatrix();

}


void GameDraw::DrawImage(GImage* image, float sx, float sy)
{
    GameDraw::DrawImagePart(image, sx,sy,0,0,image->w, image->h,0.0f,1,1,-1,-1,1);
}

void GameDraw::DrawImage(GImage* image, float x, float y, float rot, float scale)
{
    DrawImagePart(image, x, y, 0,0, image->w, image->h, rot, scale, scale, -1,-1,1);
}

void GameDraw::DrawImagePart(GImage* image, float x, float y, int sx, int sy, int sw, int sh, float rot, float scaleX, float scaleY, int rX, int rY, int posX, int posY, bool ignoreRotScale)
{

    static const GLfloat squareVertices[] = {
       -.5f, -.5f, 0,             // Top right
        -.5f, 0.5f, 0,            // Top left
        .5f, 0.5f, 0,            // Bottom left
        .5f, -.5f, 0,            // Bottom right

    };

    static GLfloat texture[] =
    {
        0,1,
        0,0,
        1,0,
        1,1

    };



    float W = (sw*scaleX*GameEngine::GlobalScale );
    float H = (sh*scaleY*GameEngine::GlobalScale );

    // convertion of coordinates from top right to top left 480
    float X = (x*GameEngine::GlobalScale + GameEngine::ScreenShiftX + ShakeX);//(-y +GameEngine::WINDOW_H-sh*scale)*GameEngine::GlobalScale + GameEngine::ScreenShiftY + ShakeX;
    float Y = (y*GameEngine::GlobalScale  + GameEngine::ScreenShiftY + ShakeY); // convertion of coordinates from top right to top left

    if (x + sw*scaleX < 0 || x > GameEngine::SCREEN_W
        || y + sh*scaleY < 0 || y > GameEngine::SCREEN_H){return;}

    if (rX == -1 && rY == -1)
    {
        rX = 0;
        rY = 0;
    }
    else if (!ignoreRotScale)
    {
       rX = (int)(rX*scaleX*GameEngine::GlobalScale - W/2);
       rY = (int)((rY)*scaleY*GameEngine::GlobalScale - H/2);
    }
    else
    {
        rX = (int)(rX*GameEngine::GlobalScale - W/2);
        rY = (int)((rY)*GameEngine::GlobalScale - H/2);
    }

  // X = (int)(X+.5f);
  // Y = (int)(Y+.5f);
    //W = (int)(W);
   // H = (int)(H);
    //rX = W - rX;
    //rY = H - rY;
    glPushMatrix();
  //  glLoadIdentity();
    glTranslatef((int)(X + W/2),(int)(Y + H/2),shiftZ);

    glTranslatef(rX,rY,0);
    glRotatef(rot,0,0,1.0f);
    glRotatef(rotY, 1.0f, 0.0f, 0.0f);
    if (posY == -1){glRotatef(180, 1.0f, 0.0f, 0.0f);}
    glTranslatef(-rX,-rY,0);
    glScalef((int)W,(int)H, 1.0f);
    glTranslatef(0, 0, shiftZ2);



    glEnable(GL_TEXTURE_2D);


    float tx = (sx)*1.0f/image->oW;
    float ty = (sy)*1.0f/image->oH;
    float tw = (sw)*1.0f/image->oW;
    float th = (sh)*1.0f/image->oH;

    if (posX == -1)
    {
        texture[0] = tx+tw;
        texture[1] = ty;

        texture[2] = tx+tw;
        texture[3] = ty + th;

        texture[4] = tx;
        texture[5] = ty + th;

        texture[6] = tx;
        texture[7] = ty;
    }
    else
    {
        texture[0] = tx;
        texture[1] = ty;

        texture[2] = tx;
        texture[3] = ty + th;

        texture[4] = tx + tw;
        texture[5] = ty + th;

        texture[6] = tx + tw;
        texture[7] = ty;
    }


    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

   // glBindTexture(GL_TEXTURE_2D, image->texture);
    if(image->data != lastTexture){ glBindTexture(GL_TEXTURE_2D, image->data);}
	glVertexPointer(3, GL_FLOAT, 0, squareVertices);
    glTexCoordPointer(2, GL_FLOAT, 0, texture);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
glPopMatrix();
}












int GameDraw::DrawText(KString stext, float x, float y, bool center, int underLine)
{
    int curPosition = 0;

    int cx; int cy; int cw; int ch;

    curPosition++;
    float scale = GameEngine::curFont->scale;

    int textW = 1;
    if (center)
    {
     textW = GameEngine::curFont->CalculateWidth(stext);
     x = x - textW/2;
    }



    //	x = x - curPosition *scale* 1.0f / 2;

    //GameEngine::Message(text.c_str()[0]);


   std::string text = std::string(stext.str.c_str());


    //text = GameEngine::ToUpperCase(text);

    curPosition = 0;

    int textLength = text.length();
    for (int i = 0; i < textLength; i++)
    {
        cx = ((int)text.c_str()[i]-GFont::STARTING_CHAR)%GameEngine::curFont->tileCountX*GameEngine::curFont->tileW;
        cy = ((int)text.c_str()[i]-GFont::STARTING_CHAR)/GameEngine::curFont->tileCountX*GameEngine::curFont->tileH;
        cw = GameEngine::curFont->tileW;
        ch = GameEngine::curFont->tileH;

        // special modifiers in string

        if (text.c_str()[i] == '^')
        {
            int endB = -1;
            for (int j = i+1; j < textLength; j++)
            {
             if (text.c_str()[j] == ']')
             {
              endB = j;
              break;
             }
            }
            if (endB != -1)
            {
             KString valStr = text.substr(i+2, (endB-i)-2);
             i = endB;
             GList<KString> valList = valStr.Split('^');
             int spacing = GameDraw::DrawSpecialCharacter(valList, (int)(x+curPosition), (int)(y));
             curPosition = curPosition + spacing;
            }
        //    GameDraw::DrawImagePart(MurderResource::imItemList, (int)(x+curPosition*scale), (int)y, cx,cy, cw,ch, 0.0f, scale, scale);
        }
        else
        {
         // draw regular characters

         GameDraw::DrawImagePart(GameEngine::curFont->image, (int)(x+curPosition), (int)y, cx,cy, cw,ch, 0.0f, scale, scale);
         curPosition = curPosition + (GameEngine::curFont->GetWSpace(text.c_str()[i])+GFont::SPACE_BLANKSPACE)*scale; // no scaling here
         if (underLine == i)
         {
          GameDraw::DrawBox( (int)(x+curPosition), (int)y + 6, 4, 1);
         }
        }
    }

    return textW;

}


int GameDraw::DrawSpecialCharacter(GList<KString> valList, float x, float y, bool calculateWidthOnly)
{
 return MainFile::DrawSpecialCharacter(valList, x, y, calculateWidthOnly);

}




void GameDraw::DrawText(GText* text, float x, float y)
{
    if (text->textWrap.GetSize() > 0) // IsWrap()
    {
        for (int i = 0; i < text->textWrap.GetSize(); i++)
        {
            DrawText(text->textWrap[i], x, y+i*GameEngine::curFont->tileH*GameEngine::curFont->scale);
        }
    }
    else
    {
        if (text->IsCentered())
        {
            x = x - text->GetTextWidth()/ 2;

        }
        DrawText(text->GetText(), x,y);
    }





}





void GameDraw::Shake(float ampX, float ampY, float speed, float dur)
{
    if (ShakeTimer <= 0)
    {
        ShakeX = 0;
        ShakeY = 0;
        ShakeCounter = 0;
    }
    ShakeAmpX = ampX;
    ShakeAmpY = ampY;

    ShakeSpeed = speed;
    ShakeTimer = dur;
}

void GameDraw::ShakeUpdate()
{
    if (ShakeTimer <= 0){ShakeX = 0; ShakeY = 0; return;}
    ShakeX = (float)(ShakeAmpX*sin(ShakeCounter));
    ShakeY = (float)(ShakeAmpY*sin(ShakeCounter));
    ShakeCounter = (float)(ShakeCounter + 3.14f/ShakeSpeed);

    if (ShakeCounter > 3.14*2){ShakeCounter = 0;}
    ShakeTimer--;
}








// SHIFT Z -------------

void GameDraw::SetShiftZ(float sz)
{
    shiftZ = sz;
}

// shift after rotation
void GameDraw::SetShiftZ2(float sz)
{
    shiftZ2 = sz;
}

void GameDraw::SetRotY(float rY)
{
    rotY = rY;
}


