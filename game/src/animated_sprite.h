#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include "animation_player.h"

#include "raylib.h"

struct animated_sprite
{
    float x;
    float y;

    Vector2 origin;
    float rotation;
    Color tint;

    bool is_flip_x;
    bool is_flip_y;

    struct animation_player animation_player;
};

struct animated_sprite animated_sprite_new(struct animation_player animation_player);
void animated_sprite_free(struct animated_sprite* animated_sprite);

void animated_sprite_play(struct animated_sprite* animated_sprite, char* name);
void animated_sprite_tick(struct animated_sprite* animated_sprite, float delta);
void animated_sprite_draw(struct animated_sprite* animated_sprite);

#endif
