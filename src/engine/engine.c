#include <engine/engine.h>

uint32_t ge_version() {
	return ENGINE_VERSION;
}
uint32_t ge_compatibilityVersion() {
	return ENGINE_COMPATIBILITY_VERSION;
}

ge_engine_t engine;

ge_engine_t* createEngine() {
	engine.version = ge_version;
	engine.compatibilityVersion = ge_compatibilityVersion;
	return &engine;
}
