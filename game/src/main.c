#include "animated_sprite.h"
#include "actor.h"

#include "raylib.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct textures
{
    Texture2D* items;
    size_t count;
    size_t capacity;
};

struct animated_sprites
{
    struct animated_sprite* items;
    size_t count;
    size_t capacity;
};

struct textures textures = { 0 };
struct animated_sprites animated_sprites = { 0 };

struct actor actor = { 0 };

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

    //

    Texture2D* textures_items = malloc(sizeof(*textures_items) * 16);
    assert(textures_items != NULL);
    memset(textures_items, 0, sizeof(*textures_items) * 16);
    textures = (struct textures)
    {
        .items = textures_items,
        .count = 0,
        .capacity = 16
    };

    textures.items[textures.count++] = LoadTexture("resources/tiles_0001.png");

    textures.items[textures.count++] = LoadTexture("resources/tile_0001.png");
    textures.items[textures.count++] = LoadTexture("resources/tile_0002.png");
    textures.items[textures.count++] = LoadTexture("resources/tile_0003.png");
    textures.items[textures.count++] = LoadTexture("resources/tile_0004.png");
    textures.items[textures.count++] = LoadTexture("resources/tile_0005.png");
    textures.items[textures.count++] = LoadTexture("resources/tile_0006.png");
    textures.items[textures.count++] = LoadTexture("resources/tile_0007.png");
    textures.items[textures.count++] = LoadTexture("resources/tile_0008.png");
    textures.items[textures.count++] = LoadTexture("resources/tile_0009.png");
    textures.items[textures.count++] = LoadTexture("resources/tile_0010.png");
    textures.items[textures.count++] = LoadTexture("resources/tile_0011.png");
    textures.items[textures.count++] = LoadTexture("resources/tile_0012.png");
    textures.items[textures.count++] = LoadTexture("resources/tile_0013.png");
    textures.items[textures.count++] = LoadTexture("resources/tile_0014.png");
    textures.items[textures.count++] = LoadTexture("resources/tile_0015.png");

    //

    struct animated_sprite* animated_sprites_items = malloc(sizeof(*animated_sprites_items));
    assert(animated_sprites_items != NULL);
    memset(animated_sprites_items, 0, sizeof(*animated_sprites_items));

    animated_sprites = (struct animated_sprites)
    {
        .items = animated_sprites_items,
        .count = 0,
        .capacity = 1
    };

    //

    animated_sprites.items[animated_sprites.count++] = animated_sprite_new(64, 64);

    animated_sprite_create_animation(&animated_sprites.items[0], "idle");
    animated_sprite_add_frame(&animated_sprites.items[0], "idle", textures.items[1], 1.0f);
    animated_sprite_add_frame(&animated_sprites.items[0], "idle", textures.items[2], 1.0f);

    animated_sprite_create_animation(&animated_sprites.items[0], "walk");
    animated_sprite_add_frame(&animated_sprites.items[0], "walk", textures.items[3], 0.1f);
    animated_sprite_add_frame(&animated_sprites.items[0], "walk", textures.items[4], 0.1f);
    animated_sprite_add_frame(&animated_sprites.items[0], "walk", textures.items[5], 0.1f);
    animated_sprite_add_frame(&animated_sprites.items[0], "walk", textures.items[6], 0.1f);
    animated_sprite_add_frame(&animated_sprites.items[0], "walk", textures.items[7], 0.1f);
    animated_sprite_add_frame(&animated_sprites.items[0], "walk", textures.items[8], 0.1f);
    animated_sprite_add_frame(&animated_sprites.items[0], "walk", textures.items[9], 0.1f);
    animated_sprite_add_frame(&animated_sprites.items[0], "walk", textures.items[10], 0.1f);
    animated_sprite_add_frame(&animated_sprites.items[0], "walk", textures.items[11], 0.1f);
    animated_sprite_add_frame(&animated_sprites.items[0], "walk", textures.items[12], 0.1f);

    animated_sprite_create_animation(&animated_sprites.items[0], "jump");
    animated_sprite_add_frame(&animated_sprites.items[0], "jump", textures.items[13], 1.0f);

    //

    actor = actor_new(GetScreenWidth() / 2.0f, GetScreenHeight() - 22.0f, 50.0f, 2, 500.0f, animated_sprites.items[0]);
}
void game_free(void)
{
    actor_free(&actor);

    //

    for (size_t i = 0; i < animated_sprites.count; ++i)
        animated_sprite_free(&animated_sprites.items[i]);

    free(animated_sprites.items);
    animated_sprites.items = NULL;
    animated_sprites.count = 0;
    animated_sprites.capacity = 0;

    //

    for (size_t i = 0; i < textures.count; ++i)
        UnloadTexture(textures.items[i]);

    free(textures.items);
    textures.items = NULL;
    textures.count = 0;
    textures.capacity = 0;

    //

    actor_vtable_free();
}
void game_tick(float delta)
{
    actor_tick(&actor, delta);
}
void game_draw(void)
{
    BeginDrawing();
    ClearBackground(WHITE);

    actor_draw(&actor);

    EndDrawing();
}
