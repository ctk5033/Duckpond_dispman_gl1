#ifndef GTYPES_H
#define GTYPES_H 1

class GColor
{
 public:

  GColor()
  {
   SetColor(1.0f,1.0f,1.0f);
  }

  GColor(float sr, float sg, float sb, float sa)
  {
   SetColor(sr,sg,sb,sa);
  }

  GColor(float sr, float sg, float sb)
  {
   SetColor(sr,sg,sb);
  }

  void Multiply(float sr, float sg, float sb , float sa = 1.0f)
  {
   r = r*sr;
   g = g*sg;
   b = b*sb;
   a = a*sa;
  }


  void SetColor(float sr, float sg, float sb, float sa = 1.0f)
  {
   if (sr > 1 || sg > 1 || sb > 1 || sa > 1)
   {
    r = sr*1.0f/255;
    g = sg*1.0f/255;
    b = sb*1.0f/255;
    a = sa;
   }
   else
   {
    r = sr;
    g = sg;
    b = sb;
    a = sa;
   }
  }


  float r;
  float g;
  float b;
  float a;



};



class GPoint
{
public:
 int x;
 int y;


 GPoint()
 {
  x = 0;
  y = 0;
 }

 GPoint(int sx, int sy)
 {
  x = sx;
  y = sy;
 }


};

class GBox
{
 public:

  GBox()
  {
   x = 0;
   y = 0;
   w = 1;
   h = 1;
   rot = 0;
  }

  float x;
  float y;
  float w;
  float h;
  float rot;

  void SetBox(int sx, int sy, int sw, int sh)
  {
   x = sx;
   y = sy;
   w = sw;
   h = sh;
  }






        float GetCenterX() { return x + w / 2; }
        float GetCenterY() { return y + h / 2; }

        bool BoxCollide(float sx, float sy, GBox oBox, float ox, float oy)
        {

            // check to see if larger bounding boxes are colliding first
            float x1 = sx + x;
            float y1 = sy + y;
            float w1 = w;
            float h1 = h;

            if (w1 > h1)
            {
                y1 = y1 - w / 2;
                h1 = w1;
            }
            else
            {
                x1 = x1 - h / 2;
                w1 = h1;
            }


            float x2 = ox + oBox.x;
            float y2 = oy + oBox.y;
            float w2 = oBox.w;
            float h2 = oBox.h;

            if (w2 > h2)
            {
                y2 = y2 - w / 2;
                h2 = w2;
            }
            else
            {
                x2 = x2 - h / 2;
                w2 = h2;
            }

            bool largeBoxCollide = false;

            if ((x1) >= (x2) && (x1) <= (x2 + w2) ||
            (x2) >= (x1) && (x2) <= (x1 + w1))
            {
                if ((y1) >= (y2) && (y1) <= (y2 + h2) ||
                   (y2) >= (y1) && (y2) <= (y1 + h1))
                {
                    largeBoxCollide = true;
                }
            }

            if (!largeBoxCollide) { return false; }



            float axisX[4];
            float axisY[4];

            // optimization: first check to see if it is colliding with a bigger bounding box before doing all thest fancy sines and cosines

            // calc A values;
            // center (rotation point)
            float aX = sx + x + w / 2;
            float aY = sy + y + h / 2;

            float aULx = aX - cos(rot) * (w / 2) + sin(rot) * (h / 2); float aULy = aY - cos(rot) * (h / 2) - sin(rot) * (w / 2);
            float aURx = aX - cos(rot) * (-w / 2) + sin(rot) * (h / 2); float aURy = aY - cos(rot) * (h / 2) - sin(rot) * (-w / 2);
            float aLLx = aX - cos(rot) * (w / 2) + sin(rot) * (-h / 2); float aLLy = aY - cos(rot) * (-h / 2) - sin(rot) * (w / 2);
            float aLRx = aX - cos(rot) * (-w / 2) + sin(rot) * (-h / 2); float aLRy = aY - cos(rot) * (-h / 2) - sin(rot) * (-w / 2);




            // calc B values
            float bX = ox + oBox.x + oBox.w / 2;
            float bY = oy + oBox.y + oBox.h / 2;

            float bULx = bX - cos(oBox.rot) * (oBox.w / 2) + sin(oBox.rot) * (oBox.h / 2); float bULy = bY - cos(oBox.rot) * (oBox.h / 2) - sin(oBox.rot) * (oBox.w / 2);
            float bURx = bX - cos(oBox.rot) * (-oBox.w / 2) + sin(oBox.rot) * (oBox.h / 2); float bURy = bY - cos(oBox.rot) * (oBox.h / 2) - sin(oBox.rot) * (-oBox.w / 2);
            float bLLx = bX - cos(oBox.rot) * (oBox.w / 2) + sin(oBox.rot) * (-oBox.h / 2); float bLLy = bY - cos(oBox.rot) * (-oBox.h / 2) - sin(oBox.rot) * (oBox.w / 2);
            float bLRx = bX - cos(oBox.rot) * (-oBox.w / 2) + sin(oBox.rot) * (-oBox.h / 2); float bLRy = bY - cos(oBox.rot) * (-oBox.h / 2) - sin(oBox.rot) * (-oBox.w / 2);

            // float calc axis values
            axisX[0] = aURx - aULx;
            axisY[0] = aURy - aULy;

            axisX[1] = aURx - aLRx;
            axisY[1] = aURy - aLRy;

            axisX[2] = bULx - bLLx;
            axisY[2] = bULy - bLLy;

            axisX[3] = bULx - bURx;
            axisY[3] = bULy - bURy;




            // cycle through all axis
            for (int i = 0; i < 4; i++)
            {
                float apX[4];
                float apY[4];
                apX[0] = projX(aULx, aULy, axisX[i], axisY[i]);
                apY[0] = projY(aULx, aULy, axisX[i], axisY[i]);
                apX[1] = projX(aURx, aURy, axisX[i], axisY[i]);
                apY[1] = projY(aURx, aURy, axisX[i], axisY[i]);
                apX[2] = projX(aLLx, aLLy, axisX[i], axisY[i]);
                apY[2] = projY(aLLx, aLLy, axisX[i], axisY[i]);
                apX[3] = projX(aLRx, aLRy, axisX[i], axisY[i]);
                apY[3] = projY(aLRx, aLRy, axisX[i], axisY[i]);

                float bpX[4];
                float bpY[4];
                bpX[0] = projX(bULx, bULy, axisX[i], axisY[i]);
                bpY[0] = projY(bULx, bULy, axisX[i], axisY[i]);
                bpX[1] = projX(bURx, bURy, axisX[i], axisY[i]);
                bpY[1] = projY(bURx, bURy, axisX[i], axisY[i]);
                bpX[2] = projX(bLLx, bLLy, axisX[i], axisY[i]);
                bpY[2] = projY(bLLx, bLLy, axisX[i], axisY[i]);
                bpX[3] = projX(bLRx, bLRy, axisX[i], axisY[i]);
                bpY[3] = projY(bLRx, bLRy, axisX[i], axisY[i]);



                // find max A
                int maxA = 0;
                // find min A
                int minA = 0;
                // find max B
                int maxB = 0;
                // find min B
                int minB = 0;

                float minAval = dot(apX[minA], apY[minA], axisX[i], axisY[i]);
                float maxAval = dot(apX[maxA], apY[maxA], axisX[i], axisY[i]);
                float minBval = dot(bpX[minB], bpY[minB], axisX[i], axisY[i]);
                float maxBval = dot(bpX[maxB], bpY[maxB], axisX[i], axisY[i]);

                for (int j = 1; j < 4; j++)
                {
                    if (dot(bpX[j], bpY[j], axisX[i], axisY[i]) < minBval)
                    {
                        minB = j;
                        minBval = dot(bpX[minB], bpY[minB], axisX[i], axisY[i]);
                    }
                    if (dot(bpX[j], bpY[j], axisX[i], axisY[i]) > maxBval)
                    {
                        maxB = j;
                        maxBval = dot(bpX[maxB], bpY[maxB], axisX[i], axisY[i]);
                    }
                    if (dot(apX[j], apY[j], axisX[i], axisY[i]) < minAval)
                    {
                        minA = j;
                        minAval = dot(apX[minA], apY[minA], axisX[i], axisY[i]);
                    }
                    // if dot product of the point is greater than the dot product of the found max, set to new max
                    if (dot(apX[j], apY[j], axisX[i], axisY[i]) > maxAval)
                    {
                        maxA = j;
                        maxAval = dot(apX[maxA], apY[maxA], axisX[i], axisY[i]);
                    }
                }



                //If the minimum scalar value of B is less than or equal to the maximum scalar value of A
                // and/or the maximum scalar value of B is greater than or equal to the minimum scalar value of A
                // then our objects overlap when projected onto this axis.
                // no overlap, end it
                if (!(minBval <= maxAval && maxBval >= minAval)) { return false; }

            }






            return true;
        }





        float projX(float pointX, float pointY, float axisX, float axisY)
        {
            return (pointX * axisX + pointY * axisY) / (axisX * axisX + axisY * axisY) * axisX;
        }

        float projY(float pointX, float pointY, float axisX, float axisY)
        {
            return (pointX * axisX + pointY * axisY) / (axisX * axisX + axisY * axisY) * axisY;
        }

        float dot(float p1x, float p1y, float p2x, float p2y)
        {
            return p1x * p2x + p1y * p2y;
        }





};





#endif
