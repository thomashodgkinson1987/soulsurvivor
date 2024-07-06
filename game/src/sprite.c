#include "sprite.h"

struct sprite sprite_new(Texture2D texture)
{
    struct sprite sprite =
    {
        .x = 0.0f,
        .y = 0.0f,
        .texture = texture,
        .source = (Rectangle){ 0.0f, 0.0f, (float)texture.width, (float)texture.height },
        .dest = (Rectangle){ 0.0f, 0.0f, (float)texture.width, (float)texture.height },
        .origin = (Vector2){ 0.0f, 0.0f },
        .rotation = 0.0f,
        .tint = WHITE,
        .is_flip_x = false,
        .is_flip_y = false
    };

    return sprite;
}

void sprite_free(struct sprite* sprite)
{
    sprite->x = 0.0f;
    sprite->y = 0.0f;
    sprite->texture = (Texture){ 0 };
    sprite->source = (Rectangle){ 0.0f, 0.0f, 0.0f, 0.0f };
    sprite->dest = (Rectangle){ 0.0f, 0.0f, 0.0f, 0.0f };
    sprite->origin = (Vector2){ 0.0f, 0.0f };
    sprite->rotation = 0.0f;
    sprite->tint = BLANK;
    sprite->is_flip_x = false;
    sprite->is_flip_y = false;
}
void sprite_draw(struct sprite* sprite)
{
    Texture texture = sprite->texture;
    Rectangle source = sprite->source;
    Rectangle dest = sprite->dest;
    Vector2 origin = sprite->origin;
    float rotation = sprite->rotation;
    Color tint = sprite->tint;

    if (sprite->is_flip_x)
    {
        source.width *= -1.0f;
    }
    if (sprite->is_flip_y)
    {
        source.height *= -1.0f;
    }

    dest.x += sprite->x;
    dest.y += sprite->y;

    DrawTexturePro(texture, source, dest, origin, rotation, tint);
}
