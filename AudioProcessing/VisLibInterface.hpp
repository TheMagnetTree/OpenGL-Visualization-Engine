#ifndef _VISLIBINTERFACE_HPP
#define _VISLIBINTERFACE_HPP

#include "PCM.hpp"

class VisLibInterface {
  public:
    float* PCMData();
    float* FFTData();
  private:
    PCM *_PCM;
}

#endif //_VISLIBINTERFACE_HPP
