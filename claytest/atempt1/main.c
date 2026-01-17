#define CLAY_IMPLEMENTATION
#include "clay.h"
#include <stdint.h>
#include "clay_renderer_raylib.h"


int main(void){
    // initiate raylib as renderer for clay
    Clay_Raylib_Initialize(800, 600, "Personal Finance Tracker V1", FLAG_WINDOW_RESIZABLE);

    // get clay minimum memory required
    uint64_t clayRequiredMemory = Clay_MinMemorySize();

    // create an arena for clay to move around
    Clay_Arena clayMemory = (Clay_Arena) {
        .memory = malloc(clayRequiredMemory),
        .capacity = clayRequiredMemory
    };

    // initialize clay
    Clay_Initialize(clayMemory, (Clay_Dimensions){
        .width = GetScreenWidth(),
        .height = GetScreenHeight()
    }, (Clay_ErrorHandler){0});

    while (!WindowShouldClose()) {
        // run shit per frame
        Clay_SetLayoutDimensions((Clay_Dimensions){
            .width = GetScreenWidth(),
            .height = GetScreenHeight()
        });

        Clay_BeginLayout();
            // Build GUI hirarchy here
            CLAY( // main/parent element
                CLAY_ID("rectangle"), {
                    .layout = {
                        .sizing = {
                            .width = CLAY_SIZING_GROW(),
                            .height = CLAY_SIZING_GROW(),
                        },
                        .padding = CLAY_PADDING_ALL(16),
                    },
                    .backgroundColor = {43, 41, 51, 255},
                }
            ){ 
                // child elements

            };
        Clay_RenderCommandArray renderCommands = Clay_EndLayout();

        // draw shit per frame
        BeginDrawing();
            ClearBackground(BLACK);
            Clay_Raylib_Render(renderCommands,(Font *) FONT_DEFAULT);
        EndDrawing();
    };

    return 0;
}