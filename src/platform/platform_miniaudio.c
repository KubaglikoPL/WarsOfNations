#include <platform/platform.h>
#ifdef PLATFORM_MINIAUDIO_IMPL
#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount) {

}

ma_device device;

bool initAudio(void) {
	ma_device_config deviceConfig;
    deviceConfig = ma_device_config_init(ma_device_type_playback);
    deviceConfig.playback.format = ma_format_f32;
    deviceConfig.playback.channels = 2;
    deviceConfig.sampleRate = 44100;
    deviceConfig.dataCallback = data_callback;
    deviceConfig.pUserData = NULL;
    if (ma_device_init(NULL, &deviceConfig, &device) != MA_SUCCESS) return false;
    if (ma_device_start(&device) != MA_SUCCESS) return false;
    
    return true;
}
#endif
