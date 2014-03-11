#ifndef _VISLIBINTERFACE_HPP
#define _VISLIBINTERFACE_HPP

#include "PCM.hpp"
#include "kiss_fft.h"

class VisLibInterface {
  public:
    vector< vector<float> > *PCMData() { return _PCM->PCMData(); };
    vector< vector<float> > *FFTData();
  private:
    PCM _PCM;
    kiss_fft_cpx *_fft_data_in;
    kiss_fft_cpx *_fft_data_out;
    kiss_fft_cfg *_fft_cfg;
}

#endif //_VISLIBINTERFACE_HPP
