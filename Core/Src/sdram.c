#include "main.h"


extern SDRAM_HandleTypeDef hsdram1;


void SDRAM_Initialization_sequence() {

  __IO uint32_t tmpmrd = 0;

  FMC_SDRAM_CommandTypeDef cmd;

  /* Step 1: Configure a clock configuration enable command */
  cmd.CommandMode            = FMC_SDRAM_CMD_CLK_ENABLE;
  cmd.CommandTarget          = FMC_SDRAM_CMD_TARGET_BANK1;
  cmd.AutoRefreshNumber      = 1;
  cmd.ModeRegisterDefinition = 0;

  /* Send the command */
  HAL_SDRAM_SendCommand(&hsdram1, &cmd, SDRAM_TIMEOUT);

  /* Step 2: Insert 100 us minimum delay */
  /* Inserted delay is equal to 1 ms due to systick time base unit (ms) */
  HAL_Delay(1);

  /* Step 3: Configure a PALL (precharge all) command */
  cmd.CommandMode            = FMC_SDRAM_CMD_PALL;
  cmd.CommandTarget          = FMC_SDRAM_CMD_TARGET_BANK1;
  cmd.AutoRefreshNumber      = 1;
  cmd.ModeRegisterDefinition = 0;

  /* Send the command */
  HAL_SDRAM_SendCommand(&hsdram1, &cmd, SDRAM_TIMEOUT);

  /* Step 4: Configure an Auto Refresh command */
  cmd.CommandMode            = FMC_SDRAM_CMD_AUTOREFRESH_MODE;
  cmd.CommandTarget          = FMC_SDRAM_CMD_TARGET_BANK1;
  cmd.AutoRefreshNumber      = 8;
  cmd.ModeRegisterDefinition = 0;

  /* Send the command */
  HAL_SDRAM_SendCommand(&hsdram1, &cmd, SDRAM_TIMEOUT);

  /* Step 5: Program the external memory mode register */
  tmpmrd = (uint32_t)SDRAM_MODEREG_BURST_LENGTH_1          |\
                     SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL   |\
                     SDRAM_MODEREG_CAS_LATENCY_2           |\
                     SDRAM_MODEREG_OPERATING_MODE_STANDARD |\
                     SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;

  cmd.CommandMode            = FMC_SDRAM_CMD_LOAD_MODE;
  cmd.CommandTarget          = FMC_SDRAM_CMD_TARGET_BANK1;
  cmd.AutoRefreshNumber      = 1;
  cmd.ModeRegisterDefinition = tmpmrd;

  /* Send the command */
  HAL_SDRAM_SendCommand(&hsdram1, &cmd, SDRAM_TIMEOUT);

  /* Step 6: Set the refresh rate counter */
  /* Set the device refresh rate */
  HAL_SDRAM_ProgramRefreshRate(&hsdram1, REFRESH_COUNT);

}
