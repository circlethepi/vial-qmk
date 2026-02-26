/**
 * Utilities for RGB lighting
 * Copyright (c) MNZK 2026
 * MIT License
 */

 #pragma once

 #define set_underglow(r, g, b) \
    rgb_matrix_set_color(0, r, g, b); \
    rgb_matrix_set_color(1, r, g, b); \
    rgb_matrix_set_color(2, r, g, b); \
    rgb_matrix_set_color(3, r, g, b); \
    rgb_matrix_set_color(4, r, g, b); \
    rgb_matrix_set_color(5, r, g, b); \
    rgb_matrix_set_color(27, r, g, b); \
    rgb_matrix_set_color(28, r, g, b); \
    rgb_matrix_set_color(29, r, g, b); \
    rgb_matrix_set_color(30, r, g, b); \
    rgb_matrix_set_color(31, r, g, b); \
    rgb_matrix_set_color(32, r, g, b);


// Flags for thumb selection
#define THUMB_LEFT   (1 << 0)
#define THUMB_RIGHT  (1 << 1)
#define THUMB_BOTH   (THUMB_LEFT | THUMB_RIGHT)

// Inline function with range checking for split keyboards
static inline void set_thumb_keys_advanced(uint8_t r, uint8_t g, uint8_t b, uint8_t sides, uint8_t led_min, uint8_t led_max) {
    if (sides & THUMB_LEFT) {
        if (6 >= led_min && 6 <= led_max) rgb_matrix_set_color(6, r, g, b);
        if (14 >= led_min && 14 <= led_max) rgb_matrix_set_color(14, r, g, b);
        if (13 >= led_min && 13 <= led_max) rgb_matrix_set_color(13, r, g, b);
    }
    if (sides & THUMB_RIGHT) {
        if (33 >= led_min && 33 <= led_max) rgb_matrix_set_color(33, r, g, b);
        if (41 >= led_min && 41 <= led_max) rgb_matrix_set_color(41, r, g, b);
        if (40 >= led_min && 40 <= led_max) rgb_matrix_set_color(40, r, g, b);
    }
}

// Macros that work with the advanced function
#define RGB_THUMB_KEYS(r, g, b, led_min, led_max)   set_thumb_keys_advanced(r, g, b, THUMB_BOTH, led_min, led_max)
#define RGB_THUMB_LEFT(r, g, b, led_min, led_max)   set_thumb_keys_advanced(r, g, b, THUMB_LEFT, led_min, led_max)
#define RGB_THUMB_RIGHT(r, g, b, led_min, led_max)  set_thumb_keys_advanced(r, g, b, THUMB_RIGHT, led_min, led_max)
