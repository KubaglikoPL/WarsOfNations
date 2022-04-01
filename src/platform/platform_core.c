#include <platform/platform.h>

const char* lastError[MAX_ERROR_LENGTH + 1] = {0};

const char* getLastError(void) {
	return lastError;
}

void setLastError(const char* e) {
	uint32_t el = strlen(e);
	if (el) {
		memcpy(lastError, e, el);
		lastError[el] = 0;
	}
}

bool thereIsLastError(void) {
	return (lastError[0] != 0);
}
