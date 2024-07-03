#include "mfn_dynamic_array.h"

#include "raylib.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void game_init(void);
void game_free(void);
void game_tick(float delta);
void game_draw(void);

int main(void)
{
    InitWindow(640, 360, "soulsurvivor");
    SetTargetFPS(60);

    game_init();

    while (!WindowShouldClose())
    {
        float delta = GetFrameTime();
        game_tick(delta);
        game_draw();
    }

    game_free();

    CloseWindow();

    return 0;
}

void game_init(void)
{

}
void game_free(void)
{

}
void game_tick(float delta)
{

}
void game_draw(void)
{
    BeginDrawing();
    ClearBackground(WHITE);



    EndDrawing();
}
