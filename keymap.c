/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#include "layers.h"
#include "oled.c"

#define KC_CTSP     LCTL_T(KC_SPACE)    // Left Ctrl | Space
#define KC_SFBS     LSFT_T(KC_BSPACE)   // Left Shft | Backspace
#define KC_SFTB     RSFT_T(KC_TAB)      // Right Shft | Tab
#define KC_CTET     RCTL_T(KC_ENTER)    // Right Ctrl | Enter
#define KC_SS       LGUI(LSFT(KC_S))    // Win + Shift + S

#if defined(TEMPLATE_ALPHA)
#   include "templates/alpha.c"
#elif defined(TEMPLATE_CODE)
#   include "templates/code.c"
#else
#   include "templates/default.c"
#endif

#ifdef RGB_MATRIX_ENABLE
void layer_rgb_matrix_indicator(uint8_t hue, uint8_t sat, uint8_t val) {
    HSV hsv = { hue, sat, val };
    RGB rgb = hsv_to_rgb(hsv);
    for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
        if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_UNDERGLOW)) {
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        }
    }
}

void matrix_scan_user(void) {
    switch (get_highest_layer(layer_state)){
        case _QWERTY:
            if (rgb_matrix_get_mode() == RGB_MATRIX_TYPING_HEATMAP) {
                layer_rgb_matrix_indicator(0, 0, 0);
            }
            break;
        case _LOWER:
            layer_rgb_matrix_indicator(0, 255, 100);
            break;
        case _RAISE:
            layer_rgb_matrix_indicator(85, 255, 100);
            break;
        case _ADJUST:
            layer_rgb_matrix_indicator(170, 255, 100);
            break;
        default:
            layer_rgb_matrix_indicator(0, 0, 0);
            break;
    }
}
#endif
