#include QMK_KEYBOARD_H
enum {
    TD_ESC_CAPS, TD_8_L1
};

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_ESC_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_P6, KC_P5),
    [TD_8_L1] = ACTION_TAP_DANCE_LAYER_MOVE(KC_P8, 1),
};

enum { DEFAULT, LOWER, RAISE, ADJUST };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┐
     * │ 7 │ 8 │ 9 │ / │───┐
     * ├───┼───┼───┼───┤   │
     * │ 0 │ . │Ent│ + │───┘
     * └───┴───┴───┴───┘
     */
    [DEFAULT] = LAYOUT_ortho_2x4(
        RESET,        KC_MPRV,   KC_MPLY,  KC_MNXT,   _______,
        LT(1, KC_A),  KC_P7,     KC_B,     KC_P9,     LT(1, KC_MUTE)
    ),

    [LOWER] = LAYOUT_ortho_2x4(
        RESET,   KC_P2,   KC_P3, KC_P4, _______,
        KC_P6,  KC_VOLU,  KC_B,   KC_P9, QK_BOOT
    )
};


bool encoder_update_user(uint8_t index, bool clockwise) {
    if (IS_LAYER_ON(DEFAULT)) {
        if (clockwise) {
            tap_code_delay(KC_VOLU, 10);
        } else {
            tap_code_delay(KC_VOLD, 10);
        }
    } else if (IS_LAYER_ON(RAISE)){
        if (clockwise) {
            tap_code_delay(KC_U, 10);
        } else {
            tap_code_delay(KC_D, 10);
        }
    }
    return false;
}