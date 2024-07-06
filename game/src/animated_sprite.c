#include "animated_sprite.h"

#include "raylib.h"

#include <assert.h>
#include <string.h>

struct animated_sprite animated_sprite_new(struct animation_player animation_player)
{
    struct animated_sprite animated_sprite =
    {
        .x = 0.0f,
        .y = 0.0f,

        .origin = (Vector2){ 0.0f, 0.0f },
        .rotation = 0.0f,
        .tint = WHITE,

        .is_flip_x = false,
        .is_flip_y = false,

        .animation_player = animation_player
    };

    return animated_sprite;
}
void animated_sprite_free(struct animated_sprite* animated_sprite)
{
    animated_sprite->x = 0;
    animated_sprite->y = 0;

    animated_sprite->origin = (Vector2){ 0.0f, 0.0f };
    animated_sprite->rotation = 0.0f;
    animated_sprite->tint = BLANK;

    animated_sprite->is_flip_x = false;
    animated_sprite->is_flip_y = false;

    animated_sprite->animation_player = (struct animation_player){ 0 };
}

void animated_sprite_play(struct animated_sprite* animated_sprite, char* name)
{
    animation_player_play(&animated_sprite->animation_player, name);
}
void animated_sprite_tick(struct animated_sprite* animated_sprite, float delta)
{
    animation_player_tick(&animated_sprite->animation_player, delta);
}
void animated_sprite_draw(struct animated_sprite* animated_sprite)
{
    struct animation_player* animation_player = &animated_sprite->animation_player;
    struct animation* animation = &animation_player->animations.items[animation_player->current_animation_index];
    struct frame* frame = &animation->frames.items[animation_player->current_frame_index];

    Texture texture = frame->texture;
    Rectangle source = (Rectangle){ 0.0f, 0.0f, (float)texture.width, (float)texture.height };
    Rectangle dest = (Rectangle){ 0.0f, 0.0f, (float)texture.width, (float)texture.height };
    Vector2 origin = animated_sprite->origin;
    float rotation = animated_sprite->rotation;
    Color tint = animated_sprite->tint;

    if (animated_sprite->is_flip_x)
    {
        source.width *= -1.0f;
    }
    if (animated_sprite->is_flip_y)
    {
        source.height *= -1.0f;
    }

    dest.x += animated_sprite->x;
    dest.y += animated_sprite->y;

    DrawTexturePro(texture, source, dest, origin, rotation, tint);
}
