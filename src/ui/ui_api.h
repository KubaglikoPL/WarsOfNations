#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <framework/renderer.h>

#define CHAR_WIDTH 8
#define CHAR_HEIGHT 12

#define CHAR_IS_ASCII(c) (c < 128)
#define CHAR_PRINTABLE(c) (c > 31)
#define ASCII_TO_CHAR_ID(c) (c - 32)

void setFontTexture(Texture texture, uint32_t textureWidth, uint32_t textureHeight);
float textf(float x, float y, float ySize, const char* fmt, ...);
