 /* Copyright 2015-2017 Christon DeWan
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
#include "keymap_swiss_fr.h"

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)


/************************************
 * states
 ************************************/

enum layers {
  _DVORAK,
  _LOWER,
  _RAISE,
  _ADJUST,
  _KEYPAD,
  _MOVE,
  _MOUSE
};

enum keymap_keycodes {
  SHRUG,  // ¯\_(ツ)_/¯
  TFLIP,  // (╯°□°)╯︵ ┻━┻
  POOP,   // 💩
  DPOINT, // (ಠ_ಠ)
  STRUT  // ᕕ( ᐛ )ᕗ
};

#define MOVE_Z LT(_MOVE, LSFT(CH_Z))

/************************************
 * keymaps!
 ************************************/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Dvorak
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   '  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  |  /   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc* |   A* |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  | Bksp |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   :  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  |Sft/Ent|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | Mouse| Alt  | GUI  |Lower*|    Space    |Raise*| Altgr| Menu | Ctrl |      |
 * `-----------------------------------------------------------------------------------'
 *
 * - Ctrl acts as Esc when tapped.
 * - Holding ; or z switches to movement layer.
 * - Raise and Lower are one-shot layers.
 * - vim disabled for now (works only on osx)
 */
[_DVORAK] = LAYOUT_planck_mit(
    KC_TAB,         CH_QUOT, CH_COMM,  CH_DOT, CH_P, CH_Y,  CH_F,   CH_G, CH_C, CH_R, CH_L, CH_SLSH,
    LCTL_T(KC_ESC), CH_A,    CH_O,     CH_E,   CH_U, CH_I,  CH_D,   CH_H, CH_T, CH_N, CH_S, KC_BSPC,
    KC_LSFT,        CH_COLN, CH_Q,     CH_J,   CH_K, CH_X,  CH_B,   CH_M, CH_W, CH_V, MOVE_Z,  RSFT_T(KC_ENT),
    KC_LCTL,        TG(_MOUSE), KC_LALT,     KC_LGUI,   LOWER,         KC_SPC,        RAISE,   KC_RALT, KC_APP,  KC_RCTL, XXXXXXX
),


/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |      |   7  |   5  |   3  |   1  |   9  |   0  |   2  |   4  |   6  |   8  |KEYPAD|
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |   `  |   ^  |   ´  |   ¨  |      |      |      |   ç  |      |INSERT|DelWrd|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  | F10  |Sft/Ent|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |    Bksp     |      |      |  F11 | F12  |      |
 * `-----------------------------------------------------------------------------------'
 */

[_LOWER] = LAYOUT_planck_mit(
    _______, CH_7,   CH_5,    CH_3,    CH_1,    CH_9, CH_0,  CH_2,  CH_4,    CH_6,  CH_8,   TG(_KEYPAD),
    _______, CH_GRV, CH_CIRC, CH_ACUT, CH_DIAE, XXXXXXX, XXXXXXX,  XXXXXXX,  CH_CCED, XXXXXXX,  KC_INSERT, LALT(KC_BSPC),
    _______, KC_F1,     KC_F2,      KC_F3,      KC_F4,      KC_F5,   KC_F6,    KC_F7,    KC_F8,      KC_F9,    KC_F10,   _______,
    _______, TO(_DVORAK), _______, _______, _______,           KC_BSPC,        _______,   _______,   KC_F11,   KC_F12,   _______
),

/* Keypad
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |   7  |   8  |   9  |   #  |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |   *  |   4  |   5  |   6  |   -  |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |   /  |   1  |   2  |   3  |   +  |Sft/Ent|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |    Space    |      |   0  |   .  |   =  |      |
 * `-----------------------------------------------------------------------------------'
 */
[_KEYPAD] = LAYOUT_planck_mit(
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     CH_7,  CH_8, CH_9,     CH_HASH,  _______,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, CH_ASTR,  CH_4,  CH_5, CH_6,     CH_MINS,  _______,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, CH_SLSH,  CH_1,  CH_2, CH_3,     CH_PLUS,  _______,
    _______, _______, _______, _______, _______,       _______,        _______,  CH_0, CH_DOT,   CH_EQL,   _______
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   "  |   !  |   #  |   $  |   (  |   )  |   &  |   *  |   %  |   ^  |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |   ~  |   @  |   ?  |   |  |   {  |   [  |   ]  |   }  |   \  |   -  |   =  | DEL  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |   ;  |   °  |      |      |   <  |   >  |      |      |   _  |   +  |Sft/Ent|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      | Bksp |Space |      | Home | PgDn | PgUp | End  |
 * `-----------------------------------------------------------------------------------'
 */

[_RAISE] = LAYOUT_planck_mit(
    CH_GRV,  CH_DQUO,  CH_EXLM, CH_HASH, CH_DLR,  CH_LPRN, CH_RPRN,  CH_AMPR, CH_ASTR, CH_PERC, CH_CIRC, _______,
    CH_TILD, CH_AT,    CH_QUES, CH_PIPE, CH_LCBR, CH_LBRC, CH_RBRC,  CH_RCBR, CH_BSLS, CH_MINS, CH_EQL,  KC_DEL,
    _______, CH_SCLN,  CH_DEG,  XXXXXXX,    XXXXXXX,    CH_LABK, CH_RABK,  XXXXXXX,    XXXXXXX,    CH_UNDS, CH_PLUS, _______,
    _______, TO(_DVORAK), _______,    _______,    _______,           _______,          _______,    KC_HOME,    KC_PGDN,    KC_PGUP,    KC_END
),

/* Adjust (Lower + Raise)
 * ,-------------------------------------------------------------------------------------.
 * |RGBPlain|      | Reset| DEBUG|      |      |      |      |      |      |      |  Del |
 * |--------+------+------+------+------+-------------+------+------+------+------+------|
 * |RGBMode-|      |      |      |PRTSCR|      |      | PLAY | PREV | NEXT |      |Lite+ |
 * |--------+------+------+------+------+------|------+------+------+------+------+------|
 * |RGBMode+|      |SHRUG |TFLIP |Poop  |DPOINT|STRUT | MUTE | Vol- | Vol+ | Play |Lite- |
 * |--------+------+------+------+------+------+------+------+------+------+------+------|
 * |  RGB   | Bail |      |      |      |             |      |      |      | Bail |      |
 * `-------------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_mit(
    RGB_MODE_PLAIN,   XXXXXXX,     QK_BOOT,   DB_TOGG,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     KC_DEL,
    RGB_MODE_REVERSE, XXXXXXX,     XXXXXXX, XXXXXXX, KC_PSCR, XXXXXXX, XXXXXXX, KC_MPLY, KC_MPRV, KC_MNXT, XXXXXXX,     RGB_VAI,
    RGB_MODE_FORWARD, XXXXXXX,     SHRUG,   TFLIP,   POOP,    DPOINT,  STRUT, KC_MUTE, KC_VOLD, KC_VOLU, XXXXXXX,     RGB_VAD,
    RGB_TOG,          TO(_DVORAK), _______, _______, _______,     _______,      _______, _______, _______, TO(_DVORAK), XXXXXXX
),


/* movement layer (hold semicolon)
* ,-------------------------------------------------------------------------------------.
* | Bail   |      |Ctrl← | Up   |Ctrl→ |      |      |      | PgUp |      |      |      |
* |--------+------+------+------+------+-------------+------+------+------+------+------|
* |        |      | Left | Down |Right |      |      | Home | PgDn | End  |      |      |
* |--------+------+------+------+------+------|------+------+------+------+------+------|
* |        |      |      |      |      |      |      |      |      |      |      |      |
* |--------+------+------+------+------+------+------+------+------+------+------+------|
* |        | Bail |      |      |      |             |      |      |      |      | Bail |
* `-------------------------------------------------------------------------------------'
*/
[_MOVE] = LAYOUT_planck_mit(
    TO(_DVORAK), XXXXXXX,      LCTL(KC_LEFT), KC_UP,   LCTL(KC_RIGHT),  XXXXXXX,  XXXXXXX, XXXXXXX, KC_PGUP, XXXXXXX, XXXXXXX,     XXXXXXX,
    _______,     XXXXXXX,      KC_LEFT,       KC_DOWN, KC_RIGHT,        XXXXXXX,  XXXXXXX, KC_HOME, KC_PGDN, KC_END,  XXXXXXX,     XXXXXXX,
    _______,     XXXXXXX,      XXXXXXX,       XXXXXXX, XXXXXXX,         XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     _______,
    _______,     TO(_DVORAK),  _______,       _______,        _______,      XXXXXXX,      _______, _______, _______, TO(_DVORAK), XXXXXXX
),

/* mouse layer
 * ,-------------------------------------------------------------------------------------.
 * | Bail   |      |      | Up   |      |      |WHLEFT|WHDOWN|WHUP  |WHRGHT|      |      |
 * |--------+------+------+------+------+-------------+------+------+------+------+------|
 * |        |      | Left | Down | Right|      |      | BTN1 | BTN2 | BTN3 |      |      |
 * |--------+------+------+------+------+------|------+------+------+------+------+------|
 * |        |      |      |      |      |      |      |      |      |      |      |      |
 * |--------+------+------+------+------+------+------+------+------+------+------+------|
 * |        | Bail |      |      |      |             |      |      |      | Bail |      |
 * `-------------------------------------------------------------------------------------'
 */
[_MOUSE] = LAYOUT_planck_mit(
    TO(_DVORAK), XXXXXXX,     XXXXXXX,    KC_MS_UP,   XXXXXXX,     XXXXXXX, KC_MS_WH_LEFT, KC_MS_WH_DOWN, KC_MS_WH_UP, KC_MS_WH_RIGHT, XXXXXXX,     XXXXXXX,
    _______,     XXXXXXX,     KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT, XXXXXXX, XXXXXXX,       KC_MS_BTN1,    KC_MS_BTN2,  KC_MS_BTN3,     XXXXXXX,     XXXXXXX,
    _______,     XXXXXXX,     XXXXXXX,    XXXXXXX,    XXXXXXX,     XXXXXXX, XXXXXXX,       XXXXXXX,       XXXXXXX,     XXXXXXX,        XXXXXXX,     _______,
    _______,     TO(_DVORAK), _______,    _______,    _______,         XXXXXXX,            _______,       _______,     _______,        TO(_DVORAK), XXXXXXX
)

};


/** Set just LEDs closest to the user. Slightly less annoying to bystanders.*/
// Light 6 to 12 when keyboard layer dvorak is active
const rgblight_segment_t PROGMEM my_dvorak_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 8, HSV_OFF},
    {8, 6, HSV_MAGENTA}
);
const rgblight_segment_t PROGMEM my_lower_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {8, 3, HSV_BLUE},
    {11, 3, HSV_RED}
);
const rgblight_segment_t PROGMEM my_raise_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {8, 3, HSV_BLUE},
    {11, 3, HSV_GREEN}
);
const rgblight_segment_t PROGMEM my_adjust_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {8, 6, HSV_GOLD}
);
const rgblight_segment_t PROGMEM my_move_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {8, 3, HSV_RED},
    {11, 3, HSV_GREEN}
);
const rgblight_segment_t PROGMEM my_mouse_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {8, 3, HSV_RED},
    {11, 3, HSV_PURPLE}
);
const rgblight_segment_t PROGMEM my_keypad_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {8, 3, HSV_PINK},
    {11, 3, HSV_YELLOW}
);

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_dvorak_layer,
    my_lower_layer,    // Overrides other layers
    my_raise_layer,     // Overrides other layers
    my_adjust_layer,    // Overrides other layers
    my_move_layer,      // Overrides other layers
    my_mouse_layer,     // Overrides other layers
    my_keypad_layer     // Overrides other layers
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}

bool led_update_user(led_t led_state) {
    return true;
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _DVORAK));
    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(1, layer_state_cmp(state, _LOWER));
    rgblight_set_layer_state(2, layer_state_cmp(state, _RAISE));
    rgblight_set_layer_state(3, layer_state_cmp(state, _ADJUST));
    rgblight_set_layer_state(4, layer_state_cmp(state, _MOVE));
    rgblight_set_layer_state(5, layer_state_cmp(state, _MOUSE));
    rgblight_set_layer_state(6, layer_state_cmp(state, _KEYPAD));
    state =  update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
    return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
    // case SHRUG:
    //   if (record->event.pressed) {
    //       send_unicode_string("¯\\_(ツ)_/¯");
    //   }
    //   return false;
    // case TFLIP:
    //   if (record->event.pressed) {
    //       send_unicode_string("(╯°□°)╯︵ ┻━┻");
    //   }
    //   return false;
    // case POOP:
    //   if (record->event.pressed) {
    //       send_unicode_string("💩");
    //   }
    //   return false;
    // case DPOINT:
    //   if (record->event.pressed) {
    //       send_unicode_string("(ಠ_ಠ)");
    //   }
    //   return false;
    // case STRUT:
    //   if (record->event.pressed) {
    //       send_unicode_string("ᕕ( ᐛ )ᕗ");
    //   }
    //   return false;
    }
  return true;
}
