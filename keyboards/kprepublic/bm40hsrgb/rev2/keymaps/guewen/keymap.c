/* Copyright 2020 tominabox1
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
 */
[_DVORAK] = LAYOUT_ortho_4x12_1x2uC(
    KC_TAB,         CH_QUOT,    CH_COMM, CH_DOT,  CH_P,  CH_Y,   CH_F,  CH_G,    CH_C,    CH_R,    CH_L,    CH_SLSH,
    LCTL_T(KC_ESC), CH_A,       CH_O,    CH_E,    CH_U,  CH_I,   CH_D,  CH_H,    CH_T,    CH_N,    CH_S,    KC_BSPC,
    KC_LSFT,        CH_COLN,    CH_Q,    CH_J,    CH_K,  CH_X,   CH_B,  CH_M,    CH_W,    CH_V,    MOVE_Z,  RSFT_T(KC_ENT),
    KC_LCTL,        TG(_MOUSE), KC_LALT, KC_LGUI, TL_LOWR, KC_SPC,      TL_UPPR,   KC_RALT, KC_APP,  KC_RCTL, XXXXXXX
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
[_LOWER] = LAYOUT_ortho_4x12_1x2uC(
    _______, CH_7,        CH_5,    CH_3,    CH_1,    CH_9,       CH_0,     CH_2,     CH_4,    CH_6,     CH_8,      TG(_KEYPAD),
    _______, CH_GRV,      CH_CIRC, CH_ACUT, CH_DIAE, XXXXXXX,    XXXXXXX,  XXXXXXX,  CH_CCED, XXXXXXX,  KC_INSERT, LALT(KC_BSPC),
    _______, KC_F1,       KC_F2,   KC_F3,   KC_F4,   KC_F5,      KC_F6,    KC_F7,    KC_F8,   KC_F9,    KC_F10,   _______,
    _______, TO(_DVORAK), _______, _______, _______, KC_BSPC,              _______,  _______, KC_F11,   KC_F12,   _______
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
[_RAISE] = LAYOUT_ortho_4x12_1x2uC(
    CH_GRV,  CH_DQUO,  CH_EXLM, CH_HASH, CH_DLR,  CH_LPRN, CH_RPRN,  CH_AMPR, CH_ASTR, CH_PERC, CH_CIRC, _______,
    CH_TILD, CH_AT,    CH_QUES, CH_PIPE, CH_LCBR, CH_LBRC, CH_RBRC,  CH_RCBR, CH_BSLS, CH_MINS, CH_EQL,  KC_DEL,
    _______, CH_SCLN,  CH_DEG,  XXXXXXX,    XXXXXXX,    CH_LABK, CH_RABK,  XXXXXXX,    XXXXXXX,    CH_UNDS, CH_PLUS, _______,
    _______, TO(_DVORAK), _______,    _______,    _______,           _______,          _______,    KC_HOME,    KC_PGDN,    KC_PGUP,    KC_END
),

/* Adjust (Lower + Raise)
 * ,-------------------------------------------------------------------------------------.
 * |        |      | Reset| DEBUG| HUE+ | HUE- | SAT+ | SAT- |BRGTH+|BRGTH-|      |  Del |
 * |--------+------+------+------+------+-------------+------+------+------+------+------|
 * |RGBMode-|      |      |      |PRTSCR|      |      | Play | PREV | NEXT |      |Lite+ |
 * |--------+------+------+------+------+------|------+------+------+------+------+------|
 * |RGBMode+|      |SHRUG |TFLIP |Poop  |DPOINT|STRUT | MUTE | Vol- | Vol+ |      |Lite- |
 * |--------+------+------+------+------+------+------+------+------+------+------+------|
 * |  RGB   | Bail |      |      |      |             |      |      |      | Bail |      |
 * `-------------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_ortho_4x12_1x2uC(
    _______,   XXXXXXX,     QK_BOOT,   DB_TOGG,   RM_HUEU, RM_HUED, RM_SATU, RM_SATD,  RM_VALU, RM_VALD, XXXXXXX,     KC_DEL,
    RM_PREV, XXXXXXX, XXXXXXX, XXXXXXX, KC_PSCR, XXXXXXX, XXXXXXX, KC_MPLY, KC_MPRV, KC_MNXT, XXXXXXX,     _______,
    RM_NEXT, XXXXXXX,     SHRUG,   TFLIP,   POOP,    DPOINT,  STRUT, KC_MUTE, KC_VOLD, KC_VOLU, XXXXXXX,     _______,
    RM_TOGG,          TO(_DVORAK), _______, _______, _______,     _______,      _______, _______, _______, TO(_DVORAK), XXXXXXX
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
[_KEYPAD] = LAYOUT_ortho_4x12_1x2uC(
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     CH_7,  CH_8, CH_9,     CH_HASH,  _______,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, CH_ASTR,  CH_4,  CH_5, CH_6,     CH_MINS,  _______,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, CH_SLSH,  CH_1,  CH_2, CH_3,     CH_PLUS,  _______,
    _______, _______, _______, _______, _______,       _______,        _______,  CH_0, CH_DOT,   CH_EQL,   _______
),

/* movement layer (hold z)
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
[_MOVE] = LAYOUT_ortho_4x12_1x2uC(
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
[_MOUSE] = LAYOUT_ortho_4x12_1x2uC(
    TO(_DVORAK), XXXXXXX,     XXXXXXX,    KC_MS_UP,   XXXXXXX,     XXXXXXX, KC_MS_WH_LEFT, KC_MS_WH_DOWN, KC_MS_WH_UP, KC_MS_WH_RIGHT, XXXXXXX,     XXXXXXX,
    _______,     XXXXXXX,     KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT, XXXXXXX, XXXXXXX,       KC_MS_BTN1,    KC_MS_BTN2,  KC_MS_BTN3,     XXXXXXX,     XXXXXXX,
    _______,     XXXXXXX,     XXXXXXX,    XXXXXXX,    XXXXXXX,     XXXXXXX, XXXXXXX,       XXXXXXX,       XXXXXXX,     XXXXXXX,        XXXXXXX,     _______,
    _______,     TO(_DVORAK), _______,    _______,    _______,         XXXXXXX,            _______,       _______,     _______,        TO(_DVORAK), XXXXXXX
)

};

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
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
