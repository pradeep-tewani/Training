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
