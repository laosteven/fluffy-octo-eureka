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

void rgb_matrix_indicators_user(void) {
#ifndef IS_SIDE_RIGHT
    if (host_keyboard_leds() & (1 << USB_LED_CAPS_LOCK)) {
        rgb_matrix_set_color(25, 15, 15, 15);
    }
#endif // IS_SIDE_RIGHT
}

#endif // RGB_MATRIX_ENABLE
