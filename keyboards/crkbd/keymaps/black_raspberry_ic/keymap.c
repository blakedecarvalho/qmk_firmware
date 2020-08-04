#include QMK_KEYBOARD_H

//Following line allows macro to read current RGB settings
// extern rgblight_config_t rgblight_config;

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define SPOTLIGHT LGUI(KC_SPC)

enum custom_keycodes {
  LOWER,
  RAISE
};

enum tap_dance_codes {
  TD_COLON,
  TD_QUOT
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_GESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_TAB,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_MINS, KC_SFTENT,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LALT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                      KC_N,   KC_M,     KC_COMM, TD(TD_QUOT), KC_EQL, TD(TD_COLON),\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LCTL, KC_DOT, RAISE,        LOWER,   KC_SPC,  KC_RGUI \
                                      //`--------------------------'  `--------------------------'

  ),

  [_LOWER] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_TRNS, KC_P1,   KC_P2,   KC_P3,   KC_AMPR, KC_QUES,                     KC_BSLS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_TRNS, KC_P4,   KC_P5,   KC_P6,   KC_PIPE, KC_PSLS,                     KC_HASH, KC_AT,   KC_EXLM,  KC_TRNS, KC_TRNS, KC_TRNS,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_TRNS, KC_P7,   KC_P8,   KC_P9,   KC_CIRC, KC_DLR,                      KC_PERC, KC_ASTR, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_TRNS,  KC_P0,  KC_HANJ,   KC_TRNS, KC_TRNS, KC_TRNS \
                                      //`--------------------------'  `--------------------------'
    ),

  [_RAISE] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LCBR, KC_RCBR,                     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_TRNS, KC_TRNS, KC_LBRC, KC_RBRC, KC_LPRN, KC_RPRN,                      KC_LEFT,  KC_DOWN, KC_UP, KC_RGHT, KC_TRNS,  KC_TRNS,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_TRNS, KC_TRNS, KC_LT,  KC_GT,   KC_TRNS, KC_TRNS,                      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_TRNS, KC_TRNS, KC_TRNS,   SPOTLIGHT, KC_TRNS, KC_TRNS \
                                      //`--------------------------'  `--------------------------'
  )
};


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

void suspend_power_down_keymap(void) { rgb_matrix_set_suspend_state(true); }

void suspend_wakeup_init_keymap(void) { rgb_matrix_set_suspend_state(false); }

void matrix_init_user(void) {
    rgb_matrix_sethsv_noeeprom(214, 221, 173);
    rgb_matrix_mode(RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE);
}

void dance_quote_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code(KC_QUOT);
    } else {
        register_code16(KC_DQUO);
    }
}

void dance_quote_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code(KC_QUOT);
    } else {
        unregister_code16(KC_DQUO);
    }
}

void dance_colon_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code(KC_SCLN);
    } else {
        register_code16(KC_COLN);
    }
}

void dance_colon_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code(KC_SCLN);
    } else {
        unregister_code16(KC_COLN);
    }
}

// All tap dance functions would go here. Only showing this one.
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_COLON] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_colon_finished, dance_colon_reset),
    [TD_QUOT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_quote_finished, dance_quote_reset)
};
