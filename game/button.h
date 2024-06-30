#ifndef BUTTON_H
#define BUTTON_H

#include <stdbool.h>

struct button_signal_on_hovered_array
{
    void(**items)(struct button* button);
    size_t count;
    size_t capacity;
};

struct button_signal_on_hovering_array
{
    void(**items)(struct button* button);
    size_t count;
    size_t capacity;
};

struct button_signal_on_unhovered_array
{
    void(**items)(struct button* button);
    size_t count;
    size_t capacity;
};

struct button_signal_on_pressed_array
{
    void(**items)(struct button* button);
    size_t count;
    size_t capacity;
};

struct button_signal_on_held_array
{
    void(**items)(struct button* button);
    size_t count;
    size_t capacity;
};

struct button_signal_on_released_array
{
    void(**items)(struct button* button);
    size_t count;
    size_t capacity;
};

struct button
{
    int x;
    int y;

    int width;
    int height;

    unsigned char color_r;
    unsigned char color_g;
    unsigned char color_b;
    unsigned char color_a;

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

struct button button_create(int x, int y, int width, int height, unsigned char color_r, unsigned char color_g, unsigned char color_b, unsigned char color_a);
void button_free(struct button* button);

void button_register_signal_on_hovered(struct button* button, void(*on_hovered)(struct button* button));
void button_register_signal_on_hovering(struct button* button, void(*on_hovering)(struct button* button));
void button_register_signal_on_unhovered(struct button* button, void(*on_unhovered)(struct button* button));

void button_register_signal_on_pressed(struct button* button, void(*on_pressed)(struct button* button));
void button_register_signal_on_held(struct button* button, void(*on_held)(struct button* button));
void button_register_signal_on_released(struct button* button, void(*on_released)(struct button* button));

void button_unregister_signal_on_hovered(struct button* button, void(*on_hovered)(struct button* button));
void button_unregister_signal_on_hovering(struct button* button, void(*on_hovering)(struct button* button));
void button_unregister_signal_on_unhovered(struct button* button, void(*on_unhovered)(struct button* button));

void button_unregister_signal_on_pressed(struct button* button, void(*on_pressed)(struct button* button));
void button_unregister_signal_on_held(struct button* button, void(*on_held)(struct button* button));
void button_unregister_signal_on_released(struct button* button, void(*on_released)(struct button* button));

void button_on_hovered(struct button* button);
void button_on_hovering(struct button* button);
void button_on_unhovered(struct button* button);

void button_on_pressed(struct button* button);
void button_on_held(struct button* button);
void button_on_released(struct button* button);

void button_tick(struct button* button, int cursor_x, int cursor_y, bool is_pressed, bool was_pressed);
void button_draw(struct button* button);

#endif
