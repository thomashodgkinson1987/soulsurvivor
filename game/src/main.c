#include "animated_sprite.h"
#include "actor.h"

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

struct animated_sprites animated_sprites = { 0 };

struct actor actor = { 0 };

Texture2D tiles_0001;

Texture2D tile_0001;
Texture2D tile_0002;
Texture2D tile_0003;
Texture2D tile_0004;
Texture2D tile_0005;
Texture2D tile_0006;
Texture2D tile_0007;
Texture2D tile_0008;
Texture2D tile_0009;
Texture2D tile_0010;
Texture2D tile_0011;
Texture2D tile_0012;
Texture2D tile_0013;
Texture2D tile_0014;
Texture2D tile_0015;

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

    tiles_0001 = LoadTexture("resources/tiles_0001.png");

    tile_0001 = LoadTexture("resources/tile_0001.png");
    tile_0002 = LoadTexture("resources/tile_0002.png");
    tile_0003 = LoadTexture("resources/tile_0003.png");
    tile_0004 = LoadTexture("resources/tile_0004.png");
    tile_0005 = LoadTexture("resources/tile_0005.png");
    tile_0006 = LoadTexture("resources/tile_0006.png");
    tile_0007 = LoadTexture("resources/tile_0007.png");
    tile_0008 = LoadTexture("resources/tile_0008.png");
    tile_0009 = LoadTexture("resources/tile_0009.png");
    tile_0010 = LoadTexture("resources/tile_0010.png");
    tile_0011 = LoadTexture("resources/tile_0011.png");
    tile_0012 = LoadTexture("resources/tile_0012.png");
    tile_0013 = LoadTexture("resources/tile_0013.png");
    tile_0014 = LoadTexture("resources/tile_0014.png");
    tile_0015 = LoadTexture("resources/tile_0015.png");

    //

    {
        struct animated_sprite* items = malloc(sizeof(*items));
        assert(items != NULL);
        memset(items, 0, sizeof(*items));

        animated_sprites = (struct animated_sprites)
        {
            .items = items,
            .count = 0,
            .capacity = 1
        };
    }

    //

    animated_sprites.items[animated_sprites.count++] = animated_sprite_new(64, 64);

    animated_sprite_create_animation(&animated_sprites.items[0], "idle");
    animated_sprite_add_frame(&animated_sprites.items[0], "idle", tile_0001, 1.0f);
    animated_sprite_add_frame(&animated_sprites.items[0], "idle", tile_0002, 1.0f);

    animated_sprite_create_animation(&animated_sprites.items[0], "walk");
    animated_sprite_add_frame(&animated_sprites.items[0], "walk", tile_0003, 0.1f);
    animated_sprite_add_frame(&animated_sprites.items[0], "walk", tile_0004, 0.1f);
    animated_sprite_add_frame(&animated_sprites.items[0], "walk", tile_0005, 0.1f);
    animated_sprite_add_frame(&animated_sprites.items[0], "walk", tile_0006, 0.1f);
    animated_sprite_add_frame(&animated_sprites.items[0], "walk", tile_0007, 0.1f);
    animated_sprite_add_frame(&animated_sprites.items[0], "walk", tile_0008, 0.1f);
    animated_sprite_add_frame(&animated_sprites.items[0], "walk", tile_0009, 0.1f);
    animated_sprite_add_frame(&animated_sprites.items[0], "walk", tile_0010, 0.1f);
    animated_sprite_add_frame(&animated_sprites.items[0], "walk", tile_0011, 0.1f);
    animated_sprite_add_frame(&animated_sprites.items[0], "walk", tile_0012, 0.1f);

    animated_sprite_create_animation(&animated_sprites.items[0], "jump");
    animated_sprite_add_frame(&animated_sprites.items[0], "jump", tile_0014, 1.0f);

    //

    actor = actor_new(animated_sprites.items[0]);
}
void game_free(void)
{
    actor_free(&actor);

    //

    actor_vtable_free();

    //

    for (size_t i = 0; i < animated_sprites.count; ++i)
        animated_sprite_free(&animated_sprites.items[i]);

    free(animated_sprites.items);
    animated_sprites.items = NULL;
    animated_sprites.count = 0;
    animated_sprites.capacity = 0;

    //

    UnloadTexture(tiles_0001);

    UnloadTexture(tile_0001);
    UnloadTexture(tile_0002);
    UnloadTexture(tile_0003);
    UnloadTexture(tile_0004);
    UnloadTexture(tile_0005);
    UnloadTexture(tile_0006);
    UnloadTexture(tile_0007);
    UnloadTexture(tile_0008);
    UnloadTexture(tile_0009);
    UnloadTexture(tile_0010);
    UnloadTexture(tile_0011);
    UnloadTexture(tile_0012);
    UnloadTexture(tile_0013);
    UnloadTexture(tile_0014);
    UnloadTexture(tile_0015);
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
