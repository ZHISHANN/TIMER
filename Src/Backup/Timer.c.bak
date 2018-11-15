#include "Timer.h"

/**
 * Initialize the timer output compare channel.
 *
 * Input:
 *  mode	is the mode of the output compare. They can be anyone below:
 *  		OC_FROZEN
 *	 	 	OC_ACTIV_ON_MATCH
 *	 	 	OC_INACTIV_ON_MATCH
 *          OC_TOGGLE
 *			OC_FORCE_ACTIV
 *			OC_FORCE_INACTIV
 *			OC_PWM1
 *			OC_PWM2
 * outPolarity is either 0 = normal or 1 = inverse
 */

void timerInitOutputCompare(TimerRegs *tim, int channel, int mode, int outpinPolarity, int compareValue)
{
	timerOcSetMode(tim,channel,mode);
	TIM_SET_OC_VALUE(tim,channel,compareValue);
	TIM_SET_OC_POLARITY(tim,channel,outpinPolarity);
}

/**
 * Set the timer output compare channel to the specified mode.
 *
 * Input:
 *  mode	is the mode of the output compare. They can be anyone below:
 *  		OC_FROZEN
 *	 	 	OC_ACTIV_ON_MATCH
 *	 	 	OC_INACTIV_ON_MATCH
 *          OC_TOGGLE
 *			OC_FORCE_ACTIV
 *			OC_FORCE_INACTIV
 *			OC_PWM1
 *			OC_PWM2
 */
void timerOcSetMode(TimerRegs *tim, int channel, int mode)
{
	int numOfShifts = 0;
	IoRegister *ccmr = &tim->captureCompareMode1;

	if(((channel - 1) & 1) == 1)
		numOfShifts = 8;

	if(channel > 2)
		ccmr++;

	*ccmr = mode << (4 + numOfShifts);
}
