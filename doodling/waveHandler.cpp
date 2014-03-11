#include "waveHandler.hpp"

#include <iostream>
#include <exception>

WaveHandler::WaveHandler();

WaveHandler::WaveHandler(string filename);

WaveHandler::~WaveHandler();

void WaveHandler::openWaveFile() {
    std::streampos currentStreamPosition = 0;
    try {
        checkRiffHeader();
        currentStreamPosition = findTag("data");
        ifstream ifile;
        ifile.open(_filename);
        ifile.read(NULL, sizeof(char[8]));
        currentStreamPosition = ifile.tellg();
        ifile.close();
        _currentStreamPosition = currentStreamPosition;
    }
    catch(...) {
        std::cerr << "Error occured in:" << __func__ << std::endl;
        return pos;
    }
}

void WaveHandle::openWaveFile(string filename) {
   _filename = filename; 
   openWaveFile();
}

void WaveHandler::checkRiffHeader() {
    try {
        ifstream ifile;
        ifile.open(_filename);
        ifile.read(reinterpret_cast<unsigned char *>&riffHeader, sizeof(RiffHeader)); // TODO unsafe
        if(string(RiffHeader.riff != "RIFF"))
            throw "RiffHeader RIFF ID invalid";
        if(string(RiffHeader.wave != "WAVE"))
            throw "RiffHeader WAVE ID invalid";
        pos = ifile.tellg();
        ifile.close();
    }
    return pos;
    catch(string e) {
        throw e + " in function:" + __func__;
        return 0;
    }
    catch(std::ifstream::failure e) {
        throw e;
        return 0;
    }
    catch(...) {
        std::cerr << "Error occured in WaveHandler::checkRiffHeader()";
        return 0;
    }
}

// Returns the position where tag starts or eof
std::streampos WaveHandler::findTag(const string tag) {
    std::streampos pos;
    try {
        ifstream ifile;
        ifile.open(_filename);
        pos = ifile.tellg();
        while(ifile.read(buf, sizeof(buf))) {
            if(std::string(buf) == tag)
                return pos;
            pos = ifile.tellg();
        }
        return pos;
    }
    catch(std::ifstream::failure e) {
        throw e;
        return pos;
    }
    catch(...) {
        std::cerr << "Error occured in WaveHandler::findTag()";
        return pos;
    }
}
