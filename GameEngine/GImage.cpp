

#include "GImage.h"


GMap< KString, GImage*  > GImage::imgMap;

GImage* GImage::GetImg(KString img)
{
 if (imgMap.Contains(img))
 {
  return imgMap.Get(img);
 }
 else
 {
  GImage* imRet = new GImage(img);
  imgMap.Put(img, imRet);
  return imRet;
 }

 return NULL;
}

void GImage::ReloadImages()
{
 for (int i = 0; i < imgMap.itemList.GetSize(); i++)
 {
  imgMap.itemList[i]->Reload();
 }
}


SDL_Color translate_color(Uint32 int_color)
{
    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
        SDL_Color color={(int_color & 0x00ff0000)/0x10000,(int_color &
         0x0000ff00)/0x100,(int_color & 0x000000ff),0};
    #else
        SDL_Color color={(int_color & 0x000000ff),(int_color &
      0x0000ff00)/0x100,(int_color & 0x00ff0000)/0x10000,0};
    #endif
    return color;
}

int getNextPowerOfTwo(int v)
{
 int s = 2;
 while (v > s)
 {
  s = s * 2;
 }
 return s;
}


GImage::GImage(KString sfilename)
{
  filename = KString(sfilename.str);
  Reload(false);
}

void GImage::Reload(bool deleteOld)
{
 if (deleteOld){glDeleteTextures( 1, &data );}

 SDL_Surface* text;
 SDL_Surface* surf;


 hasTransparent = FALSE;

//std::cout << sfilename.str.c_str();

 //sprintf(filename, "%s", sfilename.c_str());



 surf = IMG_Load(filename.str.c_str());
 if (!surf)
 {
  char errbox[256];
  sprintf(errbox, "Error Loading File: %s", filename.str.c_str());
//  ::MessageBox(0, errbox, 0 ,0);
  std::cout << errbox;
//  PostQuitMessage(0);
 }

 Uint32 rmask, gmask, bmask, amask;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
 rmask = 0xff000000;
 gmask = 0x00ff0000;
 bmask = 0x0000ff00;
 amask = 0x000000ff;
#else
 rmask = 0x000000ff;
 gmask = 0x0000ff00;
 bmask = 0x00ff0000;
 amask = 0xff000000;
#endif

 oW = getNextPowerOfTwo(surf->w);
 oH = getNextPowerOfTwo(surf->h);
 w = surf->w;
 h = surf->h;

 text = SDL_CreateRGBSurface(SDL_SWSURFACE, oW, oH, 32, rmask, gmask, bmask, amask);

 SDL_SetAlpha(surf , 0, SDL_ALPHA_OPAQUE);
 SDL_FillRect(text, NULL, SDL_MapRGBA(text->format, 0, 0, 0,0));
 SDL_BlitSurface(surf, 0, text, 0);






 SDL_Color color;
 for (int y = 0; y < text->h; y++)
 {
  for (int x = 0; x < text->w; x++)
  {
   unsigned int pix = ((unsigned int*)text->pixels)[y*(text->pitch/sizeof(unsigned int)) + x];
   color =  translate_color(pix);
   if (color.r == 255 && color.b == 255 && color.g == 0)
   {
    hasTransparent = TRUE;
    ((unsigned int*)text->pixels)[y*(text->pitch/sizeof(unsigned int)) + x] = SDL_MapRGBA(text->format, 0, 0, 0,0);
   }
  }
 }





 glGenTextures(1, &data);
 glBindTexture(GL_TEXTURE_2D, data);
 if (text->format->BitsPerPixel == 32)
 {
  hasTransparent = TRUE;
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA ,  text->w, text->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, text->pixels);
 }
 else if (text->format->BitsPerPixel == 24){glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB ,  text->w, text->h, 0, GL_RGB, GL_UNSIGNED_BYTE, text->pixels);}
 else
    {
      //  ::MessageBox(0, L"non true color! this will break!",0,0);
 }
 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);



 SDL_FreeSurface(surf);
 SDL_FreeSurface(text);



}



GImage::~GImage()
{
 glDeleteTextures( 1, &data );
}
