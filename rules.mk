MOUSEKEY_ENABLE         = no
POINTING_DEVICE_ENABLE  = no
OLED_DRIVER_ENABLE      = yes
LTO_ENABLE              = yes
CONSOLE_ENABLE          = no
COMMAND_ENABLE          = no
VIA_ENABLE              = yes

RGBLIGHT_ENABLE         = no
RGB_MATRIX_ENABLE       = yes

BOOTLOADER              = atmel-dfu
CFLAGS                 += -flto
EXTRAFLAGS             += -flto

WPM_ENABLE              = no
