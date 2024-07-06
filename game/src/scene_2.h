#ifndef SCENE_2
#define SCENE_2

struct scene_2_data
{
    float x;
    float y;
    float z;
    float t;
};

extern size_t SCENE_2_TAG;

struct scene scene_2_new(float x, float y, float z);
void scene_2_free(struct scene* scene);
void scene_2_enter(struct scene* scene);
void scene_2_exit(struct scene* scene);
void scene_2_tick(struct scene* scene, float delta);
void scene_2_draw(struct scene* scene);

#endif
