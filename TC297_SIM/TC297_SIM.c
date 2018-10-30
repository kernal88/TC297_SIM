#include "simul.h"
#include "SCU_SIM.h"
#include "EMEM_SIM.h"
#include "CPU_SIM.h"

static void * debug_file_hadle = NULL;

int SIMULAPI SIMUL_Init(simulProcessor processor, simulCallbackStruct * cbs)
{
		debug_file_hadle = SIMUL_OpenFile(processor, "./debug_tc297.log", SIMUL_FILE_CREATE);
		if (debug_file_hadle != NULL)
		{
			SIMUL_Warning(processor, "create file debug_tc297.log success!");
		} 
		else
		{
			SIMUL_Warning(processor, "create file debug_tc297.log failed!");
			return SIMUL_INIT_FAIL;
		}

		SCU_Init(processor, cbs);

		EMEM_Init(processor, cbs);

		CPU_Init(processor, cbs);
		
	    return SIMUL_INIT_OK;
}
