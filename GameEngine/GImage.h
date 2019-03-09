

#ifndef GIMAGE_H
#define GIMAGE_H 1

#include "GameEngine.h"
#include "GMap.h"

class GImage
{
 public:
  GImage(KString sfilename);
  ~GImage();

  void Reload(bool deleteOld = true);

  int w; // actual size of the image
  int h;

  int oW; // size of the image after power of two increase
  int oH;


  KString filename;

  GLuint data;

  bool hasTransparent;


  static GImage* GetImg(KString img);
  static GMap < KString, GImage* > imgMap;

  static void ReloadImages();




};





#endif
