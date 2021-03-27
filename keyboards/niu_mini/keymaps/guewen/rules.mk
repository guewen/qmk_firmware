MOUSEKEY_ENABLE = yes
BACKLIGHT_ENABLE = no
AUDIO_ENABLE = no
CONSOLE_ENABLE = no         # Console for debug(+400)
UNICODE_ENABLE = yes
# https://github.com/qmk/qmk_firmware/issues/3224
EXTRAFLAGS    += -flto
SWAP_HANDS_ENABLE= no  # Allow swapping hands of keyboard
