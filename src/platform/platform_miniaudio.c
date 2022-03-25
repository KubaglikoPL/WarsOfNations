#include <platform/platform.h>
#ifdef PLATFORM_MINIAUDIO_IMPL
#define MINIAUDIO_IMPLEMENTATION
#define MA_NO_ENCODING
#define MA_NO_WAV
#define MA_NO_FLAC
#define MA_NO_MP3
#define MA_NO_GENERATION
#include "miniaudio.h"
#include <malloc.h>

audioSource_t sources[MAX_AUDIO_SOURCES];
uint32_t num_sources;

audioSource_t sources_used[MAX_AUDIO_SOURCES];
uint32_t num_sources_used;

ma_mutex mutex;
bool audioUpdated = false;

float* mixBuffer = NULL;
float* tempBuffer = NULL;
uint32_t mixBufferSize = 0;
uint32_t tempBufferSize = 0;

void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount) {
    void* userData = pDevice->pUserData;
    if (audioUpdated) {
        for (uint32_t i = 0; i < num_sources; i++) {
            sources_used[i] = sources[i];
        }
        num_sources_used = num_sources;
        audioUpdated = false;
    }
    //Mixing
    uint32_t countInBytes = CHANNELS_AMOUNT * frameCount * sizeof(float);
    if (mixBufferSize < countInBytes) {
        mixBuffer = realloc(mixBuffer, countInBytes);
        mixBufferSize = countInBytes;
    }
    if (tempBufferSize < countInBytes) {
        tempBuffer = realloc(tempBuffer, countInBytes);
        tempBufferSize = countInBytes;
    }
    memset(mixBuffer, 0, countInBytes);

    bool firstSource = true;
    for (uint32_t i = 0; i < num_sources_used; i++) {
        if (!firstSource) {
            uint32_t samplesGet = sources_used[i].getSamples(sources_used[i].userData, tempBuffer, frameCount);
            ma_mix_pcm_frames_f32(mixBuffer, tempBuffer, samplesGet, CHANNELS_AMOUNT, 1.0f);
        }
        else sources_used[i].getSamples(sources_used[i].userData, mixBuffer, frameCount);
        firstSource = false;
    }
    memcpy(pOutput, mixBuffer, countInBytes);
}

ma_device device;

bool initAudio() {
	ma_device_config deviceConfig;
    deviceConfig = ma_device_config_init(ma_device_type_playback);
    deviceConfig.playback.format = ma_format_f32;
    deviceConfig.playback.channels = 2;
    deviceConfig.sampleRate = 44100;
    deviceConfig.dataCallback = data_callback;
    deviceConfig.pUserData = NULL;
    if (ma_device_init(NULL, &deviceConfig, &device) != MA_SUCCESS) return false;
    if (ma_device_start(&device) != MA_SUCCESS) return false;
    
    ma_mutex_init(&mutex);
    return true;
}

void updateAudio(audioSource_t* in_sources) {
    ma_mutex_lock(&mutex);
    uint32_t i2 = 0;
    for (uint32_t i = 0; i < MAX_AUDIO_SOURCES; i++) {
        if (in_sources[i].active) {
            sources[i2] = in_sources[i];
            i2++;
        }
    }
    num_sources = i2;
    audioUpdated = true;
    ma_mutex_unlock(&mutex);
}
#endif
