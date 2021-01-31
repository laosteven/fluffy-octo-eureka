/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

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

#pragma once

#define EE_HANDS

#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

#define OLED_DISABLE_TIMEOUT

#define TAPPING_TERM 200
#define IGNORE_MOD_TAP_INTERRUPT

#ifdef RGBLIGHT_ENABLE
    #undef RGBLED_NUM
    #define RGBLIGHT_ANIMATIONS
    #define RGBLED_NUM 27
    #define RGBLIGHT_LIMIT_VAL 120
    #define RGBLIGHT_HUE_STEP 10
    #define RGBLIGHT_SAT_STEP 17
    #define RGBLIGHT_VAL_STEP 17

    #define RGBLIGHT_EFFECT_RAINBOW_MOOD
#endif

#ifdef RGB_MATRIX_ENABLE
    #define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_RAINBOW_MOVING_CHEVRON
    #define RGB_MATRIX_KEYPRESSES
    #define RGB_MATRIX_FRAMEBUFFER_EFFECTS
    #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150 // limits maximum brightness of LEDs to 150 out of 255. Higher may cause the controller to crash.
    #define RGB_MATRIX_STARTUP_VAL 50
    #define RGB_MATRIX_HUE_STEP 8
    #define RGB_MATRIX_SAT_STEP 8
    #define RGB_MATRIX_VAL_STEP 8
    #define RGB_MATRIX_SPD_STEP 10

    /* Disable the animations you don't want/need.  You will need to disable a good number of these *
    * because they take up a lot of space.  Disable until you can successfully compile your firmware. */
    #define DISABLE_RGB_MATRIX_ALPHAS_MODS
    #define DISABLE_RGB_MATRIX_GRADIENT_UP_DOWN
    #define DISABLE_RGB_MATRIX_BREATHING
    #define DISABLE_RGB_MATRIX_BAND_SAT
    #define DISABLE_RGB_MATRIX_BAND_VAL
    #define DISABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
    #define DISABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
    #define DISABLE_RGB_MATRIX_BAND_SPIRAL_SAT
    #define DISABLE_RGB_MATRIX_BAND_SPIRAL_VAL
    #define DISABLE_RGB_MATRIX_CYCLE_ALL
    #define DISABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
    #define DISABLE_RGB_MATRIX_CYCLE_UP_DOWN
    #define DISABLE_RGB_MATRIX_CYCLE_OUT_IN
    #define DISABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
    // #define DISABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
    #define DISABLE_RGB_MATRIX_CYCLE_PINWHEEL
    #define DISABLE_RGB_MATRIX_DUAL_BEACON
    #define DISABLE_RGB_MATRIX_CYCLE_SPIRAL
    #define DISABLE_RGB_MATRIX_RAINBOW_BEACON
    #define DISABLE_RGB_MATRIX_RAINBOW_PINWHEELS
    #define DISABLE_RGB_MATRIX_RAINDROPS
    #define DISABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
    // #define DISABLE_RGB_MATRIX_TYPING_HEATMAP
    #define DISABLE_RGB_MATRIX_DIGITAL_RAIN
    #define DISABLE_RGB_MATRIX_SOLID_REACTIVE
    #define DISABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
    #define DISABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
    #define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
    #define DISABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
    #define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
    #define DISABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
    #define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
    #define DISABLE_RGB_MATRIX_SPLASH
    // #define DISABLE_RGB_MATRIX_MULTISPLASH
    #define DISABLE_RGB_MATRIX_SOLID_SPLASH
    #define DISABLE_RGB_MATRIX_SOLID_MULTISPLASH
    #define DISABLE_RGB_MATRIX_EFFECT_MAX
#endif

#ifndef NO_DEBUG
    #define NO_DEBUG
#endif // !NO_DEBUG

#if !defined(NO_PRINT) && !defined(CONSOLE_ENABLE)
    #define NO_PRINT
#endif // !NO_PRINT

// #define OLED_FONT_H "keyboards/crkbd/keymaps/lazyproof/glcdfont.c"
// #define OLED_FONT_H "keyboards/crkbd/lib/glcdfont.c"
