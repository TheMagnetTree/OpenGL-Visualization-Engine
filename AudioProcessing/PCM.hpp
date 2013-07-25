#ifndef _PCM_HPP
#define _PCM_HPP

#include <vector>
#include <functional>

using namespace std;

// Generic container for raw sound data

class PCM {
  public:
    PCM();
    PCM(const int maxsamples, const int numchannels);
    ~PCM();
    void faddPCM(const float *PCMdata, const int numsamples);
    void setNewPCMDataCallback(function<void()> callback) { newPCMDataCallback = callback; };
  private:
    int _maxsamples;
    int _numchannels;
    vector< vector<float> > _PCMData;

    function<void()> newPCMDataCallback;
};

#endif //_PCM_HPP
