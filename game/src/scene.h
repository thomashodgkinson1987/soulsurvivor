#ifndef SCENE_H
#define SCENE_H

struct scene
{
    size_t tag;
    void* data;
};

struct scene_funcs
{
    void(*free)(struct scene* scene);
    void(*enter)(struct scene* scene);
    void(*exit)(struct scene* scene);
    void(*tick)(struct scene* scene, float delta);
    void(*draw)(struct scene* scene);
};

struct scene_vtable
{
    struct scene_funcs* items;
    size_t count;
    size_t capacity;
};

void scene_vtable_init(void);
void scene_vtable_free(void);
size_t scene_vtable_register(struct scene_funcs funcs);

extern size_t SCENE_BASE_TAG;

struct scene scene_new(size_t tag, void* data);
void scene_free(struct scene* scene);
void scene_enter(struct scene* scene);
void scene_exit(struct scene* scene);
void scene_tick(struct scene* scene, float delta);
void scene_draw(struct scene* scene);

#endif
