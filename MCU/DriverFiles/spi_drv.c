void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi)
{
}

void SPI_Init(SPI_Handle_t *pSPIHandle)
{

    //TODO 1: Peripheral clock enable


    //TODO 2: First lets configure the SPI_CR1 register

    uint32_t tempreg = 0;

    //TODO 2: configure the device mode

    //TODO 4: Configure the bus config
    if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_FD)
    {
        //bidi mode should be cleared

    }else if (pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_HD)
    {
        //bidi mode should be set
    }else if (pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_SIMPLEX_RXONLY)
    {
        //BIDI mode should be cleared
        //RXONLY bit must be set
    }
    //TODO 5: Configure the spi serial clock speed (baud rate)

    //TODO 6:  Configure the DFF

    //TODO 7: configure the CPOL
    tempreg |= pSPIHandle->SPIConfig.SPI_CPOL << SPI_CR1_CPOL;

    //TODO 8: Configure the CPHA

	//TODO 9: Configure the Software Slave management

    pSPIHandle->pSPIx->CR1 = tempreg;
}

void SPI_DeInit(SPI_RegDef_t *pSPIx)
{
 //todo
}

uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx , uint32_t FlagName)
{
    if(pSPIx->SR & FlagName)
    {
        return FLAG_SET;
    }
    return FLAG_RESET;
}

void SPI_SendData(SPI_RegDef_t *pSPIx,uint8_t *pTxBuffer, uint32_t Len)
{
    while(Len > 0)
    {
        //TODO 1. wait until TXE is set
        while();

        //TODO 2. check the DFF bit in CR1
        if()
        {
            //16 bit DFF
            //TODO 3. load the data in to the DR
            Len--;
            Len--;
            (uint16_t*)pTxBuffer++;
        }else
        {
            //8 bit DFF
            //TODO 4. load the data in to the DR
            Len--;
            pTxBuffer++;
        }
    }
}

void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t Len)
{
	while(Len > 0)
	{
		//TODO 1. wait until RXNE is set
		while();

		//TODO 2. check the DFF bit in CR1
		if()
		{
			//16 bit DFF
			//TODO 3: load the data from DR to Rxbuffer address
			Len--;
			Len--;
			(uint16_t*)pRxBuffer++;
		}else
		{
			//8 bit DFF
			//TODO 4: load the data from DR to Rxbuffer address
			Len--;
			pRxBuffer++;
		}
	}
}

void SPI_PeripheralControl(SPI_RegDef_t *pSPIx, uint8_t EnOrDi)
{
    if(EnOrDi == ENABLE)
    {
    }else
    {
    }
}

void  SPI_SSIConfig(SPI_RegDef_t *pSPIx, uint8_t EnOrDi)
{
    if(EnOrDi == ENABLE)
    {
        pSPIx->CR1 |=  (1 << SPI_CR1_SSI);
    }else
    {
        pSPIx->CR1 &=  ~(1 << SPI_CR1_SSI);
    }
}

void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(IRQNumber <= 31)
		{
			//program ISER0 register
			*NVIC_ISER0 |= ( 1 << IRQNumber );

		}else if(IRQNumber > 31 && IRQNumber < 64 ) //32 to 63
		{
			//program ISER1 register
			*NVIC_ISER1 |= ( 1 << (IRQNumber % 32) );
		}
		else if(IRQNumber >= 64 && IRQNumber < 96 )
		{
			//program ISER2 register //64 to 95
			*NVIC_ISER2 |= ( 1 << (IRQNumber % 64) );
		}
	}else
	{
		if(IRQNumber <= 31)
		{
			//program ICER0 register
			*NVIC_ICER0 |= ( 1 << IRQNumber );
		}else if(IRQNumber > 31 && IRQNumber < 64 )
		{
			//program ICER1 register
			*NVIC_ICER1 |= ( 1 << (IRQNumber % 32) );
		}
		else if(IRQNumber >= 64 && IRQNumber < 96 )
		{
			//program ICER2 register
			*NVIC_ICER2 |= ( 1 << (IRQNumber % 64) );
			//program ICER2 register
				   *NVIC_ICER2 |= ( 1 << (IRQNumber % 64) );
		 }
	 }
}

void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority)
{
    //1. first lets find out the ipr register
    uint8_t iprx = IRQNumber / 4;
    uint8_t iprx_section  = IRQNumber % 4 ;

    uint8_t shift_amount = ( 8 * iprx_section) + ( 8 - NO_PR_BITS_IMPLEMENTED) ;

    *(  NVIC_PR_BASE_ADDR + iprx ) |=  ( IRQPriority << shift_amount );

}

uint8_t SPI_SendDataIT(SPI_Handle_t *pSPIHandle,uint8_t *pTxBuffer, uint32_t Len)
{
    uint8_t state = pSPIHandle->TxState;

    if(state != SPI_BUSY_IN_TX)
    {
        //TODO 1: Save the Tx buffer address and Len information in some global variables
        //TODO 2:  Mark the SPI state as busy in transmission so that

        //TODO 3: Set the state to Busy

        //TODO 2: Enable the TXEIE control bit to get interrupt whenever TXE flag is set in SR

    }
    return state;
}

uint8_t SPI_ReceiveDataIT(SPI_Handle_t *pSPIHandle, uint8_t *pRxBuffer, uint32_t Len)
{
    uint8_t state = pSPIHandle->RxState;

    if(state != SPI_BUSY_IN_RX)
    {
        //TODO 1: Save the Tx buffer address and Len information in some global variables
        //TODO 2: Mark the SPI state as busy in reception so that
        //TODO 3: Set the state to Busy

        //TODO 4: Enable the RXNEIE control bit to get interrupt whenever RXNEIE flag is set in SR

    }
    return state;

}

__weak void SPI_ApplicationEventCallback(SPI_Handle_t *pSPIHandle,uint8_t AppEv)
{

    //This is a weak implementation . the user application may override this function.
}

static void  spi_txe_interrupt_handle(SPI_Handle_t *pSPIHandle)
{
    // check the DFF bit in CR1
    if( (pSPIHandle->pSPIx->CR1 & ( 1 << SPI_CR1_DFF) ) )
    {
        //16 bit DFF
        //TODO 1. load the data in to the DR, decrement the length & increment the buffer pointer
    }else
    {
        //8 bit DFF
        //TODO 2. load the data in to the DR, decrement the length & increment the buffer pointer
    }

    if(! pSPIHandle->TxLen)
    {
        //TxLen is zero , so close the spi transmission and inform the application that
        //TX is over.

        //this prevents interrupts from setting up of TXE flag
        SPI_CloseTransmisson(pSPIHandle);
        SPI_ApplicationEventCallback(pSPIHandle,SPI_EVENT_TX_CMPLT);
    }
}

static void  spi_ovr_err_interrupt_handle(SPI_Handle_t *pSPIHandle)
{

    uint8_t temp;
    //1. clear the ovr flag
    if(pSPIHandle->TxState != SPI_BUSY_IN_TX)
    {
        temp = pSPIHandle->pSPIx->DR;
        temp = pSPIHandle->pSPIx->SR;
    }
    (void)temp;
    //2. inform the application
    SPI_ApplicationEventCallback(pSPIHandle,SPI_EVENT_OVR_ERR);

}


void SPI_CloseTransmisson(SPI_Handle_t *pSPIHandle)
{
    pSPIHandle->pSPIx->CR2 &= ~( 1 << SPI_CR2_TXEIE);
    pSPIHandle->pTxBuffer = NULL;
    pSPIHandle->TxLen = 0;
    pSPIHandle->TxState = SPI_READY;

}

void SPI_CloseReception(SPI_Handle_t *pSPIHandle)
{
    pSPIHandle->pSPIx->CR2 &= ~( 1 << SPI_CR2_RXNEIE);
    pSPIHandle->pRxBuffer = NULL;
    pSPIHandle->RxLen = 0;
    pSPIHandle->RxState = SPI_READY;
}

void SPI_ClearOVRFlag(SPI_RegDef_t *pSPIx)
{
    uint8_t temp;
    temp = pSPIx->DR;
    temp = pSPIx->SR;
    (void)temp;

}

static void  spi_rxne_interrupt_handle(SPI_Handle_t *pSPIHandle)
{
    //do rxing as per the dff
    if(pSPIHandle->pSPIx->CR1 & ( 1 << SPI_CR1_DFF))
    {
		//TODO 1: load the data from DR to Rxbuffer address, decrement the length and increment the buffer pointer

    }else
    {
        //8 bit
		//TODO 1: load the data from DR to Rxbuffer address, decrement the length and increment the buffer pointer
    }

    if(! pSPIHandle->RxLen)
    {
        //reception is complete
        SPI_CloseReception(pSPIHandle);
        SPI_ApplicationEventCallback(pSPIHandle,SPI_EVENT_RX_CMPLT);
    }
}


void SPI_IRQHandling(SPI_Handle_t *pHandle)
{

    uint8_t temp1 , temp2;
    //first lets check for TXE
    temp1 = pHandle->pSPIx->SR & ( 1 << SPI_SR_TXE);
    temp2 = pHandle->pSPIx->CR2 & ( 1 << SPI_CR2_TXEIE);

    if( temp1 && temp2)
    {
        //handle TXE
        spi_txe_interrupt_handle(pHandle);
    }

    // check for RXNE
    temp1 = pHandle->pSPIx->SR & ( 1 << SPI_SR_RXNE);
    temp2 = pHandle->pSPIx->CR2 & ( 1 << SPI_CR2_RXNEIE);

    if( temp1 && temp2)
    {
        //handle RXNE
        spi_rxne_interrupt_handle(pHandle);
    }

    // check for ovr flag
    temp1 = pHandle->pSPIx->SR & ( 1 << SPI_SR_OVR);
    temp2 = pHandle->pSPIx->CR2 & ( 1 << SPI_CR2_ERRIE);

    if( temp1 && temp2)
    {
        //handle ovr error
        spi_ovr_err_interrupt_handle(pHandle);
    }
}

