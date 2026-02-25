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
#define MNZK_START_SONG \
    /* Measure 1 - quirky melody with bass */ \
    E__NOTE(_C5),  E__NOTE(_C3), \
    E__NOTE(_FS5), E__NOTE(_FS2), \
    Q__NOTE(_D5),  Q__NOTE(_BF2), \
    \
    E__NOTE(_BF4), E__NOTE(_E3), \
    E__NOTE(_G5),  E__NOTE(_C3), \
    Q__NOTE(_E4),  Q__NOTE(_GS2), \
    \
    S__NOTE(_A5),  S__NOTE(_F2), \
    S__NOTE(_C4),  S__NOTE(_F2), \
    S__NOTE(_F5),  S__NOTE(_CS3), \
    S__NOTE(_GS4), S__NOTE(_CS3), \
     \
    Q__NOTE(_DS5), Q__NOTE(_A2), \
    H__NOTE(_B4),  H__NOTE(_E3)
#endif
#define STARTUP_SONG SONG(MNZK_START_SONG)

#define ANALOG_JOYSTICK_Y_AXIS_PIN GP26
#define ANALOG_JOYSTICK_X_AXIS_PIN GP27
#define POINTING_DEVICE_INVERT_Y
#define POINTING_DEVICE_INVERT_X
