#include "simul.h"
#include "reg_common.h"
#include "IfxEmem_regdef.h"
#include "IfxEmem_reg.h"
#include "EMEM_SIM.h"

static void * EMEM_debug_file = NULL;
static unsigned char buf[100] = {0};
static Ifx_EMEM emem_regs = {0U};


static int SIMULAPI EMEM_CLC_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI EMEM_CLC_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI EMEM_ID_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI EMEM_ID_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI EMEM_SBRCTR_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI EMEM_SBRCTR_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI EMEM_TILECC_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI EMEM_TILECC_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI EMEM_TILECONFIG_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI EMEM_TILECONFIG_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI EMEM_TILECONFIGXM_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI EMEM_TILECONFIGXM_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI EMEM_TILECT_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI EMEM_TILECT_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI EMEM_TILESTATE_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI EMEM_TILESTATE_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI EMEM_TILESTATEXM_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI EMEM_TILESTATEXM_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);


static reg_opt emem_regs_opt[] = {
	{0, &EMEM_CLC, EMEM_CLC_read, EMEM_CLC_write},
	{0, &EMEM_ID, EMEM_ID_read, EMEM_ID_write},
	{0, &EMEM_SBRCTR, EMEM_SBRCTR_read, EMEM_SBRCTR_write},
	{0, &EMEM_TILECC, EMEM_TILECC_read, EMEM_TILECC_write},
	{0, &EMEM_TILECONFIG, EMEM_TILECONFIG_read, EMEM_TILECONFIG_write},
	{0, &EMEM_TILECONFIGXM, EMEM_TILECONFIGXM_read, EMEM_TILECONFIGXM_write},
	{0, &EMEM_TILECT, EMEM_TILECT_read, EMEM_TILECT_write},
	{0, &EMEM_TILESTATE, EMEM_TILESTATE_read, EMEM_TILESTATE_write},
	{0, &EMEM_TILESTATEXM, EMEM_TILESTATEXM_read, EMEM_TILESTATEXM_write}

};


static int SIMULAPI EMEM_CLC_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	memcpy(&(cbs->x.bus.data), (unsigned char *)&emem_regs.CLC.U + (cbs->x.bus.address - (simulWord)&EMEM_CLC), cbs->x.bus.width / 8U);

	sprintf(buf, "EMEM_CLC read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, EMEM_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI EMEM_CLC_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	memcpy((unsigned char *)&emem_regs.CLC.U + (cbs->x.bus.address - (simulWord)&EMEM_CLC), &(cbs->x.bus.data), cbs->x.bus.width / 8U);

	sprintf(buf, "EMEM_CLC read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, EMEM_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI EMEM_ID_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	memcpy(&(cbs->x.bus.data), (unsigned char *)&emem_regs.ID.U + (cbs->x.bus.address - (simulWord)&EMEM_ID), cbs->x.bus.width / 8U);

	sprintf(buf, "EMEM_ID read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, EMEM_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI EMEM_ID_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	memcpy((unsigned char *)&emem_regs.ID.U + (cbs->x.bus.address - (simulWord)&EMEM_ID), &(cbs->x.bus.data), cbs->x.bus.width / 8U);

	sprintf(buf, "EMEM_ID read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, EMEM_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI EMEM_SBRCTR_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	emem_regs.SBRCTR.B.STBLOCK = 1;

	memcpy(&(cbs->x.bus.data), (unsigned char *)&emem_regs.SBRCTR.U + (cbs->x.bus.address - (simulWord)&EMEM_SBRCTR), cbs->x.bus.width / 8U);

	sprintf(buf, "EMEM_SBRCTR read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, EMEM_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI EMEM_SBRCTR_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	memcpy((unsigned char *)&emem_regs.SBRCTR.U + (cbs->x.bus.address - (simulWord)&EMEM_SBRCTR), &(cbs->x.bus.data), cbs->x.bus.width / 8U);

	sprintf(buf, "EMEM_SBRCTR read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, EMEM_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI EMEM_TILECC_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	memcpy(&(cbs->x.bus.data), (unsigned char *)&emem_regs.TILECC.U + (cbs->x.bus.address - (simulWord)&EMEM_TILECC), cbs->x.bus.width / 8U);

	sprintf(buf, "EMEM_TILECC read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, EMEM_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI EMEM_TILECC_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	memcpy((unsigned char *)&emem_regs.TILECC.U + (cbs->x.bus.address - (simulWord)&EMEM_TILECC), &(cbs->x.bus.data), cbs->x.bus.width / 8U);

	sprintf(buf, "EMEM_TILECC read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, EMEM_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI EMEM_TILECONFIG_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	memcpy(&(cbs->x.bus.data), (unsigned char *)&emem_regs.TILECONFIG.U + (cbs->x.bus.address - (simulWord)&EMEM_TILECONFIG), cbs->x.bus.width / 8U);

	sprintf(buf, "EMEM_TILECONFIG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, EMEM_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI EMEM_TILECONFIG_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	memcpy((unsigned char *)&emem_regs.TILECONFIG.U + (cbs->x.bus.address - (simulWord)&EMEM_TILECONFIG), &(cbs->x.bus.data), cbs->x.bus.width / 8U);

	sprintf(buf, "EMEM_TILECONFIG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, EMEM_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI EMEM_TILECONFIGXM_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	memcpy(&(cbs->x.bus.data), (unsigned char *)&emem_regs.TILECONFIGXM.U + (cbs->x.bus.address - (simulWord)&EMEM_TILECONFIGXM), cbs->x.bus.width / 8U);

	sprintf(buf, "EMEM_TILECONFIGXM read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, EMEM_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI EMEM_TILECONFIGXM_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	memcpy((unsigned char *)&emem_regs.TILECONFIGXM.U + (cbs->x.bus.address - (simulWord)&EMEM_TILECONFIGXM), &(cbs->x.bus.data), cbs->x.bus.width / 8U);

	sprintf(buf, "EMEM_TILECONFIGXM read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, EMEM_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI EMEM_TILECT_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	memcpy(&(cbs->x.bus.data), (unsigned char *)&emem_regs.TILECT.U + (cbs->x.bus.address - (simulWord)&EMEM_TILECT), cbs->x.bus.width / 8U);

	sprintf(buf, "EMEM_TILECT read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, EMEM_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI EMEM_TILECT_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	memcpy((unsigned char *)&emem_regs.TILECT.U + (cbs->x.bus.address - (simulWord)&EMEM_TILECT), &(cbs->x.bus.data), cbs->x.bus.width / 8U);

	sprintf(buf, "EMEM_TILECT read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, EMEM_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI EMEM_TILESTATE_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	emem_regs.TILESTATE.U = 0x00000000;

	memcpy(&(cbs->x.bus.data), (unsigned char *)&emem_regs.TILESTATE.U + (cbs->x.bus.address - (simulWord)&EMEM_TILESTATE), cbs->x.bus.width / 8U);

	sprintf(buf, "EMEM_TILESTATE read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, EMEM_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI EMEM_TILESTATE_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	memcpy((unsigned char *)&emem_regs.TILESTATE.U + (cbs->x.bus.address - (simulWord)&EMEM_TILESTATE), &(cbs->x.bus.data), cbs->x.bus.width / 8U);

	sprintf(buf, "EMEM_TILESTATE read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, EMEM_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI EMEM_TILESTATEXM_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	emem_regs.TILESTATEXM.B.XCM0 = 0x00;

	memcpy(&(cbs->x.bus.data), (unsigned char *)&emem_regs.TILESTATEXM.U + (cbs->x.bus.address - (simulWord)&EMEM_TILESTATEXM), cbs->x.bus.width / 8U);

	sprintf(buf, "EMEM_TILESTATEXM read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, EMEM_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI EMEM_TILESTATEXM_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	memcpy((unsigned char *)&emem_regs.TILESTATEXM.U + (cbs->x.bus.address - (simulWord)&EMEM_TILESTATEXM), &(cbs->x.bus.data), cbs->x.bus.width / 8U);

	sprintf(buf, "EMEM_TILESTATEXM read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, EMEM_debug_file, buf);

	return SIMUL_MEMORY_OK;
}





static void EMEM_reg_init(void)
{
	emem_regs.TILESTATE.U = 0xFFFFFFFF;
	emem_regs.TILESTATEXM.U = 0x0000003;
	emem_regs.CLC.U = 0x0000003;
	emem_regs.ID.U = 0x00E0C004;
}

void EMEM_Init(simulProcessor processor, simulCallbackStruct * cbs) 
{
	simulWord   from = 0;
	simulWord	to = 0;
	unsigned int i = 0;

	EMEM_debug_file = SIMUL_OpenFile(processor, "./debug_emem.log", SIMUL_FILE_CREATE);
	if (EMEM_debug_file != NULL)
	{
		SIMUL_Warning(processor, "create file debug_emem.log success!");
	} 
	else
	{
		SIMUL_Warning(processor, "create file debug_emem.log failed!");
		return ;
	}

	sprintf(buf, "EMEM_init bus type %d\n", cbs->x.init.argpbustype[1]);
	SIMUL_WritelineFile(processor, EMEM_debug_file, buf);

	EMEM_reg_init();

	for (i = 0; i< (sizeof(emem_regs_opt)/sizeof(reg_opt)); i++)
	{
		if (emem_regs_opt[i].reg_read_func_ptr != NULL)
		{
			from = emem_regs_opt[i].offset;
			to = from + 3U;

			sprintf(buf, "emem_init read func ptr 0x%x  from 0x%x to 0x%x\n", emem_regs_opt[i].reg_read_func_ptr, from, to);
			SIMUL_WriteFile(processor, EMEM_debug_file, buf, strlen(buf));

			SIMUL_RegisterBusReadCallback(processor, emem_regs_opt[i].reg_read_func_ptr, (simulPtr)NULL, cbs->x.init.argpbustype[1], (simulWord *)&from, (simulWord *)&to);
		}
		if (emem_regs_opt[i].reg_write_func_ptr != NULL)
		{
			from = emem_regs_opt[i].offset;
			to = from + 3U;

			sprintf(buf, "emem_init write func ptr 0x%x  from 0x%x to 0x%x\n", emem_regs_opt[i].reg_write_func_ptr, from, to);
			SIMUL_WriteFile(processor, EMEM_debug_file, buf, strlen(buf));

			SIMUL_RegisterBusWriteCallback(processor, emem_regs_opt[i].reg_write_func_ptr  , (simulPtr)NULL, cbs->x.init.argpbustype[1], (simulWord *)&from, (simulWord *)&to);
		}
	}
}