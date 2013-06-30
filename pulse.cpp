#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

#include <pulse/simple.h>
#include <pulse/error.h>

#define BUFSIZE 1024

int main(int argc, char *argv[])
{
    static const pa_sample_spec ss = {
        .format = PA_SAMPLE_S16LE,
        .rate = 44100,
        .channels = 2
    };

    pa_simple *s = NULL;
    int ret = 1;
    int error;

    if (argc > 1)
    {
        int fd;
        if((fd = open(argv[1], O_RDONLY)) < 0)
        {
            //fprintf(stderr, __FILE__": open() failed: %s\n" strerror(errno));
            return 1;
        }
        if(dup2(fd, STDIN_FILENO) < 0)
        {
            //fprintf(stderr, __FILE__": dup2() failed: %s\n" strerror(errno));
            return 1;
        }
        close(fd);
    }

    if(!(s = pa_simple_new(NULL, argv[0], PA_STREAM_PLAYBACK, NULL, "playback", &ss, NULL, NULL, &error)))
    {
        fprintf(stderr, __FILE__": pa_simple_new() failed: %s\n", pa_strerror(error));
        return 1;
    }

    for(;;) {
        uint8_t buf[BUFSIZE];
        ssize_t r;

#if 0
        pa_usec_t latency;
        if ((latency = pa_simple_get_latency(s, &error)) == (pa_usec_t) -1) 
        {
            fprintf(stderr, __FILE__": pa_simple_get_latency() failed: %s\n", pa_strerror(error));
            return 1;
        }
#endif
        if ((r = read(STDIN_FILENO, buf, sizeof(buf))) <= 0)
        {
            if (r == 0)
                break;
            fprintf(stderr, __FILE__": read() failed: %s\n", strerror(errno));
            return 1;
        }
        for(int i = 0; i < BUFSIZE; i++)
        {
            fprintf(stdout, "%d\n", buf[i]);
        }
        if (pa_simple_write(s, buf, (size_t) r, &error) < 0)
        {
            fprintf(stderr, __FILE__": pa_simple_write() failed: %s\n", pa_strerror(error));
            return 1;
        }
    }

    if (pa_simple_drain(s, &error) < 0)
    {
        fprintf(stderr, __FILE__": pa_simple_drain() failed: %s\n", pa_strerror(error));
        return 1;
    }

    ret = 0;

    if (s)
        pa_simple_free(s);
    return ret;
}
