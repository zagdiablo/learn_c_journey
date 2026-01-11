#include "raylib.h"
#include <stdbool.h>


typedef struct GameState{
    int score;
    Rectangle player;
    Rectangle coin;
    Rectangle enemy;
    bool gameOver;
    int enemy_dx;
    int enemy_dy;
} gamestate_t;


gamestate_t InitGame(const int *window_width, const int *window_height){
    gamestate_t initialState = {
        .score = 0,
        .player = {
            .x = 400,
            .y = 300,
            .width = 50,
            .height = 50,
        },
        .coin = {
            .x = GetRandomValue(50, (*window_width) - 50),
            .y = GetRandomValue(50, (*window_height) - 50),
            .width = 25,
            .height = 25,
        },
        .enemy = {
            .x = 0,
            .y = 0,
            .width = 40,
            .height= 40,
        },
        .gameOver = false,
        .enemy_dx = 10,
        .enemy_dy = 10,
    };

    return initialState;
}


int main(void){
    const int window_width = 800;
    const int window_height = 600;

    InitWindow(window_width, window_height, "Duggerio");
    InitAudioDevice();
    SetTargetFPS(60);

    gamestate_t state = InitGame(&window_width, &window_height);
    Texture2D player_sprite = LoadTexture("assets/player/player_9mmhandgun.png");
    Sound coin_sound = LoadSound("assets/sounds/coin-recieved.mp3");

    while (!WindowShouldClose()) {
        // CPU calculation
        // enemy movement
        if(!state.gameOver){
            state.enemy.x += state.enemy_dx;
            if(state.enemy.x >= (window_width - state.enemy.width) || state.enemy.x <= 0){
                state.enemy_dx *= -1;
            }
            state.enemy.y += state.enemy_dy;
            if(state.enemy.y >= (window_height - state.enemy.height) || state.enemy.y <= 0){
                state.enemy_dy *= -1;
            }

            // player movement
            if(IsKeyDown(KEY_W) && state.player.y >= 0){
                state.player.y -= 10;
            }
            if(IsKeyDown(KEY_S) && state.player.y <= (window_height - state.player.height)){
                state.player.y += 10;
            }
            if(IsKeyDown(KEY_A) && state.player.x >= 0){
                state.player.x -= 10;
            }
            if(IsKeyDown(KEY_D) && state.player.x <= (window_width - state.player.width)){
                state.player.x += 10;
            }

            // collision check
            if(CheckCollisionRecs(state.player, state.coin)){
                PlaySound(coin_sound);
                state.score++;
                state.coin.x = GetRandomValue(50, window_width - 50);
                state.coin.y = GetRandomValue(50, window_height - 50);
            }

            // game over check
            if(CheckCollisionRecs(state.player, state.enemy)){
                state.gameOver = true;
            }

            // GPU Draw
            BeginDrawing();   
                ClearBackground(RAYWHITE);
                // draw score
                DrawText(TextFormat("Score: %d", state.score), 50, 50, 50, GREEN);
                // draw player
                //DrawRectangle(state.player.x, state.player.y, state.player.width, state.player.height, BLACK);
                DrawTexture(player_sprite, state.player.x, state.player.y, WHITE);
                // draw coin
                DrawRectangle(state.coin.x, state.coin.y, state.coin.width, state.coin.height, GOLD);
                // draw enemy
                DrawRectangle(state.enemy.x, state.enemy.y, state.enemy.width, state.enemy.height, RED);
            EndDrawing();    
        }

        if(state.gameOver){
            // restart check
            if(IsKeyDown(KEY_R)){
                state = InitGame(&window_width, &window_height);
            }

            BeginDrawing();
                ClearBackground(BLACK);
                DrawText("SKILL ISSUE", window_width/8, window_height/4, 100, RED);
                DrawText("Press R to restart", window_width/4, window_height/2, 50, RED);
            EndDrawing();
        }
    }

    UnloadTexture(player_sprite);
    UnloadSound(coin_sound);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}