#ifndef LIMIT_SWITCH_H
#define LIMIT_SWITCH_H

#include <stdbool.h>

bool LimitSwitch1_IsPressed(void);
bool LimitSwitch2_IsPressed(void);
bool LimitSwitch3_IsPressed(void);
bool LimitSwitch_AnyPressed(void);

#endif /* LIMIT_SWITCH_H */
