

#ifndef GPAIR_H
#define GPAIR_H 1

#include <vector>

template <class T1, class T2>
class GPair
{
 public:
  T1 a;
  T2 b;
  GPair(T1 sa, T2 sb)
  {
   a = sa;
   b = sb;
  }

};


#endif

