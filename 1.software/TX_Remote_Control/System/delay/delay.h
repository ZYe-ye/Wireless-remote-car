#ifndef __DELAY_H
#define __DELAY_H
#include "sys.h"

#ifdef __cplusplus
extern "C" {
#endif

#define CPU_FREQUENCY_MHZ    72		// STM32Ê±ÖÓÖ÷Æµ

void delay_us(__IO uint32_t delay);

#ifdef __cplusplus
}
#endif

#endif
