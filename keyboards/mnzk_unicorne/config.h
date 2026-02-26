// Copyright 2023 jack (@waffle87)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET

#define I2C_DRIVER I2CD1
#define I2C1_SDA_PIN GP22
#define I2C1_SCL_PIN GP23

#define AUDIO_PIN GP28
#define AUDIO_PWM_DRIVER PWMD6
#define AUDIO_INIT_DELAY
#define AUDIO_PWM_CHANNEL RP2040_PWM_CHANNEL_A

// custom startup song!
#define AUDIO_ENABLE_TONE_MULTIPLEXING
#define AUDIO_VOICES
#ifdef AUDIO_ENABLE
#   define MNZK_START_SONG \
        Q__NOTE(_DS5), Q__NOTE(_GS4), H__NOTE(_FS4), \
        E__NOTE(_DS4), E__NOTE(_G4), E__NOTE(_AS4), Q__NOTE(_C5), \
        Q__NOTE(_D5), Q__NOTE(_DS5), H__NOTE(_G5)
#endif
#define STARTUP_SONG SONG(MNZK_START_SONG)

#define ANALOG_JOYSTICK_Y_AXIS_PIN GP26
#define ANALOG_JOYSTICK_X_AXIS_PIN GP27
#define POINTING_DEVICE_INVERT_Y
#define POINTING_DEVICE_INVERT_X

// Mouse 
#define MK_KINETIC_SPEED
#define MOUSEKEY_MOVE_DELTA         8  // default 16
#define MOUSEKEY_INITIAL_SPEED      100  // default 100
#define MOUSEKEY_BASE_SPEED         1000 // dfault 5000
#define MOUSEKEY_WHEEL_INITIAL_MOVEMENTS    8 // default 16
#define MOUSEKEY_WHEEL_BASE_MOVEMENTS       20 // default 32

// Layer Toggling
#define TAPPING_TOGGLE 2

#define VIAL_TAP_DANCE_ENTRIES 8
#define VIAL_TAP_DANCE_USER
