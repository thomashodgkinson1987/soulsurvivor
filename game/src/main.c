#include "button.h"

#include "mfn_dynamic_array.h"

#include "raylib.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct buttons
{
    struct button* items;
    size_t count;
    size_t capacity;
};

struct buttons buttons = { 0 };

bool is_pressed = false;
bool was_pressed = false;

void game_init(void);
void game_free(void);
void game_tick(float delta);
void game_draw(void);

void draw_button(struct button* button);

void on_pressed(struct button* button);
void on_released(struct button* button);

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
    MFN_ARRAY_INIT(struct button, &buttons);

    MFN_ARRAY_APPEND(struct button, &buttons, button_new(8, 8, 32, 32, 255, 0, 0, 255));
    MFN_ARRAY_APPEND(struct button, &buttons, button_new(48, 8, 32, 32, 0, 255, 0, 255));
    MFN_ARRAY_APPEND(struct button, &buttons, button_new(88, 8, 32, 32, 0, 0, 255, 255));

    for (size_t i = 0; i < buttons.count; ++i)
    {
        struct button* button = &buttons.items[i];
        button->on_draw = draw_button;
        button_register_signal_on_pressed(button, on_pressed);
        button_register_signal_on_released(button, on_released);
    }
}
void game_free(void)
{
    MFN_ARRAY_FREE(&buttons);
}
void game_tick(float delta)
{
    Vector2 mouse_pos = GetMousePosition();
    int mouse_x = (int)mouse_pos.x;
    int mouse_y = (int)mouse_pos.y;

    was_pressed = is_pressed;
    is_pressed = IsMouseButtonDown(MOUSE_BUTTON_LEFT);

    for (size_t i = 0; i < buttons.count; ++i)
    {
        struct button* button = &buttons.items[i];
        button_tick(button, mouse_x, mouse_y, is_pressed, was_pressed);
    }
}
void game_draw(void)
{
    BeginDrawing();
    ClearBackground(WHITE);

    for (size_t i = 0; i < buttons.count; ++i)
    {
        struct button* button = &buttons.items[i];
        button_draw(button);
    }

    EndDrawing();
}

void draw_button(struct button* button)
{
    int x = button->x;
    int y = button->y;
    int width = button->width;
    int height = button->height;
    unsigned char color_r = button->color[0];
    unsigned char color_g = button->color[1];
    unsigned char color_b = button->color[2];
    unsigned char color_a = button->color[3];
    Color color = { color_r, color_g, color_b, color_a };
    DrawRectangle(x, y, width, height, color);
}

void on_pressed(struct button* button)
{
    printf("on_pressed: %hhu %hhu %hhu %hhu\n", button->color[0], button->color[1], button->color[2], button->color[3]);
}
void on_released(struct button* button)
{
    printf("on_released: %hhu %hhu %hhu %hhu\n", button->color[0], button->color[1], button->color[2], button->color[3]);
}
