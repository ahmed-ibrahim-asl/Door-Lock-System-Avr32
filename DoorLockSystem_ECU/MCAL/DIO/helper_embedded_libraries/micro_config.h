#ifndef MICRO_CONFIG_H_
#define MICRO_CONFIG_H_

	/******************* Include Section *******************/
	#include "bit_math.h"
	#include "error_types.h"
	#include "std_types.h"
	#include "register.h"
	#include <math.h>
	/******************************************************/


	#ifndef F_CPU
	#define F_CPU(F_CPU_VALUE) (F_CPU_VALUE*1000000)UL
	#endif



#endif /* MICRO_CONFIG_H_ */






