// Load some sound in openAL / ALURE
#include <cstdio>
#include <AL/alure.h>
#include "kiss_fft130/kiss_fft.h"

int main(int argc, char *argv[]) {

    kiss_fft_cfg fftcfg = kiss_fft_alloc(1032, 0, NULL, NULL);

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

    kiss_fft_cpx in[1032], out[1032];

    while(true) {
        alGetSourcei(src, AL_SOURCE_STATE, &state);
        alGetSourcei(src, AL_BUFFERS_PROCESSED, &processed);
        if(processed > 0) {
            ALuint bufs[1032];
            alSourceUnqueueBuffers(src, processed, bufs);

            processed = alureBufferDataFromStream(stream, processed, bufs);
            alSourceQueueBuffers(src, processed, bufs);
            for(int i = 0; i < 1032; ++i) {
                in[i].r = buf[0][i];
                in[i].i = 0;
                printf("%d ", buf[i]);
            }
        }

        if(state != AL_PLAYING)
            alSourcePlay(src);

    }

    alGetError();
    alcCloseDevice(device);
    return 0;
}
