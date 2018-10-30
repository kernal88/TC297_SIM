#ifndef REG_COMMON_H
#define REG_COMMNO_H

#include "simul.h"



typedef struct
{
	unsigned char id;
	unsigned int offset;
	simulCallbackFunctionPtr reg_read_func_ptr;
	simulCallbackFunctionPtr reg_write_func_ptr;
}reg_opt;


#endif
