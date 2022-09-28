/*
 *  Macros to reset GPIOx peripherals
 */
#define GPIOA_REG_RESET()               do{ (RCC->AHB1RSTR |= (1 << 0)); (RCC->AHB1RSTR &= ~(1 << 0)); }while(0)

typedef struct {
	volatile uint32_t CR;
	volatile uint32_t PLLCFGR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;           /*!< TODO,                                           Address offset: 0x0C */
	volatile uint32_t AHB1RSTR;      /*!< TODO,                                           Address offset: 0x10 */
	volatile uint32_t AHB2RSTR;      /*!< TODO,                                           Address offset: 0x14 */
	volatile uint32_t AHB3RSTR;      /*!< TODO,                                           Address offset: 0x18 */
	uint32_t      RESERVED0;     /*!< Reserved, 0x1C                                                       */
	volatile uint32_t APB1RSTR;      /*!< TODO,                                           Address offset: 0x20 */
	volatile uint32_t APB2RSTR;      /*!< TODO,                                           Address offset: 0x24 */
	uint32_t      RESERVED1[2];  /*!< Reserved, 0x28-0x2C                                                  */
	volatile uint32_t AHB1ENR;       /*!< TODO,                                           Address offset: 0x30 */
	volatile uint32_t AHB2ENR;       /*!< TODO,                                           Address offset: 0x34 */
	volatile uint32_t AHB3ENR;       /*!< TODO,                                           Address offset: 0x38 */
	uint32_t      RESERVED2;     /*!< Reserved, 0x3C                                                       */
	volatile uint32_t APB1ENR;       /*!< TODO,                                           Address offset: 0x40 */
	volatile uint32_t APB2ENR;       /*!< TODO,                                           Address offset: 0x44 */
	uint32_t      RESERVED3[2];  /*!< Reserved, 0x48-0x4C                                                  */
	volatile uint32_t AHB1LPENR;     /*!< TODO,                                           Address offset: 0x50 */
	volatile uint32_t AHB2LPENR;     /*!< TODO,                                           Address offset: 0x54 */
	volatile uint32_t AHB3LPENR;     /*!< TODO,                                           Address offset: 0x58 */
	uint32_t      RESERVED4;     /*!< Reserved, 0x5C                                                       */
	volatile uint32_t APB1LPENR;     /*!< TODO,                                           Address offset: 0x60 */
	volatile uint32_t APB2LPENR;     /*!< RTODO,                                          Address offset: 0x64 */
	uint32_t      RESERVED5[2];  /*!< Reserved, 0x68-0x6C                                                  */
	volatile uint32_t BDCR;          /*!< TODO,                                           Address offset: 0x70 */
	volatile uint32_t CSR;           /*!< TODO,                                           Address offset: 0x74 */
	uint32_t      RESERVED6[2];  /*!< Reserved, 0x78-0x7C                                                  */
	volatile uint32_t SSCGR;         /*!< TODO,                                           Address offset: 0x80 */
	volatile uint32_t PLLI2SCFGR;    /*!< TODO,                                           Address offset: 0x84 */
	volatile uint32_t PLLSAICFGR;    /*!< TODO,                                           Address offset: 0x88 */
	volatile uint32_t DCKCFGR;       /*!< TODO,                                           Address offset: 0x8C */
	volatile uint32_t CKGATENR;      /*!< TODO,                                           Address offset: 0x90 */
	volatile uint32_t DCKCFGR2;      /*!< TODO,                                           Address offset: 0x94 */
} RCC_RegDef_t;

#define USART2_BASEADDR			(APB1PERIPH_BASEADDR + 0x4400)
#define USART3_BASEADDR			(APB1PERIPH_BASEADDR + 0x4800)
#define UART4_BASEADDR			(APB1PERIPH_BASEADDR + 0x4C00)
#define UART5_BASEADDR			(APB1PERIPH_BASEADDR + 0x5000)

#define USART1_BASEADDR			(APB2PERIPH_BASEADDR + 0x1000)
#define USART6_BASEADDR			(APB2PERIPH_BASEADDR + 0x1400)

typedef struct
{
    __vo uint32_t SR;         /*!< TODO,                                            Address offset: 0x00 */
    __vo uint32_t DR;         /*!< TODO,                                            Address offset: 0x04 */
    __vo uint32_t BRR;        /*!< TODO,                                            Address offset: 0x08 */
    __vo uint32_t CR1;        /*!< TODO,                                            Address offset: 0x0C */
    __vo uint32_t CR2;        /*!< TODO,                                            Address offset: 0x10 */
    __vo uint32_t CR3;        /*!< TODO,                                            Address offset: 0x14 */
    __vo uint32_t GTPR;       /*!< TODO,                                            Address offset: 0x18 */
} USART_RegDef_t;

#define USART1              ((USART_RegDef_t*)USART1_BASEADDR)
#define USART2              ((USART_RegDef_t*)USART2_BASEADDR)
#define USART3              ((USART_RegDef_t*)USART3_BASEADDR)
#define UART4               ((USART_RegDef_t*)UART4_BASEADDR)
#define UART5               ((USART_RegDef_t*)UART5_BASEADDR)
#define USART6              ((USART_RegDef_t*)USART6_BASEADDR)

/*
 * Clock Enable Macros for USARTx peripherals
 */
#define USART1_PCCK_EN() (RCC->APB2ENR |= (1 << 4))
#define USART2_PCCK_EN() (RCC->APB1ENR |= (1 << 17))
#define USART3_PCCK_EN() (RCC->APB1ENR |= (1 << 18))
#define UART4_PCCK_EN()  (RCC->APB1ENR |= (1 << 19))
#define UART5_PCCK_EN()  (RCC->APB1ENR |= (1 << 20))
#define USART6_PCCK_EN() (RCC->APB1ENR |= (1 << 5))

#define SPI_CR1_CPHA                     0
#define SPI_CR1_CPOL                     1
#define SPI_CR1_MSTR                     2
#define SPI_CR1_BR                       3
#define SPI_CR1_SPE                      6
#define SPI_CR1_LSBFIRST                 7
#define SPI_CR1_SSI                      8
#define SPI_CR1_SSM                      9
#define SPI_CR1_RXONLY                  10
#define SPI_CR1_DFF                     11
#define SPI_CR1_CRCNEXT                 12
#define SPI_CR1_CRCEN                   13
#define SPI_CR1_BIDIOE                  14
#define SPI_CR1_BIDIMODE                15

/*
 * Bit position definitions SPI_CR2
 */
#define SPI_CR2_RXDMAEN                 0
#define SPI_CR2_TXDMAEN                 1
#define SPI_CR2_SSOE                    2
#define SPI_CR2_FRF                     4
#define SPI_CR2_ERRIE                   5
#define SPI_CR2_RXNEIE                  6
#define SPI_CR2_TXEIE                   7


/*
 * Bit position definitions SPI_SR
 */
#define SPI_SR_RXNE                     0
#define SPI_SR_TXE                      1
#define SPI_SR_CHSIDE                   2
#define SPI_SR_UDR                      3
#define SPI_SR_CRCERR                   4
#define SPI_SR_MODF                     5
#define SPI_SR_OVR                      6
#define SPI_SR_BSY                      7
#define SPI_SR_FRE                      8

/*
 * Bit position definitions USART_CR1
 */
#define USART_CR1_SBK                   0
#define USART_CR1_RWU                   1
#define USART_CR1_RE                    2
#define USART_CR1_TE                    3
#define USART_CR1_IDLEIE                4
#define USART_CR1_RXNEIE                5
#define USART_CR1_TCIE                  6
#define USART_CR1_TXEIE                 7
#define USART_CR1_PEIE                  8
#define USART_CR1_PS                    9
#define USART_CR1_PCE                   10
#define USART_CR1_WAKE                  11
#define USART_CR1_M                     12
#define USART_CR1_UE                    13
#define USART_CR1_OVER8                 15



/*
 * Bit position definitions USART_CR2
 */
#define USART_CR2_ADD                   0
#define USART_CR2_LBDL                  5
#define USART_CR2_LBDIE                 6
#define USART_CR2_LBCL                  8
#define USART_CR2_CPHA                  9
#define USART_CR2_CPOL                  10
#define USART_CR2_STOP                  12
#define USART_CR2_LINEN                 14

/*
 * Bit position definitions USART_CR3
 */
#define USART_CR3_EIE                   0
#define USART_CR3_IREN                  1
#define USART_CR3_IRLP                  2
#define USART_CR3_HDSEL                 3
#define USART_CR3_NACK                  4
#define USART_CR3_SCEN                  5
#define USART_CR3_DMAR                  6
#define USART_CR3_DMAT                  7
#define USART_CR3_RTSE                  8
#define USART_CR3_CTSE                  9
#define USART_CR3_CTSIE                 10
#define USART_CR3_ONEBIT                11

/*
 * Bit position definitions USART_SR
 */

#define USART_SR_PE                     0
#define USART_SR_FE                     1
#define USART_SR_NE                     2
#define USART_SR_ORE                    3
#define USART_SR_IDLE                   4
#define USART_SR_RXNE                   5
#define USART_SR_TC                     6
#define USART_SR_TXE                    7
#define USART_SR_LBD                    8
#define USART_SR_CTS                    9



