// clay_renderer_raylib.h
#ifndef CLAY_RENDERER_RAYLIB_H
#define CLAY_RENDERER_RAYLIB_H

#include "clay.h"
#include "raylib.h"

void Clay_Raylib_Initialize(int width, int height, const char *title, unsigned int flags);
void Clay_Raylib_Render(Clay_RenderCommandArray renderCommands, Font* fonts);

Ray GetScreenToWorldPointWithZDistance(Vector2 position, Camera camera, int screenWidth, int screenHeight, float zDistance);

#endif // CLAY_RENDERER_RAYLIB_H