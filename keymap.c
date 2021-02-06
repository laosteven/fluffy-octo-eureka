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

char wpm_str[15];
char hsv_str[15];
char mod_str[15];
char state_str[30];
char keylog_str[24] = {};
uint16_t wpm_graph_timer = 0;
static uint32_t oled_timer = 0;
enum layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
    KC_ESCAPE,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P, KC_BSLASH,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_CAPS,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_GRAVE,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,KC_MINUS,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                        MO(1), LCTL_T(KC_SPACE), LSFT_T(KC_BSPACE),     RSFT_T(KC_TAB), RCTL_T(KC_ENTER), MO(2)
                                      //`--------------------------'  `--------------------------'
  ),

  [_LOWER] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,KC_EQUAL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                      _______,   KC_UP, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LGUI, _______, _______, _______, _______, _______,                      KC_LEFT, KC_DOWN,KC_RIGHT, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    KC_LSFT, _______, MO(3)
                                      //`--------------------------'  `--------------------------'
  ),

  [_RAISE] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                        KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, KC_LBRACKET,              KC_RBRACKET, _______, _______, _______, _______,  KC_F12,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, KC_LPRN,                      KC_RPRN, _______, _______, _______, KC_VOLD, KC_VOLU,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            MO(3),_______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  [_ADJUST] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        RESET, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, _______, _______,                      _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, _______, _______,                      _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  )
};

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

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

void oled_render_wpm(void) {
    sprintf(wpm_str, "[WPM] %03d ", get_current_wpm());
    oled_write(wpm_str, false);
}

void oled_render_hsv(void) {
    sprintf(hsv_str, "h:%3ds:%3dv:%3d",
        rgb_matrix_get_hue(),
        rgb_matrix_get_sat(),
        rgb_matrix_get_val()
    );
    oled_write(hsv_str, false);
}

void oled_render_keylock(uint8_t led_usb_state) {

    sprintf(mod_str, "num %scap %s",
        led_usb_state & (1 << USB_LED_NUM_LOCK) ? "-" : "+",
        led_usb_state & (1 << USB_LED_CAPS_LOCK) ? "-" : "+"
    );
    oled_write(mod_str, false);
}

#ifdef WPM_ENABLE
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
#endif

void oled_render_separator(void) {
    oled_write_ln("_____", false);
}

void oled_render_space(void) {
    oled_write_ln("     ", false);
}

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

void oled_task_user(void) {
    if (timer_elapsed32(oled_timer) > 380000 && timer_elapsed32(oled_timer) < 480000) {
        oled_render_space();
        oled_render_space();
        oled_render_space();
        oled_render_crkbd_logo();
        oled_render_space();
        oled_render_space();
        oled_render_space();
        oled_render_space();
        return;
    }
    else if (timer_elapsed32(oled_timer) > 480000) {
        // 8mins
        oled_off();
        rgb_matrix_disable();
        return;
    }
    else {
        if (!is_oled_on()) {
            oled_on();
            rgb_matrix_enable();
        }

        if (is_master) {
            oled_render_layer_state();
            oled_render_separator();

            oled_render_keylog();
            oled_render_separator();

            oled_render_keylock(host_keyboard_leds());
            oled_render_separator();

            oled_render_wpm();
            oled_render_wpm_graph();
        } else {
            oled_render_crkbd_logo();
            oled_write("crkbd", false);
            oled_render_separator();

            oled_render_hsv();

            oled_render_separator();
            oled_render_kapi_logo();
        }
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        oled_timer = timer_read32();
        set_keylog(keycode, record);
    }
    return true;
}
#endif // OLED_DRIVER_ENABLE
