#pragma once

#include <platform/platform.h>

#define SOUND_TYPE_STREAMED 1

typedef struct streamedSound {
	void* decoder;
	uint64_t sizeInSamples;
	uint64_t pos;
	audioSource_t internalSource;
} streamedSound_t;

streamedSound_t openStreamedSound(const char *filepath);

void playStreamedSound(streamedSound_t* sound);

void updateSounds(void);
