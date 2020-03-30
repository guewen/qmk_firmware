/* Copyright 2015-2017 Jack Humbert
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
#include "planck.h"
#include "action_layer.h"
#include "muse.h"
#include "keymap_extras/keymap_fr_ch.h"
// #include "keymap_extras/keymap_dvp.h"

extern keymap_config_t keymap_config;

enum planck_layers {
  _DVORAK,
  _LOWER,
  _RAISE,
  _KEYPAD,
  _ADJUST,
  _FN,
  _MOVE_FN,
  _MOUSE
};

enum planck_keycodes {
  BACKLIT,
  ROLL,
  SHRUG
};

enum unicode_name {
  BANG, // ‽
  IRONY, // ⸮
  SNEK // snke 🐍
};

const uint32_t PROGMEM unicode_map[] = {
  [BANG]      = 0x0203D, // ‽
  [IRONY]     = 0x02E2E, // ⸮
  [SNEK]      = 0x1F40D // snke 🐍
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO
#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define FN MO(_FN)
#define MOVE_FN MO(_MOVE_FN)
#define SHIFTENT MT(MOD_RSFT, KC_ENT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Dvorak
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   '  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  |  /   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   :  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  |Sft/Ent|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | FN   | Ctrl | Alt  | GUI  |Lower | Bksp |Space |Raise | AltGr|Menu  |Ctrl  |MOVE_FN|
 * `-----------------------------------------------------------------------------------'
 */
[_DVORAK] = LAYOUT_planck_grid(
    KC_TAB,  FR_CH_QUOT, FR_CH_COMM, FR_CH_DOT, FR_CH_P, FR_CH_Y,  FR_CH_F,   FR_CH_G, FR_CH_C, FR_CH_R, FR_CH_L, FR_CH_SLSH,
    KC_ESC,  FR_CH_A,    FR_CH_O,    FR_CH_E,   FR_CH_U, FR_CH_I,  FR_CH_D,   FR_CH_H, FR_CH_T, FR_CH_N, FR_CH_S, XXXXXXX,
    KC_LSFT, FR_CH_COLN, FR_CH_Q,    FR_CH_J,   FR_CH_K, FR_CH_X,  FR_CH_B,   FR_CH_M, FR_CH_W, FR_CH_V, FR_CH_Z, SHIFTENT,
    FN,      KC_LCTL,    KC_LALT,    KC_LGUI,   LOWER,   KC_BSPC,  KC_SPC,  RAISE,   KC_RALT, KC_MENU, KC_RCTL, MOVE_FN
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |      |   7  |   5  |   3  |   1  |   9  |   0  |   2  |   4  |   6  |   8  |KEYPAD|
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |   `  |   ^  |   ´  |   ¨  |      |      |      |   ç  |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |Sft/Ent|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      | Bksp |Space |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_planck_grid(
    XXXXXXX, FR_CH_7,   FR_CH_5,    FR_CH_3,    FR_CH_1,    FR_CH_9, FR_CH_0,  FR_CH_2,  FR_CH_4,    FR_CH_6,  FR_CH_8,  TG(_KEYPAD),
    XXXXXXX, FR_CH_GRV, FR_CH_CIRC, FR_CH_ACUT, FR_CH_DIAE, XXXXXXX, XXXXXXX,  XXXXXXX,  FR_CH_CCED, XXXXXXX,  XXXXXXX,  XXXXXXX,
    _______, XXXXXXX,   XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX,    XXXXXXX,  XXXXXXX,  _______,
    _______, _______,   _______,    _______,    _______,    KC_BSPC, KC_SPC,   _______,  XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX
),

/* Keypad
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |   7  |   8  |   9  |   #  |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |   *  |   4  |   5  |   6  |   -  |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |   /  |   1  |   2  |   3  |   +  |Sft/Ent|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      | Bksp |Space |      |   0  |   .  |   =  |      |
 * `-----------------------------------------------------------------------------------'
 */
[_KEYPAD] = LAYOUT_planck_grid(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     FR_CH_7,  FR_CH_8, FR_CH_9,     FR_CH_HASH,  _______,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, FR_CH_ASTR,  FR_CH_4,  FR_CH_5, FR_CH_6,     FR_CH_MINS,  XXXXXXX,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, FR_CH_SLSH,  FR_CH_1,  FR_CH_2, FR_CH_3,     FR_CH_PLUS,  _______,
    _______, _______, _______, _______, _______, _______, _______,     _______,  FR_CH_0, FR_CH_DOT,   FR_CH_EQL,   XXXXXXX
),


/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   "  |   !  |   #  |   $  |   (  |   )  |   &  |   *  |   %  |   ^  |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |   ~  |   @  |   ?  |   |  |   {  |   [  |   ]  |   }  |   \  |   -  |   =  |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |   °  |   ;  |      |      |      |   <  |   >  |      |      |   _  |   +  |Sft/Ent|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      | Bksp |Space |      | Home | PgDn | PgUp | End  |
 * `-----------------------------------------------------------------------------------'
 */

[_RAISE] = LAYOUT_planck_grid(
    FR_CH_GRV,  FR_CH_DQOT, FR_CH_EXLM, FR_CH_HASH, FR_CH_DLR,  FR_CH_LPRN, FR_CH_RPRN,  FR_CH_AMPR, FR_CH_ASTR, FR_CH_PERC, FR_CH_CIRC, _______,
    FR_CH_TILD, FR_CH_AT,   FR_CH_QST, FR_CH_PIPE, FR_CH_LCBR, FR_CH_LBRC, FR_CH_RBRC,  FR_CH_RCBR, FR_CH_BSLS, FR_CH_MINS, FR_CH_EQL,   _______,
    FR_CH_RING, FR_CH_SCLN, XXXXXXX,    XXXXXXX,    XXXXXXX,    FR_CH_LESS, FR_CH_MORE,  XXXXXXX,    XXXXXXX,    FR_CH_UNDS, FR_CH_PLUS,    _______,
    _______,    XXXXXXX,    _______,    _______,    _______,    _______,    _______,    _______,    KC_HOME,    KC_PGDN,    KC_PGUP,    KC_END
),

/* FN
 * ,-----------------------------------------------------------------------------------.
 * |DelWrd|  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  | F10  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |Mouse |  F11 |  F12 |  F13 | F14  | F15  |  F16 |      |      |      |      |Insert|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      | ROLL |      |      |      |      |      |      |      | SHRUG| Enter|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      | Del  |Space |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_FN] = LAYOUT_planck_grid(
    LALT(KC_BSPC),  KC_F1,   KC_F2,   KC_F3,   KC_F4,    KC_F5,    KC_F6,    KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_DEL,
    TG(_MOUSE),     KC_F11,  KC_F12,  KC_F13,  KC_F14,   KC_F15,   KC_F16,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_INSERT,
    _______,        XXXXXXX, ROLL,    XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, SHRUG,   _______,
    XXXXXXX,        _______, XXXXXXX, KC_DEL,  XXXXXXX,  KC_DEL,  KC_SPC,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
),

/* MOVE_FN
 * ,-----------------------------------------------------------------------------------.
 * |PRNT SC| HOME |  UP  | END  | PGUP |      |      |      |      |      |      |      |
 * |-------+------+------+------+------+-------------+------+------+------+------+------|
 * |Mouse  | LEFT | DOWN | RIGHT|PGDOWN|      |      | LEFT | DOWN |  UP  | RIGHT|      |
 * |-------+------+------+------+------+------|------+------+------+------+------+------|
 * |       |      |      |      |      |      |      |      |      |PLAYPA| PREV | NEXT |
 * |-------+------+------+------+------+------+------+------+------+------+------+------|
 * |       |      |      |      |      |             |      | MUTE |VOLDWN|VOL UP|      |
 * `-----------------------------------------------------------------------------------'
 */
[_MOVE_FN] = LAYOUT_planck_grid(
    KC_PSCR,  KC_HOME, KC_UP,    KC_END,    KC_PGUP,   XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX,  XXXXXXX,     XXXXXXX,    XXXXXXX,
    TG(_MOUSE),    KC_LEFT, KC_DOWN,  KC_RIGHT,  KC_PGDN,   XXXXXXX,  XXXXXXX,  KC_LEFT, KC_DOWN,  KC_UP,       KC_RIGHT,   XXXXXXX,
    _______,  XXXXXXX, XXXXXXX,  XXXXXXX,   XXXXXXX,   XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX,  KC_MPLY,     KC_MPRV,    KC_MNXT,
    _______,  _______, _______,  _______,   _______,   _______,  _______,  _______, KC_MUTE,  KC_VOLD,     KC_VOLU,    _______
),


/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * | Reset|Debug|       |      |      |      |      |      |      |MIDIof|MIDIon|  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |AGnorm|AGswap|      |      |Audoff|Aud on|      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |Musoff|Mus on|      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |Voice-|Voice+|      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid(
    RESET,   DEBUG,   XXXXXXX,   XXXXXXX,   XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   MI_OFF,   MI_ON,   KC_DEL,
    XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX,   XXXXXXX,  AG_NORM, AG_SWAP, XXXXXXX, XXXXXXX,   AU_OFF,   AU_ON,   XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX,   XXXXXXX,  XXXXXXX, XXXXXXX, TERM_ON, TERM_OFF,  MU_OFF,   MU_ON,   XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX,   _______,  XXXXXXX, XXXXXXX, _______, XXXXXXX,   MUV_DE,   MUV_IN,  XXXXXXX
),

/* Mouse
 * ,-----------------------------------------------------------------------------------.
 * |      |      |WHUP  |      | ACC0 | ACC1 | ACC2 | BTN1 |  UP  | BTN2 |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |WHLEFT|WHDOWN|WHRGHT| ACC0 | ACC1 | ACC2 | LEFT | DOWN |RIGHT |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      | ACC0 | ACC1 | ACC2 |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_MOUSE] = LAYOUT_planck_grid(
    _______, _______,       KC_MS_WH_UP,   _______,        KC_MS_ACCEL0, KC_MS_ACCEL1,   KC_MS_ACCEL2, KC_MS_BTN1,  KC_MS_UP,   KC_MS_BTN2,  _______, _______,
    _______, KC_MS_WH_LEFT, KC_MS_WH_DOWN, KC_MS_WH_RIGHT, KC_MS_ACCEL0, KC_MS_ACCEL1,   KC_MS_ACCEL2, KC_MS_LEFT,  KC_MS_DOWN, KC_MS_RIGHT, _______, _______,
    _______, _______,       _______,       _______,        KC_MS_ACCEL0, KC_MS_ACCEL1,   KC_MS_ACCEL2, _______,     _______,    _______,     _______, _______,
    _______, _______,       _______,       _______,        _______,      _______,        _______,      _______,     _______,    _______,     _______, _______
)

};

uint32_t layer_state_set_user(uint32_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case BACKLIT:
      if (record->event.pressed) {
        register_code(KC_RSFT);
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
        #endif
        #ifdef KEYBOARD_planck_rev5
          PORTE &= ~(1<<6);
        #endif
      } else {
        unregister_code(KC_RSFT);
        #ifdef KEYBOARD_planck_rev5
          PORTE |= (1<<6);
        #endif
      }
      return false;
      break;
  }
  return true;
}

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

void encoder_update(bool clockwise) {
  if (muse_mode) {
    if (IS_LAYER_ON(_RAISE)) {
      if (clockwise) {
        muse_offset++;
      } else {
        muse_offset--;
      }
    } else {
      if (clockwise) {
        muse_tempo+=1;
      } else {
        muse_tempo-=1;
      }
    }
  } else {
    if (clockwise) {
      #ifdef MOUSEKEY_ENABLE
        register_code(KC_MS_WH_DOWN);
        unregister_code(KC_MS_WH_DOWN);
      #else
        register_code(KC_PGDN);
        unregister_code(KC_PGDN);
      #endif
    } else {
      #ifdef MOUSEKEY_ENABLE
        register_code(KC_MS_WH_UP);
        unregister_code(KC_MS_WH_UP);
      #else
        register_code(KC_PGUP);
        unregister_code(KC_PGUP);
      #endif
    }
  }
}

void matrix_scan_user(void) {
  #ifdef AUDIO_ENABLE
    if (muse_mode) {
      if (muse_counter == 0) {
        uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
        if (muse_note != last_muse_note) {
          stop_note(compute_freq_for_midi_note(last_muse_note));
          play_note(compute_freq_for_midi_note(muse_note), 0xF);
          last_muse_note = muse_note;
        }
      }
      muse_counter = (muse_counter + 1) % muse_tempo;
    }
  #endif
}

bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    case RAISE:
    case LOWER:
      return false;
    default:
      return true;
  }
}
