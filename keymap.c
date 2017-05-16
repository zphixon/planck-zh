#include "planck.h"
#include "action_layer.h"
#include "eeconfig.h"
#include "audio.h"

extern keymap_config_t keymap_config;

#define _______ KC_TRNS
#define XXXXXXX KC_NO

// normal layers
#define __COLEMAK 0
#define __QWERTY 1
#define __LOWER 2
#define __RAISE 3
#define __GAME 4
#define __SPIN 5
#define __FLAP 6

// tri-layers
#define __SCREW 15
#define __ROLL 16

// macros
enum planck_macros {
    CAPREG = 2,
    CAPWIN = 3,
    CAPREC = 4,
    CAPSCR = 5,
    VMEXIT = 6,
    LAYOUT = 7,
};

#define _CAPREG M(CAPREG)
#define _CAPWIN M(CAPWIN)
#define _CAPREC M(CAPREC)
#define _CAPSCR M(CAPSCR)
#define _VMEXIT M(VMEXIT)
#define _LAYOUT M(LAYOUT)

// normal layers
enum planck_keycodes {
    COLEMAK = SAFE_RANGE,
    QWERTY,
    LOWER,
    RAISE,
    SPIN,
    FLAP,
};

// layer maps
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    // colemak layer, default
    [__COLEMAK] = {
      {KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC},
      {KC_ESC,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT},
      {KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT },
      {KC_LCTL, SPIN,    KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   _LAYOUT, XXXXXXX, XXXXXXX, FLAP   }
    },

    // qwerty layout for vim/programming
    [__QWERTY] = {
      {KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC},
      {KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT},
      {KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT },
      {KC_LCTL, SPIN,    KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   _LAYOUT, XXXXXXX, XXXXXXX, FLAP   }
    },

    // lower: symbols, arrows, mouse movement
    [__LOWER] = {
      {KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______},
      {_______, KC_PSCR, KC_INS,  KC_HOME, KC_END,  _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, KC_BSLS},
      {_______, _______, _______, _______, _______, _______, _______, _______, KC_BTN1, KC_MS_U, KC_BTN2, KC_WH_U},
      {_______, _______, _______, _______, _______, _______, _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D}
    },

    // raise: ()[]{}, numbers, misc movement
    [__RAISE] = {
      {S(KC_GRV),KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_MINS, KC_EQL,  _______},
      {_______,  _______, KC_LCBR, KC_LBRC, KC_LPRN, _______, _______, KC_RPRN, KC_RBRC, KC_RCBR, _______, _______},
      {_______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
      {_______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
    },

    // roll: macros for sharex screen capture, virtualbox management, audio
    [__ROLL] = {
      {RESET,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL },
      {_______, _CAPREC, _CAPWIN, _CAPSCR, _CAPREG, _______, _______, _VMEXIT, AU_ON,   AU_OFF,  _______, _______},
      {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
      {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
    },

    // spin: number pad
    [__SPIN] = {
      {_______, _______, _______, _______, _______, _______, KC_NLCK, KC_7,    KC_8,    KC_9,    KC_PMNS, _______},
      {_______, _______, _______, _______, _______, _______, _______, KC_4,    KC_5,    KC_6,    KC_PPLS, _______},
      {_______, _______, _______, _______, _______, _______, _______, KC_1,    KC_2,    KC_3,    KC_PAST, KC_PENT},
      {_______, _______, _______, _______, _______, _______, _______, KC_0,    KC_0,    KC_DOT,  KC_PSLS, _______}
    },

    // flap: function keys
    [__FLAP] = {
      {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL },
      {_______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   _______, _______, _______, _______, _______},
      {_______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, _______, _______, _______},
      {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
    },

    // screw: there's really no reason why this should exist
    [__SCREW] = {
      {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
      {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
      {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
      {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
    },

    // there's room for more tri-layers but I think I have enough
};

// keep track of current layout
// TODO: move to the actual layout numbers/some sort of bit flags
#define CM_LAYOUT 0
#define QT_LAYOUT 1
static int current_layout = CM_LAYOUT;

// set default layer
void persistant_default_layer_set(uint16_t default_layer) {
    eeconfig_update_default_layer(default_layer);
    default_layer_set(default_layer);
}

// little jingles for switching layouts, copied from default layout
float tone_qwerty[][2] = SONG(QWERTY_SOUND);
float tone_colemak[][2] = SONG(COLEMAK_SOUND);

// macros
const macro_t* action_get_macro(keyrecord_t* record, uint8_t id, uint8_t opt) {
    switch (id) {
    // switch layout: not technically a macro, but it needs to be here since
    // the other function is just for momentary key presses
    // I'm sure there's a better way to do this other than
    // defining a macro, but whatever
    case LAYOUT:
        if (record->event.pressed) {
            if (current_layout == CM_LAYOUT) {
                current_layout = QT_LAYOUT;
                persistant_default_layer_set(1UL<<__QWERTY);
                PLAY_NOTE_ARRAY(tone_qwerty, false, 0);
            } else {
                current_layout = CM_LAYOUT;
                persistant_default_layer_set(1UL<<__COLEMAK);
                PLAY_NOTE_ARRAY(tone_colemak, false, 0);
            }
            return MACRO_NONE;
        }
        break;

    // exit virtualbox fullscreen
    case VMEXIT:
        if (record->event.pressed) {
            return MACRO( I(50), D(F12), T(F), U(F12), END );
        }
        break;

    // sharex macros
    case CAPWIN:
        // capture window with sharex
        if (record->event.pressed) {
            return MACRO( I(50), D(LALT), T(END), U(LALT), END );
        }
        break;
    case CAPREC:
        // record screen with sharex
        if (record->event.pressed) {
            return MACRO( I(50), D(LALT), T(HOME), U(LALT), END );
        }
        break;
    case CAPSCR:
        // screenie with sharex
        if (record->event.pressed) {
            return MACRO( I(50), D(LCTL), T(HOME), U(LCTL), END );
        }
        break;
    case CAPREG:
        // capture region with sharex
        if (record->event.pressed) {
            return MACRO( I(50), D(LCTL), T(END), U(LCTL), END );
        }
        break;
    }
    return MACRO_NONE;
}

// function layers
bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
    case FLAP:
        if (record->event.pressed) {
            layer_on(__FLAP);
            update_tri_layer(__SPIN, __FLAP, __SCREW);
        } else {
            layer_off(__FLAP);
            update_tri_layer(__SPIN, __FLAP, __SCREW);
        }
        return false;
        break;
    case SPIN:
        if (record->event.pressed) {
            layer_on(__SPIN);
            update_tri_layer(__SPIN, __FLAP, __SCREW);
        } else {
            layer_off(__SPIN);
            update_tri_layer(__SPIN, __FLAP, __SCREW);
        }
        return false;
        break;
    case LOWER:
        if (record->event.pressed) {
            layer_on(__LOWER);
            update_tri_layer(__LOWER, __RAISE, __ROLL);
        } else {
            layer_off(__LOWER);
            update_tri_layer(__LOWER, __RAISE, __ROLL);
        }
        return false;
        break;
    case RAISE:
        if (record->event.pressed) {
            layer_on(__RAISE);
            update_tri_layer(__LOWER, __RAISE, __ROLL);
        } else {
            layer_off(__RAISE);
            update_tri_layer(__LOWER, __RAISE, __ROLL);
        }
        return false;
        break;
    }
    return true;
}

void matrix_init_user(void) {}

const uint16_t PROGMEM fn_actions[] = {};

