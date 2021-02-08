#pragma once

#ifdef OLED_DRIVER_ENABLE
char wpm_str[15];
char hsv_str[15];
char mod_str[15];
char state_str[30];
char keylog_str[24] = {};
uint16_t wpm_graph_timer = 0;
static uint32_t oled_timer = 0;

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

void oled_render_separator(void) {
    oled_write_ln("_____", false);
}

void oled_render_space(void) {
    oled_write_ln("     ", false);
}

void oled_render_layer_state(void) {
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write("[QWR]", false);
            break;
        case _LOWER:
            oled_write("[LWR]", true);
            break;
        case _RAISE:
            oled_write("[RSE]", true);
            break;
        case _ADJUST:
            oled_write("[ADJ]", true);
            break;
        default:
            oled_write("[NOP]", true);
            break;
    }
}

void set_keylog(uint16_t keycode, keyrecord_t *record) {
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
        (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) {
        keycode = keycode & 0xFF;
    } else if (keycode > 0xFF) {
        keycode = 0;
    }

    // update keylog
    snprintf(keylog_str, sizeof(keylog_str), "[MAT] %dx%d [KYC] %03d ",
        record->event.key.row, record->event.key.col,
        keycode);
}

void oled_render_keylog(void) {
    if (strlen(keylog_str) == 0) {
        snprintf(keylog_str, sizeof(keylog_str), "[MAT] 0x0 [KYC] 000 ");
    }
    oled_write(keylog_str, false);
}

#ifdef RGB_MATRIX_ENABLE
void oled_render_hsv(void) {
    sprintf(hsv_str, "h:%3ds:%3dv:%3d",
        rgb_matrix_get_hue(),
        rgb_matrix_get_sat(),
        rgb_matrix_get_val()
    );
    oled_write(hsv_str, false);
}
#else
void oled_render_hsv(void) {
    oled_render_space();
    oled_render_space();
}
#endif // RGB_MATRIX_ENABLE

void oled_render_keymods(uint8_t led_usb_state) {
    sprintf(mod_str, "num %scap %s",
        led_usb_state & (1 << USB_LED_NUM_LOCK) ? "+" : "-",
        led_usb_state & (1 << USB_LED_CAPS_LOCK) ? "+" : "-"
    );
    oled_write(mod_str, false);
}

#ifdef WPM_ENABLE
void oled_render_wpm(void) {
    sprintf(wpm_str, "[WPM] %03d ", get_current_wpm());
    oled_write(wpm_str, false);
}

// Inspired from brickbots' Kyria keymap
// - https://github.com/brickbots/qmk_firmware/tree/brickbots_dev/keyboards/kyria/keymaps/brickbots
// - https://www.reddit.com/r/MechanicalKeyboards/comments/evimyg/kyria_is_kool_onboard_wpm_calc_oled_graph/
static void oled_render_wpm_graph(void) {
    static uint8_t bar_count = 0;
    uint8_t bar_height = 0;
    uint8_t bar_segment = 0;

    if (wpm_graph_timer == 0) {
        wpm_graph_timer = timer_read();
        return;
    }
    if(timer_elapsed(wpm_graph_timer) > 500) {
        wpm_graph_timer = timer_read();
        bar_height = get_current_wpm() / 20;

        oled_pan(false);
        bar_count++;
        for (uint8_t i = (OLED_DISPLAY_WIDTH / 8); i > 0; i--) {
            switch (bar_height) {
                case 0:
                    bar_segment = 128;
                    break;

                case 1:
                    bar_segment = 128;
                    break;

                case 2:
                    bar_segment = 192;
                    break;

                case 3:
                    bar_segment = 224;
                    break;

                case 4:
                    bar_segment = 240;
                    break;

                case 5:
                    bar_segment = 248;
                    break;

                case 6:
                    bar_segment = 252;
                    break;

                case 7:
                    bar_segment = 254;
                    break;
            }
            bar_height = 0;

            if (i % 2 == 1 && bar_count % 3 == 0)
                bar_segment++;

            oled_write_raw_byte(bar_segment, (i-1) * OLED_DISPLAY_HEIGHT);
        }
    }
}
#else
void oled_render_wpm(void) {
    oled_render_space();
}
static void oled_render_wpm_graph(void) {
    oled_render_space();
}
#endif // WPM_ENABLE

void render_bootmagic_status(bool status) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    if (status) {
        oled_write_ln_P(logo[0][0], false);
        oled_write_ln_P(logo[0][1], false);
    } else {
        oled_write_ln_P(logo[1][0], false);
        oled_write_ln_P(logo[1][1], false);
    }
}

// 5x3 Logos
void oled_render_crkbd_logo(void) {
    static const char PROGMEM font_logo[16] = {0x80, 0x81, 0x82, 0x83, 0x84, 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0};
    oled_write_P(font_logo, false);
};

void oled_render_qmk_logo(void) {
    static const char PROGMEM font_qmk_logo[16] = {0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0};
    oled_write_P(font_qmk_logo, false);
};

void oled_render_kapi_logo(void) {
    static const char PROGMEM font_kapi_logo_1[16] = {0x85, 0x86, 0x87, 0x88, 0x89, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0};
    static const char PROGMEM font_kapi_logo_2[16] = {0x95, 0x96, 0x97, 0x98, 0x99, 0xb5, 0xb6, 0xb7, 0xb8, 0xb9, 0xd5, 0xd6, 0xd7, 0xd8, 0xd9, 0};
    oled_write_P(get_current_wpm() % 2 == 1 ? font_kapi_logo_1 : font_kapi_logo_2, false);
};

void oled_render_idle(void) {
    oled_render_space();
    oled_render_space();
    oled_render_space();
    oled_render_crkbd_logo();
    oled_render_space();
    oled_render_space();
    oled_render_space();
    oled_render_space();
}

void oled_render_master(void) {
    oled_render_layer_state();
    oled_render_separator();

    oled_render_keylog();
    oled_render_separator();

    oled_render_keymods(host_keyboard_leds());
    oled_render_separator();

    oled_render_wpm();
    oled_render_wpm_graph();
}

void oled_render_slave(void) {
    oled_render_crkbd_logo();
    oled_write("crkbd", false);
    oled_render_separator();

    oled_render_hsv();
    oled_render_separator();

    oled_render_kapi_logo();
}

void oled_task_user(void) {
    if (timer_elapsed32(oled_timer) > 360000 && timer_elapsed32(oled_timer) < 480000) {
        // 6mins
        oled_render_idle();
        return;
    }
    else if (timer_elapsed32(oled_timer) > 480000) {
        // 8mins
        oled_off();

        #ifdef RGB_MATRIX_ENABLE
        rgb_matrix_disable();
        #endif // OLED_DRIVER_ENABLE

        return;
    }
    else {
        if (!is_oled_on()) {
            oled_on();

            #ifdef RGB_MATRIX_ENABLE
            rgb_matrix_enable();
            #endif // RGB_MATRIX_ENABLE
        }

        if (is_master) {
            oled_render_master();
        } else {
            oled_render_slave();
        }
    }
}
#endif // OLED_DRIVER_ENABLE
