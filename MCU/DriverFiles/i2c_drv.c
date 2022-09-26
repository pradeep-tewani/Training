#include "i2c_drv.h"
#include "stm32f446x_rcc_driver.h"
#include "stm32f446x_gpio_driver_intr.h"

static void I2C_GenerateStartCondition(I2C_RegDef_t *pI2Cx)
{
	//TODO: Generate Start condition
}

static void I2C_ExecuteAddressPhaseWrite(I2C_RegDef_t *pI2Cx, uint8_t SlaveAddr)
{
	//SlaveAddr is Slave address + r/w bit=0
}


static void I2C_ExecuteAddressPhaseRead(I2C_RegDef_t *pI2Cx, uint8_t SlaveAddr)
{
	//SlaveAddr is Slave address + r/w bit=1
}


static void I2C_ClearADDRFlag(I2C_Handle_t *pI2CHandle )
{
	uint32_t dummy_read;

	//clear the ADDR flag ( read SR1 , read SR2)

}


 void I2C_GenerateStopCondition(I2C_RegDef_t *pI2Cx)
{
}

void I2C_PeripheralControl(I2C_RegDef_t *pI2Cx, uint8_t EnOrDi)
{
	if(EnOrDi == ENABLE)
	{
		pI2Cx->CR1 |= (1 << I2C_CR1_PE);
		//pI2cBaseAddress->CR1 |= I2C_CR1_PE_Bit_Mask;
	}else
	{
		pI2Cx->CR1 &= ~(1 << 0);
	}

}

void I2C_PeriClockControl(I2C_RegDef_t *pI2Cx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(pI2Cx == I2C1)
		{
			I2C1_PCLK_EN();
		}else if (pI2Cx == I2C2)
		{
			I2C2_PCLK_EN();
		}else if (pI2Cx == I2C3)
		{
			I2C3_PCLK_EN();
		}
	}
	else
	{
		//TODO
	}
}

void I2C_Init(I2C_Handle_t *pI2CHandle)
{
	uint32_t tempreg = 0 ;

	//TODO 1: Enable the clock for the i2cx peripheral

	//TODO 2: Configure the ACK bit

	//TODO 3: Configure the FREQ field of CR2

   //TODO 4: Program the device own address
	tempreg = 0;

	//TODO 5: CCR calculations
	uint16_t ccr_value = 0;
	tempreg = 0;
	if(pI2CHandle->I2C_Config.I2C_SCLSpeed <= I2C_SCL_SPEED_SM)
	{
		//mode is standard mode
		ccr_value = (RCC_GetPCLK1Value() / ( 2 * pI2CHandle->I2C_Config.I2C_SCLSpeed ) );
		tempreg |= (ccr_value & 0xFFF);
	}else
	{
		//mode is fast mode
		tempreg |= ( 1 << 15);
		tempreg |= (pI2CHandle->I2C_Config.I2C_FMDutyCycle << 14);
		if(pI2CHandle->I2C_Config.I2C_FMDutyCycle == I2C_FM_DUTY_2)
		{
			ccr_value = (RCC_GetPCLK1Value() / ( 3 * pI2CHandle->I2C_Config.I2C_SCLSpeed ) );
		}else
		{
			ccr_value = (RCC_GetPCLK1Value() / ( 25 * pI2CHandle->I2C_Config.I2C_SCLSpeed ) );
		}
		tempreg |= (ccr_value & 0xFFF);
	}
	pI2CHandle->pI2Cx->CCR = tempreg;

	//TODO 6: TRISE Configuration.
	//As per specifications, max 1000ns for SM and 300ns for FM
	// FPCLK1 * 1000ns for SM and FPCLK1 * 300ns for FM
	if(pI2CHandle->I2C_Config.I2C_SCLSpeed <= I2C_SCL_SPEED_SM)
	{
		//mode is standard mode
		tempreg = (RCC_GetPCLK1Value() /1000000U) + 1 ;

	}else
	{
		//mode is fast mode
		tempreg = ( (RCC_GetPCLK1Value() * 300) / 1000000000U ) + 1;

	}

	pI2CHandle->pI2Cx->TRISE = (tempreg & 0x3F);

}

void I2C_ManageAcking(I2C_RegDef_t *pI2Cx, uint8_t EnorDi)
{
	if(EnorDi == I2C_ACK_ENABLE)
	{
		//TODO 7: enable the ack
	}else
	{
		//TODO 8: disable the ack
	}
}

void I2C_DeInit(I2C_RegDef_t *pI2Cx)
{

}


uint8_t I2C_GetFlagStatus(I2C_RegDef_t *pI2Cx , uint32_t FlagName)
{
	if(pI2Cx->SR1 & FlagName)
	{
		return FLAG_SET;
	}
	return FLAG_RESET;
}

void i2c_delay()
{
	volatile uint8_t i;
	for (i = 0; i < 10; i++);
}

void I2C_MasterSendData(I2C_Handle_t *pI2CHandle,uint8_t *pTxbuffer, uint32_t Len, uint8_t SlaveAddr,uint8_t Sr)
{
	// TODO 1: Generate the START condition

	//TODO 2: confirm that start generation is completed by checking the SB flag in the SR1
	//   Note: Until SB is cleared SCL will be stretched (pulled to LOW)

	//TODO 3: Send the address of the slave with r/nw bit set to w(0) (total 8 bits )

	//TODO 4: Confirm that address phase is completed by checking the ADDR flag in teh SR1

	//TODO 5: clear the ADDR flag according to its software sequence
	//   Note: Until ADDR is cleared SCL will be stretched (pulled to LOW)

	while(Len > 0)
	{
		//TODO 6: Wait for TXE bit to be set and write into data register, once set
		pTxbuffer++;
		Len--;
	}

	//TODO 7: when Len becomes zero wait for TXE=1 and BTF=1 before generating the STOP condition
	//   Note: TXE=1 , BTF=1 , means that both SR and DR are empty and next transmission should begin
	//   when BTF=1 SCL will be stretched (pulled to LOW)


	//TODO 8: Generate STOP condition and master need not to wait for the completion of stop condition.
	//   Note: generating STOP, automatically clears the BTF
	i2c_delay();

}


void I2C_MasterReceiveData(I2C_Handle_t *pI2CHandle,uint8_t *pRxBuffer, uint8_t Len, uint8_t SlaveAddr,uint8_t Sr)
{

	//TODO 1: Generate the START condition

	//TODO 2: confirm that start generation is completed by checking the SB flag in the SR1
	//   Note: Until SB is cleared SCL will be stretched (pulled to LOW)

	//TODO 3: Send the address of the slave with r/nw bit set to R(1) (total 8 bits )

	//TODO 4: wait until address phase is completed by checking the ADDR flag in teh SR1
	while( !  I2C_GetFlagStatus(pI2CHandle->pI2Cx,I2C_FLAG_ADDR)   );

	//procedure to read only 1 byte from slave
	if(Len == 1)
	{
		//TODO 5: Disable Acking

		//TODO 6: clear the ADDR flag

		//TODO 7: wait until  RXNE becomes 1

		//TODO 8: generate STOP condition

		//TODO 9: read data in to buffer

	}
    //procedure to read data from slave when Len > 1
	if(Len > 1)
	{
		//TODO 10: clear the ADDR flag

		//read the data until Len becomes zero
		for ( uint32_t i = Len ; i > 0 ; i--)
		{
			//TODO 11: wait until RXNE becomes 1

			if(i == 2) //if last 2 bytes are remaining
			{
				//TODO 12: Disable Acking

				//TODO 13: generate STOP condition

			}

			//TODO 14: read the data from data register in to buffer

			//TODO 15: increment the buffer address

		}
	}
	//re-enable ACKing
	if(pI2CHandle->I2C_Config.I2C_AckControl == I2C_ACK_ENABLE)
	{
		I2C_ManageAcking(pI2CHandle->pI2Cx,I2C_ACK_ENABLE);
	}
}

