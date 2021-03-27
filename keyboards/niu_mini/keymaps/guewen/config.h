#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "../../config.h"

#define UNICODE_SELECTED_MODES UC_LNX

// help for fast typist+dual function keys?
#define PERMISSIVE_HOLD

/* speed up mousekeys a bit */
#define MOUSEKEY_DELAY             50
#define MOUSEKEY_INTERVAL          20
#define MOUSEKEY_MAX_SPEED         8
#define MOUSEKEY_TIME_TO_MAX       30
#define MOUSEKEY_WHEEL_MAX_SPEED   8
#define MOUSEKEY_WHEEL_TIME_TO_MAX 40


// reduce size of firmware
#if !defined(NO_DEBUG) && !defined(CONSOLE_ENABLE)
  #define NO_DEBUG
#endif // !NO_DEBUG

#if !defined(NO_PRINT) && !defined(CONSOLE_ENABLE)
  #define NO_PRINT
#endif // !NO_PRINT

#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

#endif
