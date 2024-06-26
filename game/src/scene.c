#include "scene.h"
#include "scene_1.h"
#include "scene_2.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static struct scene_vtable vtable = { 0 };

void scene_vtable_init(void)
{
    struct scene_funcs* funcs = malloc(sizeof(*funcs));
    assert(funcs != NULL);
    memset(funcs, 0, sizeof(*funcs));

    vtable = (struct scene_vtable)
    {
        .items = funcs,
        .count = 0,
        .capacity = 1
    };

    struct scene_funcs scene_1_funcs =
    {
        .init = scene_1_init,
        .free = scene_1_free,
        .enter = scene_1_enter,
        .exit = scene_1_exit,
        .tick = scene_1_tick,
        .draw = scene_1_draw,
    };
    SCENE_1_TAG = scene_vtable_register(scene_1_funcs);

    struct scene_funcs scene_2_funcs =
    {
        .init = scene_2_init,
        .free = scene_2_free,
        .enter = scene_2_enter,
        .exit = scene_2_exit,
        .tick = scene_2_tick,
        .draw = scene_2_draw,
    };
    SCENE_2_TAG = scene_vtable_register(scene_2_funcs);
}
void scene_vtable_free(void)
{
    free(vtable.items);
    vtable.items = NULL;
    vtable.count = 0;
    vtable.capacity = 0;
}
size_t scene_vtable_register(struct scene_funcs funcs)
{
    if (vtable.count == vtable.capacity)
    {
        struct scene_funcs* ptr = realloc(vtable.items, sizeof(*ptr) * vtable.capacity * 2);
        assert(ptr != NULL);
        memset(&ptr[vtable.count], 0, sizeof(*ptr) * vtable.capacity);
        vtable.items = ptr;
        vtable.capacity *= 2;
    }

    vtable.items[vtable.count] = funcs;

    return vtable.count++;
}

void scene_init(struct scene* scene)
{
    vtable.items[scene->tag].init(scene);
}
void scene_free(struct scene* scene)
{
    vtable.items[scene->tag].free(scene);
}
void scene_enter(struct scene* scene)
{
    vtable.items[scene->tag].enter(scene);
}
void scene_exit(struct scene* scene)
{
    vtable.items[scene->tag].exit(scene);
}
void scene_tick(struct scene* scene, float delta)
{
    vtable.items[scene->tag].tick(scene, delta);
}
void scene_draw(struct scene* scene)
{
    vtable.items[scene->tag].draw(scene);
}
