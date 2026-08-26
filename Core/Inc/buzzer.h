#ifndef BUZZER_H
#define BUZZER_H

#include <stdbool.h>

void Buzzer_Init(void);
void Buzzer_Set(bool on);
void Buzzer_Update(bool proximity_detected, bool limit_switch_pressed);

#endif /* BUZZER_H */
