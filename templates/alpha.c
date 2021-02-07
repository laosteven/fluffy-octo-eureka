#pragma once

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_split_3x6_3(),
    [_LOWER] = LAYOUT_split_3x6_3(),
    [_RAISE] = LAYOUT_split_3x6_3(),
    [_ADJUST] = LAYOUT_split_3x6_3(),
};
