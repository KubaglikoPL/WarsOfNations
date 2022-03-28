#pragma once

#include <stdint.h>

#define Socket uint32_t
#define SOCKET_IS_VALID(s) ((s) != (uint32_t)(~0))
