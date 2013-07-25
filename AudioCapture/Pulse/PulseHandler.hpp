#ifndef _PULSEHANDLER_HPP
#define _PULSEHANDLER_HPP

#include "PCM.hpp"

#include <pulse/pulseaudio.h>
#include <string>

using std::string;

class PulseHandler {
  public:
      PulseHandler();
      ~PulseHandler();
      PCM pcmtest;

  private:
  // Intializer helper functions
    void initMainloop(); 
    void initContext(); 
    void initStream();
    void initDefaults();

  // Destruction helper functions
    void destroyMainloop();
    void destroyContext();
    void destroyStream();

  // Callbacks
    // Context Callbacks
    static void context_state_callback(pa_context *context, void *userdata);

    // Stream Callbacks
    static void stream_read_callback(pa_stream *stream, size_t length, void *userdata);
    
    // Variables & stuff
    pa_context              *_context;
    pa_stream               *_stream;
    pa_threaded_mainloop    *_mainloop;
    pa_mainloop_api         *_mainloop_api;

    pa_sample_spec           _sample_spec;
    pa_context_flags_t       _context_flags;

    string                   _client_name;
    string                   _device_name;

    const void              *_peek_data;
    size_t                   _peek_data_length;
};

#endif //_PULSEHANDLER_HPP
