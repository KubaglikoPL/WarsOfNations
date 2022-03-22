#include "ui_api.h"

uiVec2_t uiVec2(float x, float y) {
	uiVec2_t v;
	v.x = x;
	v.y = y;
	return v;
}

uiVec4_t uiVec4(float r, float g, float b, float a) {
	uiVec4_t v;
	v.r = r;
	v.g = g;
	v.b = b;
	v.a = a;
	return v;
}

uiRect2_t uiRect2(uiVec2_t pos, uiVec2_t size) {
	uiRect2_t r;
	r.pos = pos;
	r.size = size;
	return r;
}

uiApiContext uiContextInit(uiVec2_t displaySize, uiVec2_t uiSize) {
	uiApiContext ctx;
	uiSetCoordinateRelative(&ctx, true);
	uiSetPercentCoordinates(&ctx, true);
	uiSetStyle(&ctx, uiGetDefaultStyle(&ctx));
	uiSetTextColor(&ctx, uiVec4(1, 1, 1, 1));
	return ctx;
}

void uiNewFrame(uiApiContext* ctx) {

}

void uiSetCoordinateRelative(uiApiContext* ctx, bool enabled) {
	ctx->relativeCoordinates = enabled;
}

void uiSetPercentCoordinates(uiApiContext* ctx, bool enabled) {
	ctx->percentCoordinates = enabled;
}

uiStyle uiGetDefaultStyle(uiApiContext* ctx) {

}
void uiSetStyle(uiApiContext* ctx, uiStyle style) {
	ctx->style = style;
}
void uiSetTextColor(uiApiContext* ctx, uiVec4_t color) {
	ctx->textColor = color;
}

uint32_t uiWindow(uiApiContext* ctx, uiVec2_t pos, uiVec2_t size) {

}
void uiEndWindow(uiApiContext* ctx) {
	ctx->windowPos = uiVec2(0, 0);
	ctx->windowSize = uiVec2(0, 0);
	ctx->insideWindow = false;
}

uint32_t uiText(uiApiContext* ctx, uiVec2_t pos, uint32_t textSize, uiTextPosition position, const char* text) {
	return uiTextf(ctx, pos, textSize, position, "%s", text);
}

uint32_t uiTextf(uiApiContext* ctx, uiVec2_t pos, uint32_t textSize, uiTextPosition position, const char* fmt, ...) {

}

uiRect2_t widgetPosAndSize(uint32_t ID) {

}
bool widgetHovered(uint32_t ID) {
	uiRect2_t posAndSize = widgetPosAndSize(ID);

}
bool widgetClicked(uint32_t ID) {
	return widgetHovered(ID);
}

uint32_t uiAddWidget(uiApiContext* ctx, uiVec2_t pos, uiVec2_t size) {

}
uiVec4_t widgetPosition(uiApiContext* ctx, uiVec2_t pos, uiVec2_t size) {

}
uiVec2_t uiGetCoords(uiApiContext* ctx, uiVec2_t pos) {

}
