#pragma once

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

void layer_rgb_matrix_lower(void) {
    const uint16_t top_row[5] = { 9, 10, 17, 18, 23 };
    const uint16_t nav_keys[2] = { 12, 15 };

    for (uint8_t i = 0; i < sizeof top_row / sizeof *top_row; i++) {
        rgb_matrix_set_color(top_row[i], 15, 0, 0);
    }
    for (uint8_t i = 0; i < sizeof nav_keys / sizeof *nav_keys; i++) {
        rgb_matrix_set_color(nav_keys[i], 15, 0, 15);
    }
}

void layer_rgb_matrix_raise(void) {
#if defined(IS_SIDE_RIGHT)
    const uint16_t fn_keys[7] = { 9, 10, 17, 18, 23, 24, 25 };

    const uint16_t volume[2] = { 20, 21 };
    for (uint8_t i = 0; i < sizeof volume / sizeof *volume; i++) {
        rgb_matrix_set_color(volume[i], 15, 15, 0);
    }
#else
    const uint16_t fn_keys[5] = { 9, 10, 17, 18, 23 };
#endif
    for (uint8_t i = 0; i < sizeof fn_keys / sizeof *fn_keys; i++) {
        rgb_matrix_set_color(fn_keys[i], 0, 15, 0);
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
            layer_rgb_matrix_lower();
            break;
        case _RAISE:
            layer_rgb_matrix_indicator(85, 255, 100);
            layer_rgb_matrix_raise();
            break;
        case _ADJUST:
            layer_rgb_matrix_indicator(170, 255, 100);
            break;
        default:
            layer_rgb_matrix_indicator(0, 0, 0);
            break;
    }
}

void rgb_matrix_indicators_user(void) {
#ifndef IS_SIDE_RIGHT
    if (host_keyboard_leds() & (1 << USB_LED_CAPS_LOCK)) {
        rgb_matrix_set_color(25, 15, 15, 15);
    }
#endif // IS_SIDE_RIGHT
}

#endif // RGB_MATRIX_ENABLE
