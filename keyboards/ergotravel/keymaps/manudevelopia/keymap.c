#include QMK_KEYBOARD_H

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2

#define _ADJUST 16

#define KC_CUT   G(KC_X)
#define KC_COPY  G(KC_C)
#define KC_PASTE G(KC_V)
#define KC_UNDO  G(KC_Z)
#define KC_FIND  G(KC_F)
#define ALFRED   G(KC_SPC)

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
};

#define CALTDEL  LCTL(LALT(KC_DEL))
#define TSKMGR LCTL(LSFT(KC_ESC ))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT(
  //,--------+--------+--------+--------+--------+--------+--------.       ,--------+--------+--------+--------+--------+--------+--------.
     KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_MINS,         KC_EQL,  KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
  //|--------+--------+--------+--------+--------+--------+--------|       |--------+--------+--------+--------+--------+--------+--------|
     KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_LBRC,         KC_RBRC, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------+--------|       |--------+--------+--------+--------+--------+--------+--------|
     KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_SPC,          KC_ENT,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_SFTENT,
  //|--------+--------+--------+--------+--------+--------+--------|       |--------+--------+--------+--------+--------+--------+--------|
     RAISE  , KC_LCTL, KC_LALT, KC_LGUI, LOWER,            KC_SPC,          KC_ENT,           RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
  //`--------+--------+--------+--------+--------+--------+--------/       \--------+--------+--------+--------+--------+--------+--------'
  ),

  [_LOWER] = LAYOUT(
     KC_GRV,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, _______,        _______, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN,  KC_RPRN, KC_DEL,
     _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______,        _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,  _______, KC_BSLS,
     _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_BSPC,        ALFRED,  KC_F11,  KC_F12,  KC_COPY, KC_PASTE, KC_FIND, _______,
     _______, _______,  _______, _______, _______,         KC_BSPC,        ALFRED,           ADJUST,  KC_HOME, KC_PGDN,  KC_PGUP, KC_END
  ),

  [_RAISE] = LAYOUT(
     KC_TILD, KC_1,     KC_2,    KC_3,    KC_COMM, KC_DOT,  _______,       KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_BSPC,
     _______, KC_4,     KC_5,    KC_6,    KC_PAST, KC_PSLS, _______,       KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,
     _______, KC_7,     KC_8,    KC_9,    _______, _______, ALFRED,        KC_BSPC, KC_VOLD, KC_VOLU, KC_MUTE, _______, _______, _______,
     _______, _______,  KC_0,    _______, _______,          ALFRED,        KC_BSPC,          _______, KC_MPRV, KC_MSTP, KC_MPLY, KC_MNXT
  ),

  [_ADJUST] = LAYOUT(
     RESET,   _______, _______, _______, _______, _______, KC_ASDN,        KC_ASUP,  _______, RGB_MOD,  RGB_VAI, RGB_SAI, RGB_HUI, KC_PWR,
     _______, _______, _______, _______, _______, _______, KC_ASON,        KC_ASOFF, _______, RGB_RMOD, RGB_VAD, RGB_SAD, RGB_HUD, RGB_TOG,
     _______, _______, _______, _______, _______, KC_ASRP, _______,        _______,  KC_ASTG, _______,  _______, _______, _______, KC_ASRP,
     _______, _______, _______, _______, _______,          _______,        _______,  _______, KC_ASRP, KC_ASDN, KC_ASUP, KC_ASTG
  )

};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
  }
  return true;
}
