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
#include "xtonhasvim.h"
#include "fancylighting.h"
#include "keymap_extras/keymap_fr_ch.h"


/************************************
 * states
 ************************************/

enum layers {
  _DVORAK,
  _LOWER,
  _RAISE,
  _KEYPAD,
  _ADJUST,
  _MOVE,
  _MOUSE,
  _CMD
};

extern uint8_t vim_cmd_layer(void) { return _CMD; }

enum keymap_keycodes {
  RAISE = VIM_SAFE_RANGE,
  LOWER,
  SHRUG,  // ¯\_(ツ)_/¯
  TFLIP,  // (╯°□°)╯︵ ┻━┻
  POOP,   // 💩
  DPOINT, // (ಠ_ಠ)
  STRUT  // ᕕ( ᐛ )ᕗ
};

#define MOVE_COLN LT(_MOVE, LSFT(FR_CH_COLN))
#define MOVE_Z LT(_MOVE, LSFT(FR_CH_Z))

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
 * | Shift|   :  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | Mouse| Alt  | GUI  |Lower*|    Space    |Raise*| Altgr| Menu | Ctrl | Vim  |
 * `-----------------------------------------------------------------------------------'
 *
 * - Ctrl acts as Esc when tapped.
 * - Holding ; or z switches to movement layer.
 * - Raise and Lower are one-shot layers.
 * - vim disabled for now (works only on osx)
 */
[_DVORAK] = LAYOUT_planck_mit(
    KC_TAB,         FR_CH_QUOT, FR_CH_COMM,  FR_CH_DOT, FR_CH_P, FR_CH_Y,  FR_CH_F,   FR_CH_G, FR_CH_C, FR_CH_R, FR_CH_L, FR_CH_SLSH,
    LCTL_T(KC_ESC), FR_CH_A,    FR_CH_O,     FR_CH_E,   FR_CH_U, FR_CH_I,  FR_CH_D,   FR_CH_H, FR_CH_T, FR_CH_N, FR_CH_S, KC_BSPC,
    KC_LSFT,        FR_CH_COLN, FR_CH_Q,     FR_CH_J,   FR_CH_K, FR_CH_X,  FR_CH_B,   FR_CH_M, FR_CH_W, FR_CH_V, MOVE_Z,  RSFT_T(KC_ENT),
    KC_LCTL,        TG(_MOUSE), KC_LALT,     KC_LGUI,   LOWER,         KC_SPC,        RAISE,   KC_RALT, KC_APP,  KC_RCTL, X_____X
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
    _______, FR_CH_7,   FR_CH_5,    FR_CH_3,    FR_CH_1,    FR_CH_9, FR_CH_0,  FR_CH_2,  FR_CH_4,    FR_CH_6,  FR_CH_8,   TG(_KEYPAD),
    _______, FR_CH_GRV, FR_CH_CIRC, FR_CH_ACUT, FR_CH_DIAE, X_____X, X_____X,  X_____X,  FR_CH_CCED, X_____X,  KC_INSERT, LALT(KC_BSPC),
    _______, KC_F1,     KC_F2,      KC_F3,      KC_F4,      KC_F5,   KC_F6,    KC_F7,    KC_F8,      KC_F9,    KC_F10,   FIREY_RETURN,
    _______, TO(_DVORAK), _______, _______, _______,           KC_BSPC,        _______,   _______,   KC_F11,   KC_F12,   X_____X
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
    _______, X_____X, X_____X, X_____X, X_____X, X_____X, X_____X,     FR_CH_7,  FR_CH_8, FR_CH_9,     FR_CH_HASH,  _______,
    _______, X_____X, X_____X, X_____X, X_____X, X_____X, FR_CH_ASTR,  FR_CH_4,  FR_CH_5, FR_CH_6,     FR_CH_MINS,  _______,
    _______, X_____X, X_____X, X_____X, X_____X, X_____X, FR_CH_SLSH,  FR_CH_1,  FR_CH_2, FR_CH_3,     FR_CH_PLUS,  _______,
    _______, _______, _______, _______, _______,       _______,        _______,  FR_CH_0, FR_CH_DOT,   FR_CH_EQL,   _______
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   "  |   !  |   #  |   $  |   (  |   )  |   &  |   *  |   %  |   ^  |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |   ~  |   @  |   ?  |   |  |   {  |   [  |   ]  |   }  |   \  |   -  |   =  | DEL  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |   °  |   ;  |      |      |      |   <  |   >  |      |      |   _  |   +  |Sft/Ent|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      | Bksp |Space |      | Home | PgDn | PgUp | End  |
 * `-----------------------------------------------------------------------------------'
 */

[_RAISE] = LAYOUT_planck_mit(
    FR_CH_GRV,  FR_CH_DQOT,  FR_CH_EXLM, FR_CH_HASH, FR_CH_DLR,  FR_CH_LPRN, FR_CH_RPRN,  FR_CH_AMPR, FR_CH_ASTR, FR_CH_PERC, FR_CH_CIRC, _______,
    FR_CH_TILD, FR_CH_AT,    FR_CH_QST,  FR_CH_PIPE, FR_CH_LCBR, FR_CH_LBRC, FR_CH_RBRC,  FR_CH_RCBR, FR_CH_BSLS, FR_CH_MINS, FR_CH_EQL,  KC_DEL,
    FR_CH_RING, FR_CH_SCLN,  X_____X,    X_____X,    X_____X,    FR_CH_LESS, FR_CH_MORE,  X_____X,    X_____X,    FR_CH_UNDS, FR_CH_PLUS, FIREY_RETURN,
    _______,    TO(_DVORAK), _______,    _______,    _______,           _______,          _______,    KC_HOME,    KC_PGDN,    KC_PGUP,    KC_END
),

/* Adjust (Lower + Raise)
 * ,-------------------------------------------------------------------------------------.
 * |RGBPlain|      | Reset| DEBUG|      |      |      |      |      |      |      |  Del |
 * |--------+------+------+------+------+-------------+------+------+------+------+------|
 * |RGBMode-|      |      |      |      |      |      |      | PREV | NEXT |      |Lite+ |
 * |--------+------+------+------+------+------|------+------+------+------+------+------|
 * |RGBMode+|      |SHRUG |TFLIP |Poop  |DPOINT|STRUT | MUTE | Vol- | Vol+ | Play |Lite- |
 * |--------+------+------+------+------+------+------+------+------+------+------+------|
 * |  RGB   | Bail |      |      |      |             |      |      |      | Bail |      |
 * `-------------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_mit(
    RGB_MODE_PLAIN,   X_____X,     RESET,   DEBUG,   X_____X, X_____X, X_____X, X_____X, X_____X, X_____X, X_____X,     KC_DEL,
    RGB_MODE_REVERSE, X_____X,     X_____X, X_____X, X_____X, X_____X, X_____X, KC_MPLY, KC_MPRV, KC_MNXT, X_____X,     RGB_VAI,
    RGB_MODE_FORWARD, X_____X,     SHRUG,   TFLIP,   POOP,    DPOINT,  STRUT, KC_MUTE, KC_VOLD, KC_VOLU, X_____X,     RGB_VAD,
    RGB_TOG,          TO(_DVORAK), _______, _______, _______,     _______,      _______, _______, _______, TO(_DVORAK), X_____X
),


/* movement layer (hold semicolon)
* ,-------------------------------------------------------------------------------------.
* | Bail   |      |Ctrl← | Up   |Ctrl→ |      |      |      | PgUp |      |      |      |
* |--------+------+------+------+------+-------------+------+------+------+------+------|
* |        |      | Left | Down |Right |      |      | Home |      | End  |      |      |
* |--------+------+------+------+------+------|------+------+------+------+------+------|
* |        |      |      |      |      |      |      |      | PgDn |      |      |      |
* |--------+------+------+------+------+------+------+------+------+------+------+------|
* |        | Bail |      |      |      |             |      |      |      |      | Bail |
* `-------------------------------------------------------------------------------------'
*/
[_MOVE] = LAYOUT_planck_mit(
    TO(_DVORAK), X_____X,      LCTL(KC_LEFT), KC_UP,   LCTL(KC_RIGHT),  X_____X,  X_____X, X_____X, KC_PGUP, X_____X, X_____X,     X_____X,
    _______,     X_____X,      KC_LEFT,       KC_DOWN, KC_RIGHT,        X_____X,  X_____X, KC_HOME, X_____X, KC_END,  X_____X,     X_____X,
    _______,     X_____X,      X_____X,       X_____X, X_____X,         X_____X,  X_____X, X_____X, KC_PGDN, X_____X, X_____X,     _______,
    _______,     TO(_DVORAK),  _______,       _______,        _______,      X_____X,      _______, _______, _______, TO(_DVORAK), X_____X
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
    TO(_DVORAK), X_____X,     X_____X,    KC_MS_UP,   X_____X,     X_____X, KC_MS_WH_LEFT, KC_MS_WH_DOWN, KC_MS_WH_UP, KC_MS_WH_RIGHT, X_____X,     X_____X,
    _______,     X_____X,     KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT, X_____X, X_____X,       KC_MS_BTN1,    KC_MS_BTN2,  KC_MS_BTN3,     X_____X,     X_____X,
    _______,     X_____X,     X_____X,    X_____X,    X_____X,     X_____X, X_____X,       X_____X,       X_____X,     X_____X,        X_____X,     _______,
    _______,     TO(_DVORAK), _______,    _______,    _______,         X_____X,            _______,       _______,     _______,        TO(_DVORAK), X_____X
),

/* vim command layer.
 */
[_CMD] = LAYOUT_planck_mit(
    X_____X,   X_____X,     VIM_COMMA, VIM_PERIOD, VIM_P,   VIM_Y,   X_____X, VIM_G,   VIM_C,     X_____X,   VIM_L,       X_____X,
    VIM_ESC,   VIM_A,       VIM_O,     VIM_E,      VIM_U,   VIM_I,   VIM_D,   VIM_H,   X_____X,   X_____X,   VIM_S,       X_____X,
    VIM_SHIFT, X_____X,     X_____X,   VIM_J,      VIM_K,   VIM_X,   VIM_B,   X_____X, VIM_W,     VIM_V,     X_____X,     VIM_SHIFT,
    _______,   TO(_DVORAK), _______,   _______,    X_____X,      X_____X,     X_____X, _______,   _______,   TO(_DVORAK), X_____X
)

};

#define C_RED 0xFF, 0x00, 0x00
#define C_GRN 0x00, 0xFF, 0x00
#define C_BLU 0x00, 0x00, 0xFF

#define C_YAN 0x00, 0xFF, 0xFF
#define C_PRP 0x7A, 0x00, 0xFF
#define C_ORG 0xFF, 0x93, 0x00
#define C_PNK 0xFF, 0x14, 0x93

/** Set just 4 LEDs closest to the user. Slightly less annoying to bystanders.*/
void rgbflag(uint8_t r, uint8_t g, uint8_t b, uint8_t rr, uint8_t gg, uint8_t bb) {
  LED_TYPE *target_led = user_rgb_mode ? shadowed_led : led;
  for (int i = 0; i < RGBLED_NUM; i++)  {
    switch (i) {
    case 12: case 13:
      target_led[i].r = r;
      target_led[i].g = g;
      target_led[i].b = b;
      break;
    case 8: case 9:
      target_led[i].r = rr;
      target_led[i].g = gg;
      target_led[i].b = bb;
      break;
    default:
      target_led[i].r = 0;
      target_led[i].g = 0;
      target_led[i].b = 0;
      break;
    }
  }
  rgblight_set();
}

void set_state_leds(void) {
  if (rgblight_get_mode() == 1) {
    switch (biton32(layer_state)) {
    case _RAISE:
      rgbflag(C_BLU, C_GRN);
      break;
    case _LOWER:
      rgbflag(C_BLU, C_RED);
      break;
    case _ADJUST:
      rgbflag(C_BLU, C_PRP);
      break;
    case _MOVE:
      rgbflag(C_RED, C_PRP);
      break;
    case _KEYPAD:
      rgbflag(C_PNK, C_ORG);
      break;
    case _MOUSE:
      rgbflag(C_RED, C_GRN);
      break;
    case _CMD:
      switch(vstate) {
        case VIM_V:
        case VIM_VI:
        case VIM_VS:
          rgbflag(C_GRN, C_YAN);
          break;
        case VIM_C:
        case VIM_CI:
          rgbflag(C_GRN, C_ORG);
          break;
        case VIM_D:
        case VIM_DI:
          rgbflag(C_GRN, C_RED);
          break;
        case VIM_G:
          rgbflag(C_GRN, C_BLU);
          break;
        case VIM_Y:
          rgbflag(C_GRN, C_PRP);
          break;
        case VIM_START:
        default:
          rgbflag(C_GRN, C_GRN);
          break;
      }
      break;
    default: //  for any other layers, or the default layer
      rgbflag(C_PNK, C_PNK);
      break;
    }
  }
}

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
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
    case SHRUG:
      if (record->event.pressed) {
          send_unicode_string("¯\\_(ツ)_/¯");
      }
      return false;
      break;
    case TFLIP:
      if (record->event.pressed) {
          send_unicode_string("(╯°□°)╯︵ ┻━┻");
      }
      return false;
      break;
    case POOP:
      if (record->event.pressed) {
          send_unicode_string("💩");
      }
      return false;
      break;
    case DPOINT:
      if (record->event.pressed) {
          send_unicode_string("(ಠ_ಠ)");
      }
      return false;
      break;
    case STRUT:
      if (record->event.pressed) {
          send_unicode_string("ᕕ( ᐛ )ᕗ");
      }
      return false;
      break;
  }
  return true;
}
