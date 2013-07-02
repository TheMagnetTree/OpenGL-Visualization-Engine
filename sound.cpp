// Load some sound in openAL / ALURE
#include <cstdio>
#include <AL/alure.h>

int main(int argc, char *argv[]) {
    ALCcontext *context;
    ALCdevice *device;

    const ALCchar *default_device;
    default_device = alcGetString(NULL, ALC_DEFAULT_DEVICE_SPECIFIER);

    if ((device = alcOpenDevice(default_device)) == NULL) {
        return -1;
    }

    context = alcCreateContext(device, NULL);
    alcMakeContextCurrent(context);
    alcProcessContext(context);

    ALuint src, buf[1032];
    alGenSources(1, &src);
    alureStream* stream = alureCreateStreamFromFile("test.wav", 19200, 1032, buf);
    alSourceQueueBuffers(src, 1032, buf);
    alSourcePlay(src);

    ALint state = AL_PLAYING;
    ALint processed = 0;

    while(true) {
        alGetSourcei(src, AL_SOURCE_STATE, &state);
        alGetSourcei(src, AL_BUFFERS_PROCESSED, &processed);
        if(processed > 0) {
            ALuint bufs[1032];
            alSourceUnqueueBuffers(src, processed, bufs);

            processed = alureBufferDataFromStream(stream, processed, bufs);
            alSourceQueueBuffers(src, processed, bufs);
        }

        if(state != AL_PLAYING)
            alSourcePlay(src);
    }

    alGetError();
    alcCloseDevice(device);
    return 0;
}
