#include "simul.h"
#include "reg_common.h"
#include "IfxCpu_regdef.h"
#include "IfxCpu_reg.h"
#include "CPU_SIM.h"



static void * CPU_debug_file = NULL;
static unsigned char buf[100] = {0};
static Ifx_CPU cpu_regs[3] = {0U};
static Ifx_CPU_SPROT cpu_sprot[3] = {0};


static int SIMULAPI CPU_SEGEN_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_SEGEN_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_TASK_ASI_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_TASK_ASI_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_PMA0_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_PMA0_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_PMA1_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_PMA1_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_PMA2_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_PMA2_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_DCON2_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_DCON2_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_SMACON_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_SMACON_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_DSTR_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_DSTR_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_DATR_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_DATR_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_DEADD_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_DEADD_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_DIEAR_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_DIEAR_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_DIETR_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_DIETR_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_DCON0_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_DCON0_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_PSTR_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_PSTR_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_PCON1_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_PCON1_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_PCON2_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_PCON2_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_PCON0_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_PCON0_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_PIEAR_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_PIEAR_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_PIETR_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_PIETR_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_COMPAT_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_COMPAT_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_FPU_TRAP_CON_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_FPU_TRAP_CON_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_FPU_TRAP_PC_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_FPU_TRAP_PC_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_FPU_TRAP_OPC_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_FPU_TRAP_OPC_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_FPU_TRAP_SRC1_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_FPU_TRAP_SRC1_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_FPU_TRAP_SRC2_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_FPU_TRAP_SRC2_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_FPU_TRAP_SRC3_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_FPU_TRAP_SRC3_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_DPR_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_DPR_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_CPR_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_CPR_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_CPXE_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_CPXE_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_DPRE_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_DPRE_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_DPWE_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_DPWE_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_TPS_CON_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_TPS_CON_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_TPS_TIMER_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_TPS_TIMER_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_TR_EVT_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_TR_EVT_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_TR_ADR_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_TR_ADR_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_CCTRL_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_CCTRL_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_CCNT_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_CCNT_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_ICNT_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_ICNT_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_M1CNT_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_M1CNT_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_M2CNT_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_M2CNT_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_M3CNT_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_M3CNT_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_DBGSR_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_DBGSR_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_EXEVT_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_EXEVT_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_CREVT_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_CREVT_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_SWEVT_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_SWEVT_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_TRIG_ACC_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_TRIG_ACC_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_DMS_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_DMS_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_DCX_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_DCX_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_DBGTCR_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_DBGTCR_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_PCXI_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_PCXI_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_PSW_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_PSW_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_PC_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_PC_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_SYSCON_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_SYSCON_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_CPU_ID_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_CPU_ID_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_CORE_ID_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_CORE_ID_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_BIV_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_BIV_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_BTV_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_BTV_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_ISP_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_ISP_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_ICR_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_ICR_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_FCX_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_FCX_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_LCX_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_LCX_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_CUS_ID_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_CUS_ID_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_D_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_D_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_A_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_A_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_SPROT_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI CPU_SPROT_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);


static reg_opt cpu_regs_opt[] = {
	{0, &CPU0_SEGEN, CPU_SEGEN_read, CPU_SEGEN_write},
	{0, &CPU1_SEGEN, CPU_SEGEN_read, CPU_SEGEN_write},
	{0, &CPU2_SEGEN, CPU_SEGEN_read, CPU_SEGEN_write},
	{0, &CPU0_TASK_ASI, CPU_TASK_ASI_read, CPU_TASK_ASI_write},
	{0, &CPU1_TASK_ASI, CPU_TASK_ASI_read, CPU_TASK_ASI_write},
	{0, &CPU2_TASK_ASI, CPU_TASK_ASI_read, CPU_TASK_ASI_write},
	{0, &CPU0_PMA0, CPU_PMA0_read, CPU_PMA0_write},
	{0, &CPU0_PMA1, CPU_PMA1_read, CPU_PMA1_write},
	{0, &CPU0_PMA2, CPU_PMA2_read, CPU_PMA2_write},
	{0, &CPU1_PMA0, CPU_PMA0_read, CPU_PMA0_write},
	{0, &CPU1_PMA1, CPU_PMA1_read, CPU_PMA1_write},
	{0, &CPU1_PMA2, CPU_PMA2_read, CPU_PMA2_write},
	{0, &CPU2_PMA0, CPU_PMA0_read, CPU_PMA0_write},
	{0, &CPU2_PMA1, CPU_PMA1_read, CPU_PMA1_write},
	{0, &CPU2_PMA2, CPU_PMA2_read, CPU_PMA2_write},
	{0, &CPU0_DCON2, CPU_DCON2_read, CPU_DCON2_write},
	{0, &CPU1_DCON2, CPU_DCON2_read, CPU_DCON2_write},
	{0, &CPU2_DCON2, CPU_DCON2_read, CPU_DCON2_write},
	{0, &CPU0_SMACON, CPU_SMACON_read, CPU_SMACON_write},
	{0, &CPU1_SMACON, CPU_SMACON_read, CPU_SMACON_write},
	{0, &CPU2_SMACON, CPU_SMACON_read, CPU_SMACON_write},
	{0, &CPU0_DSTR, CPU_DSTR_read, CPU_DSTR_write},
	{0, &CPU1_DSTR, CPU_DSTR_read, CPU_DSTR_write},
	{0, &CPU2_DSTR, CPU_DSTR_read, CPU_DSTR_write},
	{0, &CPU0_DATR, CPU_DATR_read, CPU_DATR_write},
	{0, &CPU1_DATR, CPU_DATR_read, CPU_DATR_write},
	{0, &CPU2_DATR, CPU_DATR_read, CPU_DATR_write},
	{0, &CPU0_DEADD, CPU_DEADD_read, CPU_DEADD_write},
	{0, &CPU1_DEADD, CPU_DEADD_read, CPU_DEADD_write},
	{0, &CPU2_DEADD, CPU_DEADD_read, CPU_DEADD_write},
	{0, &CPU0_DIEAR, CPU_DEADD_read, CPU_DEADD_write},
	{0, &CPU1_DIEAR, CPU_DEADD_read, CPU_DEADD_write},
	{0, &CPU2_DIEAR, CPU_DEADD_read, CPU_DEADD_write},
	{0, &CPU0_DIETR, CPU_DIETR_read, CPU_DIETR_write},
	{0, &CPU1_DIETR, CPU_DIETR_read, CPU_DIETR_write},
	{0, &CPU2_DIETR, CPU_DIETR_read, CPU_DIETR_write},
	{0, &CPU0_DCON0, CPU_DCON0_read, CPU_DCON0_write},
	{0, &CPU1_DCON0, CPU_DCON0_read, CPU_DCON0_write},
	{0, &CPU2_DCON0, CPU_DCON0_read, CPU_DCON0_write},
	{0, &CPU0_PSTR, CPU_PSTR_read, CPU_PSTR_write},
	{0, &CPU1_PSTR, CPU_PSTR_read, CPU_PSTR_write},
	{0, &CPU2_PSTR, CPU_PSTR_read, CPU_PSTR_write},
	{0, &CPU0_PCON1, CPU_PCON1_read, CPU_PCON1_write},
	{0, &CPU1_PCON1, CPU_PCON1_read, CPU_PCON1_write},
	{0, &CPU2_PCON1, CPU_PCON1_read, CPU_PCON1_write},
	{0, &CPU0_PCON2, CPU_PCON2_read, CPU_PCON2_write},
	{0, &CPU1_PCON2, CPU_PCON2_read, CPU_PCON2_write},
	{0, &CPU2_PCON2, CPU_PCON2_read, CPU_PCON2_write},
	{0, &CPU0_PCON0, CPU_PCON0_read, CPU_PCON0_write},
	{0, &CPU1_PCON0, CPU_PCON0_read, CPU_PCON0_write},
	{0, &CPU2_PCON0, CPU_PCON0_read, CPU_PCON0_write},
	{0, &CPU0_PIEAR, CPU_PIEAR_read, CPU_PIEAR_write},
	{0, &CPU1_PIEAR, CPU_PIEAR_read, CPU_PIEAR_write},
	{0, &CPU2_PIEAR, CPU_PIEAR_read, CPU_PIEAR_write},
	{0, &CPU0_PIETR, CPU_PIETR_read, CPU_PIETR_write},
	{0, &CPU1_PIETR, CPU_PIETR_read, CPU_PIETR_write},
	{0, &CPU2_PIETR, CPU_PIETR_read, CPU_PIETR_write},
	{0, &CPU0_COMPAT, CPU_COMPAT_read, CPU_COMPAT_write},
	{0, &CPU1_COMPAT, CPU_COMPAT_read, CPU_COMPAT_write},
	{0, &CPU2_COMPAT, CPU_COMPAT_read, CPU_COMPAT_write},
	{0, &CPU0_FPU_TRAP_CON, CPU_FPU_TRAP_CON_read, CPU_FPU_TRAP_CON_write},
	{0, &CPU1_FPU_TRAP_CON, CPU_FPU_TRAP_CON_read, CPU_FPU_TRAP_CON_write},
	{0, &CPU2_FPU_TRAP_CON, CPU_FPU_TRAP_CON_read, CPU_FPU_TRAP_CON_write},
	{0, &CPU0_FPU_TRAP_PC, CPU_FPU_TRAP_PC_read, CPU_FPU_TRAP_PC_write},
	{0, &CPU1_FPU_TRAP_PC, CPU_FPU_TRAP_PC_read, CPU_FPU_TRAP_PC_write},
	{0, &CPU2_FPU_TRAP_PC, CPU_FPU_TRAP_PC_read, CPU_FPU_TRAP_PC_write},
	{0, &CPU0_FPU_TRAP_OPC, CPU_FPU_TRAP_OPC_read, CPU_FPU_TRAP_OPC_write},
	{0, &CPU1_FPU_TRAP_OPC, CPU_FPU_TRAP_OPC_read, CPU_FPU_TRAP_OPC_write},
	{0, &CPU2_FPU_TRAP_OPC, CPU_FPU_TRAP_OPC_read, CPU_FPU_TRAP_OPC_write},
	{0, &CPU0_FPU_TRAP_SRC1, CPU_FPU_TRAP_SRC1_read, CPU_FPU_TRAP_SRC1_write},
	{0, &CPU1_FPU_TRAP_SRC1, CPU_FPU_TRAP_SRC1_read, CPU_FPU_TRAP_SRC1_write},
	{0, &CPU2_FPU_TRAP_SRC1, CPU_FPU_TRAP_SRC1_read, CPU_FPU_TRAP_SRC1_write},
	{0, &CPU0_FPU_TRAP_SRC2, CPU_FPU_TRAP_SRC2_read, CPU_FPU_TRAP_SRC2_write},
	{0, &CPU1_FPU_TRAP_SRC2, CPU_FPU_TRAP_SRC2_read, CPU_FPU_TRAP_SRC2_write},
	{0, &CPU2_FPU_TRAP_SRC2, CPU_FPU_TRAP_SRC2_read, CPU_FPU_TRAP_SRC2_write},
	{0, &CPU0_FPU_TRAP_SRC3, CPU_FPU_TRAP_SRC3_read, CPU_FPU_TRAP_SRC3_write},
	{0, &CPU1_FPU_TRAP_SRC3, CPU_FPU_TRAP_SRC3_read, CPU_FPU_TRAP_SRC3_write},
	{0, &CPU2_FPU_TRAP_SRC3, CPU_FPU_TRAP_SRC3_read, CPU_FPU_TRAP_SRC3_write},
  
	{0, &CPU0_DPR0_L, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU1_DPR0_L, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU2_DPR0_L, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU0_DPR0_U, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU1_DPR0_U, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU2_DPR0_U, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU0_DPR1_L, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU1_DPR1_L, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU2_DPR1_L, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU0_DPR1_U, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU1_DPR1_U, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU2_DPR1_U, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU0_DPR2_L, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU1_DPR2_L, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU2_DPR2_L, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU0_DPR2_U, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU1_DPR2_U, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU2_DPR2_U, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU0_DPR3_L, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU1_DPR3_L, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU2_DPR3_L, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU0_DPR3_U, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU1_DPR3_U, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU2_DPR3_U, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU0_DPR4_L, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU1_DPR4_L, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU2_DPR4_L, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU0_DPR4_U, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU1_DPR4_U, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU2_DPR4_U, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU0_DPR5_L, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU1_DPR5_L, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU2_DPR5_L, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU0_DPR5_U, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU1_DPR5_U, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU2_DPR5_U, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU0_DPR6_L, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU1_DPR6_L, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU2_DPR6_L, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU0_DPR6_U, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU1_DPR6_U, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU2_DPR6_U, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU0_DPR7_L, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU1_DPR7_L, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU2_DPR7_L, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU0_DPR7_U, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU1_DPR7_U, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU2_DPR7_U, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU0_DPR8_L, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU1_DPR8_L, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU2_DPR8_L, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU0_DPR8_U, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU1_DPR8_U, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU2_DPR8_U, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU0_DPR9_L, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU1_DPR9_L, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU2_DPR9_L, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU0_DPR9_U, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU1_DPR9_U, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU2_DPR9_U, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU0_DPR10_L, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU1_DPR10_L, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU2_DPR10_L, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU0_DPR10_U, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU1_DPR10_U, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU2_DPR10_U, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU0_DPR11_L, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU1_DPR11_L, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU2_DPR11_L, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU0_DPR11_U, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU1_DPR11_U, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU2_DPR11_U, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU0_DPR12_L, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU1_DPR12_L, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU2_DPR12_L, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU0_DPR12_U, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU1_DPR12_U, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU2_DPR12_U, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU0_DPR13_L, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU1_DPR13_L, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU2_DPR13_L, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU0_DPR13_U, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU1_DPR13_U, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU2_DPR13_U, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU0_DPR14_L, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU1_DPR14_L, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU2_DPR14_L, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU0_DPR14_U, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU1_DPR14_U, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU2_DPR14_U, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU0_DPR15_L, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU1_DPR15_L, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU2_DPR15_L, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU0_DPR15_U, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU1_DPR15_U, CPU_DPR_read, CPU_DPR_write},
	{0, &CPU2_DPR15_U, CPU_DPR_read, CPU_DPR_write},
  
	{0, &CPU0_CPR0_L, CPU_CPR_read, CPU_CPR_write},
	{0, &CPU0_CPR0_U, CPU_CPR_read, CPU_CPR_write},
	{0, &CPU0_CPR1_L, CPU_CPR_read, CPU_CPR_write},
	{0, &CPU0_CPR1_U, CPU_CPR_read, CPU_CPR_write},
	{0, &CPU0_CPR2_L, CPU_CPR_read, CPU_CPR_write},
	{0, &CPU0_CPR2_U, CPU_CPR_read, CPU_CPR_write},
	{0, &CPU0_CPR3_L, CPU_CPR_read, CPU_CPR_write},
	{0, &CPU0_CPR3_U, CPU_CPR_read, CPU_CPR_write},
	{0, &CPU0_CPR4_L, CPU_CPR_read, CPU_CPR_write},
	{0, &CPU0_CPR4_U, CPU_CPR_read, CPU_CPR_write},
	{0, &CPU0_CPR5_L, CPU_CPR_read, CPU_CPR_write},
	{0, &CPU0_CPR5_U, CPU_CPR_read, CPU_CPR_write},
	{0, &CPU0_CPR6_L, CPU_CPR_read, CPU_CPR_write},
	{0, &CPU0_CPR6_U, CPU_CPR_read, CPU_CPR_write},
	{0, &CPU0_CPR7_L, CPU_CPR_read, CPU_CPR_write},
	{0, &CPU0_CPR7_U, CPU_CPR_read, CPU_CPR_write},
	{0, &CPU1_CPR0_L, CPU_CPR_read, CPU_CPR_write},
	{0, &CPU1_CPR0_U, CPU_CPR_read, CPU_CPR_write},
	{0, &CPU1_CPR1_L, CPU_CPR_read, CPU_CPR_write},
	{0, &CPU1_CPR1_U, CPU_CPR_read, CPU_CPR_write},
	{0, &CPU1_CPR2_L, CPU_CPR_read, CPU_CPR_write},
	{0, &CPU1_CPR2_U, CPU_CPR_read, CPU_CPR_write},
	{0, &CPU1_CPR3_L, CPU_CPR_read, CPU_CPR_write},
	{0, &CPU1_CPR3_U, CPU_CPR_read, CPU_CPR_write},
	{0, &CPU1_CPR4_L, CPU_CPR_read, CPU_CPR_write},
	{0, &CPU1_CPR4_U, CPU_CPR_read, CPU_CPR_write},
	{0, &CPU1_CPR5_L, CPU_CPR_read, CPU_CPR_write},
	{0, &CPU1_CPR5_U, CPU_CPR_read, CPU_CPR_write},
	{0, &CPU1_CPR6_L, CPU_CPR_read, CPU_CPR_write},
	{0, &CPU1_CPR6_U, CPU_CPR_read, CPU_CPR_write},
	{0, &CPU1_CPR7_L, CPU_CPR_read, CPU_CPR_write},
	{0, &CPU1_CPR7_U, CPU_CPR_read, CPU_CPR_write},
	{0, &CPU2_CPR0_L, CPU_CPR_read, CPU_CPR_write},
	{0, &CPU2_CPR0_U, CPU_CPR_read, CPU_CPR_write},
	{0, &CPU2_CPR1_L, CPU_CPR_read, CPU_CPR_write},
	{0, &CPU2_CPR1_U, CPU_CPR_read, CPU_CPR_write},
	{0, &CPU2_CPR2_L, CPU_CPR_read, CPU_CPR_write},
	{0, &CPU2_CPR2_U, CPU_CPR_read, CPU_CPR_write},
	{0, &CPU2_CPR3_L, CPU_CPR_read, CPU_CPR_write},
	{0, &CPU2_CPR3_U, CPU_CPR_read, CPU_CPR_write},
	{0, &CPU2_CPR4_L, CPU_CPR_read, CPU_CPR_write},
	{0, &CPU2_CPR4_U, CPU_CPR_read, CPU_CPR_write},
	{0, &CPU2_CPR5_L, CPU_CPR_read, CPU_CPR_write},
	{0, &CPU2_CPR5_U, CPU_CPR_read, CPU_CPR_write},
	{0, &CPU2_CPR6_L, CPU_CPR_read, CPU_CPR_write},
	{0, &CPU2_CPR6_U, CPU_CPR_read, CPU_CPR_write},
	{0, &CPU2_CPR7_L, CPU_CPR_read, CPU_CPR_write},
	{0, &CPU2_CPR7_U, CPU_CPR_read, CPU_CPR_write},
  
	{0, &CPU0_CPXE0, CPU_CPXE_read, CPU_CPXE_write},
	{0, &CPU1_CPXE0, CPU_CPXE_read, CPU_CPXE_write},
	{0, &CPU2_CPXE0, CPU_CPXE_read, CPU_CPXE_write},
	{0, &CPU0_CPXE1, CPU_CPXE_read, CPU_CPXE_write},
	{0, &CPU1_CPXE1, CPU_CPXE_read, CPU_CPXE_write},
	{0, &CPU2_CPXE1, CPU_CPXE_read, CPU_CPXE_write},
	{0, &CPU0_CPXE2, CPU_CPXE_read, CPU_CPXE_write},
	{0, &CPU1_CPXE2, CPU_CPXE_read, CPU_CPXE_write},
	{0, &CPU2_CPXE2, CPU_CPXE_read, CPU_CPXE_write},
  
	{0, &CPU0_DPRE0, CPU_DPRE_read, CPU_DPRE_write},
	{0, &CPU1_DPRE0, CPU_DPRE_read, CPU_DPRE_write},
	{0, &CPU2_DPRE0, CPU_DPRE_read, CPU_DPRE_write},
	{0, &CPU0_DPRE1, CPU_DPRE_read, CPU_DPRE_write},
	{0, &CPU1_DPRE1, CPU_DPRE_read, CPU_DPRE_write},
	{0, &CPU2_DPRE1, CPU_DPRE_read, CPU_DPRE_write},
	{0, &CPU0_DPRE2, CPU_DPRE_read, CPU_DPRE_write},
	{0, &CPU1_DPRE2, CPU_DPRE_read, CPU_DPRE_write},
	{0, &CPU2_DPRE2, CPU_DPRE_read, CPU_DPRE_write},
	{0, &CPU0_DPRE3, CPU_DPRE_read, CPU_DPRE_write},
	{0, &CPU1_DPRE3, CPU_DPRE_read, CPU_DPRE_write},
	{0, &CPU2_DPRE3, CPU_DPRE_read, CPU_DPRE_write},
  
	{0, &CPU0_DPWE0, CPU_DPWE_read, CPU_DPWE_write},
	{0, &CPU1_DPWE0, CPU_DPWE_read, CPU_DPWE_write},
	{0, &CPU2_DPWE0, CPU_DPWE_read, CPU_DPWE_write},
	{0, &CPU0_DPWE1, CPU_DPWE_read, CPU_DPWE_write},
	{0, &CPU1_DPWE1, CPU_DPWE_read, CPU_DPWE_write},
	{0, &CPU2_DPWE1, CPU_DPWE_read, CPU_DPWE_write},
	{0, &CPU0_DPWE2, CPU_DPWE_read, CPU_DPWE_write},
	{0, &CPU1_DPWE2, CPU_DPWE_read, CPU_DPWE_write},
	{0, &CPU2_DPWE2, CPU_DPWE_read, CPU_DPWE_write},
	{0, &CPU0_DPWE3, CPU_DPWE_read, CPU_DPWE_write},
	{0, &CPU1_DPWE3, CPU_DPWE_read, CPU_DPWE_write},
	{0, &CPU2_DPWE3, CPU_DPWE_read, CPU_DPWE_write},
  
	{0, &CPU0_TPS_CON, CPU_TPS_CON_read, CPU_TPS_CON_write},
	{0, &CPU1_TPS_CON, CPU_TPS_CON_read, CPU_TPS_CON_write},
	{0, &CPU2_TPS_CON, CPU_TPS_CON_read, CPU_TPS_CON_write},
  
	{0, &CPU0_TPS_TIMER0, CPU_TPS_TIMER_read, CPU_TPS_TIMER_write},
	{0, &CPU1_TPS_TIMER0, CPU_TPS_TIMER_read, CPU_TPS_TIMER_write},
	{0, &CPU2_TPS_TIMER0, CPU_TPS_TIMER_read, CPU_TPS_TIMER_write},
	{0, &CPU0_TPS_TIMER1, CPU_TPS_TIMER_read, CPU_TPS_TIMER_write},
	{0, &CPU1_TPS_TIMER1, CPU_TPS_TIMER_read, CPU_TPS_TIMER_write},
	{0, &CPU2_TPS_TIMER1, CPU_TPS_TIMER_read, CPU_TPS_TIMER_write},
	{0, &CPU0_TPS_TIMER2, CPU_TPS_TIMER_read, CPU_TPS_TIMER_write},
	{0, &CPU1_TPS_TIMER2, CPU_TPS_TIMER_read, CPU_TPS_TIMER_write},
	{0, &CPU2_TPS_TIMER2, CPU_TPS_TIMER_read, CPU_TPS_TIMER_write},
  
	{0, &CPU0_TR0_EVT, CPU_TR_EVT_read, CPU_TR_EVT_write},
	{0, &CPU1_TR0_EVT, CPU_TR_EVT_read, CPU_TR_EVT_write},
	{0, &CPU2_TR0_EVT, CPU_TR_EVT_read, CPU_TR_EVT_write},
	{0, &CPU0_TR0_ADR, CPU_TR_ADR_read, CPU_TR_ADR_write},
	{0, &CPU1_TR0_ADR, CPU_TR_ADR_read, CPU_TR_ADR_write},
	{0, &CPU2_TR0_ADR, CPU_TR_ADR_read, CPU_TR_ADR_write},
	{0, &CPU0_TR1_EVT, CPU_TR_EVT_read, CPU_TR_EVT_write},
	{0, &CPU1_TR1_EVT, CPU_TR_EVT_read, CPU_TR_EVT_write},
	{0, &CPU2_TR1_EVT, CPU_TR_EVT_read, CPU_TR_EVT_write},
	{0, &CPU0_TR1_ADR, CPU_TR_ADR_read, CPU_TR_ADR_write},
	{0, &CPU1_TR1_ADR, CPU_TR_ADR_read, CPU_TR_ADR_write},
	{0, &CPU2_TR1_ADR, CPU_TR_ADR_read, CPU_TR_ADR_write},
	{0, &CPU0_TR2_EVT, CPU_TR_EVT_read, CPU_TR_EVT_write},
	{0, &CPU1_TR2_EVT, CPU_TR_EVT_read, CPU_TR_EVT_write},
	{0, &CPU2_TR2_EVT, CPU_TR_EVT_read, CPU_TR_EVT_write},
	{0, &CPU0_TR2_ADR, CPU_TR_ADR_read, CPU_TR_ADR_write},
	{0, &CPU1_TR2_ADR, CPU_TR_ADR_read, CPU_TR_ADR_write},
	{0, &CPU2_TR2_ADR, CPU_TR_ADR_read, CPU_TR_ADR_write},
	{0, &CPU0_TR3_EVT, CPU_TR_EVT_read, CPU_TR_EVT_write},
	{0, &CPU1_TR3_EVT, CPU_TR_EVT_read, CPU_TR_EVT_write},
	{0, &CPU2_TR3_EVT, CPU_TR_EVT_read, CPU_TR_EVT_write},
	{0, &CPU0_TR3_ADR, CPU_TR_ADR_read, CPU_TR_ADR_write},
	{0, &CPU1_TR3_ADR, CPU_TR_ADR_read, CPU_TR_ADR_write},
	{0, &CPU2_TR3_ADR, CPU_TR_ADR_read, CPU_TR_ADR_write},
	{0, &CPU0_TR4_EVT, CPU_TR_EVT_read, CPU_TR_EVT_write},
	{0, &CPU1_TR4_EVT, CPU_TR_EVT_read, CPU_TR_EVT_write},
	{0, &CPU2_TR4_EVT, CPU_TR_EVT_read, CPU_TR_EVT_write},
	{0, &CPU0_TR4_ADR, CPU_TR_ADR_read, CPU_TR_ADR_write},
	{0, &CPU1_TR4_ADR, CPU_TR_ADR_read, CPU_TR_ADR_write},
	{0, &CPU2_TR4_ADR, CPU_TR_ADR_read, CPU_TR_ADR_write},
	{0, &CPU0_TR5_EVT, CPU_TR_EVT_read, CPU_TR_EVT_write},
	{0, &CPU1_TR5_EVT, CPU_TR_EVT_read, CPU_TR_EVT_write},
	{0, &CPU2_TR5_EVT, CPU_TR_EVT_read, CPU_TR_EVT_write},
	{0, &CPU0_TR5_ADR, CPU_TR_ADR_read, CPU_TR_ADR_write},
	{0, &CPU1_TR5_ADR, CPU_TR_ADR_read, CPU_TR_ADR_write},
	{0, &CPU2_TR5_ADR, CPU_TR_ADR_read, CPU_TR_ADR_write},
	{0, &CPU0_TR6_EVT, CPU_TR_EVT_read, CPU_TR_EVT_write},
	{0, &CPU1_TR6_EVT, CPU_TR_EVT_read, CPU_TR_EVT_write},
	{0, &CPU2_TR6_EVT, CPU_TR_EVT_read, CPU_TR_EVT_write},
	{0, &CPU0_TR6_ADR, CPU_TR_ADR_read, CPU_TR_ADR_write},
	{0, &CPU1_TR6_ADR, CPU_TR_ADR_read, CPU_TR_ADR_write},
	{0, &CPU2_TR6_ADR, CPU_TR_ADR_read, CPU_TR_ADR_write},
	{0, &CPU0_TR7_EVT, CPU_TR_EVT_read, CPU_TR_EVT_write},
	{0, &CPU1_TR7_EVT, CPU_TR_EVT_read, CPU_TR_EVT_write},
	{0, &CPU2_TR7_EVT, CPU_TR_EVT_read, CPU_TR_EVT_write},
	{0, &CPU0_TR7_ADR, CPU_TR_ADR_read, CPU_TR_ADR_write},
	{0, &CPU1_TR7_ADR, CPU_TR_ADR_read, CPU_TR_ADR_write},
	{0, &CPU2_TR7_ADR, CPU_TR_ADR_read, CPU_TR_ADR_write},
  
	{0, &CPU0_CCTRL, CPU_CCTRL_read, CPU_CCTRL_write},
	{0, &CPU1_CCTRL, CPU_CCTRL_read, CPU_CCTRL_write},
	{0, &CPU2_CCTRL, CPU_CCTRL_read, CPU_CCTRL_write},
	{0, &CPU0_CCNT, CPU_CCNT_read, CPU_CCNT_write},
	{0, &CPU1_CCNT, CPU_CCNT_read, CPU_CCNT_write},
	{0, &CPU2_CCNT, CPU_CCNT_read, CPU_CCNT_write},
	{0, &CPU0_ICNT, CPU_ICNT_read, CPU_ICNT_write},
	{0, &CPU1_ICNT, CPU_ICNT_read, CPU_ICNT_write},
	{0, &CPU2_ICNT, CPU_ICNT_read, CPU_ICNT_write},
	{0, &CPU0_M1CNT, CPU_M1CNT_read, CPU_M1CNT_write},
	{0, &CPU1_M1CNT, CPU_M1CNT_read, CPU_M1CNT_write},
	{0, &CPU2_M1CNT, CPU_M1CNT_read, CPU_M1CNT_write},
	{0, &CPU0_M2CNT, CPU_M2CNT_read, CPU_M2CNT_write},
	{0, &CPU1_M2CNT, CPU_M2CNT_read, CPU_M2CNT_write},
	{0, &CPU2_M2CNT, CPU_M2CNT_read, CPU_M2CNT_write},
	{0, &CPU0_M3CNT, CPU_M3CNT_read, CPU_M3CNT_write},
	{0, &CPU1_M3CNT, CPU_M3CNT_read, CPU_M3CNT_write},
	{0, &CPU2_M3CNT, CPU_M3CNT_read, CPU_M3CNT_write},
	{0, &CPU0_DBGSR, CPU_DBGSR_read, CPU_DBGSR_write},
	{0, &CPU1_DBGSR, CPU_DBGSR_read, CPU_DBGSR_write},
	{0, &CPU2_DBGSR, CPU_DBGSR_read, CPU_DBGSR_write},
	{0, &CPU0_EXEVT, CPU_EXEVT_read, CPU_EXEVT_write},
	{0, &CPU1_EXEVT, CPU_EXEVT_read, CPU_EXEVT_write},
	{0, &CPU2_EXEVT, CPU_EXEVT_read, CPU_EXEVT_write},
	{0, &CPU0_CREVT, CPU_CREVT_read, CPU_CREVT_write},
	{0, &CPU1_CREVT, CPU_CREVT_read, CPU_CREVT_write},
	{0, &CPU2_CREVT, CPU_CREVT_read, CPU_CREVT_write},
	{0, &CPU0_SWEVT, CPU_SWEVT_read, CPU_SWEVT_write},
	{0, &CPU1_SWEVT, CPU_SWEVT_read, CPU_SWEVT_write},
	{0, &CPU2_SWEVT, CPU_SWEVT_read, CPU_SWEVT_write},
	{0, &CPU0_TRIG_ACC, CPU_TRIG_ACC_read, CPU_TRIG_ACC_write},
	{0, &CPU1_TRIG_ACC, CPU_TRIG_ACC_read, CPU_TRIG_ACC_write},
	{0, &CPU2_TRIG_ACC, CPU_TRIG_ACC_read, CPU_TRIG_ACC_write},
	{0, &CPU0_DMS, CPU_DMS_read, CPU_DMS_write},
	{0, &CPU1_DMS, CPU_DMS_read, CPU_DMS_write},
	{0, &CPU2_DMS, CPU_DMS_read, CPU_DMS_write},
	{0, &CPU0_DCX, CPU_DCX_read, CPU_DCX_write},
	{0, &CPU1_DCX, CPU_DCX_read, CPU_DCX_write},
	{0, &CPU2_DCX, CPU_DCX_read, CPU_DCX_write},
	{0, &CPU0_DBGTCR, CPU_DBGTCR_read, CPU_DBGTCR_write},
	{0, &CPU1_DBGTCR, CPU_DBGTCR_read, CPU_DBGTCR_write},
	{0, &CPU2_DBGTCR, CPU_DBGTCR_read, CPU_DBGTCR_write},
	{0, &CPU0_PCXI, CPU_PCXI_read, CPU_PCXI_write},
	{0, &CPU1_PCXI, CPU_PCXI_read, CPU_PCXI_write},
	{0, &CPU2_PCXI, CPU_PCXI_read, CPU_PCXI_write},
	{0, &CPU0_PSW, CPU_PSW_read, CPU_PSW_write},
	{0, &CPU1_PSW, CPU_PSW_read, CPU_PSW_write},
	{0, &CPU2_PSW, CPU_PSW_read, CPU_PSW_write},
	{0, &CPU0_PC, CPU_PC_read, CPU_PC_write},
	{0, &CPU1_PC, CPU_PC_read, CPU_PC_write},
	{0, &CPU2_PC, CPU_PC_read, CPU_PC_write},
	{0, &CPU0_SYSCON, CPU_SYSCON_read, CPU_SYSCON_write},
	{0, &CPU1_SYSCON, CPU_SYSCON_read, CPU_SYSCON_write},
	{0, &CPU2_SYSCON, CPU_SYSCON_read, CPU_SYSCON_write},
	{0, &CPU0_CPU_ID, CPU_CPU_ID_read, CPU_CPU_ID_write},
	{0, &CPU1_CPU_ID, CPU_CPU_ID_read, CPU_CPU_ID_write},
	{0, &CPU2_CPU_ID, CPU_CPU_ID_read, CPU_CPU_ID_write},
	{0, &CPU0_CORE_ID, CPU_CORE_ID_read, CPU_CORE_ID_write},
	{0, &CPU1_CORE_ID, CPU_CORE_ID_read, CPU_CORE_ID_write},
	{0, &CPU2_CORE_ID, CPU_CORE_ID_read, CPU_CORE_ID_write},
	{0, &CPU0_BIV, CPU_BIV_read, CPU_BIV_write},
	{0, &CPU1_BIV, CPU_BIV_read, CPU_BIV_write},
	{0, &CPU2_BIV, CPU_BIV_read, CPU_BIV_write},
	{0, &CPU0_BTV, CPU_BTV_read, CPU_BTV_write},
	{0, &CPU1_BTV, CPU_BTV_read, CPU_BTV_write},
	{0, &CPU2_BTV, CPU_BTV_read, CPU_BTV_write},
	{0, &CPU0_ISP, CPU_ISP_read, CPU_ISP_write},
	{0, &CPU1_ISP, CPU_ISP_read, CPU_ISP_write},
	{0, &CPU2_ISP, CPU_ISP_read, CPU_ISP_write},
	{0, &CPU0_ICR, CPU_ICR_read, CPU_ICR_write},
	{0, &CPU1_ICR, CPU_ICR_read, CPU_ICR_write},
	{0, &CPU2_ICR, CPU_ICR_read, CPU_ICR_write},
	{0, &CPU0_FCX, CPU_FCX_read, CPU_FCX_write},
	{0, &CPU1_FCX, CPU_FCX_read, CPU_FCX_write},
	{0, &CPU2_FCX, CPU_FCX_read, CPU_FCX_write},
	{0, &CPU0_LCX, CPU_LCX_read, CPU_LCX_write},
	{0, &CPU1_LCX, CPU_LCX_read, CPU_LCX_write},
	{0, &CPU2_LCX, CPU_LCX_read, CPU_LCX_write},
	{0, &CPU0_CUS_ID, CPU_CUS_ID_read, CPU_CUS_ID_write},
	{0, &CPU1_CUS_ID, CPU_CUS_ID_read, CPU_CUS_ID_write},
	{0, &CPU2_CUS_ID, CPU_CUS_ID_read, CPU_CUS_ID_write},
  
	{0, &CPU0_D0, CPU_D_read, CPU_D_write},
	{0, &CPU1_D0, CPU_D_read, CPU_D_write},
	{0, &CPU2_D0, CPU_D_read, CPU_D_write},
	{0, &CPU0_D1, CPU_D_read, CPU_D_write},
	{0, &CPU1_D1, CPU_D_read, CPU_D_write},
	{0, &CPU2_D1, CPU_D_read, CPU_D_write},
	{0, &CPU0_D2, CPU_D_read, CPU_D_write},
	{0, &CPU1_D2, CPU_D_read, CPU_D_write},
	{0, &CPU2_D2, CPU_D_read, CPU_D_write},
	{0, &CPU0_D3, CPU_D_read, CPU_D_write},
	{0, &CPU1_D3, CPU_D_read, CPU_D_write},
	{0, &CPU2_D3, CPU_D_read, CPU_D_write},
	{0, &CPU0_D4, CPU_D_read, CPU_D_write},
	{0, &CPU1_D4, CPU_D_read, CPU_D_write},
	{0, &CPU2_D4, CPU_D_read, CPU_D_write},
	{0, &CPU0_D5, CPU_D_read, CPU_D_write},
	{0, &CPU1_D5, CPU_D_read, CPU_D_write},
	{0, &CPU2_D5, CPU_D_read, CPU_D_write},
	{0, &CPU0_D6, CPU_D_read, CPU_D_write},
	{0, &CPU1_D6, CPU_D_read, CPU_D_write},
	{0, &CPU2_D6, CPU_D_read, CPU_D_write},
	{0, &CPU0_D7, CPU_D_read, CPU_D_write},
	{0, &CPU1_D7, CPU_D_read, CPU_D_write},
	{0, &CPU2_D7, CPU_D_read, CPU_D_write},
	{0, &CPU0_D8, CPU_D_read, CPU_D_write},
	{0, &CPU1_D8, CPU_D_read, CPU_D_write},
	{0, &CPU2_D8, CPU_D_read, CPU_D_write},
	{0, &CPU0_D9, CPU_D_read, CPU_D_write},
	{0, &CPU1_D9, CPU_D_read, CPU_D_write},
	{0, &CPU2_D9, CPU_D_read, CPU_D_write},
	{0, &CPU0_D10, CPU_D_read, CPU_D_write},
	{0, &CPU1_D10, CPU_D_read, CPU_D_write},
	{0, &CPU2_D10, CPU_D_read, CPU_D_write},
	{0, &CPU0_D11, CPU_D_read, CPU_D_write},
	{0, &CPU1_D11, CPU_D_read, CPU_D_write},
	{0, &CPU2_D11, CPU_D_read, CPU_D_write},
	{0, &CPU0_D12, CPU_D_read, CPU_D_write},
	{0, &CPU1_D12, CPU_D_read, CPU_D_write},
	{0, &CPU2_D12, CPU_D_read, CPU_D_write},
	{0, &CPU0_D13, CPU_D_read, CPU_D_write},
	{0, &CPU1_D13, CPU_D_read, CPU_D_write},
	{0, &CPU2_D13, CPU_D_read, CPU_D_write},
	{0, &CPU0_D14, CPU_D_read, CPU_D_write},
	{0, &CPU1_D14, CPU_D_read, CPU_D_write},
	{0, &CPU2_D14, CPU_D_read, CPU_D_write},
	{0, &CPU0_D15, CPU_D_read, CPU_D_write},
	{0, &CPU1_D15, CPU_D_read, CPU_D_write},
	{0, &CPU2_D15, CPU_D_read, CPU_D_write},
  
	{0, &CPU0_A0, CPU_A_read, CPU_A_write},
	{0, &CPU1_A0, CPU_A_read, CPU_A_write},
	{0, &CPU2_A0, CPU_A_read, CPU_A_write},
	{0, &CPU0_A1, CPU_A_read, CPU_A_write},
	{0, &CPU1_A1, CPU_A_read, CPU_A_write},
	{0, &CPU2_A1, CPU_A_read, CPU_A_write},
	{0, &CPU0_A2, CPU_A_read, CPU_A_write},
	{0, &CPU1_A2, CPU_A_read, CPU_A_write},
	{0, &CPU2_A2, CPU_A_read, CPU_A_write},
	{0, &CPU0_A3, CPU_A_read, CPU_A_write},
	{0, &CPU1_A3, CPU_A_read, CPU_A_write},
	{0, &CPU2_A3, CPU_A_read, CPU_A_write},
	{0, &CPU0_A4, CPU_A_read, CPU_A_write},
	{0, &CPU1_A4, CPU_A_read, CPU_A_write},
	{0, &CPU2_A4, CPU_A_read, CPU_A_write},
	{0, &CPU0_A5, CPU_A_read, CPU_A_write},
	{0, &CPU1_A5, CPU_A_read, CPU_A_write},
	{0, &CPU2_A5, CPU_A_read, CPU_A_write},
	{0, &CPU0_A6, CPU_A_read, CPU_A_write},
	{0, &CPU1_A6, CPU_A_read, CPU_A_write},
	{0, &CPU2_A6, CPU_A_read, CPU_A_write},
	{0, &CPU0_A7, CPU_A_read, CPU_A_write},
	{0, &CPU1_A7, CPU_A_read, CPU_A_write},
	{0, &CPU2_A7, CPU_A_read, CPU_A_write},
	{0, &CPU0_A8, CPU_A_read, CPU_A_write},
	{0, &CPU1_A8, CPU_A_read, CPU_A_write},
	{0, &CPU2_A8, CPU_A_read, CPU_A_write},
	{0, &CPU0_A9, CPU_A_read, CPU_A_write},
	{0, &CPU1_A9, CPU_A_read, CPU_A_write},
	{0, &CPU2_A9, CPU_A_read, CPU_A_write},
	{0, &CPU0_A10, CPU_A_read, CPU_A_write},
	{0, &CPU1_A10, CPU_A_read, CPU_A_write},
	{0, &CPU2_A10, CPU_A_read, CPU_A_write},
	{0, &CPU0_A11, CPU_A_read, CPU_A_write},
	{0, &CPU1_A11, CPU_A_read, CPU_A_write},
	{0, &CPU2_A11, CPU_A_read, CPU_A_write},
	{0, &CPU0_A12, CPU_A_read, CPU_A_write},
	{0, &CPU1_A12, CPU_A_read, CPU_A_write},
	{0, &CPU2_A12, CPU_A_read, CPU_A_write},
	{0, &CPU0_A13, CPU_A_read, CPU_A_write},
	{0, &CPU1_A13, CPU_A_read, CPU_A_write},
	{0, &CPU2_A13, CPU_A_read, CPU_A_write},
	{0, &CPU0_A14, CPU_A_read, CPU_A_write},
	{0, &CPU1_A14, CPU_A_read, CPU_A_write},
	{0, &CPU2_A14, CPU_A_read, CPU_A_write},
	{0, &CPU0_A15, CPU_A_read, CPU_A_write},
	{0, &CPU1_A15, CPU_A_read, CPU_A_write},
	{0, &CPU2_A15, CPU_A_read, CPU_A_write}       
};

static int SIMULAPI CPU_SEGEN_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_SEGEN_read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}
static int SIMULAPI CPU_SEGEN_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_SEGEN_write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_TASK_ASI_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_TASK_ASI_read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_TASK_ASI_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_TASK_ASI_write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_PMA0_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_PMA0_read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_PMA0_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_PMA0_write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_PMA1_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_PMA1_read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_PMA1_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_PMA1_write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_PMA2_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_PMA2_read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_PMA2_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_PMA2_write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_DCON2_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_DCON2_read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_DCON2_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_DCON2_write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_SMACON_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_SMACON_read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_SMACON_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_SMACON_write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_DSTR_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_DSTR_read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_DSTR_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_DSTR_write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_DATR_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_DATR_read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_DATR_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_DATR_write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_DEADD_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_DEADD_read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_DEADD_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_DEADD_write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_DIEAR_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_DIEAR_read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_DIEAR_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_DIEAR_write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_DIETR_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_DIETR_read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_DIETR_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_DIETR_write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_DCON0_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_DCON0_read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_DCON0_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_DCON0_write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_PSTR_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_PSTR_read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_PSTR_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_PSTR_write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_PCON1_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_PCON1_read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_PCON1_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_PCON1_write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_PCON2_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_PCON2_read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_PCON2_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_PCON2_write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_PCON0_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_PCON0_read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_PCON0_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_PCON0_write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_PIEAR_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_PIEAR_read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_PIEAR_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_PIEAR_write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_PIETR_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_PIETR_read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_PIETR_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_PIETR_write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_COMPAT_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_COMPAT_read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_COMPAT_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_COMPAT_write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_FPU_TRAP_CON_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_FPU_TRAP_CON_read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_FPU_TRAP_CON_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_FPU_TRAP_CON_write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_FPU_TRAP_PC_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_FPU_TRAP_PC_read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_FPU_TRAP_PC_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_FPU_TRAP_PC_write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_FPU_TRAP_OPC_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_FPU_TRAP_OPC_read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_FPU_TRAP_OPC_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_FPU_TRAP_OPC_write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_FPU_TRAP_SRC1_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_FPU_TRAP_SRC1_read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_FPU_TRAP_SRC1_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_FPU_TRAP_SRC1_write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_FPU_TRAP_SRC2_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_FPU_TRAP_SRC2_read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_FPU_TRAP_SRC2_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_FPU_TRAP_SRC2_write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_FPU_TRAP_SRC3_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_FPU_TRAP_SRC3_read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_FPU_TRAP_SRC3_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_FPU_TRAP_SRC3_write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_DPR_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_DPR_read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_DPR_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_DPR_write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_CPR_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_CPR_read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_CPR_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_CPR_write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_CPXE_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_CPXE_read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_CPXE_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_CPXE_write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_DPRE_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_DPRE_read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_DPRE_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_DPRE_write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_DPWE_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_DPWE_read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_DPWE_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_DPWE_write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_TPS_CON_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_TPS_CON_read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_TPS_CON_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_TPS_CON_write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_TPS_TIMER_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_TPS_TIMER_read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_TPS_TIMER_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_TPS_TIMER_write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_TR_EVT_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_TR_EVT_read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_TR_EVT_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_TR_EVT_write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_TR_ADR_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_TR_ADR_read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_TR_ADR_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_TR_ADR_write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_CCTRL_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_CCTRL_read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_CCTRL_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_CCTRL_write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_CCNT_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_CCNT_read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_CCNT_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_CCNT_write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_ICNT_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_ICNT_read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_ICNT_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_ICNT_write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_M1CNT_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_M1CNT_read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_M1CNT_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_M1CNT_write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_M2CNT_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_M2CNT_read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_M2CNT_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_M2CNT_write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_M3CNT_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_M3CNT_read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_M3CNT_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_M3CNT_write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_DBGSR_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_DBGSR_read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_DBGSR_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_DBGSR_write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_EXEVT_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_EXEVT_read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_EXEVT_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_EXEVT_write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_CREVT_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_CREVT_read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_CREVT_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_CREVT_write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_SWEVT_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_SWEVT_read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_SWEVT_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_SWEVT_write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_TRIG_ACC_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_TRIG_ACC_read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_TRIG_ACC_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_TRIG_ACC_write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_DMS_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_DMS_read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_DMS_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_DMS_write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_DCX_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_DCX_read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_DCX_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_DCX_write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_DBGTCR_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_DBGTCR_read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_DBGTCR_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_DBGTCR_write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_PCXI_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_PCXI_read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_PCXI_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_PCXI_write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_PSW_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_PSW_read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_PSW_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_PSW_write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_PC_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_PC_read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_PC_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_PC_write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_SYSCON_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_SYSCON_read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_SYSCON_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_SYSCON_write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_CPU_ID_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_CPU_ID_read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_CPU_ID_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_CPU_ID_write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_CORE_ID_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_CORE_ID_read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_CORE_ID_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_CORE_ID_write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_BIV_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_BIV_read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_BIV_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_BIV_write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_BTV_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_BTV_read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_BTV_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_BTV_write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_ISP_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_ISP_read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_ISP_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_ISP_write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_ICR_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_ICR_read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_ICR_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_ICR_write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_FCX_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_FCX_read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_FCX_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_FCX_write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_LCX_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_LCX_read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_LCX_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_LCX_write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_CUS_ID_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_CUS_ID_read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_CUS_ID_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_CUS_ID_write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_D_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_D_read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_D_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_D_write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_A_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_A_read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_A_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_A_write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_SPROT_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_SPROT_read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}

static int SIMULAPI CPU_SPROT_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "CPU_SPROT_write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, CPU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}


static void CPU_reg_init(void)
{
	cpu_regs[0].D[0].U = 0x00000001;
	cpu_regs[0].A[0].U = 0xAFFFBB0C;
	cpu_regs[0].D[1].U = 0x00000006;
	cpu_regs[0].A[1].U = 0xAFFFBB0C;
	cpu_regs[0].D[2].U = 0x4B469052;
	cpu_regs[0].A[2].U = 0xAFFFB140;
	cpu_regs[0].D[3].U = 0x00000000;
	cpu_regs[0].A[3].U = 0xF0000478;
	cpu_regs[0].D[4].U = 0x00000000;
	cpu_regs[0].A[4].U = 0x000010EC;
	cpu_regs[0].D[5].U = 0x00000000;
	cpu_regs[0].A[5].U = 0x00000007;
	cpu_regs[0].D[6].U = 0x003B4B6D;
	cpu_regs[0].A[6].U = 0xF0062800;
	cpu_regs[0].D[7].U = 0x00000000;
	cpu_regs[0].A[7].U = 0xAFFFD19E;
	cpu_regs[0].D[8].U = 0x80008051;
	cpu_regs[0].A[8].U = 0xA0000020;
	cpu_regs[0].D[9].U = 0x00000000;
	cpu_regs[0].A[9].U = 0xF0040000;
	cpu_regs[0].D[10].U = 0x0000007A;
	cpu_regs[0].A[10].U = 0xF0036000;
	cpu_regs[0].D[11].U = 0x80008051;
	cpu_regs[0].A[11].U = 0xAFFFD19E;
	cpu_regs[0].D[12].U = 0x00002C7D;
	cpu_regs[0].A[12].U = 0xF8001000;
	cpu_regs[0].D[13].U = 0x00000004;
	cpu_regs[0].A[13].U = 0x00000000;
	cpu_regs[0].D[14].U = 0x00000000;
	cpu_regs[0].A[14].U = 0xF0060000;
	cpu_regs[0].D[15].U = 0x00000000;
	cpu_regs[0].A[15].U = 0xF8000528;

	cpu_regs[0].PC.U = 0xA0000020;
	cpu_regs[1].PC.U = 0xAFFFC000;
	cpu_regs[2].PC.U = 0xAFFFC000;

	cpu_regs[0].PSW.U = 0x18000B80;
	cpu_regs[1].PSW.U = 0x00000B80;
	cpu_regs[2].PSW.U = 0x00000B80;

	cpu_regs[0].PCXI.U = 0x00000000;
	cpu_regs[1].PCXI.U = 0x00000000;
	cpu_regs[2].PCXI.U = 0x00000000;

	cpu_regs[0].FCX.U = 0x00000000;
	cpu_regs[1].FCX.U = 0x00000000;
	cpu_regs[2].FCX.U = 0x00000000;

	cpu_regs[0].LCX.U = 0x00000000;
	cpu_regs[1].LCX.U = 0x00000000;
	cpu_regs[2].LCX.U = 0x00000000;

	cpu_regs[0].ICR.U = 0x00000000;
	cpu_regs[1].ICR.U = 0x00000000;
	cpu_regs[2].ICR.U = 0x00000000;

	cpu_regs[0].BIV.U = 0x00000000;
	cpu_regs[1].BIV.U = 0x00000000;
	cpu_regs[2].BIV.U = 0x00000000;

	cpu_regs[0].BTV.U = 0xA0000100;
	cpu_regs[1].BTV.U = 0xA0000100;
	cpu_regs[2].BTV.U = 0xA0000100;

	cpu_regs[0].ISP.U = 0x00000100;
	cpu_regs[1].ISP.U = 0x00000100;
	cpu_regs[2].ISP.U = 0x00000100;

	cpu_regs[0].SYSCON.U = 0x00000000;
	cpu_regs[1].SYSCON.U = 0x00000000;
	cpu_regs[2].SYSCON.U = 0x00000000;


	cpu_regs[0].TASK_ASI.U = 0x0000001F;
	cpu_regs[1].TASK_ASI.U = 0x0000001F;
	cpu_regs[2].TASK_ASI.U = 0x0000001F;

	cpu_regs[0].CPU_ID.U = 0x00C0C012;
	cpu_regs[1].CPU_ID.U = 0x00C0C012;
	cpu_regs[2].CPU_ID.U = 0x00C0C012;

	cpu_regs[0].CORE_ID.U = 0x00000000;
	cpu_regs[1].CORE_ID.U = 0x00000001;
	cpu_regs[2].CORE_ID.U = 0x00000002;

	cpu_regs[0].CUS_ID.U = 0x00000000;
	cpu_regs[1].CUS_ID.U = 0x00000000;
	cpu_regs[2].CUS_ID.U = 0x00000000;

	cpu_regs[0].PMA0.U = 0x00000300;
	cpu_regs[0].PMA1.U = 0x00000300;
	cpu_regs[0].PMA2.U = 0x0000C000;

	cpu_regs[1].PMA0.U = 0x00000300;
	cpu_regs[1].PMA1.U = 0x00000300;
	cpu_regs[1].PMA2.U = 0x0000C000;

	cpu_regs[2].PMA0.U = 0x00000300;
	cpu_regs[2].PMA1.U = 0x00000300;
	cpu_regs[2].PMA2.U = 0x0000C000;

	cpu_regs[0].COMPAT.U = 0xFFFFFFFF;
	cpu_regs[1].COMPAT.U = 0xFFFFFFFF;
	cpu_regs[2].COMPAT.U = 0xFFFFFFFF;

	cpu_regs[0].PIETR.U = 0x00000000;
	cpu_regs[1].PIETR.U = 0x00000000;
	cpu_regs[2].PIETR.U = 0x00000000;

	cpu_regs[0].PIEAR.U = 0x00000000;
	cpu_regs[1].PIEAR.U = 0x00000000;
	cpu_regs[2].PIEAR.U = 0x00000000;

	cpu_regs[0].DIETR.U = 0x00000000;
	cpu_regs[1].DIETR.U = 0x00000000;
	cpu_regs[2].DIETR.U = 0x00000000;

	cpu_regs[0].DIEAR.U = 0x00000000;
	cpu_regs[1].DIEAR.U = 0x00000000;
	cpu_regs[2].DIEAR.U = 0x00000000;

	cpu_regs[0].SMACON.U = 0x00000000;
	cpu_regs[1].SMACON.U = 0x00000000;
	cpu_regs[2].SMACON.U = 0x00000000;

	cpu_regs[0].PCON0.U = 0x00000002;
	cpu_regs[0].PCON1.U = 0x00000000;
	cpu_regs[0].PCON2.U = 0x00200010;

	cpu_regs[1].PCON0.U = 0x00000002;
	cpu_regs[1].PCON1.U = 0x00000000;
	cpu_regs[1].PCON2.U = 0x00200010;

	cpu_regs[2].PCON0.U = 0x00000002;
	cpu_regs[2].PCON1.U = 0x00000000;
	cpu_regs[2].PCON2.U = 0x00200010;

	cpu_regs[0].PSTR.U = 0x00000000;
	cpu_regs[1].PSTR.U = 0x00000000;
	cpu_regs[2].PSTR.U = 0x00000000;

	cpu_regs[0].DCON0.U = 0x00000002;
	cpu_regs[0].DCON2.U = 0x00780002;

	cpu_regs[1].DCON0.U = 0x00000002;
	cpu_regs[1].DCON2.U = 0x00780002;

	cpu_regs[2].DCON0.U = 0x00000002;
	cpu_regs[2].DCON2.U = 0x00780002;

	cpu_regs[0].DSTR.U = 0x00000000;
	cpu_regs[1].DSTR.U = 0x00000000;
	cpu_regs[2].DSTR.U = 0x00000000;

	cpu_regs[0].DATR.U = 0x00000000;
	cpu_regs[1].DATR.U = 0x00000000;
	cpu_regs[2].DATR.U = 0x00000000;

	cpu_regs[0].DEADD.U = 0x00000000;
	cpu_regs[1].DEADD.U = 0x00000000;
	cpu_regs[2].DEADD.U = 0x00000000;

	cpu_regs[0].SEGEN.U = 0x00000000;
	cpu_regs[1].SEGEN.U = 0x00000000;
	cpu_regs[2].SEGEN.U = 0x00000000;

	cpu_sprot[0].RGN[0].LA.U = 0x00000000;
	cpu_sprot[0].RGN[0].UA.U = 0xFFFFFFE0;
	cpu_sprot[0].RGN[0].ACCENA.U = 0xFFFFFFFF;
	cpu_sprot[0].RGN[0].ACCENB.U = 0x00000000;
	cpu_sprot[0].RGN[1].LA.U = 0x00000000;
	cpu_sprot[0].RGN[1].UA.U = 0xFFFFFFE0;
	cpu_sprot[0].RGN[1].ACCENA.U = 0xFFFFFFFF;
	cpu_sprot[0].RGN[1].ACCENB.U = 0x00000000;
	cpu_sprot[0].RGN[2].LA.U = 0x00000000;
	cpu_sprot[0].RGN[2].UA.U = 0xFFFFFFE0;
	cpu_sprot[0].RGN[2].ACCENA.U = 0xFFFFFFFF;
	cpu_sprot[0].RGN[2].ACCENB.U = 0x00000000;
	cpu_sprot[0].RGN[3].LA.U = 0x00000000;
	cpu_sprot[0].RGN[3].UA.U = 0xFFFFFFE0;
	cpu_sprot[0].RGN[3].ACCENA.U = 0xFFFFFFFF;
	cpu_sprot[0].RGN[3].ACCENB.U = 0x00000000;
	cpu_sprot[0].RGN[4].LA.U = 0x00000000;
	cpu_sprot[0].RGN[4].UA.U = 0xFFFFFFE0;
	cpu_sprot[0].RGN[4].ACCENA.U = 0xFFFFFFFF;
	cpu_sprot[0].RGN[4].ACCENB.U = 0x00000000;
	cpu_sprot[0].RGN[5].LA.U = 0x00000000;
	cpu_sprot[0].RGN[5].UA.U = 0xFFFFFFE0;
	cpu_sprot[0].RGN[5].ACCENA.U = 0xFFFFFFFF;
	cpu_sprot[0].RGN[5].ACCENB.U = 0x00000000;
	cpu_sprot[0].RGN[6].LA.U = 0x00000000;
	cpu_sprot[0].RGN[6].UA.U = 0xFFFFFFE0;
	cpu_sprot[0].RGN[6].ACCENA.U = 0xFFFFFFFF;
	cpu_sprot[0].RGN[6].ACCENB.U = 0x00000000;
	cpu_sprot[0].RGN[7].LA.U = 0x00000000;
	cpu_sprot[0].RGN[7].UA.U = 0xFFFFFFE0;
	cpu_sprot[0].RGN[7].ACCENA.U = 0xFFFFFFFF;
	cpu_sprot[0].RGN[7].ACCENB.U = 0x00000000;
	cpu_sprot[0].ACCENA.U = 0xFFFFFFFF;
	cpu_sprot[0].ACCENB.U = 0x00000000;

}