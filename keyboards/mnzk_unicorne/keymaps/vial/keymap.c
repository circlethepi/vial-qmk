#include QMK_KEYBOARD_H

#ifdef OLED_ENABLE
#include "animation.c"
#endif

#ifdef RGB_MATRIX_ENABLE
#include "rgb-utils.c"
#endif

// TAP DANCE DEFINITIONS
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP, // Send two single taps
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

// Tap dance enums
enum {
    V_NUM_LAYER,
    NAV_LAYER,
};

td_state_t cur_dance(tap_dance_state_t *state);

// Tap dace info: Put it here so it can be used in any keymap
void v_finished(tap_dance_state_t *state, void *user_data);
void v_reset(tap_dance_state_t *state, void *user_data);

void nav_finished(tap_dance_state_t *state, void *user_data);
void nav_reset(tap_dance_state_t *state, void *user_data);

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

/*===========================================================================*/

td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed) return TD_DOUBLE_HOLD;
        else return TD_DOUBLE_TAP;
    }

    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TD_TRIPLE_SINGLE_TAP', and define that enum just like 'TD_DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (state->interrupted || !state->pressed) return TD_TRIPLE_TAP;
        else return TD_TRIPLE_HOLD;
    } else return TD_UNKNOWN;
}

// V tap dance
// acts like V normally; on double tap, toggle layer 1. On tap+hold, MO(1)
static td_tap_t v_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void v_finished(tap_dance_state_t *state, void *user_data) {
    v_tap_state.state = cur_dance(state);  
    switch (v_tap_state.state) {            
        case TD_SINGLE_TAP: register_code(KC_V); break;
        case TD_SINGLE_HOLD: register_code(KC_V); break;
        case TD_DOUBLE_TAP: layer_invert(1); break; 
        case TD_DOUBLE_HOLD: layer_on(1); break;     
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_V); register_code(KC_V); break;
        default: break;
    }
}

void v_reset(tap_dance_state_t *state, void *user_data) {
    switch (v_tap_state.state) { 
        case TD_SINGLE_TAP: unregister_code(KC_V); break;
        case TD_SINGLE_HOLD: unregister_code(KC_V); break;
        case TD_DOUBLE_TAP: break; 
        case TD_DOUBLE_HOLD: layer_off(1); break; 
        case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_V); break;
        default: break;
    }
    v_tap_state.state = TD_NONE; 
}

// NAV tap dance
// Toggle layer 2 (nav) on tap; MO(2) on hold
static td_tap_t nav_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// NAV tap dance implementation
void nav_finished(tap_dance_state_t *state, void *user_data) {
    nav_tap_state.state = cur_dance(state);
    switch (nav_tap_state.state) {
        case TD_SINGLE_TAP: layer_invert(2); break;
        case TD_SINGLE_HOLD: layer_on(2); break;
        default: break;
    }
}

void nav_reset(tap_dance_state_t *state, void *user_data) {
    switch (nav_tap_state.state) {
        case TD_SINGLE_HOLD: layer_off(2); break;
        default: break;
    }
    nav_tap_state.state = TD_NONE;
}


// Tap dance settings
// tap_dance_action_t tap_dance_actions[] = {
//     [V_NUM_LAYER] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, v_finished, v_reset),
//     [NAV_LAYER] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, nav_finished, nav_reset)
// };