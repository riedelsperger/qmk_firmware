/* Copyright 2020 Duckle
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#include "analog.h"
#include "qmk_midi.h"

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _WASD,
    _NUML,
    _DIABLO,
    _DIABLO2,
    _LIGHT,
    _FN
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    WRKACTJOB = SAFE_RANGE,
    WRKVUSJOB
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_WASD] = LAYOUT(
        LT(_FN, KC_ESC),
        KC_Q, KC_W, KC_E,
        KC_A, KC_S, KC_D, KC_F
    ),
    [_NUML] = LAYOUT(
        KC_TRNS,
        KC_1, KC_2, KC_3,
        KC_4, KC_5, KC_6, KC_NLCK
    ),
    [_DIABLO] = LAYOUT(
        KC_TRNS,
        KC_1, KC_2, KC_3,
        KC_LSFT, KC_TAB, OSL(_DIABLO2), KC_Q
    ),
    [_DIABLO2] = LAYOUT(
        KC_TRNS,
        KC_I, KC_F, KC_M,
        KC_S, KC_G,  KC_TRNS, KC_T
    ),
    [_LIGHT] = LAYOUT(
        KC_TRNS,
        RGB_TOG, RGB_MOD, RGB_VAI,
        RGB_VAD, KC_TRNS, KC_TRNS, RESET
    ),
    [_FN] = LAYOUT(
        KC_TRNS,
        TO(_WASD), TO(_NUML), TO(_DIABLO),
        TO(_LIGHT), KC_LALT, KC_TAB, LALT(KC_TAB)
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case WRKACTJOB:
            if (record->event.pressed) {
                SEND_STRING("wrkactjob"SS_TAP(X_RCTRL));
            } else {
            }
            break;
        case WRKVUSJOB:
            if (record->event.pressed) {
                SEND_STRING("wrkvusjob"SS_TAP(X_RCTRL));
            } else {
            }
            break;
    }
    return true;
}

uint8_t divisor = 0;

void slider(void) {
    if (divisor++) { // only run the slider function 1/256 times it's called
        return;
    }

    midi_send_cc(&midi_device, 2, 0x3E, 0x7F - (analogReadPin(SLIDER_PIN) >> 3));
}

void matrix_scan_user(void) {
    slider();
}
