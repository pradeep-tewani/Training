#include <stdint.h>
#include <string.h>
#include "stm32f446x.h"
#include "stm32f446x_gpio_driver_intr.h"
#include "stm32f446x_spi_driver.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

void delay()
{
	for(uint32_t i = 0; i < 500000; i++);
}

/*
 * PB14 (CN10, Pin 28) --> SPI2_MISO
 * PB15 (CN10, PIN 26)--> SPI2_MOSI
 * PB13 (CN10, PIN 30)-> SPI2_SCLK
 * PB12 (CN10, PIN 16)--> SPI2_NSS
 * ALT function mode : 5
 */

void SPI2_GPIOInits(void)
{
    GPIO_Handle_t SPIPins;

    SPIPins.pGPIOx = GPIOB;
    SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
    SPIPins.GPIO_PinConfig.GPIO_PinAltFunMode = 5;
    SPIPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    SPIPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
    SPIPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

    //SCLK
    SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
    GPIO_Init(&SPIPins);

    //MOSI
    SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_15;
    GPIO_Init(&SPIPins);

    //MISO
    SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_14;
    GPIO_Init(&SPIPins);
    //NSS
    //SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
    //GPIO_Init(&SPIPins);


}

void SPI2_Inits(void)
{

    SPI_Handle_t SPI2handle;

    SPI2handle.pSPIx = SPI2;
    SPI2handle.SPIConfig.SPI_BusConfig = SPI_BUS_CONFIG_FD;
    SPI2handle.SPIConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
    SPI2handle.SPIConfig.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV8;//generates sclk of 8MHz
    SPI2handle.SPIConfig.SPI_DFF = SPI_DFF_8BITS;
    SPI2handle.SPIConfig.SPI_CPOL = SPI_CPOL_LOW;
    SPI2handle.SPIConfig.SPI_CPHA = SPI_CPHA_LOW;
    SPI2handle.SPIConfig.SPI_SSM = SPI_SSM_EN; //software slave management enabled for NSS pin

    SPI_Init(&SPI2handle);
}

int main(void)
{
	char user_data[] = "Hello world";
	char rx_buf[15];
	uint8_t i = 0;

	//this function is used to initialize the GPIO pins to behave as SPI2 pins
	SPI2_GPIOInits();

	//This function is used to initialize the SPI2 peripheral parameters
	SPI2_Inits();

	//this makes NSS signal internally high and avoids MODF error
	SPI_SSIConfig(SPI2,ENABLE);

	//enable the SPI2 peripheral
	SPI_PeripheralControl(SPI2,ENABLE);
	memset(rx_buf, 0, sizeof(rx_buf));
while (1) {
	//to send data
	//SPI_SendData(SPI2,(uint8_t*)user_data,strlen(user_data));
	SPI_SendData(SPI2,(uint8_t*)user_data + i, 1);

	SPI_ReceiveData(SPI2, rx_buf + i, 1);
	i++;
	if (i >= strlen(user_data))
	{
		i = 0;
		memset(rx_buf, 0, sizeof(rx_buf));
	}

	//lets confirm SPI is not busy
	while( SPI_GetFlagStatus(SPI2,SPI_BUSY_FLAG) );
}

	//Disable the SPI2 peripheral
  //  SPI_PeripheralControl(SPI2,DISABLE);

	while(1);

	return 0;
}

