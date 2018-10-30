#include "simul.h"
#include "reg_common.h"
#include "IfxScu_regdef.h"
#include "SCU_SIM.h"

#define SCU_BASE_ADDRESS (0xF0036000U)
#define SCU_END_ADDRESS (0xF00363FFU)

static void  * SCU_debug_file = NULL;
static unsigned char buf[100] = {0};
static int SCU_bus_type = 0;

static int SIMULAPI SCU_OSCCON_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_PLLSTAT_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_PLLCON0_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_PLLCON1_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_PLLCON2_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_PLLERAYSTAT_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_PLLERAYCON0_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_PLLERAYCON1_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_CCUCON0_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_CCUCON1_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_FDR_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_EXTCON_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_CCUCON2_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_CCUCON3_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_CCUCON4_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_CCUCON5_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_CCUCON6_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_CCUCON7_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_CCUCON8_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_RSTSTAT_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_RSTCON_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_ARSTDIS_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_SWRSTCON_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_RSTCON2_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_ESRCFG0_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_ESRCFG1_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_ESROCFG_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_PDR_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_IOCR_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_OUT_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_OMR_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_IN_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_STSTAT_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_TRAPSTAT_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_TRAPSET_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_TRAPCLR_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_TRAPDIS_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_EVRRSTCON_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_EVRSTAT_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_EVRDVSTAT_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_EVR13CON_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_EVR33CON_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_PMSWCR0_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_PMSWSTAT_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_PMSWSTATCLR_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_PMCSR0_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_PMCSR1_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_PMCSR2_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_PMSWCR1_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_EVRTRIM_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_EVRADCSTAT_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_EVRUVMON_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_EVROVMON_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_EVRMONCTRL_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_EVRSDCTRL1_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_EVRSDCTRL2_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_EVRSDCTRL3_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_EVRSDCTRL4_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_EVRSDCOEFF1_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_EVRSDCOEFF2_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_EVRSDCOEFF3_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_EVRSDCOEFF4_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_EVRSDCOEFF5_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_EVRSDCOEFF6_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_SYSCON_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_DTSSTAT_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_DTSCON_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_WDTSCON0_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_WDTSCON1_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_WDTSSR_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_EMSR_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_WDTCPU0CON0_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_WDTCPU0CON1_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_WDTCPU0SR_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_WDTCPU1CON0_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_WDTCPU1CON1_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_WDTCPU1SR_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_WDTCPU2CON0_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_WDTCPU2CON1_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_WDTCPU2SR_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_LCLCON0_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_LCLCON1_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_LCLTEST_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_CHIPID_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_ID_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_MANID_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_LBISTCTRL0_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_LBISTCTRL1_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_LBISTCTRL2_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_OVCENABLE_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_OVCCON_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_EICR0_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_EICR1_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_EICR2_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_EICR3_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_EIFR_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_FMR_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_PDRR_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_IGCR0_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_IGCR1_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_IGCR2_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_IGCR3_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_DTSLIM_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_ACCEN1_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_ACCEN0_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_OSCCON_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_PLLSTAT_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_PLLCON0_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_PLLCON1_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_PLLCON2_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_PLLERAYSTAT_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_PLLERAYCON0_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_PLLERAYCON1_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_CCUCON0_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_CCUCON1_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_FDR_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_EXTCON_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_CCUCON2_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_CCUCON3_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_CCUCON4_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_CCUCON5_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_CCUCON6_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_CCUCON7_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_CCUCON8_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_RSTSTAT_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_RSTCON_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_ARSTDIS_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_SWRSTCON_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_RSTCON2_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_ESRCFG0_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_ESRCFG1_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_ESROCFG_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_PDR_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_IOCR_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_OUT_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_OMR_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_IN_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_STSTAT_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_TRAPSTAT_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_TRAPSET_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_TRAPCLR_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_TRAPDIS_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_EVRRSTCON_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_EVRSTAT_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_EVRDVSTAT_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_EVR13CON_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_EVR33CON_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_PMSWCR0_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_PMSWSTAT_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_PMSWSTATCLR_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_PMCSR0_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_PMCSR1_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_PMCSR2_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_PMSWCR1_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_EVRTRIM_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_EVRADCSTAT_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_EVRUVMON_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_EVROVMON_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_EVRMONCTRL_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_EVRSDCTRL1_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_EVRSDCTRL2_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_EVRSDCTRL3_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_EVRSDCTRL4_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_EVRSDCOEFF1_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_EVRSDCOEFF2_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_EVRSDCOEFF3_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_EVRSDCOEFF4_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_EVRSDCOEFF5_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_EVRSDCOEFF6_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_SYSCON_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_DTSSTAT_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_DTSCON_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_WDTSCON0_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_WDTSCON1_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_WDTSSR_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_EMSR_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_WDTCPU0CON0_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_WDTCPU0CON1_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_WDTCPU0SR_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_WDTCPU1CON0_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_WDTCPU1CON1_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_WDTCPU1SR_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_WDTCPU2CON0_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_WDTCPU2CON1_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_WDTCPU2SR_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_LCLCON0_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_LCLCON1_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_LCLTEST_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_CHIPID_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_ID_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_MANID_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_LBISTCTRL0_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_LBISTCTRL1_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_LBISTCTRL2_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_OVCENABLE_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_OVCCON_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_EICR0_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_EICR1_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_EICR2_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_EICR3_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_EIFR_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_FMR_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_PDRR_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_IGCR0_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_IGCR1_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_IGCR2_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_IGCR3_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_DTSLIM_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_ACCEN1_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);
static int SIMULAPI SCU_ACCEN0_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private);


/*global variables*/
Ifx_SCU scu_regs = {0U};

static reg_opt scu_regs_opt[SCU_REG_MAX] = {
{SCU_OSCCON,0x010U,SCU_OSCCON_read,SCU_OSCCON_write},
{SCU_PLLSTAT,0x014U,SCU_PLLSTAT_read,SCU_PLLSTAT_write},
{SCU_PLLCON0,0x018U,SCU_PLLCON0_read,SCU_PLLCON0_write},
{SCU_PLLCON1,0x01CU,SCU_PLLCON1_read,SCU_PLLCON1_write},
{SCU_PLLCON2,0x020U,SCU_PLLCON2_read,SCU_PLLCON2_write},
{SCU_PLLERAYSTAT,0x024U,SCU_PLLERAYSTAT_read,SCU_PLLERAYSTAT_write},
{SCU_PLLERAYCON0,0x028U,SCU_PLLERAYCON0_read,SCU_PLLERAYCON0_write},
{SCU_PLLERAYCON1,0x02CU,SCU_PLLERAYCON1_read,SCU_PLLERAYCON1_write},
{SCU_CCUCON0,0x030U,SCU_CCUCON0_read,SCU_CCUCON0_write},
{SCU_CCUCON1,0x034U,SCU_CCUCON1_read,SCU_CCUCON1_write},
{SCU_FDR,0x038U,SCU_FDR_read,SCU_FDR_write},
{SCU_EXTCON,0x03CU,SCU_EXTCON_read,SCU_EXTCON_write},
{SCU_CCUCON2,0x040U,SCU_CCUCON2_read,SCU_CCUCON2_write},
{SCU_CCUCON3,0x044U,SCU_CCUCON3_read,SCU_CCUCON3_write},
{SCU_CCUCON4,0x048U,SCU_CCUCON4_read,SCU_CCUCON4_write},
{SCU_CCUCON5,0x04CU,SCU_CCUCON5_read,SCU_CCUCON5_write},
{SCU_CCUCON6,0x080U,SCU_CCUCON6_read,SCU_CCUCON6_write},
{SCU_CCUCON7,0x084U,SCU_CCUCON7_read,SCU_CCUCON7_write},
{SCU_CCUCON8,0x088U,SCU_CCUCON8_read,SCU_CCUCON8_write},
{SCU_RSTSTAT,0x050U,SCU_RSTSTAT_read,SCU_RSTSTAT_write},
{SCU_RSTCON,0x058U,SCU_RSTCON_read,SCU_RSTCON_write},
{SCU_ARSTDIS,0x05CU,SCU_ARSTDIS_read,SCU_ARSTDIS_write},
{SCU_SWRSTCON,0x060U,SCU_SWRSTCON_read,SCU_SWRSTCON_write},
{SCU_RSTCON2,0x064U,SCU_RSTCON2_read,SCU_RSTCON2_write},
{SCU_ESRCFG0,0x070U,SCU_ESRCFG0_read,SCU_ESRCFG0_write},
{SCU_ESRCFG1,0x074U,SCU_ESRCFG1_read,SCU_ESRCFG1_write},
{SCU_ESROCFG,0x078U,SCU_ESROCFG_read,SCU_ESROCFG_write},
{SCU_PDR,0x09CU,SCU_PDR_read,SCU_PDR_write},
{SCU_IOCR,0x0A0U,SCU_IOCR_read,SCU_IOCR_write},
{SCU_OUT,0x0A4U,SCU_OUT_read,SCU_OUT_write},
{SCU_OMR,0x0A8U,SCU_OMR_read,SCU_OMR_write},
{SCU_IN,0x0ACU,SCU_IN_read,SCU_IN_write},
{SCU_STSTAT,0x0C0U,SCU_STSTAT_read,SCU_STSTAT_write},
{SCU_TRAPSTAT,0x124U,SCU_TRAPSTAT_read,SCU_TRAPSTAT_write},
{SCU_TRAPSET,0x128U,SCU_TRAPSET_read,SCU_TRAPSET_write},
{SCU_TRAPCLR,0x12CU,SCU_TRAPCLR_read,SCU_TRAPCLR_write},
{SCU_TRAPDIS,0x130U,SCU_TRAPDIS_read,SCU_TRAPDIS_write},
{SCU_EVRRSTCON,0x06CU,SCU_EVRRSTCON_read,SCU_EVRRSTCON_write},
{SCU_EVRSTAT,0x0B0U,SCU_EVRSTAT_read,SCU_EVRSTAT_write},
{SCU_EVRDVSTAT,0x0B4U,SCU_EVRDVSTAT_read,SCU_EVRDVSTAT_write},
{SCU_EVR13CON,0x0B8U,SCU_EVR13CON_read,SCU_EVR13CON_write},
{SCU_EVR33CON,0x0BCU,SCU_EVR33CON_read,SCU_EVR33CON_write},
{SCU_PMSWCR0,0x0C8U,SCU_PMSWCR0_read,SCU_PMSWCR0_write},
{SCU_PMSWSTAT,0x0CCU,SCU_PMSWSTAT_read,SCU_PMSWSTAT_write},
{SCU_PMSWSTATCLR,0x0D0U,SCU_PMSWSTATCLR_read,SCU_PMSWSTATCLR_write},
{SCU_PMCSR0,0x0D4U,SCU_PMCSR0_read,SCU_PMCSR0_write},
{SCU_PMCSR1,0x0D8U,SCU_PMCSR1_read,SCU_PMCSR1_write},
{SCU_PMCSR2,0x0DCU,SCU_PMCSR2_read,SCU_PMCSR2_write},
{SCU_PMSWCR1,0x0E8U,SCU_PMSWCR1_read,SCU_PMSWCR1_write},
{SCU_EVRTRIM,0x198U,SCU_EVRTRIM_read,SCU_EVRTRIM_write},
{SCU_EVRADCSTAT,0x19CU,SCU_EVRADCSTAT_read,SCU_EVRADCSTAT_write},
{SCU_EVRUVMON,0x1A0U,SCU_EVRUVMON_read,SCU_EVRUVMON_write},
{SCU_EVROVMON,0x1A4U,SCU_EVROVMON_read,SCU_EVROVMON_write},
{SCU_EVRMONCTRL,0x1A8U,SCU_EVRMONCTRL_read,SCU_EVRMONCTRL_write},
{SCU_EVRSDCTRL1,0x1B0U,SCU_EVRSDCTRL1_read,SCU_EVRSDCTRL1_write},
{SCU_EVRSDCTRL2,0x1B4U,SCU_EVRSDCTRL2_read,SCU_EVRSDCTRL2_write},
{SCU_EVRSDCTRL3,0x1B8U,SCU_EVRSDCTRL3_read,SCU_EVRSDCTRL3_write},
{SCU_EVRSDCTRL4,0x1BCU,SCU_EVRSDCTRL4_read,SCU_EVRSDCTRL4_write},
{SCU_EVRSDCOEFF1,0x1C0U,SCU_EVRSDCOEFF1_read,SCU_EVRSDCOEFF1_write},
{SCU_EVRSDCOEFF2,0x1C4U,SCU_EVRSDCOEFF2_read,SCU_EVRSDCOEFF2_write},
{SCU_EVRSDCOEFF3,0x1C8U,SCU_EVRSDCOEFF3_read,SCU_EVRSDCOEFF3_write},
{SCU_EVRSDCOEFF4,0x1CCU,SCU_EVRSDCOEFF4_read,SCU_EVRSDCOEFF4_write},
{SCU_EVRSDCOEFF5,0x1D0U,SCU_EVRSDCOEFF5_read,SCU_EVRSDCOEFF5_write},
{SCU_EVRSDCOEFF6,0x1D4U,SCU_EVRSDCOEFF6_read,SCU_EVRSDCOEFF6_write},
{SCU_SYSCON,0x07CU,SCU_SYSCON_read,SCU_SYSCON_write},
{SCU_DTSSTAT,0x0E0U,SCU_DTSSTAT_read,SCU_DTSSTAT_write},
{SCU_DTSCON,0x0E4U,SCU_DTSCON_read,SCU_DTSCON_write},
{SCU_WDTSCON0,0x0F0U,SCU_WDTSCON0_read,SCU_WDTSCON0_write},
{SCU_WDTSCON1,0x0F4U,SCU_WDTSCON1_read,SCU_WDTSCON1_write},
{SCU_WDTSSR,0x0F8U,SCU_WDTSSR_read,SCU_WDTSSR_write},
{SCU_EMSR,0x0FCU,SCU_EMSR_read,SCU_EMSR_write},
{SCU_WDTCPU0CON0,0x100U,SCU_WDTCPU0CON0_read,SCU_WDTCPU0CON0_write},
{SCU_WDTCPU0CON1,0x104U,SCU_WDTCPU0CON1_read,SCU_WDTCPU0CON1_write},
{SCU_WDTCPU0SR,0x108U,SCU_WDTCPU0SR_read,SCU_WDTCPU0SR_write},
{SCU_WDTCPU1CON0,0x10CU,SCU_WDTCPU1CON0_read,SCU_WDTCPU1CON0_write},
{SCU_WDTCPU1CON1,0x110U,SCU_WDTCPU1CON1_read,SCU_WDTCPU1CON1_write},
{SCU_WDTCPU1SR,0x114U,SCU_WDTCPU1SR_read,SCU_WDTCPU1SR_write},
{SCU_WDTCPU2CON0,0x118U,SCU_WDTCPU2CON0_read,SCU_WDTCPU2CON0_write},
{SCU_WDTCPU2CON1,0x11CU,SCU_WDTCPU2CON1_read,SCU_WDTCPU2CON1_write},
{SCU_WDTCPU2SR,0x120U,SCU_WDTCPU2SR_read,SCU_WDTCPU2SR_write},
{SCU_LCLCON0,0x134U,SCU_LCLCON0_read,SCU_LCLCON0_write},
{SCU_LCLCON1,0x138U,SCU_LCLCON1_read,SCU_LCLCON1_write},
{SCU_LCLTEST,0x13CU,SCU_LCLTEST_read,SCU_LCLTEST_write},
{SCU_CHIPID,0x140U,SCU_CHIPID_read,SCU_CHIPID_write},
{SCU_ID,0x008U,SCU_ID_read,SCU_ID_write},
{SCU_MANID,0x144U,SCU_MANID_read,SCU_MANID_write},
{SCU_LBISTCTRL0,0x164U,SCU_LBISTCTRL0_read,SCU_LBISTCTRL0_write},
{SCU_LBISTCTRL1,0x168U,SCU_LBISTCTRL1_read,SCU_LBISTCTRL1_write},
{SCU_LBISTCTRL2,0x16CU,SCU_LBISTCTRL2_read,SCU_LBISTCTRL2_write},
{SCU_OVCENABLE,0x1E0U,SCU_OVCENABLE_read,SCU_OVCENABLE_write},
{SCU_OVCCON,0x1E4U,SCU_OVCCON_read,SCU_OVCCON_write},
{SCU_EICR0,0x210U,SCU_EICR0_read,SCU_EICR0_write},
{SCU_EICR1,0x214U,SCU_EICR1_read,SCU_EICR1_write},
{SCU_EICR2,0x218U,SCU_EICR2_read,SCU_EICR2_write},
{SCU_EICR3,0x21CU,SCU_EICR3_read,SCU_EICR3_write},
{SCU_EIFR,0x220U,SCU_EIFR_read,SCU_EIFR_write},
{SCU_FMR,0x224U,SCU_FMR_read,SCU_FMR_write},
{SCU_PDRR,0x228U,SCU_PDRR_read,SCU_PDRR_write},
{SCU_IGCR0,0x22CU,SCU_IGCR0_read,SCU_IGCR0_write},
{SCU_IGCR1,0x230U,SCU_IGCR1_read,SCU_IGCR1_write},
{SCU_IGCR2,0x234U,SCU_IGCR2_read,SCU_IGCR2_write},
{SCU_IGCR3,0x238U,SCU_IGCR3_read,SCU_IGCR3_write},
{SCU_DTSLIM,0x240U,SCU_DTSLIM_read,SCU_DTSLIM_write},
{SCU_ACCEN1,0x3F8U,SCU_ACCEN1_read,SCU_ACCEN1_write},
{SCU_ACCEN0,0x3FCU,SCU_ACCEN0_read,SCU_ACCEN0_write}
};


static int SIMULAPI SCU_OSCCON_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.OSCCON.B.PLLHV = 0x01;
	scu_regs.OSCCON.B.PLLLV = 0x01;

	memcpy(&(cbs->x.bus.data), (unsigned char *)&scu_regs.OSCCON.U + (cbs->x.bus.address - SCU_BASE_ADDRESS - scu_regs_opt[SCU_OSCCON].offset), cbs->x.bus.width / 8U);
	

	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_PLLSTAT_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	if(scu_regs.PLLCON0.B.VCOBYP == 1)
	{
		scu_regs.PLLSTAT.B.VCOBYST = 1;
	}
	else
	{
		scu_regs.PLLSTAT.B.VCOBYST = 0;
	}

	if ((scu_regs.PLLCON0.B.OSCDISCDIS == 1) && (scu_regs.PLLCON0.B.CLRFINDIS == 1))
	{
		scu_regs.PLLSTAT.B.FINDIS = 0;
	}

	if ((scu_regs.PLLCON0.B.OSCDISCDIS == 1) && (scu_regs.PLLCON0.B.RESLD == 1))
	{
		scu_regs.PLLSTAT.B.VCOLOCK = 1;
	}

	memcpy(&(cbs->x.bus.data), (unsigned char *)&scu_regs.PLLSTAT.U + (cbs->x.bus.address - SCU_BASE_ADDRESS - scu_regs_opt[SCU_PLLSTAT].offset), cbs->x.bus.width / 8U);

	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_PLLCON0_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.PLLCON0.U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_PLLCON1_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.PLLCON1.U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_PLLCON2_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.PLLCON2.U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_PLLERAYSTAT_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.PLLERAYSTAT.U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_PLLERAYCON0_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.PLLERAYCON0.U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_PLLERAYCON1_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.PLLERAYCON1.U;

	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_CCUCON0_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.CCUCON0.U;

	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_CCUCON1_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.CCUCON1.U;

	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_FDR_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.FDR.U;

	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_EXTCON_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.EXTCON.U;

	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_CCUCON2_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.CCUCON2.U;

	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_CCUCON3_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.CCUCON3.U;

	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_CCUCON4_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.CCUCON4.U;

	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_CCUCON5_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.CCUCON5.U;

	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_CCUCON6_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.CCUCON6.U;

	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_CCUCON7_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.CCUCON7.U;

	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_CCUCON8_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.CCUCON8.U;

	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_RSTSTAT_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.RSTSTAT.U;

	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_RSTCON_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.RSTCON.U;

	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_ARSTDIS_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.ARSTDIS.U;

	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_SWRSTCON_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.SWRSTCON.U;

	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_RSTCON2_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.RSTCON2.U;

	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_ESRCFG0_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.ESRCFG[0].U;

	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_ESRCFG1_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.ESRCFG[1].U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_ESROCFG_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.ESROCFG.U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_PDR_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.PDR.U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_IOCR_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.IOCR.U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_OUT_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.SCU_OUT.U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_OMR_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.OMR.U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_IN_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.SCU_IN.U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_STSTAT_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.STSTAT.U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_TRAPSTAT_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.TRAPSTAT.U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_TRAPSET_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.TRAPSET.U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_TRAPCLR_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.TRAPCLR.U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_TRAPDIS_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.TRAPDIS.U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_EVRRSTCON_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.EVRRSTCON.U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_EVRSTAT_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.EVRSTAT.U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_EVRDVSTAT_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.EVRDVSTAT.U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_EVR13CON_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.EVR13CON.U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_EVR33CON_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.EVR33CON.U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_PMSWCR0_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.PMSWCR0.U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_PMSWSTAT_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.PMSWSTAT.U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_PMSWSTATCLR_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.PMSWSTATCLR.U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_PMCSR0_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.PMCSR[0].U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_PMCSR1_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.PMCSR[1].U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_PMCSR2_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.PMCSR[2].U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_PMSWCR1_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.PMSWCR1.U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_EVRTRIM_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.EVRTRIM.U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_EVRADCSTAT_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.EVRADCSTAT.U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_EVRUVMON_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.EVRUVMON.U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_EVROVMON_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.EVROVMON.U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_EVRMONCTRL_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.EVRMONCTRL.U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_EVRSDCTRL1_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.EVRSDCTRL1.U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_EVRSDCTRL2_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.EVRSDCTRL2.U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_EVRSDCTRL3_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.EVRSDCTRL3.U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_EVRSDCTRL4_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.EVRSDCTRL4.U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_EVRSDCOEFF1_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.EVRSDCOEFF1.U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_EVRSDCOEFF2_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.EVRSDCOEFF2.U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_EVRSDCOEFF3_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.EVRSDCOEFF3.U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_EVRSDCOEFF4_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.EVRSDCOEFF4.U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_EVRSDCOEFF5_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.EVRSDCOEFF5.U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_EVRSDCOEFF6_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.EVRSDCOEFF6.U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_SYSCON_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.SYSCON.U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_DTSSTAT_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.DTSSTAT.U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_DTSCON_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.DTSCON.U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_WDTSCON0_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.WDTS.CON0.U;
	sprintf(buf, "SCU_REG read address 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_WDTSCON1_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.WDTS.CON1.U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_WDTSSR_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.WDTS.SR.U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_EMSR_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.EMSR.U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_WDTCPU0CON0_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.WDTCPU[0].CON0.U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_WDTCPU0CON1_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.WDTCPU[0].CON1.U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_WDTCPU0SR_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.WDTCPU[0].SR.U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_WDTCPU1CON0_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.WDTCPU[1].CON0.U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_WDTCPU1CON1_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.WDTCPU[1].CON1.U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_WDTCPU1SR_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.WDTCPU[1].SR.U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_WDTCPU2CON0_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.WDTCPU[2].CON0.U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_WDTCPU2CON1_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.WDTCPU[2].CON1.U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_WDTCPU2SR_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.WDTCPU[2].SR.U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_LCLCON0_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = 0;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_LCLCON1_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.LCLCON1.U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_LCLTEST_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.LCLTEST.U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_CHIPID_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.CHIPID.U;

	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_ID_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.ID.U;

	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_MANID_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.MANID.U;

	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_LBISTCTRL0_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.LBISTCTRL0.U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_LBISTCTRL1_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.LBISTCTRL1.U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_LBISTCTRL2_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.LBISTCTRL2.U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_OVCENABLE_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.OVCENABLE.U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_OVCCON_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.OVCCON.B.OVCONF = 1;

	memcpy(&(cbs->x.bus.data), (unsigned char *)&scu_regs.OVCCON.U + (cbs->x.bus.address - SCU_BASE_ADDRESS - scu_regs_opt[SCU_OVCCON].offset), cbs->x.bus.width / 8U);

	sprintf(buf, "SCU_OVCCON read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_EICR0_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.EICR[0].U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_EICR1_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.EICR[1].U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_EICR2_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.EICR[2].U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_EICR3_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.EICR[3].U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_EIFR_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.EIFR.U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_FMR_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.FMR.U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_PDRR_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.PDRR.U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_IGCR0_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.IGCR[0].U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_IGCR1_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.IGCR[1].U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_IGCR2_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.IGCR[2].U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_IGCR3_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.IGCR[3].U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_DTSLIM_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.DTSLIM.U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}

static int SIMULAPI SCU_ACCEN1_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.ACCEN1.U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}

static int SIMULAPI SCU_ACCEN0_read(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	cbs->x.bus.data = scu_regs.ACCEN0.U;
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_OSCCON_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.OSCCON.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_PLLSTAT_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.PLLSTAT.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_PLLCON0_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	memcpy((unsigned char *)&scu_regs.PLLCON0.U + (cbs->x.bus.address - SCU_BASE_ADDRESS - scu_regs_opt[SCU_PLLCON0].offset), &(cbs->x.bus.data),  cbs->x.bus.width / 8U);

	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_PLLCON1_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.PLLCON1.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_PLLCON2_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.PLLCON2.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_PLLERAYSTAT_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.PLLERAYSTAT.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_PLLERAYCON0_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.PLLERAYCON0.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_PLLERAYCON1_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.PLLERAYCON1.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_CCUCON0_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.CCUCON0.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_CCUCON1_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.CCUCON1.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_FDR_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.FDR.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_EXTCON_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.EXTCON.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_CCUCON2_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.CCUCON2.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_CCUCON3_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.CCUCON3.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_CCUCON4_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.CCUCON4.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_CCUCON5_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.CCUCON5.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_CCUCON6_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.CCUCON6.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_CCUCON7_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.CCUCON7.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_CCUCON8_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.CCUCON8.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_RSTSTAT_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.RSTSTAT.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_RSTCON_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.RSTCON.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_ARSTDIS_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.ARSTDIS.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_SWRSTCON_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.SWRSTCON.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_RSTCON2_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.RSTCON2.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_ESRCFG0_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.ESRCFG[0].U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_ESRCFG1_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.ESRCFG[1].U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_ESROCFG_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.ESROCFG.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_PDR_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.PDR.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_IOCR_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.IOCR.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_OUT_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.SCU_OUT.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_OMR_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.OMR.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_IN_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.SCU_IN.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_STSTAT_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.STSTAT.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_TRAPSTAT_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.TRAPSTAT.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_TRAPSET_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.TRAPSET.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_TRAPCLR_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.TRAPCLR.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_TRAPDIS_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.TRAPDIS.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_EVRRSTCON_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.EVRRSTCON.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_EVRSTAT_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.EVRSTAT.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_EVRDVSTAT_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.EVRDVSTAT.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_EVR13CON_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.EVR13CON.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_EVR33CON_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.EVR33CON.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_PMSWCR0_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.PMSWCR0.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_PMSWSTAT_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.PMSWSTAT.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_PMSWSTATCLR_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.PMSWSTATCLR.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_PMCSR0_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.PMCSR[0].U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_PMCSR1_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.PMCSR[1].U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_PMCSR2_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.PMCSR[2].U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_PMSWCR1_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.PMSWCR1.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_EVRTRIM_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.EVRTRIM.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_EVRADCSTAT_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.EVRADCSTAT.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_EVRUVMON_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.EVRUVMON.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_EVROVMON_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.EVROVMON.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_EVRMONCTRL_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.EVRMONCTRL.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_EVRSDCTRL1_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.EVRSDCTRL1.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_EVRSDCTRL2_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.EVRSDCTRL2.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_EVRSDCTRL3_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.EVRSDCTRL3.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_EVRSDCTRL4_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.EVRSDCTRL4.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_EVRSDCOEFF1_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.EVRSDCOEFF1.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_EVRSDCOEFF2_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.EVRSDCOEFF2.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_EVRSDCOEFF3_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.EVRSDCOEFF3.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_EVRSDCOEFF4_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.EVRSDCOEFF4.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_EVRSDCOEFF5_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.EVRSDCOEFF5.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_EVRSDCOEFF6_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.EVRSDCOEFF6.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_SYSCON_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.SYSCON.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_DTSSTAT_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.DTSSTAT.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_DTSCON_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.DTSCON.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}

static int SIMULAPI SCU_WDTSCON0_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.WDTS.CON0.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_WDTSCON1_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.WDTS.CON1.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_WDTSSR_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.WDTS.SR.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_EMSR_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.EMSR.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_WDTCPU0CON0_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.WDTCPU[0].CON0.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_WDTCPU0CON1_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.WDTCPU[0].CON1.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_WDTCPU0SR_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.WDTCPU[0].SR.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_WDTCPU1CON0_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.WDTCPU[1].CON0.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_WDTCPU1CON1_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.WDTCPU[1].CON1.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_WDTCPU1SR_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.WDTCPU[1].SR.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_WDTCPU2CON0_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.WDTCPU[2].CON0.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_WDTCPU2CON1_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.WDTCPU[2].CON1.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_WDTCPU2SR_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.WDTCPU[2].SR.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_LCLCON0_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_LCLCON1_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.LCLCON1.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_LCLTEST_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.LCLTEST.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_CHIPID_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.CHIPID.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;

}
static int SIMULAPI SCU_ID_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.ID.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_MANID_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.MANID.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_LBISTCTRL0_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.LBISTCTRL0.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_LBISTCTRL1_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.LBISTCTRL1.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_LBISTCTRL2_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.LBISTCTRL2.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_OVCENABLE_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.OVCENABLE.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_OVCCON_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.OVCCON.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_EICR0_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.EICR[0].U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_EICR1_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.EICR[1].U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_EICR2_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.EICR[2].U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_EICR3_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.EICR[3].U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_EIFR_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.EIFR.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_FMR_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.FMR.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_PDRR_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.PDRR.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_IGCR0_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.IGCR[0].U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_IGCR1_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.IGCR[1].U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_IGCR2_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.IGCR[2].U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_IGCR3_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.IGCR[3].U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_DTSLIM_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.DTSLIM.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_ACCEN1_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.ACCEN1.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}
static int SIMULAPI SCU_ACCEN0_write(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	scu_regs.ACCEN0.U = cbs->x.bus.data;
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);
	return SIMUL_MEMORY_OK;
}

static int SIMULAPI SCU_RegisterReadData(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "SCU_REG read address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);


	return SIMUL_MEMORY_OK;
}

static int SIMULAPI SCU_RegisterWriteData(simulProcessor processor, simulCallbackStruct * cbs, simulPtr private)
{
	sprintf(buf, "SCU_REG write address 0x%x width 0x%x type 0x%x  data 0x%x\n", cbs->x.bus.address, cbs->x.bus.width, cbs->type, cbs->x.bus.data);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);

	return SIMUL_MEMORY_OK;
}


static void SCU_reg_init(void)
{
	/************************************************************************/
	/* init chipid reg                                                                     */
	/************************************************************************/
	scu_regs.CHIPID.B.CHREV = 0x1F;
	scu_regs.CHIPID.B.CHTEC = 0x01;
	scu_regs.CHIPID.B.CHID = 0x03;
	scu_regs.CHIPID.B.EEA = 0x01;
	scu_regs.CHIPID.B.UCODE = 0x7F;
	scu_regs.CHIPID.B.FSIZE = 0x0B;
	scu_regs.CHIPID.B.SP = 0x00;
	scu_regs.CHIPID.B.SEC = 0x01;

	/************************************************************************/
	/* init id reg                                                                     */
	/************************************************************************/
	scu_regs.ID.U = 0x00C4C081;

	/************************************************************************/
	/*init manid reg                                                                      */
	/************************************************************************/
	scu_regs.MANID.U = 0x00001820;

	/************************************************************************/
	/*                                                                      */
	/************************************************************************/
	scu_regs.OSCCON.B.GAINSEL = 0x02;

	scu_regs.PLLSTAT.U = 0x00000038;

	scu_regs.PLLCON0.U = 0x0001C600;

	scu_regs.PLLCON1.U = 0x0002020F;

	scu_regs.PLLERAYSTAT.U = 0x00000038;

	scu_regs.PLLERAYCON0.U = 0x00012E00;

	scu_regs.PLLERAYCON1.U = 0x000F020F;

	scu_regs.CCUCON0.U = 0x01120148;

	scu_regs.CCUCON1.U = 0x00002211;

	scu_regs.CCUCON5.U = 0x00000041;

	scu_regs.CCUCON2.U = 0x00000002;

	scu_regs.RSTSTAT.U = 0x13810000;

	scu_regs.RSTCON.U = 0x00000282;

	scu_regs.ESRCFG[0].U = 0x00000100;

	scu_regs.ESRCFG[1].U = 0x00000100;

	scu_regs.IOCR.U = 0x000020E0;

	scu_regs.STSTAT.U = 0x00008000;

	scu_regs.TRAPDIS.U = 0x0000FFFF;

	scu_regs.EVRSTAT.U = 0x00000400;

	scu_regs.EVRRSTCON.U = 0x007F7EC7;

	scu_regs.EVROVMON.U = 0x00F19EFD;

	scu_regs.EVRUVMON.U = 0x00D084CD;

	scu_regs.EVRMONCTRL.U = 0x00212121;

	scu_regs.EVR13CON.U = 0x03800380;

	scu_regs.EVR33CON.U = 0x07800780;

	scu_regs.EVRTRIM.U = 0x008F73E4;

	scu_regs.EVRSDCTRL1.U = 0x0940051F;

	scu_regs.EVRSDCTRL2.U = 0x15CC06CC;

	scu_regs.EVRSDCTRL3.U = 0x00090A3C;

	scu_regs.EVRSDCTRL4.U = 0x00001001;

	scu_regs.EVRSDCOEFF1.U = 0x00696D6C;

	scu_regs.EVRSDCOEFF2.U = 0x00696D6C;

	scu_regs.EVRSDCOEFF3.U = 0x00B65212;

	scu_regs.EVRSDCOEFF4.U = 0x00005AB6;

	scu_regs.EVRSDCOEFF5.U = 0x00B65212;

	scu_regs.EVRSDCOEFF6.U = 0x00005AB6;

	scu_regs.PMCSR[0].U = 0x00000100;

	scu_regs.PMCSR[1].U = 0x00000100;

	scu_regs.PMCSR[2].U = 0x00000100;

	scu_regs.PMSWCR0.U = 0x000002D0;

	scu_regs.PMSWCR1.U = 0x01000000;

	scu_regs.PMSWSTAT.U = 0x00010000;

	scu_regs.LCLCON1.U = 0x80010000;

	scu_regs.DTSCON.U = 0x00000001;

	scu_regs.DTSLIM.U = 0x03FF0000;

	scu_regs.WDTS.CON0.U = 0xFFFC000E;

	scu_regs.WDTCPU[0].CON0.U = 0xFFFC000E;

	scu_regs.WDTCPU[1].CON0.U = 0xFFFC000E;

	scu_regs.WDTCPU[2].CON0.U = 0xFFFC000E;

	scu_regs.WDTCPU[1].CON1.U = 0x00000008;

	scu_regs.WDTCPU[2].CON1.U = 0x00000008;

	scu_regs.WDTS.SR.U = 0xFFFC0010;

	scu_regs.WDTCPU[0].SR.U = 0xFFFC0010;

	scu_regs.WDTCPU[1].SR.U = 0xFFFC0008;

	scu_regs.WDTCPU[2].SR.U = 0xFFFC0008;

	scu_regs.EMSR.U = 0x00000001;

	scu_regs.ACCEN0.U = 0xFFFFFFFF;
}

void SCU_Init(simulProcessor processor, simulCallbackStruct * cbs) 
{
	simulWord   from = 0;
	simulWord	to = 0;
	unsigned int i = 0;

	SCU_debug_file = SIMUL_OpenFile(processor, "./debug_scu.log", SIMUL_FILE_CREATE);
	if (SCU_debug_file != NULL)
	{
		SIMUL_Warning(processor, "create file debug_scu.log success!");
	} 
	else
	{
		SIMUL_Warning(processor, "create file debug_scu.log failed!");
		return ;
	}

	sprintf(buf, "SCU_init bus type %d\n", cbs->x.init.argpbustype[1]);
	SIMUL_WritelineFile(processor, SCU_debug_file, buf);

	SCU_reg_init();

#if 1
	for (i = 0; i<SCU_REG_MAX; i++)
	{
		if (scu_regs_opt[i].reg_read_func_ptr != NULL)
		{
			from = SCU_BASE_ADDRESS + scu_regs_opt[i].offset;
			to = from + 3U;

			sprintf(buf, "SCU_init read func ptr 0x%x  from 0x%x to 0x%x\n", scu_regs_opt[i].reg_read_func_ptr, from, to);
			SIMUL_WriteFile(processor, SCU_debug_file, buf, strlen(buf));

			SIMUL_RegisterBusReadCallback(processor, scu_regs_opt[i].reg_read_func_ptr, (simulPtr)NULL, cbs->x.init.argpbustype[1], (simulWord *)&from, (simulWord *)&to);
		}
		if (scu_regs_opt[i].reg_write_func_ptr != NULL)
		{
			from = SCU_BASE_ADDRESS + scu_regs_opt[i].offset;
			to = from + 3U;

			sprintf(buf, "SCU_init write func ptr 0x%x  from 0x%x to 0x%x\n", scu_regs_opt[i].reg_write_func_ptr, from, to);
			SIMUL_WriteFile(processor, SCU_debug_file, buf, strlen(buf));

			SIMUL_RegisterBusWriteCallback(processor, scu_regs_opt[i].reg_write_func_ptr  , (simulPtr)NULL, cbs->x.init.argpbustype[1], (simulWord *)&from, (simulWord *)&to);
		}
	}

	SCU_bus_type = cbs->x.init.argpbustype[1];

#else
	from = SCU_BASE_ADDRESS;
	to = SCU_END_ADDRESS;
	SIMUL_RegisterBusReadCallback(processor, SCU_RegisterReadData, (simulPtr)NULL, cbs->x.init.argpbustype[1], (simulWord *)&from, (simulWord *)&to);
	SIMUL_RegisterBusWriteCallback(processor, SCU_RegisterWriteData , (simulPtr)NULL, cbs->x.init.argpbustype[1], (simulWord *)&from, (simulWord *)&to);
#endif 
}