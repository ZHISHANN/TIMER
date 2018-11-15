#ifndef _TIMER_H_
#define _TIMER_H_

#include "Common.h"

typedef struct TimerRegs TimerRegs;
struct TimerRegs{
	IoRegister controlReg1 ;                             //0x00
	IoRegister controlReg2;								 //0x04
	IoRegister slaveMode;                                //0x08
	IoRegister DMA_InterruptEnable;                      //0x0c
	IoRegister status;                                   //0x10
	IoRegister eventGeneration;                          //0x14
	IoRegister captureCompareMode1;                      //0x18
	IoRegister captureCompareMode2;                      //0x1c
	IoRegister captureCompareEnable;                     //0x20
	IoRegister counter;                                  //0x24
	IoRegister prescaler;                                //0x28
	IoRegister autoReload;                               //0x2c
	IoRegister Reserved0;                                //0x30
	IoRegister CCR1;                                     //0x34
	IoRegister CCR2;                                     //0x38
	IoRegister CCR3;                                     //0x3c
	IoRegister CCR4;                                     //0x40
	IoRegister Reserved1;                                //0x44
	IoRegister DMA_ControlReg;                           //0x48
	IoRegister DMA_Address;                              //0x4c
	IoRegister OR;										 //0x50
};

#define Timer2 		((TimerRegs *)0x40000000)
#define Timer3 		((TimerRegs *)0x40000400)
#define Timer4 		((TimerRegs *)0x40000800)
#define Timer5 		((TimerRegs *)0x40000C00)
#define Timer6 		((TimerRegs *)0x40000100)
#define Timer7 		((TimerRegs *)0x40001400)
#define Timer12 	((TimerRegs *)0x40001800)
#define Timer13 	((TimerRegs *)0x40001C00)
#define Timer14 	((TimerRegs *)0x40002000)

//CR1
#define TIM_CEN 	1

// SR
#define   TIM_UIF			(1 << 0)
#define   TIM_CC1IF			(1 << 1)
#define   TIM_CC2IF			(1 << 2)
#define   TIM_CC3IF			(1 << 3)
#define   TIM_CC4IF			(1 << 4)
#define   TIM_TIF			(1 << 6)
#define   TIM_CC1OF			(1 << 9)
#define   TIM_CC2OF			(1 << 10)
#define   TIM_CC3OF			(1 << 11)
#define   TIM_CC4OF			(1 << 12)

// CCMR
// Compare Mode (bit 6:4)
#define OC_FROZEN 				0
#define OC_ACTIV_ON_MATCH 		1
#define OC_INACTIV_ON_MATCH 	2
#define OC_TOGGLE				3
#define OC_FORCE_ACTIV			4
#define OC_FORCE_INACTIV 		5
#define OC_PWM1					6
#define OC_PWM2					7
// (bit 3)
#define OC_PRELOAD_EN           1
// Compare capture 1/3 selection (bit 1:0)
#define CC_SELECT_OC			0
#define CC_SELECT_IC_DIRECT		1
#define CC_SELECT_IC_INDIRECT	2
#define CC_SELECT_IC_TRC		3

//CCER
#define OC_NORMAL_POLARITY 		0
#define OC_INVERSE_POLARITY		1

// EGR
#define	TIM_UG 		1

// DIER
#define	  dmaInterruptEnable	1

//Timer Macros
#define TIM_SET_COUNTER(tim,value)			(tim)->counter = (value)
#define TIM_SET_OC_VALUE(tim,ch,value)		*(&((tim)->CCR1) + (ch) - 1) = (value)
#define TIM_SET_OC_POLARITY(tim,ch,polarity)                        		    	\
			do{																		\
				(tim)->captureCompareEnable &= ~(2 << (((ch) - 1) * 4));			\
				(tim)->captureCompareEnable |= polarity << ((((ch) - 1) * 4) + 1);	\
			}while(0)

#define TIM_CAPTURE_COMPARE_EN(tim,ch)		(tim)->captureCompareEnable |= 1 << (((ch) - 1) * 4)
#define TIM_CAPTURE_COMPARE_DIS(tim,ch)		(tim)->captureCompareEnable &= ~(1 << (((ch) - 1) * 4))

// Clear SR register of Timer, which Flag should be one of the following:
//   TIM_UIF			Update interrupt flag
//   TIM_CC1IF			Capture/Compare 1 interrupt flag
//   TIM_CC2IF			Capture/Compare 2 interrupt flag
//   TIM_CC3IF			Capture/Compare 3 interrupt flag
//   TIM_CC4IF			Capture/Compare 4 interrupt flag
//   TIM_TIF			Trigger interrupt flag
//   TIM_CC1OF			Capture/Compare 1 over capture flag
//   TIM_CC2OF			Capture/Compare 2 over capture flag
//   TIM_CC3OF			Capture/Compare 3 over capture flag
//   TIM_CC4OF			Capture/Compare 4 over capture flag
#define TIM_CLEAR_FLAG(tim,whichFlag)	(tim)->status = ~(whichFlag)
#define TIM_GET_FLAG(tim, whichFlag)	(tim)->status & whichFlag

#define TIM_COUNTER_ENABLE(tim)			(tim)->controlReg1 |= TIM_CEN
#define TIM_COUNTER_DISABLE(tim)		(tim)->controlReg2 &= ~TIM_CEN

#define TIME_UPDATE_GEN					(tim)->EGR |= TIM_UG

void timerOcSetMode(TimerRegs *tim, int channel, int mode);
void timerInitOutputCompare(TimerRegs *tim, int channel, int mode, int outpinPolarity, int compareValue);

#endif /* __TIMER_H__ */
