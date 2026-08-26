#ifndef SEVEN_SEG_H
#define SEVEN_SEG_H

#include <stdint.h>

/*
 * 4-digit 7-segment display
 *
 * Segment pins:
 *   A = PB11, B = PB10, C = PB7, D = PB12
 *   E = PB13, F = PB1, G = PB0, DP = PB14
 *
 * Digit enable pins:
 *   SEG1 = PA8, SEG2 = PA11, SEG3 = PA12, SEG4 = PB3
 *
 * This implementation assumes a common-cathode display:
 *   segment HIGH = ON, digit enable HIGH = ON.
 */

void SevenSeg_Init(void);
void SevenSeg_SetNumber(uint16_t value);
void SevenSeg_Tick(void);

#endif /* SEVEN_SEG_H */
