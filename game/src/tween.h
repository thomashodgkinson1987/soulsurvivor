#ifndef TWEEN_H
#define TWEEN_H

#include "raylib.h"

struct tween
{
    size_t tag;
    void* data;

    float duration;
    float elapsed;
    bool is_complete;
};

struct tween_funcs
{
    void(*tick)(struct tween* tween, float delta);
};

struct tween_vtable
{
    struct tween_funcs* items;
    size_t count;
    size_t capacity;
};

void tween_vtable_init(void);
void tween_vtable_free(void);
size_t tween_vtable_register(struct tween_funcs funcs);

extern size_t TWEEN_BASE_TAG;

struct tween tween_new(size_t tag, void* data, float duration);
void tween_free(struct tween* tween);
void tween_reset(struct tween* tween);
void tween_tick(struct tween* tween, float delta);

struct tween_float_data
{
    float* value;
    float from;
    float to;
};

extern size_t TWEEN_FLOAT_TAG;

struct tween tween_float_new(float* value, float from, float to, float duration);
void tween_float_tick(struct tween* tween, float delta);

struct tween_color_data
{
    Color* value;
    Color from;
    Color to;
};

extern size_t TWEEN_COLOR_TAG;

struct tween tween_color_new(Color* value, Color from, Color to, float duration);
void tween_color_tick(struct tween* tween, float delta);

struct tween_unsigned_char_data
{
    unsigned char* value;
    unsigned char from;
    unsigned char to;
};

extern size_t TWEEN_UNSIGNED_CHAR_TAG;

struct tween tween_unsigned_char_new(unsigned char* value, unsigned char from, unsigned char to, float duration);
void tween_unsigned_char_tick(struct tween* tween, float delta);

#endif
