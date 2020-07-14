#include QMK_KEYBOARD_H

//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2

enum custom_keycodes {
  LOWER,
  RAISE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_GESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_TAB,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_MINS, KC_SFTENT,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LALT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_QUOT, KC_EQL, KC_SCLN,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LCTL,   RAISE,  KC_DOT,     KC_SPC,  LOWER,  KC_RGUI \
                                      //`--------------------------'  `--------------------------'

  ),

  [_LOWER] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_TRNS, KC_P1,   KC_P2,   KC_P3,   KC_AMPR, KC_QUES,                     KC_BSLS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_BSPC,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_TRNS, KC_P4,   KC_P5,   KC_P6,   KC_PIPE, KC_PSLS,                     KC_HASH, KC_AT,   KC_EXLM,  KC_TRNS, KC_TRNS, KC_TRNS,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_TRNS, KC_P7,   KC_P8,   KC_P9,   KC_CIRC, KC_DLR,                      KC_PERC, KC_ASTR, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_TRNS,  KC_P0,  KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS \
                                      //`--------------------------'  `--------------------------'
    ),

  [_RAISE] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LCBR, KC_RCBR,                     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_GRV, KC_TRNS, KC_LBRC, KC_RBRC, KC_LPRN, KC_RPRN,                      KC_LEFT,  KC_DOWN, KC_UP, KC_RGHT, KC_TRNS,  KC_TRNS,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, KC_TRNS, KC_LT,  KC_GT,   KC_TRNS, KC_TRNS,                      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS \
                                      //`--------------------------'  `--------------------------'
  )
};

void matrix_init_user(void) {
  sethsv(HSV_WHITE, (LED_TYPE *)&led[0]); // led 0
  sethsv(HSV_RED,   (LED_TYPE *)&led[1]); // led 1
  sethsv(HSV_GREEN, (LED_TYPE *)&led[2]); // led 2
  rgblight_set(); // Utility functions do not call rgblight_set() automatically, so they need to be called explicitly.
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
      } else {
        layer_off(_LOWER);
      }
      return false;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
      } else {
        layer_off(_RAISE);
      }
      return false;
  }
  return true;
}
