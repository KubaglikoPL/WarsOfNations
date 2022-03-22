#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <framework/renderer.h>

typedef struct {
	float x, y;
} uiVec2_t;

typedef struct {
	float r, g, b, a;
} uiVec4_t;

typedef struct {
	uiVec2_t pos;
	uiVec2_t size;
} uiRect2_t;

uiVec2_t uiVec2(float x, float y);
uiVec4_t uiVec4(float r, float g, float b, float a);
uiRect2_t uiRect2(uiVec2_t pos, uiVec2_t size);

typedef struct {
	uiVec4_t windowColor;
	uiVec4_t windowBorderColor;
	float windowBorderSize;
	bool windowBorder;
} uiStyle;

typedef enum {
	CENTERED,
	LEFT,
	RIGHT
} uiTextPosition;

typedef struct {
	uint32_t ID;
	uiRect2_t sizeAndPos;
} uiWidget_t;

typedef struct {
	//Display Size
	uiVec2_t displaySize;
	uiVec2_t uiSize;
	//Coordinate Configuration
	bool relativeCoordinates;
	bool percentCoordinates;
	//Other
	uiStyle style;
	uiVec4_t textColor;
	//Current Window
	bool insideWindow;
	uiVec2_t windowPos;
	uiVec2_t windowSize;
	//Widget Data
	uint32_t nextWidgetID;
	uint32_t widgetCapacity;
	uiWidget_t* widgetData;
	//Render Data
	uint32_t capacity_verticies;
	uint32_t capacity_indices;
	uint32_t num_verticies;
	uint32_t num_indices;
	vertex* verticies;
	uint32_t* indices;
} uiApiContext;

uiApiContext uiContextInit(uiVec2_t displaySize, uiVec2_t uiSize);
void uiNewFrame(uiApiContext* ctx);

//Coordinate Stuff
void uiSetCoordinateRelative(uiApiContext* ctx, bool enabled);
void uiSetPercentCoordinates(uiApiContext* ctx, bool enabled);
//Style
uiStyle uiGetDefaultStyle(uiApiContext* ctx);
void uiSetStyle(uiApiContext* ctx, uiStyle style);
void uiSetTextColor(uiApiContext* ctx, uiVec4_t color);

//Widgets
uint32_t uiWindow(uiApiContext* ctx, uiVec2_t pos, uiVec2_t size);
void uiEndWindow(uiApiContext* ctx);

uint32_t uiText(uiApiContext* ctx, uiVec2_t pos, uint32_t textSize, uiTextPosition position, const char* text);

uint32_t uiTextf(uiApiContext* ctx, uiVec2_t pos, uint32_t textSize, uiTextPosition position, const char* fmt, ...);

uiRect2_t widgetPosAndSize(uint32_t ID);
bool widgetHovered(uint32_t ID);
bool widgetClicked(uint32_t ID);

//Internal Stuff
uint32_t uiAddWidget(uiApiContext* ctx, uiVec2_t pos, uiVec2_t size);
uiVec2_t uiGetCoords(uiApiContext* ctx, uiVec2_t pos);
