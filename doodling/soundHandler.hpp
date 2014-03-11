// Get some very basic openAL + ALURE sound going 
// with a focus on accessing it's buffer for visualization
#include <functional>
#include <string>

#include <AL/alure.h>

using std::string;

class soundStream {
  public:
    soundStream(int bufSize);
    ~soundStream();

    alureStream *streamFromFile(string filename);
    void play();

  private:
    static const ALCchar *_defaultDevice;
    const int _bufSize;
    int _bitrate;

    ALCcontext  *_context;
    ALCdevice   *_device;
    alureStream *_stream;
    ALuint _source
    ALuint *_buffer;

    std::function< void() > *_bufferFilledCallback;
    std::function< void() > *_bufferProcessingCallback;

}

