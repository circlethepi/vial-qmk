#include QMK_KEYBOARD_H

#ifdef OLED_ENABLE
#include "animation.c"
#endif

#ifdef RGB_MATRIX_ENABLE
#include "rgb-utils.c"
#endif

// Tap dance enums - purely for me to remember which does which
enum {
    V_NUM, // v normally; double tap: TG(1); tap+hold: MO(1)
    NAV, // tap: TG(2); hold: MO(2);
};


/*===========================================================================*/
// ACTUAL KEYMAPPING (from json2c)
/*===========================================================================*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_3x6_3(\
      KC_TAB,     KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,           KC_Y,   KC_U,   KC_I,   KC_O,     KC_SCLN,  KC_BSPC, \
      KC_ESCAPE,  KC_A,   KC_S,   KC_D,   KC_F,   KC_G,           KC_H,   KC_J,   KC_K,   KC_L,     KC_P,     KC_QUOTE, \
      KC_LCTL,    KC_Z,   KC_X,   KC_C,   TD(V_NUM), KC_NO,       KC_B,   KC_N,   KC_M,   KC_COMMA, KC_DOT,   KC_SLASH, \
                                  TD(NAV), KC_LSFT, KC_LGUI,        KC_ENTER, KC_SPACE, KC_RALT\
      ),
    [1] = LAYOUT_split_3x6_3(\
      _______,  LSFT(KC_COMMA), LSFT(KC_DOT), _______,  _______,  _______,      KC_KP_SLASH,  KC_7,  KC_8,  KC_9,   KC_MINUS,   _______, \
      TG(1),    LSFT(KC_9),     LSFT(KC_0),   KC_LBRC,  KC_RBRC,  KC_BSLS,      KC_KP_COMMA,  KC_4,  KC_5,  KC_6,   KC_EQUAL,   _______, \
      _______,  KC_UNDO,        KC_CUT,       KC_COPY,  KC_PSTE,  _______,      KC_KP_DOT,    KC_1,  KC_2,  KC_3,   _______,    _______, \
                                              _______,  _______,  _______,      _______,      _______, KC_KP_0\
      ),
    [2] = LAYOUT_split_3x6_3(\
      _______,  _______,  _______,  MS_UP,    _______,  _______,        _______,  _______,  KC_UP,    _______,  _______,  _______,  \
      TG(2),    _______,  MS_LEFT,  MS_DOWN,  MS_RGHT,  MS_WHLD,        _______,  KC_LEFT,  KC_DOWN,  KC_RIGHT, _______, _______, \
      KC_LCTL,  _______,  _______,  _______,  _______,  MS_WHLU,        _______,  _______,  _______,  _______,  _______, _______, \
                                    _______,  MS_BTN1,  MS_BTN2,        _______,  _______,  _______ \
      ),
    [3] = LAYOUT_split_3x6_3(QK_BOOT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, QK_CLEAR_EEPROM, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______)
};

/*===========================================================================*/
// OLED 
/*===========================================================================*/

#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) { // for right side
        return OLED_ROTATION_180;  
    }
    return rotation;
}

bool oled_task_user(void) {
  if (is_keyboard_master()) {
    oled_render_anim();
  }
  return false;
}

#endif

/*===========================================================================*/
// RGB MATRIX
/*===========================================================================*/

#ifdef RGB_MATRIX_ENABLE

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
  set_underglow(128, 128, 128);  
  
  uint8_t layer = get_highest_layer(layer_state);
  switch(layer) {
      case 0:
          RGB_THUMB_KEYS(0, 255, 0, led_min, led_max); // green
          break;
      case 1:
          RGB_THUMB_KEYS(0, 0, 255, led_min, led_max); // blue
          break;
      case 2:
          RGB_THUMB_KEYS(128, 0, 255, led_min, led_max); // purple
          break;
    }
  return false;
}

#endif

