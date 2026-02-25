#include QMK_KEYBOARD_H

#ifdef OLED_ENABLE
#include "animation.c"
#endif

// oled_rotation_t oled_init_user(oled_rotation_t rotation) {
//     if (is_keyboard_master()) {
//         return OLED_ROTATION_90;  // flips the display 180 degrees if offhand
//     }

//     return rotation;
// }


#ifdef OLED_ENABLE
bool oled_task_user(void) {
  if (is_keyboard_master()) {
    oled_render_anim();
  }
  return false;
}
#endif