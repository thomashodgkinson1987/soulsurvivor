#include "actor.h"
#include "animated_sprite.h"

#include "mfn_dynamic_array.h"

#include "raylib.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct animated_sprites
{
    struct animated_sprite* items;
    size_t count;
    size_t capacity;
};

struct actors
{
    struct actor* items;
    size_t count;
    size_t capacity;
};

struct animated_sprites animated_sprites = { 0 };
struct actors actors = { 0 };

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
    actor_vtable_init();

    MFN_ARRAY_INIT(struct animated_sprite, &animated_sprites);
    MFN_ARRAY_APPEND(struct animated_sprite, &animated_sprites, animated_sprite_new(0, 0));

    MFN_ARRAY_INIT(struct actor, &actors);
    MFN_ARRAY_APPEND(struct actor, &actors, actor_new(0.0f, 0.0f, 64.0f, 1, 500.0f, animated_sprites.items[0]));
}
void game_free(void)
{
    for (size_t i = 0; i < actors.count; ++i)
    {
        struct actor* actor = &actors.items[i];
        actor_free(actor);
    }

    MFN_ARRAY_FREE(struct actor, &actors);

    actor_vtable_free();

    for (size_t i = 0; i < animated_sprites.count; ++i)
    {
        struct animated_sprite* animated_sprite = &animated_sprites.items[i];
        animated_sprite_free(animated_sprite);
    }

    MFN_ARRAY_FREE(struct animated_sprite, &animated_sprites);
}
void game_tick(float delta)
{
    for (size_t i = 0; i < actors.count; ++i)
    {
        struct actor* actor = &actors.items[i];
        actor_tick(actor, delta);
    }
}
void game_draw(void)
{
    BeginDrawing();
    ClearBackground(WHITE);

    for (size_t i = 0; i < actors.count; ++i)
    {
        struct actor* actor = &actors.items[i];
        actor_draw(actor);
    }

    EndDrawing();
}
