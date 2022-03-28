#include <framework/audio.h>
#define STB_VORBIS_HEADER_ONLY
#include <stb_vorbis.c>

audioSource_t audioSources[MAX_AUDIO_SOURCES];
bool soundsUpdated = false;

streamedSound_t openStreamedSound(const char* filepath) {
	streamedSound_t s;

	int error;
	stb_vorbis* vorbis = stb_vorbis_open_filename(filepath, &error, NULL);
	if (vorbis) {
		s.decoder = vorbis;
		s.pos = 0;
		stb_vorbis_info info = stb_vorbis_get_info(vorbis);
		s.sizeInSamples = stb_vorbis_stream_length_in_samples(vorbis);
	}

	return s;
}

void addAudioSource(audioSource_t source) {
	source.active = true;
	for (uint32_t i = 0; i < MAX_AUDIO_SOURCES; i++) {
		if (!audioSources[i].active) {
			audioSources[i] = source;
			return;
		}
	}
	soundsUpdated = true;
}

uint32_t streamedAudioGetSamples(void *userData, float *outf, uint32_t samples);

void playStreamedSound(streamedSound_t* sound) {
	audioSource_t s;
	s.userData = sound;
	s.getSamples = streamedAudioGetSamples;
	s.type = SOUND_TYPE_STREAMED;
	addAudioSource(s);
	soundsUpdated = true;
}

void updateSounds(void) {
	if (soundsUpdated) {
		updateAudio(audioSources);
		soundsUpdated = false;
	}
}

uint32_t streamedAudioGetSamples(void* userData, float* outf, uint32_t samples) {
	streamedSound_t* sound = (streamedSound_t*)userData;
	stb_vorbis *vorbis = (stb_vorbis*)sound->decoder;
	int32_t read_out = stb_vorbis_get_samples_float_interleaved(vorbis, CHANNELS_AMOUNT, outf, samples * CHANNELS_AMOUNT);
	if (read_out == -1) return 0;
	else {
		sound->pos += read_out;
		return (uint32_t)read_out;
	}
}
