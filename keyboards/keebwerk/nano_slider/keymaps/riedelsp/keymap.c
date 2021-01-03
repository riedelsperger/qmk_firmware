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
    _ARROW,
    _PAGE,
    _TKL,
    _FKT,
    _DIABLO,
    _MACROS,
    _EMPTY,
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
    [_ARROW] = LAYOUT(
        LT(_FN, KC_ESC),
        KC_HOME,    KC_UP,      KC_END,
        KC_LEFT,    KC_DOWN,    KC_RIGHT,    TG(_PAGE)
    ),
    [_PAGE] = LAYOUT(
        KC_TRNS,
        KC_PGUP, KC_TRNS, KC_PGDOWN,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [_TKL] = LAYOUT(
        KC_TRNS,
        KC_INSERT, KC_HOME, KC_PGUP,
        KC_DELETE, KC_END,  KC_PGDOWN, KC_PSCREEN
    ),
    [_FKT] = LAYOUT(
        KC_TRNS,
        KC_F9, KC_F10, KC_F11,
        KC_F4, KC_F5,  KC_F6,  KC_F12
    ),
    [_DIABLO] = LAYOUT(
        KC_TRNS,
        KC_1, KC_2, KC_3,
        LSFT_T(KC_Q), KC_TAB, KC_T, KC_4
    ),
    [_LIGHT] = LAYOUT(
        KC_TRNS,
        RGB_TOG, RGB_MOD, RGB_VAI,
        RGB_VAD, KC_TRNS, KC_TRNS, RESET
    ),
    [_EMPTY] = LAYOUT(
        KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [_MACROS] = LAYOUT(
        KC_TRNS,
        KC_F4, KC_F3, KC_F12,
        WRKACTJOB, WRKVUSJOB, KC_F17, KC_RCTRL
    ),
    [_FN] = LAYOUT(
        KC_TRNS,
        TO(_TKL), TO(_FKT), TO(_DIABLO),
        TO(_LIGHT), TO(_EMPTY), TO(_MACROS), TO(_ARROW)
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
