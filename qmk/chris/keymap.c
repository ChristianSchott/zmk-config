#include QMK_KEYBOARD_H

enum custom_keycodes {
    CKC_RTB = SAFE_RANGE,
    CKC_LTB = SAFE_RANGE + 1,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {[0] = LAYOUT_split_3x5_2(KC_Q, KC_W, KC_F, KC_P, KC_B, KC_J, KC_L, KC_U, KC_Y, KC_BSPC, KC_A, KC_R, KC_S, KC_T, KC_G, KC_M, KC_N, KC_E, KC_I, KC_O, KC_Z, KC_X, KC_C, KC_D, KC_V, KC_K, KC_H, KC_TAB, LALT_T(KC_GRV), KC_ENT, CKC_LTB, KC_SPC, OSL(1), CKC_RTB),
                                                              [1] = LAYOUT_split_3x5_2(KC_TILD, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_AMPR, KC_ASTR, KC_LCBR, KC_RCBR, KC_CIRC, KC_QUES, KC_EXLM, KC_COMM, KC_DOT, KC_DQUO, KC_UNDS, KC_EQL, KC_LPRN, KC_RPRN, KC_COLN, KC_SLSH, KC_PIPE, KC_LT, KC_GT, KC_QUOT, KC_MINS, KC_PLUS, KC_LBRC, KC_RBRC, KC_SCLN, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
                                                              [2] = LAYOUT_split_3x5_2(KC_LALT, KC_7, KC_8, KC_9, KC_ESC, KC_SPC, KC_TAB, KC_INS, KC_DEL, KC_BSPC, KC_LSFT, KC_4, KC_5, KC_6, KC_0, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_ESC, KC_LCTL, KC_1, KC_2, KC_3, KC_LGUI, KC_HOME, KC_PGDN, KC_PGUP, KC_END, KC_ENT, KC_TRNS, KC_TRNS, KC_TRNS, MO(4)),
                                                              [3] = LAYOUT_split_3x5_2(KC_LALT, KC_F7, KC_F8, KC_F9, KC_F10, KC_PSCR, KC_MUTE, KC_VOLD, KC_VOLU, KC_BSPC, KC_LSFT, KC_F4, KC_F5, KC_F6, KC_F11, RALT(KC_5), RALT(KC_Q), RALT(KC_P), RALT(KC_Y), RALT(KC_S), KC_LCTL, KC_F1, KC_F2, KC_F3, KC_F12, KC_BSLS, KC_CAPS, KC_COMM, KC_DOT, KC_ENT, MO(4), KC_TRNS, KC_TRNS, KC_TRNS),
                                                              [4] = LAYOUT_split_3x5_2(KC_TRNS, KC_TRNS, KC_SCRL, KC_NUM, KC_TRNS, KC_TRNS, KC_WH_D, KC_MS_U, KC_WH_U, KC_TRNS, KC_TRNS, KC_BTN3, KC_BTN2, KC_BTN1, KC_TRNS, KC_WH_L, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_R, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)

};

static uint8_t ltb_state = 0;
#define LTB_LAYER 2
static uint8_t rtb_state = 0;
#define RTB_LAYER 3

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    {
        static uint32_t tap_deadline = 0;
        if (keycode == CKC_LTB) {
            if (record->event.pressed) {
                if (ltb_state == 2 && !timer_expired32(timer_read32(), tap_deadline)) {
                    del_oneshot_mods(MOD_LCTL);
                    register_mods(MOD_LCTL);
                    ltb_state = 3;
                } else {
                    tap_deadline = timer_read32() + 250;
                    layer_on(LTB_LAYER);
                    ltb_state = 1;
                }
            } else {
                if (ltb_state == 1) {
                    layer_off(LTB_LAYER);
                    if (!timer_expired32(timer_read32(), tap_deadline)) {
                        add_oneshot_mods(MOD_LCTL);
                        ltb_state = 2;
                    }
                } else if (ltb_state == 3) {
                    unregister_mods(MOD_LCTL);
                }
            }
        } else {
            if (ltb_state == 1) {
                tap_deadline = 0;
            }
        }
    }

    {
        static uint32_t tap_deadline = 0;
        if (keycode == CKC_RTB) {
            if (record->event.pressed) {
                if (rtb_state == 2 && !timer_expired32(timer_read32(), tap_deadline)) {
                    del_oneshot_mods(MOD_LSFT);
                    register_mods(MOD_LSFT);
                    rtb_state = 3;
                } else {
                    tap_deadline = timer_read32() + 250;
                    layer_on(RTB_LAYER);
                    rtb_state = 1;
                }
            } else {
                if (rtb_state == 1) {
                    layer_off(RTB_LAYER);
                    if (!timer_expired32(timer_read32(), tap_deadline)) {
                        add_oneshot_mods(MOD_LSFT);
                        rtb_state = 2;
                    }
                } else if (rtb_state == 3) {
                    unregister_mods(MOD_LSFT);
                }
            }
        } else {
            if (ltb_state == 1) {
                tap_deadline = 0;
            }
        }
    }

    return true;
}

// void post_process_record_user(uint16_t keycode, keyrecord_t* record) {
//   if (keycode != CKC_LTB && ltb_state == ) {
//     layer_off(LTB_LAYER);
// 	ltb_state=0;
//   }
// }
