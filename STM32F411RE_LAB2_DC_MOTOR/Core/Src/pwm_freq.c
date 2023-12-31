/*
 * pwm_freq.c
 *
 *  Created on: Oct 14, 2023
 *      Author: 08809
 */

#include "pwm_freq.h"
#include "math.h"

#define CPU_FREQ 100.0 * 1.0e6

uint8_t PWMWrite(TIM_HandleTypeDef* htimx, uint16_t tim_chx, float freq, float percent_duty)
{
	if (freq == 0)
	{
		__HAL_TIM_SET_COMPARE(htimx, tim_chx, 0);
		return 0;
	} else if (freq >= CPU_FREQ / 2.0) return -1;
	uint32_t period_cyc = (uint32_t) (CPU_FREQ / freq);
	uint16_t prescaler = (uint16_t) (period_cyc / 65535 + 1);
	uint16_t overflow = (uint16_t) ((period_cyc + (prescaler / 2)) / prescaler);
	__HAL_TIM_SET_PRESCALER(htimx, prescaler);
	__HAL_TIM_SET_AUTORELOAD(htimx, overflow);
	__HAL_TIM_SET_COMPARE(htimx, tim_chx, (uint16_t) (overflow * fabs(percent_duty) / 100.0));
	return 0;
}
