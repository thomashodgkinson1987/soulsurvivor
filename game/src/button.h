#ifndef BUTTON_H
#define BUTTON_H

#include <stdbool.h>

typedef void(*button_signal_on_hovered)(struct button* button);
typedef void(*button_signal_on_hovering)(struct button* button);
typedef void(*button_signal_on_unhovered)(struct button* button);
typedef void(*button_signal_on_pressed)(struct button* button);
typedef void(*button_signal_on_held)(struct button* button);
typedef void(*button_signal_on_released)(struct button* button);

struct button_signal_on_hovered_array
{
    button_signal_on_hovered* items;
    size_t count;
    size_t capacity;
};

struct button_signal_on_hovering_array
{
    button_signal_on_hovering* items;
    size_t count;
    size_t capacity;
};

struct button_signal_on_unhovered_array
{
    button_signal_on_unhovered* items;
    size_t count;
    size_t capacity;
};

struct button_signal_on_pressed_array
{
    button_signal_on_pressed* items;
    size_t count;
    size_t capacity;
};

struct button_signal_on_held_array
{
    button_signal_on_held* items;
    size_t count;
    size_t capacity;
};

struct button_signal_on_released_array
{
    button_signal_on_released* items;
    size_t count;
    size_t capacity;
};

struct button
{
    int x;
    int y;

    int width;
    int height;

    unsigned char color[4];

    struct button_signal_on_hovered_array signal_on_hovered_array;
    struct button_signal_on_hovering_array signal_on_hovering_array;
    struct button_signal_on_unhovered_array signal_on_unhovered_array;

    struct button_signal_on_pressed_array signal_on_pressed_array;
    struct button_signal_on_held_array signal_on_held_array;
    struct button_signal_on_released_array signal_on_released_array;

    bool is_hovering;
    bool was_hovering;

    bool is_pressed;
    bool was_pressed;

    void(*on_draw)(struct button* button);
};

struct button button_new(int x, int y, int width, int height, unsigned char color_r, unsigned char color_g, unsigned char color_b, unsigned char color_a);
void button_free(struct button* button);

void button_register_signal_on_hovered(struct button* button, button_signal_on_hovered signal);
void button_register_signal_on_hovering(struct button* button, button_signal_on_hovering signal);
void button_register_signal_on_unhovered(struct button* button, button_signal_on_unhovered signal);

void button_register_signal_on_pressed(struct button* button, button_signal_on_pressed signal);
void button_register_signal_on_held(struct button* button, button_signal_on_held signal);
void button_register_signal_on_released(struct button* button, button_signal_on_released signal);

void button_unregister_signal_on_hovered(struct button* button, button_signal_on_hovered signal);
void button_unregister_signal_on_hovering(struct button* button, button_signal_on_hovering signal);
void button_unregister_signal_on_unhovered(struct button* button, button_signal_on_unhovered signal);

void button_unregister_signal_on_pressed(struct button* button, button_signal_on_pressed signal);
void button_unregister_signal_on_held(struct button* button, button_signal_on_held signal);
void button_unregister_signal_on_released(struct button* button, button_signal_on_released signal);

void button_on_hovered(struct button* button);
void button_on_hovering(struct button* button);
void button_on_unhovered(struct button* button);

void button_on_pressed(struct button* button);
void button_on_held(struct button* button);
void button_on_released(struct button* button);

void button_tick(struct button* button, int cursor_x, int cursor_y, bool is_pressed, bool was_pressed);
void button_draw(struct button* button);

#endif
