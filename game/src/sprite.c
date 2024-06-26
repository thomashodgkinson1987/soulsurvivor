#include "sprite.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static struct sprite_vtable vtable = { 0 };

void sprite_vtable_init(void)
{
    struct sprite_funcs* funcs = malloc(sizeof(*funcs));
    assert(funcs != NULL);
    memset(funcs, 0, sizeof(*funcs));

    vtable = (struct sprite_vtable)
    {
        .items = funcs,
        .count = 0,
        .capacity = 1
    };

    struct sprite_funcs sprite_funcs =
    {
        .draw = sprite_base_draw,
        .free = sprite_base_free
    };
    SPRITE_BASE_TAG = sprite_vtable_register(sprite_funcs);
}
size_t sprite_vtable_register(struct sprite_funcs funcs)
{
    if (vtable.count == vtable.capacity)
    {
        struct sprite_funcs* ptr = realloc(vtable.items, sizeof(*ptr) * vtable.capacity * 2);
        assert(ptr != NULL);
        memset(&ptr[vtable.capacity], 0, sizeof(*ptr) * vtable.capacity);
        vtable.items = ptr;
        vtable.capacity *= 2;
    }

    vtable.items[vtable.count] = funcs;

    return vtable.count++;
}
void sprite_vtable_free(void)
{
    free(vtable.items);
    vtable.items = NULL;
    vtable.count = 0;
    vtable.capacity = 0;
}

struct sprite sprite_new(Texture2D texture)
{
    struct sprite_data* data = malloc(sizeof(*data));
    assert(data != NULL);

    *data = (struct sprite_data)
    {
        .texture = texture,
        .source = (Rectangle){ 0.0f, 0.0f, (float)texture.width, (float)texture.height },
        .dest = (Rectangle){ 0.0f, 0.0f, (float)texture.width, (float)texture.height },
        .origin = (Vector2){ 0.0f, 0.0f },
        .rotation = 0.0f,
        .tint = WHITE
    };

    struct sprite sprite =
    {
        .tag = SPRITE_BASE_TAG,
        .data = data
    };

    return sprite;
}

void sprite_free(struct sprite* sprite)
{
    vtable.items[sprite->tag].free(sprite);
}
void sprite_draw(struct sprite* sprite)
{
    vtable.items[sprite->tag].draw(sprite);
}

void sprite_base_free(struct sprite* sprite)
{
    struct sprite_data* data = (struct sprite_data*)sprite->data;

    free(data);
}
void sprite_base_draw(struct sprite* sprite)
{
    struct sprite_data* data = (struct sprite_data*)sprite->data;

    Texture texture = data->texture;
    Rectangle source = data->source;
    Rectangle dest = data->dest;
    Vector2 origin = data->origin;
    float rotation = data->rotation;
    Color tint = data->tint;

    DrawTexturePro(texture, source, dest, origin, rotation, tint);
}
