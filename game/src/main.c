#include "frame.h"
#include "animation.h"
#include "animation_player.h"
#include "animated_sprite.h"

#include "mfn_dynamic_array.h"

#include "raylib.h"

struct textures
{
    Texture2D* items;
    size_t count;
    size_t capacity;
};

struct frame_sets
{
    struct frames* items;
    size_t count;
    size_t capacity;
};

struct animation_sets
{
    struct animations* items;
    size_t count;
    size_t capacity;
};

struct textures textures = { 0 };
struct frames frames = { 0 };
struct frame_sets frame_sets = { 0 };
struct animations animations = { 0 };
struct animation_sets animation_sets = { 0 };

struct animation_player animation_player = { 0 };
struct animated_sprite animated_sprite = { 0 };

void game_init_textures(void);
void game_init_frames(void);
void game_init_frame_sets(void);
void game_init_animations(void);
void game_init_animation_sets(void);
void game_init(void);

void game_free_animation_sets(void);
void game_free_animations(void);
void game_free_frame_sets(void);
void game_free_frames(void);
void game_free_textures(void);
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

void game_init_textures(void)
{
    MFN_ARRAY_INIT(Texture2D, &textures);

    MFN_ARRAY_APPEND(Texture2D, &textures, LoadTexture("resources/tile_0001.png"));
    MFN_ARRAY_APPEND(Texture2D, &textures, LoadTexture("resources/tile_0002.png"));
    MFN_ARRAY_APPEND(Texture2D, &textures, LoadTexture("resources/tile_0003.png"));
    MFN_ARRAY_APPEND(Texture2D, &textures, LoadTexture("resources/tile_0004.png"));
    MFN_ARRAY_APPEND(Texture2D, &textures, LoadTexture("resources/tile_0005.png"));
    MFN_ARRAY_APPEND(Texture2D, &textures, LoadTexture("resources/tile_0006.png"));
    MFN_ARRAY_APPEND(Texture2D, &textures, LoadTexture("resources/tile_0007.png"));
    MFN_ARRAY_APPEND(Texture2D, &textures, LoadTexture("resources/tile_0008.png"));
    MFN_ARRAY_APPEND(Texture2D, &textures, LoadTexture("resources/tile_0009.png"));
    MFN_ARRAY_APPEND(Texture2D, &textures, LoadTexture("resources/tile_0010.png"));
    MFN_ARRAY_APPEND(Texture2D, &textures, LoadTexture("resources/tile_0011.png"));
    MFN_ARRAY_APPEND(Texture2D, &textures, LoadTexture("resources/tile_0012.png"));
    MFN_ARRAY_APPEND(Texture2D, &textures, LoadTexture("resources/tile_0013.png"));
    MFN_ARRAY_APPEND(Texture2D, &textures, LoadTexture("resources/tile_0014.png"));
    MFN_ARRAY_APPEND(Texture2D, &textures, LoadTexture("resources/tile_0015.png"));
}
void game_init_frames(void)
{
    MFN_ARRAY_INIT(struct frame, &frames);

    MFN_ARRAY_APPEND(struct frame, &frames, frame_new(textures.items[0], 0.5f));
    MFN_ARRAY_APPEND(struct frame, &frames, frame_new(textures.items[1], 0.5f));
    MFN_ARRAY_APPEND(struct frame, &frames, frame_new(textures.items[2], 0.1f));
    MFN_ARRAY_APPEND(struct frame, &frames, frame_new(textures.items[3], 0.1f));
    MFN_ARRAY_APPEND(struct frame, &frames, frame_new(textures.items[4], 0.1f));
    MFN_ARRAY_APPEND(struct frame, &frames, frame_new(textures.items[5], 0.1f));
    MFN_ARRAY_APPEND(struct frame, &frames, frame_new(textures.items[6], 0.1f));
    MFN_ARRAY_APPEND(struct frame, &frames, frame_new(textures.items[7], 0.1f));
    MFN_ARRAY_APPEND(struct frame, &frames, frame_new(textures.items[8], 0.1f));
    MFN_ARRAY_APPEND(struct frame, &frames, frame_new(textures.items[9], 0.1f));
    MFN_ARRAY_APPEND(struct frame, &frames, frame_new(textures.items[10], 0.1f));
    MFN_ARRAY_APPEND(struct frame, &frames, frame_new(textures.items[11], 0.1f));
    MFN_ARRAY_APPEND(struct frame, &frames, frame_new(textures.items[12], 0.25f));
    MFN_ARRAY_APPEND(struct frame, &frames, frame_new(textures.items[13], 0.25f));
    MFN_ARRAY_APPEND(struct frame, &frames, frame_new(textures.items[14], 0.25f));
}
void game_init_frame_sets(void)
{
    MFN_ARRAY_INIT(struct frames, &frame_sets);

    struct frames frame_set_0001 = { 0 };
    MFN_ARRAY_INIT(struct frame, &frame_set_0001);
    MFN_ARRAY_APPEND(struct frame, &frame_set_0001, frames.items[0]);
    MFN_ARRAY_APPEND(struct frame, &frame_set_0001, frames.items[1]);
    MFN_ARRAY_APPEND(struct frames, &frame_sets, frame_set_0001);

    struct frames frame_set_0002 = { 0 };
    MFN_ARRAY_INIT(struct frame, &frame_set_0002);
    MFN_ARRAY_APPEND(struct frame, &frame_set_0002, frames.items[2]);
    MFN_ARRAY_APPEND(struct frame, &frame_set_0002, frames.items[3]);
    MFN_ARRAY_APPEND(struct frame, &frame_set_0002, frames.items[4]);
    MFN_ARRAY_APPEND(struct frame, &frame_set_0002, frames.items[5]);
    MFN_ARRAY_APPEND(struct frame, &frame_set_0002, frames.items[6]);
    MFN_ARRAY_APPEND(struct frame, &frame_set_0002, frames.items[7]);
    MFN_ARRAY_APPEND(struct frame, &frame_set_0002, frames.items[8]);
    MFN_ARRAY_APPEND(struct frame, &frame_set_0002, frames.items[9]);
    MFN_ARRAY_APPEND(struct frame, &frame_set_0002, frames.items[10]);
    MFN_ARRAY_APPEND(struct frame, &frame_set_0002, frames.items[11]);
    MFN_ARRAY_APPEND(struct frames, &frame_sets, frame_set_0002);

    struct frames frame_set_0003 = { 0 };
    MFN_ARRAY_INIT(struct frame, &frame_set_0003);
    MFN_ARRAY_APPEND(struct frame, &frame_set_0003, frames.items[12]);
    MFN_ARRAY_APPEND(struct frame, &frame_set_0003, frames.items[13]);
    MFN_ARRAY_APPEND(struct frame, &frame_set_0003, frames.items[14]);
    MFN_ARRAY_APPEND(struct frames, &frame_sets, frame_set_0003);
}
void game_init_animations(void)
{
    MFN_ARRAY_INIT(struct animation, &animations);

    MFN_ARRAY_APPEND(struct animation, &animations, animation_new("animation_0001", frame_sets.items[0]));
    MFN_ARRAY_APPEND(struct animation, &animations, animation_new("animation_0002", frame_sets.items[1]));
    MFN_ARRAY_APPEND(struct animation, &animations, animation_new("animation_0003", frame_sets.items[2]));
}
void game_init_animation_sets(void)
{
    MFN_ARRAY_INIT(struct animations, &animation_sets);

    struct animations animation_set_0001 = { 0 };
    MFN_ARRAY_INIT(struct animation, &animation_set_0001);
    MFN_ARRAY_APPEND(struct animation, &animation_set_0001, animations.items[0]);
    MFN_ARRAY_APPEND(struct animation, &animation_set_0001, animations.items[1]);
    MFN_ARRAY_APPEND(struct animation, &animation_set_0001, animations.items[2]);

    MFN_ARRAY_APPEND(struct animations, &animation_sets, animation_set_0001);
}
void game_init(void)
{
    game_init_textures();
    game_init_frames();
    game_init_frame_sets();
    game_init_animations();
    game_init_animation_sets();

    animation_player = animation_player_new(animation_sets.items[0]);
    animated_sprite = animated_sprite_new(animation_player);
}

void game_free_animation_sets(void)
{
    for (size_t i = 0; i < animation_sets.count; ++i)
    {
        MFN_ARRAY_FREE(&animation_sets.items[i]);
    }

    MFN_ARRAY_FREE(&animation_sets);
}
void game_free_animations(void)
{
    for (size_t i = 0; i < animations.count; ++i)
    {
        animation_free(&animations.items[i]);
    }

    MFN_ARRAY_FREE(&animations);
}
void game_free_frame_sets(void)
{
    for (size_t i = 0; i < frame_sets.count; ++i)
    {
        MFN_ARRAY_FREE(&frame_sets.items[i]);
    }

    MFN_ARRAY_FREE(&frame_sets);
}
void game_free_frames(void)
{
    for (size_t i = 0; i < frames.count; ++i)
    {
        frame_free(&frames.items[i]);
    }

    MFN_ARRAY_FREE(&frames);
}
void game_free_textures(void)
{
    for (size_t i = 0; i < textures.count; ++i)
    {
        UnloadTexture(textures.items[i]);
    }

    MFN_ARRAY_FREE(&textures);
}
void game_free(void)
{
    animated_sprite_free(&animated_sprite);
    animation_player_free(&animation_player);

    game_free_animation_sets();
    game_free_animations();
    game_free_frame_sets();
    game_free_frames();
    game_free_textures();
}

void game_tick(float delta)
{
    if (IsKeyDown(KEY_LEFT))
    {
        animated_sprite.x -= 4.0f;
    }
    if (IsKeyDown(KEY_RIGHT))
    {
        animated_sprite.x += 4.0f;
    }
    if (IsKeyDown(KEY_UP))
    {
        animated_sprite.y -= 4.0f;
    }
    if (IsKeyDown(KEY_DOWN))
    {
        animated_sprite.y += 4.0f;
    }

    if (IsKeyPressed(KEY_ONE))
    {
        animated_sprite.is_flip_x = false;
    }
    if (IsKeyPressed(KEY_TWO))
    {
        animated_sprite.is_flip_x = true;
    }
    if (IsKeyPressed(KEY_THREE))
    {
        animated_sprite.is_flip_y = false;
    }
    if (IsKeyPressed(KEY_FOUR))
    {
        animated_sprite.is_flip_y = true;
    }

    if (IsKeyPressed(KEY_Z))
    {
        animated_sprite_play(&animated_sprite, "animation_0001");
    }
    if (IsKeyPressed(KEY_X))
    {
        animated_sprite_play(&animated_sprite, "animation_0002");
    }
    if (IsKeyPressed(KEY_C))
    {
        animated_sprite_play(&animated_sprite, "animation_0003");
    }

    animated_sprite_tick(&animated_sprite, delta);
}
void game_draw(void)
{
    BeginDrawing();
    ClearBackground(WHITE);

    animated_sprite_draw(&animated_sprite);

    EndDrawing();
}
