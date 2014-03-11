#include "PCM.hpp"
#include <iostream>

using namespace std;

PCM::PCM() {
    _maxsamples = 2048;
    _numchannels = 2;

    for(int i = 0; i < _numchannels; ++i) {
        _PCMData.push_back(vector<float>());
        for(int j = 0; j < _maxsamples; j++)
            _PCMData[i].push_back(0);
    }
}

PCM::PCM(const int maxsamples = 2048, const int numchannels = 2) {
    _numchannels = numchannels;
    _maxsamples  = maxsamples;

    for(int i = 0; i < _numchannels; ++i) {
        _PCMData.push_back(vector<float>());
        for(int j = 0; j < _maxsamples; j++)
            _PCMData[i].push_back(0);
    }
}

PCM::~PCM() {

}

// Adds a chunk of PCM data given in float format
void PCM::faddPCM(const float *newPCMData, const int numsamples) {
    int newsamples = numsamples;
    if(newsamples > _maxsamples) {
        newsamples = _maxsamples;
    }

    for(int i = 0; i < newsamples; ++i) {
        for(int j = 0; j < _numchannels; ++j) {
            _PCMData[j][i] = newPCMData[i];
        }
    }
    if(newPCMDataCallback)
    {
        newPCMDataCallback((void *) &PCMData);
    }
}

