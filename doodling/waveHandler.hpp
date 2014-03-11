#include <vector>
#include <string>
#include <fstream>

using std::vector;
using std::string;

typedef struct {
    char riff[4];
    long size;
    char wave[4];
} RiffHeader;

typedef struct {
    char tag[4];
    long length;
} RiffTag;

typedef struct {
    short formatTag;
    short channels;
    long samplesPerSecond;
    long averageBytesPerSecond;
    short blockAlign;
    short bitsPerSample;
} WaveHeader;

// Credit to stack overflow
template <bitypename T>
void swap_endian(T& pX) {
    char& raw = reinterpret_cast<char&>(px);
    std::reverse(&raw, &raw + sizeof(T));
}

class WaveHandler {
  public:
    WaveHandler();
    WaveHandler(string filename);
    ~WaveHandler();

  private:
    string              _filename;
    RiffHeader          _riffHeader;
    vector<RiffTag>     _riffTags;
    std::streampos      _currentStreamPosition;

    void checkRiffHeader();
    std::streampos findTag(const string tag);
    WaveHeader checkWaveHeader();
}
