#include "raylib.h"
#include <stdbool.h>
#include "save_io.h"


#define MAX_ENEMIES 10
#define ENEMY_SPEED 10
#define ENEMY_WIDTH 25
#define ENEMY_HEIGHT 25


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
    int player_highscore;
    int next_enemy_spawn_score;
    int enemy_count;
    bool gameOver;
}gamestate_t;


enemy_t CreateEnemy(const int win_w, const int win_h){
    int top_bottom = GetRandomValue(0, 1);
    int initial_x = 0;
    int initial_y = 0;
    if(top_bottom == 0){
        initial_x = 0;
        initial_y = GetRandomValue(0, (win_h - ENEMY_HEIGHT));
        top_bottom = GetRandomValue(0, 1);
    }else{
        initial_x = GetRandomValue(0, (win_w - ENEMY_WIDTH));
        initial_y = 0;
        top_bottom = GetRandomValue(0, 1);
    }
    
    enemy_t enemy = {
        .body = {
            .x = initial_x,
            .y = initial_y,
            .width = ENEMY_WIDTH,
            .height = ENEMY_HEIGHT,
        },
        .dx = ENEMY_SPEED,
        .dy = ENEMY_SPEED,
        .active = false,
    };

    return enemy;
}


gamestate_t InitGame(const int win_w, const int win_h){
    // TODO save new highscore
    // display previous high score
    savefile_t player_data = load_savefile("player.dat");

    gamestate_t gameState = {
        .coin = {
            .x = GetRandomValue(50, win_w - 50),
            .y = GetRandomValue(50, win_h - 50),
            .width = 20,
            .height = 20,
        },
        .enemies = {
            CreateEnemy(win_w, win_h),
            CreateEnemy(win_w, win_h),
            CreateEnemy(win_w, win_h),
            CreateEnemy(win_w, win_h),
            CreateEnemy(win_w, win_h),
            CreateEnemy(win_w, win_h),
            CreateEnemy(win_w, win_h),
            CreateEnemy(win_w, win_h),
            CreateEnemy(win_w, win_h),
            CreateEnemy(win_w, win_h),
        },
        .player = {
            .x = 400,
            .y = 300,
            .width = 50,
            .height = 50,
        },
        .player_speed = 10,
        .player_score = 0,
        .player_highscore = player_data.high_score,
        .next_enemy_spawn_score = 0,
        .enemy_count = 0,
        .gameOver = false,
    };

    return gameState;
}


void updateGame(gamestate_t *state, const int win_w, const int win_h, Sound coin_collected, Sound game_over){
    // active enemy loop
    if(!state->gameOver){
        for(int i=0; i<MAX_ENEMIES; i++){
            if(state->enemies[i].active){
                // enemy movement
                state->enemies[i].body.x += state->enemies[i].dx;
                if(state->enemies[i].body.x >= win_w - state->enemies[i].body.width || state->enemies[i].body.x <= 0){
                    state->enemies[i].dx *= -1;
                }
                state->enemies[i].body.y += state->enemies[i].dy;
                if(state->enemies[i].body.y >= win_h - state->enemies[i].body.height || state->enemies[i].body.y <= 0){
                    state->enemies[i].dy *= -1;
                }

                // check enemy collision
                if(CheckCollisionRecs(state->player, state->enemies[i].body)){
                    PlaySound(game_over);
                    state->gameOver = true;
                }
            }
        }

        // if player score == enemy spawn score the add more enemy
        if(state->player_score == state->next_enemy_spawn_score && state->enemy_count < MAX_ENEMIES){
            state->enemies[state->enemy_count].active = true;
            state->next_enemy_spawn_score += 5;
            state->enemy_count += 1;
        }

        // player movement
        if(IsKeyDown(KEY_W) && state->player.y >= 0){
            state->player.y -= state->player_speed;
        }
        if(IsKeyDown(KEY_S) && state->player.y <= (win_h - state->player.height)){
            state->player.y += state->player_speed;
        }
        if(IsKeyDown(KEY_A) && state->player.x >= 0){
            state->player.x -= state->player_speed;
        }
        if(IsKeyDown(KEY_D) && state->player.x <= (win_w - state->player.width)){
            state->player.x += state->player_speed;
        }

        // check coin collision
        if(CheckCollisionRecs(state->player, state->coin)){
            state->player_score++;
            PlaySound(coin_collected);
            state->coin.x = GetRandomValue(50, win_w - 50);
            state->coin.y = GetRandomValue(50, win_h - 50);
        }
    }

    if(state->gameOver){
        if(state->player_score > state->player_highscore){
            write_savefile("player.dat", state->player_score);
        }
        if(IsKeyPressed(KEY_R)){
            (*state) = InitGame(win_w, win_h);
        }
    }
}


void drawGame(gamestate_t *state, Texture2D player_sprite){
    if(!state->gameOver){
        BeginDrawing();
            ClearBackground(WHITE);

            DrawText(TextFormat("Score: %d", state->player_score), 20, 20, 35, GREEN);
            DrawTexture(player_sprite, state->player.x, state->player.y, WHITE);
            DrawRectangle(state->coin.x, state->coin.y, state->coin.width, state->coin.height, GOLD);
            // loop enemy draw
            for(int i=0; i<MAX_ENEMIES; i++){
                if(state->enemies[i].active){
                    DrawRectangle(state->enemies[i].body.x, state->enemies[i].body.y, state->enemies[i].body.width, state->enemies[i].body.height, RED);
                }
            }
        EndDrawing();
    }

    if(state->gameOver){
        BeginDrawing();
            ClearBackground(BLACK);
            DrawText("SKILL ISSUE", 400, 200, 50, RED);
            DrawText(TextFormat("Final score: %d", state->player_score), 400, 250, 30, RED);
            DrawText(TextFormat("High score: %d", state->player_highscore), 400, 275, 30, RED);
            DrawText("Press R to retry", 400, 300, 30, RED);
        EndDrawing();
    }
}


int main(void){
    const int win_w = 800;
    const int win_h = 600;

    InitWindow(win_w, win_h, "Duggerio");
    InitAudioDevice();
    SetTargetFPS(60);

    gamestate_t currentState = InitGame(win_w, win_h);
    Texture2D player_sprite = LoadTexture("assets/sprites/doge_face_cool_smoll.png");
    Sound coin_collected = LoadSound("assets/sounds/coin-recieved.mp3");
    Sound game_over = LoadSound("assets/sounds/mario_game_over.mp3");

    while (!WindowShouldClose()) {
        updateGame(&currentState, win_w, win_h, coin_collected, game_over);
        drawGame(&currentState, player_sprite);
    }

    UnloadTexture(player_sprite);
    UnloadSound(coin_collected);
    UnloadSound(game_over);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}