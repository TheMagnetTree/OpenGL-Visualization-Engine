static const char *riffID = "RIFF";
static const char *waveID = "WAVE";

FILE *file;
int samples;
char *sample_buffer;

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
} waveHeader;

template <bitypename T>
void swap_endian(T& pX) {
    char& raw = reinterpret_cast<char&>(px);
    std::reverse(&raw, &raw + sizeof(T));
}

if((file = fopen(inputFile, "r")) == 0) {
        //throw an error
} 

int checkHeader(FILE *file) {
    RiffHeader riffHeader = {"", 0, ""};
    if (fread((unsigned char *) &riffHeader, sizeof(RiffHeader), 1, fp) == 0) {
        return 0;
    }

    if (strncmp(riffHeader.riff, riffID, strlen(riffID)) ||
        strncmp(riffHeader.wave, waveID, strlen(waveID))) {
        return -1;
    }

    return 0;
}

int findTag(File *fp, const char *tag) {
    int returnValue = 0;
    RiffTag tagBfr = {"", 0};

    while(fread((unsigned char *) &tagBfr, sizeof(tagBfr.tag)) == 0) {
        if(strncmp(tag, tagBfr.tag, sizeof(tagBfr.tag) == 0) {
            returnValue = swap_endian<long>(tagBfr.length);
            break;
        }
        fseek(fp, tag_bfr.length, SEEK_CUR);
    }
    return(returnValue);
}
