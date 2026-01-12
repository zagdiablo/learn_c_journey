#include "raylib.h"
#include <stdbool.h>


#define MAX_ENEMIES 10
#define ENEMY_SPEED 10


typedef struct Enemy{
    Rectangle body;
    int speed;
    int dx;
    int dy;
    bool active;
} enemy_t;



typedef struct GameState{
    Rectangle coin;
    enemy_t enemies[MAX_ENEMIES];
    Rectangle player;
    int player_speed;
    int player_score;
    int next_enemy_spawn_score;
    int enemy_count;
    bool gameOver;
}gamestate_t;


enemy_t CreateEnemy(){
    enemy_t enemy = {
        .body = {
            .x = 0,
            .y = 0,
            .width = 40,
            .height = 40,
        },
        .dx = ENEMY_SPEED,
        .dy = ENEMY_SPEED,
        .active = false,
    };

    return enemy;
}


gamestate_t InitGame(const int *win_w, const int *win_h){
    gamestate_t gameState = {
        .coin = {
            .x = GetRandomValue(50, (*win_w) - 50),
            .y = GetRandomValue(50, (*win_h) - 50),
            .width = 20,
            .height = 20,
        },
        .enemies = {
            CreateEnemy(),
            CreateEnemy(),
            CreateEnemy(),
            CreateEnemy(),
            CreateEnemy(),
            CreateEnemy(),
            CreateEnemy(),
            CreateEnemy(),
            CreateEnemy(),
            CreateEnemy(),
        },
        .player = {
            .x = 400,
            .y = 300,
            .width = 50,
            .height = 50,
        },
        .player_speed = 10,
        .player_score = 0,
        .next_enemy_spawn_score = 0,
        .enemy_count = 0,
        .gameOver = false,
    };

    return gameState;
}


int main(void){
    const int win_w = 800;
    const int win_h = 600;

    InitWindow(win_w, win_h, "Duggerio");
    InitAudioDevice();
    SetTargetFPS(60);

    gamestate_t currentState = InitGame(&win_w, &win_h);
    Texture2D player_sprite = LoadTexture("assets/sprites/doge_face_cool_smoll.png");
    Sound coin_collected = LoadSound("assets/sounds/coin-recieved.mp3");
    Sound game_over = LoadSound("assets/sounds/mario_game_over.mp3");

    while (!WindowShouldClose()) {
        if(!currentState.gameOver){
            // active enemy loop
            for(int i=0; i<MAX_ENEMIES; i++){
                if(currentState.enemies[i].active){
                    // enemy movement
                    currentState.enemies[i].body.x += currentState.enemies[i].dx;
                    if(currentState.enemies[i].body.x >= win_w - currentState.enemies[i].body.width || currentState.enemies[i].body.x <= 0){
                        currentState.enemies[i].dx *= -1;
                    }
                    currentState.enemies[i].body.y += currentState.enemies[i].dy;
                    if(currentState.enemies[i].body.y >= win_h - currentState.enemies[i].body.height || currentState.enemies[i].body.y <= 0){
                        currentState.enemies[i].dy *= -1;
                    }

                    // check enemy collision
                    if(CheckCollisionRecs(currentState.player, currentState.enemies[i].body)){
                        PlaySound(game_over);
                        currentState.gameOver = true;
                    }
                }

                // if player score == enemy spawn score the add more enemy
                if(currentState.player_score == currentState.next_enemy_spawn_score && currentState.enemy_count < MAX_ENEMIES){
                    currentState.enemies[currentState.enemy_count].active = true;
                    currentState.next_enemy_spawn_score += 5;
                    currentState.enemy_count += 1;
                }
            }


            // player movement
            if(IsKeyDown(KEY_W) && currentState.player.y >= 0){
                currentState.player.y -= currentState.player_speed;
            }
            if(IsKeyDown(KEY_S) && currentState.player.y <= (win_h - currentState.player.height)){
                currentState.player.y += currentState.player_speed;
            }
            if(IsKeyDown(KEY_A) && currentState.player.x >= 0){
                currentState.player.x -= currentState.player_speed;
            }
            if(IsKeyDown(KEY_D) && currentState.player.x <= (win_w - currentState.player.width)){
                currentState.player.x += currentState.player_speed;
            }

            // check coin collision
            if(CheckCollisionRecs(currentState.player, currentState.coin)){
                currentState.player_score++;
                PlaySound(coin_collected);
                currentState.coin.x = GetRandomValue(50, win_w - 50);
                currentState.coin.y = GetRandomValue(50, win_h - 50);
            }

            BeginDrawing();
                ClearBackground(WHITE);

                DrawText(TextFormat("Score: %d", currentState.player_score), 20, 20, 35, GREEN);
                // DrawRectangle(currentState.player.x, currentState.player.y, currentState.player.width, currentState.player.height, BLACK);
                DrawTexture(player_sprite, currentState.player.x, currentState.player.y, WHITE);
                DrawRectangle(currentState.coin.x, currentState.coin.y, currentState.coin.width, currentState.coin.height, GOLD);
                // loop enemy draw
                for(int i=0; i<MAX_ENEMIES; i++){
                    if(currentState.enemies[i].active){
                        DrawRectangle(currentState.enemies[i].body.x, currentState.enemies[i].body.y, currentState.enemies[i].body.width, currentState.enemies[i].body.height, RED);
                    }
                }
            EndDrawing();
        }

        if(currentState.gameOver){
            if(IsKeyPressed(KEY_R)){
                currentState = InitGame(&win_w, &win_h);
            }

            BeginDrawing();
                ClearBackground(BLACK);
                DrawText("SKILL ISSUE", 400, 200, 50, RED);
                DrawText(TextFormat("Final score: %d", currentState.player_score), 400, 250, 30, RED);
                DrawText("Press R to retry", 400, 300, 30, RED);
            EndDrawing();
        }
    }

    UnloadTexture(player_sprite);
    UnloadSound(coin_collected);
    UnloadSound(game_over);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}