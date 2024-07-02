#include "tween_sequence.h"

#include "mfn_dynamic_array.h"

#include "raylib.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct box
{
    float x;
    float y;
    float width;
    float height;
    Color color;
};

struct boxes
{
    struct box* items;
    size_t count;
    size_t capacity;
};

struct boxes boxes = { 0 };

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
    MFN_ARRAY_INIT(struct box, &boxes);

    struct box box_1 =
    {
        .x = 64.0f,
        .y = 64.0f,
        .width = 32.0f,
        .height = 16.0f,
        .color = BLUE
    };
    struct box box_2 =
    {
        .x = 32.0f,
        .y = 32.0f,
        .width = 16.0f,
        .height = 8.0f,
        .color = RED
    };
    struct box box_3 =
    {
        .x = 128.0f,
        .y = 128.0f,
        .width = 72.0f,
        .height = 56.0f,
        .color = GREEN
    };

    MFN_ARRAY_APPEND(struct box, &boxes, box_1);
    // cppcheck-suppress C6386
    MFN_ARRAY_APPEND(struct box, &boxes, box_2);
    MFN_ARRAY_PREPEND(struct box, &boxes, box_3);
}
void game_free(void)
{
    MFN_ARRAY_FREE(struct box, &boxes);
}
void game_tick(float delta)
{

}
void game_draw(void)
{
    BeginDrawing();
    ClearBackground(WHITE);

    for (size_t i = 0; i < boxes.count; ++i)
    {
        struct box* box = &boxes.items[i];
        DrawRectangle((int)box->x, (int)box->y, (int)box->width, (int)box->height, box->color);
    }

    EndDrawing();
}
