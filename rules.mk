BOOTLOADER              = qmk-dfu

MOUSEKEY_ENABLE         = no    # Mouse keys(+1482)
EXTRAKEY_ENABLE         = yes   # Audio control and System control(+470)
OLED_DRIVER_ENABLE      = yes   # 128X32 OLED Screen
LTO_ENABLE              = yes   # Link Time Optimization
VIA_ENABLE              = no    # Configuring keyboard with VIA
MIDI_ENABLE             = no    # MIDI controls
WPM_ENABLE              = yes   # WPM Calculation

RGB_MATRIX_ENABLE       = yes   # Matrix LEDs

CFLAGS                 += -flto
EXTRAFLAGS             += -flto

ifeq ($(strip $(SIDE)), right)
    OPT_DEFS += -DIS_SIDE_RIGHT
endif

ifeq ($(strip $(TEMPLATE)), code)
    OPT_DEFS += -DTEMPLATE_CODE
endif

ifeq ($(strip $(TEMPLATE)), discord)
    OPT_DEFS += -DTEMPLATE_DISCORD
endif
