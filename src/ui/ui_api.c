#include "ui_api.h"
#include <stb_sprintf.h>

Texture fontTexture;
uint32_t textureCharWidth;
uint32_t textureWidth;
uint32_t textureHeight;
float tx_charSizeX;
float tx_charSizeY;

void setFontTexture(Texture texture, uint32_t textureWidth, uint32_t textureHeight) {
	fontTexture = texture;
	textureCharWidth = textureWidth / CHAR_WIDTH;
	textureWidth = textureWidth;
	textureHeight = textureHeight;
	tx_charSizeX = CHAR_WIDTH / (float)textureWidth;
	tx_charSizeY = CHAR_WIDTH / (float)textureHeight;
}

float textf(float x, float y, float ySize, const char* fmt, ...) {
	va_list va;
	va_start(va, fmt);
	uint32_t textf_size = stbsp_vsnprintf(NULL, 0, fmt, va);
	char* textf_buf = alloca(textf_size + 1);
	stbsp_vsnprintf(textf_buf, textf_size, fmt, va);
	va_end(va);

	vertex* verticies = alloca(textf_size * sizeof(vertex) * 4);
	uint32_t* indicies = alloca(textf_size * sizeof(uint32_t) * 6);
	uint32_t i2 = 0;
	float char_x = x;
	//float 

	for (uint32_t i = 0; i < textf_size; i++) {
		char c = textf_buf[i];
		uint32_t charID = UINT32_MAX;
		bool extendedChar = false;
		if (CHAR_IS_ASCII(c)) {
			if (CHAR_PRINTABLE(c)) {
				charID = ASCII_TO_CHAR_ID(c);
			}
		}
		else {
			//TODO
		}

		float tx_x = 0.0f;
		float tx_y = 0.0f;
		if (charID != UINT32_MAX) {
			if (!extendedChar) {
				uint32_t x = (charID % textureCharWidth);
				uint32_t y = (charID / textureCharWidth);
				tx_x = (x * CHAR_WIDTH) / (float)textureWidth;
				tx_y = (y * CHAR_HEIGHT) / (float)textureHeight;

				verticies[i2 + 0].x = 

				i2++;
			}
		}
	}
}
