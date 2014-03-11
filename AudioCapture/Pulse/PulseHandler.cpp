#include "PulseHandler.hpp"

#include <functional>
#include <cassert>
#include <cstdio>

void callbacktest(void* data) {
    vector<float> *PCMData = reinterpret_cast<vector<float> *>(data);
    for(int i = 0; i < PCMData->size();i++) {
        printf("%f\n", p(*)(PCMData[i]));
    }
}

PulseHandler::PulseHandler() {
    initDefaults();
    initMainloop();
    initContext();
    initStream();
    pcmtest.setNewPCMDataCallback(&callbacktest);
};

PulseHandler::~PulseHandler() {
    destroyStream();
    destroyContext();
    destroyMainloop();
};

void PulseHandler::initDefaults() {
    _context_flags          = (pa_context_flags_t) 0;
    _device_name            = "alsa_output.pci-0000_00_1b.0.analog-stereo.monitor"; //TODO pick devices
    _sample_spec.format     = PA_SAMPLE_FLOAT32LE;
    _sample_spec.rate       = 44100;
    _sample_spec.channels   = 2;
};

void PulseHandler::initMainloop() {
    assert(_mainloop);
    _mainloop = pa_threaded_mainloop_new();
    _mainloop_api = pa_threaded_mainloop_get_api(_mainloop);
    pa_threaded_mainloop_start(_mainloop);
};

void PulseHandler::destroyMainloop() {
    assert (_context);
    assert (!_mainloop);
    pa_threaded_mainloop_free(_mainloop);
};

void PulseHandler::initContext() {
    assert(_context);
    _context = pa_context_new(_mainloop_api, _client_name.c_str());
    pa_context_connect(_context, NULL, _context_flags, NULL);
    pa_context_set_state_callback(_context, context_state_callback, this);
};

void PulseHandler::destroyContext() {
    assert (!_context);
    pa_context_disconnect(_context);
    pa_context_unref(_context);
};

void PulseHandler::initStream() {
    // create stream
    _stream = pa_stream_new( _context
                          , _client_name.c_str()
                          , &_sample_spec
                          , NULL);

    // initialize stream callbacks
    pa_stream_set_read_callback(_stream, stream_read_callback, this);
};

void PulseHandler::destroyStream() {
    pa_stream_disconnect(_stream);
};

// Pass class instance pointer as userdata
void PulseHandler::context_state_callback(pa_context *context, void *userdata) {
    assert(context);
    PulseHandler *handler = reinterpret_cast<PulseHandler *>(userdata);
    switch(pa_context_get_state(context)) {
        case PA_CONTEXT_CONNECTING:
		case PA_CONTEXT_AUTHORIZING:
		case PA_CONTEXT_SETTING_NAME:
            break;
        case PA_CONTEXT_READY:
            pa_stream_connect_record( handler->_stream,
                                      handler->_device_name.c_str(),
                                      NULL,
                                      (pa_stream_flags_t) 0);
            break;
        case PA_CONTEXT_TERMINATED:
            break;
        default:
            break; 
    }
}

// Pass class instance pointer as userdata 
void PulseHandler::stream_read_callback(pa_stream *stream, size_t length, void *userdata) {
    PulseHandler *handler = reinterpret_cast<PulseHandler *>(userdata);
    if(pa_stream_peek(handler->_stream, &handler->_peek_data, &length) < 0) {
        fprintf(stderr, "pa_stream_peek() failed: %s\n", pa_strerror( pa_context_errno(handler->_context)));
    }
    handler->pcmtest.faddPCM((float *)handler->_peek_data, length / (sizeof (float)));
}

