#include "soundHandler.h"

// TODO does too much stuff, not very flexible, learn openAL more
soundStream::soundStream(int bufSize) {
    _bufSize = bufSize;
    _defaultDevice = alcGetString(NULL, ALC_DEFAULT_DEVICE_SPECIFIER);
    if ((device = alcOpenDevice(defaultDevice)) == NULL) {
        // throw error
    }
    context = alcCreateContext(device, NULL);
    alcMakeContextCurrent(context);
    alcProcessContext(context);
}

soundStream::~soundStream() {
    // TODO deallocate everything
    alGetError(); // Clear errors
    alcCloseDevice(device);
}

alureStream *soundStream::streamFromFile(string filename) {
    _stream = alureCreateStreamFromFile(filename.c_str(), _bitrate, _bufSize, _buffer);
    alGenSources(1, &_source);
    alSourceQueueBuffers(_source, _bufSize, _buffer);
    return _stream;
}

void soundStream::play() {
    ALint processed = 0;
    alGetSourcei(src, AL_BUFFERS_PROCESSED, &processed);
    if(processed == 0){
    }
}
