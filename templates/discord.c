#pragma once

enum custom_keycodes {
    MONKAS = SAFE_RANGE,
    P_THIEF,
    P_SUS,
    P_HAND,
    POGGER
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.                    ,------------------------------------------------------.
          KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                        MONKAS, P_THIEF,   P_SUS,  P_HAND,  POGGER,   KC_NO,
    //|--------+--------+--------+--------+--------+--------|                    |---------+--------+--------+--------+--------+--------|
          KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                         KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    //|--------+--------+--------+--------+--------+--------|                    |---------+--------+--------+--------+--------+--------|
          KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                         KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                              TT(1),   KC_NO,   KC_NO,      KC_NO,    KC_NO,   TT(2)
                                        //`--------------------------'  `--------------------------'
    ),

    [_LOWER] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.                    ,------------------------------------------------------.
          KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                         KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    //|--------+--------+--------+--------+--------+--------|                    |---------+--------+--------+--------+--------+--------|
          KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                         KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    //|--------+--------+--------+--------+--------+--------|                    |---------+--------+--------+--------+--------+--------|
          KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                         KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            _______, _______, _______,    _______, _______,   MO(3)
                                        //`--------------------------'  `--------------------------'
    ),

    [_RAISE] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.                    ,------------------------------------------------------.
          KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                         KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    //|--------+--------+--------+--------+--------+--------|                    |---------+--------+--------+--------+--------+--------|
          KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                         KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    //|--------+--------+--------+--------+--------+--------|                    |---------+--------+--------+--------+--------+--------|
          KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                         KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                              MO(3), _______, _______,    _______, _______, _______
                                        //`--------------------------'  `--------------------------'
    ),

    [_ADJUST] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.                    ,------------------------------------------------------.
          KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                         KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    //|--------+--------+--------+--------+--------+--------|                    |---------+--------+--------+--------+--------+--------|
          KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                         KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    //|--------+--------+--------+--------+--------+--------|                    |---------+--------+--------+--------+--------+--------|
          KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                         KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            _______, _______, _______,    _______, _______, _______
                                        //`--------------------------'  `--------------------------'
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MONKAS:
            if (record->event.pressed) {
                SEND_STRING(":monkaS:");
            }
            break;

        case P_THIEF:
            if (record->event.pressed) {
                SEND_STRING(":pepethief:");
            }
            break;

        case P_SUS:
            if (record->event.pressed) {
                SEND_STRING(":pepesus:");
            }
            break;

        case P_HAND:
            if (record->event.pressed) {
                SEND_STRING(":PepeHands:");
            }
            break;

        case POGGER:
            if (record->event.pressed) {
                SEND_STRING(":poggers:");
            }
            break;

        default:
            if (record->event.pressed) {
                oled_timer = timer_read32();
                set_keylog(keycode, record);
            }
            break;
    }
    return true;
}
