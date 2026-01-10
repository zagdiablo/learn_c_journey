#include "raylib.h"


typedef struct Box {
    float width;
    float height;
    float x;
    float y;
    float dx;
    float dy;
    Color color;
} box_t;


int main(void){
    const int window_width = 800;
    const int window_height = 600;
    InitWindow(window_width, window_height, "Dugerio");
    SetTargetFPS(60);

    // box object
    box_t box_1 = {
        .width = 50,
        .height = 50,
        .x = window_width / 2.0f,
        .y = window_height / 2.0f,
        .dx = 5.0f,
        .dy = 5.0f,
        .color = MAROON,
    };

    while (!WindowShouldClose()){
        box_1.x += box_1.dx;
        box_1.y += box_1.dy;

        if(box_1.x >= (window_width - box_1.width) || box_1.x <= 0){
            box_1.dx *= -1;
        }

        if(box_1.y >= (window_height - box_1.height) || box_1.y <= 0){
            box_1.dy *= -1;
        }

        if(IsKeyDown(KEY_SPACE)){
            DrawText("SPACE IS PRESSED", (window_width / 2), (window_height / 2), 20, RED);
        }

        // draw logic
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawRectangle(
                (int)box_1.x,
                (int)box_1.y,
                (int)box_1.width,
                (int)box_1.height,
                box_1.color
            );

            DrawText("Watch it bounce!", 10, 10, 20, LIGHTGRAY);
        EndDrawing();
    }
    

    CloseWindow();
    return 0;
}