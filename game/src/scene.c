#include "scene.h"
#include "scene_1.h"
#include "scene_2.h"

#include "mfn_dynamic_array.h"

static struct scene_vtable vtable = { 0 };

size_t SCENE_BASE_TAG = 0;

void scene_vtable_init(void)
{
    MFN_ARRAY_INIT(struct scene_funcs, &vtable);

    SCENE_BASE_TAG = scene_vtable_register((struct scene_funcs)
    {
        .free = NULL,
            .enter = NULL,
            .exit = NULL,
            .tick = NULL,
            .draw = NULL
    });

    SCENE_1_TAG = scene_vtable_register((struct scene_funcs)
    {
        .free = scene_1_free,
            .enter = scene_1_enter,
            .exit = scene_1_exit,
            .tick = scene_1_tick,
            .draw = scene_1_draw
    });

    SCENE_2_TAG = scene_vtable_register((struct scene_funcs)
    {
        .free = scene_2_free,
            .enter = scene_2_enter,
            .exit = scene_2_exit,
            .tick = scene_2_tick,
            .draw = scene_2_draw
    });
}
void scene_vtable_free(void)
{
    MFN_ARRAY_FREE(&vtable);

    SCENE_BASE_TAG = 0;
    SCENE_1_TAG = 0;
    SCENE_2_TAG = 0;
}
size_t scene_vtable_register(struct scene_funcs funcs)
{
    size_t tag = vtable.count;

    MFN_ARRAY_APPEND(struct scene_funcs, &vtable, funcs);

    return tag;
}

struct scene scene_new(size_t tag, void* data)
{
    struct scene scene =
    {
        .tag = tag,
        .data = data
    };

    return scene;
}
void scene_free(struct scene* scene)
{
    if (vtable.items[scene->tag].free)
    {
        vtable.items[scene->tag].free(scene);
    }

    scene->tag = 0;

    if (scene->data)
    {
        free(scene->data);
        scene->data = NULL;
    }
}
void scene_enter(struct scene* scene)
{
    if (vtable.items[scene->tag].enter)
    {
        vtable.items[scene->tag].enter(scene);
    }
}
void scene_exit(struct scene* scene)
{
    if (vtable.items[scene->tag].exit)
    {
        vtable.items[scene->tag].exit(scene);
    }
}
void scene_tick(struct scene* scene, float delta)
{
    if (vtable.items[scene->tag].tick)
    {
        vtable.items[scene->tag].tick(scene, delta);
    }
}
void scene_draw(struct scene* scene)
{
    if (vtable.items[scene->tag].draw)
    {
        vtable.items[scene->tag].draw(scene);
    }
}
