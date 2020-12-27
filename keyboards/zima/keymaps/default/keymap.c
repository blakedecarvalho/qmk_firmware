/* Copyright 2019 Thomas Baart
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

// Defines the keycodes used by our macros in process_record_user
// enum custom_keycodes { QMKBEST = SAFE_RANGE, QMKURL };

enum custom_keycodes {
    HS_PCB = SAFE_RANGE,
    HS_CASE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(/* Base */
                 KC_MUTE,  LCTL(KC_R),  KC_KP_2,
                 KC_MEDIA_PREV_TRACK,  KC_MEDIA_PLAY_PAUSE,  KC_MEDIA_NEXT_TRACK,
                 LCTL(KC_G),   LCTL(KC_H),  LCTL(KC_T),
                 LCTL(KC_B),  LCTL(KC_N),  LCTL(KC_Y))
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case HS_PCB:
            if (record->event.pressed) {
                SEND_STRING("853400");
            } else {
            }
            break;
        case HS_CASE:
            if (record->event.pressed) {
                SEND_STRING("847160");
            } else {
            }
            break;
    }
    return true;
}

#ifdef RGBLIGHT_ENABLE
void keyboard_post_init_user(void) {
  rgblight_enable_noeeprom(); // Enables RGB, without saving settings
  rgblight_sethsv_noeeprom(33, 252, 200);
  rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
}
#endif

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
	return OLED_ROTATION_180;
}

static void oled_draw(void) {
  oled_write_P(PSTR("~ ~ deetee! ~ ~"), false);
}

void oled_task_user(void) {
    oled_draw();
}
#endif

void matrix_init_user(void) {}

void matrix_scan_user(void) {}

void led_set_user(uint8_t usb_led) {}

#ifdef ENCODER_ENABLE
void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        // Move whole words. Hold shift to select while moving.
        if (clockwise) {
            tap_code16(KC_VOLU);
        } else {
            tap_code16(KC_VOLD);
        }
    }
}
#endif
