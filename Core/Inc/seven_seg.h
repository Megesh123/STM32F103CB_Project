#ifndef SEVEN_SEG_H
#define SEVEN_SEG_H

#include <stdint.h>

/*
 * 4-digit 7-segment display mapping from the supplied schematic:
 *
 * Segment pins:
 *   A = PB10, B = PB2, C = PB5, D = PB12
 *   E = PB11, F = PB1, G = PB0, DP = PB14
 *
 * Digit enable pins:
 *   SEG1 = PA8, SEG2 = PA11, SEG3 = PA12, SEG4 = PA15
 *
 * Common-cathode display assumption:
 *   segment HIGH = ON, digit enable HIGH = ON.
 *
 * TIM2 must call SevenSeg_Tick() every 1 ms.
 * SevenSeg_Tick() is for continuous multiplex refresh only.
 * The seconds value is advanced separately once every 1000 ms.
 */

void SevenSeg_Init(void);
void SevenSeg_SetNumber(uint16_t value);
void SevenSeg_Tick(void);       /* Call every 1 ms */
void SevenSeg_SecondTick(void); /* Call every 1 second */

#endif /* SEVEN_SEG_H */
