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
    uint8_t iprx_section  = IRQNumber %4 ;

    uint8_t shift_amount = ( 8 * iprx_section) + ( 8 - NO_PR_BITS_IMPLEMENTED) ;

    *(  NVIC_PR_BASE_ADDR + iprx ) |=  ( IRQPriority << shift_amount );

}

uint8_t SPI_SendDataIT(SPI_Handle_t *pSPIHandle,uint8_t *pTxBuffer, uint32_t Len)
{
    uint8_t state = pSPIHandle->TxState;

    if(state != SPI_BUSY_IN_TX)
    {
        //1 . Save the Tx buffer address and Len information in some global variables
        pSPIHandle->pTxBuffer = pTxBuffer;
        pSPIHandle->TxLen = Len;
        //2.  Mark the SPI state as busy in transmission so that
        //    no other code can take over same SPI peripheral until transmission is over
        pSPIHandle->TxState = SPI_BUSY_IN_TX;

        //3. Enable the TXEIE control bit to get interrupt whenever TXE flag is set in SR
        pSPIHandle->pSPIx->CR2 |= ( 1 << SPI_CR2_TXEIE );

    }
    return state;
}

uint8_t SPI_ReceiveDataIT(SPI_Handle_t *pSPIHandle, uint8_t *pRxBuffer, uint32_t Len)
{
    uint8_t state = pSPIHandle->RxState;

    if(state != SPI_BUSY_IN_RX)
    {
        //1 . Save the Rx buffer address and Len information in some global variables
        pSPIHandle->pRxBuffer = pRxBuffer;
        pSPIHandle->RxLen = Len;
        //2.  Mark the SPI state as busy in reception so that
        //    no other code can take over same SPI peripheral until reception is over
        pSPIHandle->RxState = SPI_BUSY_IN_RX;

        //3. Enable the RXNEIE control bit to get interrupt whenever RXNEIE flag is set in SR
        pSPIHandle->pSPIx->CR2 |= ( 1 << SPI_CR2_RXNEIE );

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
        //1. load the data in to the DR
        pSPIHandle->pSPIx->DR =   *((uint16_t*)pSPIHandle->pTxBuffer);
        pSPIHandle->TxLen--;
        pSPIHandle->TxLen--;
        (uint16_t*)pSPIHandle->pTxBuffer++;
    }else
    {
        //8 bit DFF
        pSPIHandle->pSPIx->DR =   *pSPIHandle->pTxBuffer;
        pSPIHandle->TxLen--;
        pSPIHandle->pTxBuffer++;
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
    if(pSPIHandle->pSPIx->CR1 & ( 1 << 11))
    {
        //16 bit
        *((uint16_t*)pSPIHandle->pRxBuffer) = (uint16_t) pSPIHandle->pSPIx->DR;
        pSPIHandle->RxLen -= 2;
        pSPIHandle->pRxBuffer++;
        pSPIHandle->pRxBuffer++;

    }else
    {
        //8 bit
        *(pSPIHandle->pRxBuffer) = (uint8_t) pSPIHandle->pSPIx->DR;
        pSPIHandle->RxLen--;
        pSPIHandle->pRxBuffer++;
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
