#include <stdtypes.hpp>

#include <kernel/bcm2711/gpio.hpp>

#ifndef _BCM2711_UART_H_
#define _BCM2711_UART_H_

/* The one on the Pi is a lot like the one on a PC, other than
 * there's a bunch of MMIO instead of inb/outb stuff.
 */

/* Page 8, BCM2711 peripherals */
typedef enum BCMAuxRegisters
{
	AUX_BASE = BCM2711_PERIPHERAL_BASE + 0x215000,
	AUX_IRQ = AUX_BASE,

	AUX_ENABLES = AUX_BASE + 0x04,

	AUX_MU_IO_REG = AUX_BASE + 0x40,
	AUX_MU_IER_REG = AUX_BASE + 0x44,
	AUX_MU_IIR_REG = AUX_BASE + 0x48,
	AUX_MU_LCR_REG = AUX_BASE + 0x4C,
	AUX_MU_MCR_REG = AUX_BASE + 0x50,
	AUX_MU_LSR_REG = AUX_BASE + 0x54,
	AUX_MU_MSR_REG = AUX_BASE + 0x58,
	AUX_MU_SCRATCH_REG = AUX_BASE + 0x5C,
	AUX_MU_CNTL_REG = AUX_BASE + 0x60,
	AUX_MU_STAT_REG = AUX_BASE + 0x64,
	AUX_MU_BAUD_REG = AUX_BASE + 0x68,
}BCMAuxRegisters;


typedef enum BCMUARTRegisters
{
	UART0_BASE_ADDR = BCM2711_PERIPHERAL_BASE + 0x00201000,
	UART2_BASE_ADDR = BCM2711_PERIPHERAL_BASE + 0x00201400,
	UART3_BASE_ADDR = BCM2711_PERIPHERAL_BASE + 0x00201600,
	UART4_BASE_ADDR = BCM2711_PERIPHERAL_BASE + 0x00201800,
	UART5_BASE_ADDR = BCM2711_PERIPHERAL_BASE + 0x00201A00,

	UART0_DATA_REG = UART0_BASE_ADDR + 0x00,
	UART0_RSRECR   = UART0_BASE_ADDR + 0x04,
	UART0_FLAG_REG = UART0_BASE_ADDR + 0x18,
	UART0_INVALID1 = UART0_BASE_ADDR + 0x20,
	UART0_INT_BAUD_REG = UART0_BASE_ADDR + 0x24,
	UART0_FRACT_BAUD_REG = UART0_BASE_ADDR + 0x28,
	UART0_LINE_CTRL_REG = UART0_BASE_ADDR + 0x2C,
	UART0_CTRL_REG = UART0_BASE_ADDR + 0x30,
	UART0_INT_FIFO_SEL_REG = UART0_BASE_ADDR + 0x34,
	UART0_INT_MASK_CLR_REG = UART0_BASE_ADDR + 0x38,
	UART0_INT_STATUS_REG = UART0_BASE_ADDR + 0x3C,
	UART0_MASKED_INT_STATUS_REG = UART0_BASE_ADDR + 0x40,
	UART0_INT_CLR_REG = UART0_BASE_ADDR + 0x44,
	UART0_DMA_CTRL_REG = UART0_BASE_ADDR + 0x48,
	UART0_TEST_CTRL_REG = UART0_BASE_ADDR + 0x80,
	UART0_ITIP_REG = UART0_BASE_ADDR + 0x84,
	UART0_ITOP_REG = UART0_BASE_ADDR + 0x88,
	UART0_TDR_REG = UART0_BASE_ADDR + 0x8C,

	/* TODO: Copy paste definitions for uart2,3,4, and 5. */

}BCMUARTRegisters;

typedef struct UARTDataReg
{
	union
	{
		UINT32  Raw;
		struct
		{
			UINT16 Invalid;
			UINT8 Invalid2 : 4;
			BOOL OverrunError : 1;
			BOOL BreakError : 1;
			BOOL ParityError : 1;
			BOOL FramingError : 1;
			UINT8 Data;
		};
	};
}__attribute__((__packed__)) UARTDataReg;

typedef struct UARTRSRECR
{
	union
	{
		UINT32  Raw;
		struct
		{
			UINT16 Invalid;
			UINT16 Invalid2 : 12;
			BOOL OverrunError : 1;
			BOOL BreakError : 1;
			BOOL ParityError : 1;
			BOOL FramingError : 1;
		};
	};
}__attribute__((__packed__)) UARTRSRECR;


typedef struct UARTFlagReg
{
	union
	{
		UINT32 Raw;
		struct
		{
			UINT16 Invalid1;
			UINT8 Invalid2;
			BOOL RI : 1;
			BOOL TXFE : 1;
			BOOL RXFF : 1;
			BOOL TXFF : 1;
			BOOL RXFE : 1;
			BOOL BUSY : 1;
			BOOL DCD : 1;
			BOOL DSR : 1;
			BOOL CTS : 1;
		};
	};
}__attribute__((__packed__)) UARTFlagReg;


typedef struct UARTIntBaudReg
{
	union
	{
		UINT32 Raw;
		struct
		{
			UINT16 Invalid1;
			UINT16 IntBaud; 
		};
	};
}__attribute__((__packed__)) UARTIntBaudReg;

typedef struct UARTFractBaudReg
{
	union
	{
		UINT32 Raw;
		struct
		{
			UINT16 Invalid1;
			UINT16 Invalid2 : 11; 
			UINT8 Fraction : 5;
		};
	};
}__attribute__((__packed__)) UARTFractBaudReg;

typedef struct UARTLineControlReg
{
	union
	{
		UINT32 Raw;
		struct
		{
			UINT16 Invalid1;
			UINT8 Invalid2; 
			BOOL SPS : 1;
			UINT8 WLEN : 2;
			BOOL FEN : 1;
			BOOL STP2 : 1;
			BOOL EPS : 1;
			BOOL PEN : 1;
			BOOL BRK : 1;
		};
	};
}__attribute__((__packed__)) UARTLineControlReg;

typedef struct UARTControlReg
{
	union
	{
		UINT32 Raw;
		struct
		{
			UINT16 Invalid1;
			BOOL CTSEN : 1;
			BOOL RTSEN : 1;
			BOOL OUT2 : 1;
			BOOL OUT1 : 1;
			BOOL RTS : 1;
			BOOL DTR : 1;
			BOOL RXE : 1;
			BOOL TXE : 1;
			BOOL LBE : 1;
			UINT8 Invalid2 : 4;
			BOOL SIRLP : 1;
			BOOL SIREN : 1;
			BOOL ENABLE : 1;
		};
	};
}__attribute__((__packed__)) UARTControlReg;

typedef struct UARTInterruptFIFOLevelSelect
{
	union
	{
		UINT32 Raw;
		struct
		{
			UINT16 Invalid1;
			UINT8 Invalid2 : 4;
			UINT8 RXIFPSEL : 3;
			UINT8 TXIFPSEL : 3;
			UINT8 RXIFLSEL : 3;
			UINT8 TXIFLSEL : 3;
		};
	};
}__attribute__((__packed__)) UARTInterruptFIFOLevelSelect;

typedef struct UARTInterruptMaskSelect
{
	union
	{
		UINT32 Raw;
		struct
		{
			UINT32 Invalid1 : 21;
			BOOL OEIM : 1;
			BOOL BEIM : 1;
			BOOL PEIM : 1;
			BOOL FEIM : 1;
			BOOL RTIM : 1;
			BOOL TXIM : 1;
			BOOL RXIM : 1;
			BOOL DSRMIM : 1;
			BOOL DCDMIM : 1;
			BOOL CTSMIM : 1;
			BOOL RIMIM : 1;
		};
	};
}__attribute__((__packed__)) UARTInterruptMaskSelect;

typedef struct UARTRawInterrupt
{
	union
	{
		UINT32 Raw;
		struct
		{
			UINT32 Invalid1 : 21;
			BOOL OERIS : 1;
			BOOL BERIS : 1;
			BOOL PERIS : 1;
			BOOL FERIS : 1;
			BOOL RTRIS : 1;
			BOOL TXRIS : 1;
			BOOL RXRIS : 1;
			BOOL DSRRMIS : 1;
			BOOL DCDRMIS : 1;
			BOOL CTSRMIS : 1;
			BOOL RIRMIS : 1;
		};
	};
}__attribute__((__packed__)) UARTRawInterrupt;

typedef struct UARTMaskedInterrupt
{
	union
	{
		UINT32 Raw;
		struct
		{
			UINT32 Invalid1 : 21;
			BOOL OEMIS : 1;
			BOOL BEMIS : 1;
			BOOL PEMIS : 1;
			BOOL FEMIS : 1;
			BOOL RTMIS : 1;
			BOOL TXMIS : 1;
			BOOL RXMIS : 1;
			BOOL DSMMMIS : 1;
			BOOL DCDMMIS : 1;
			BOOL CTSMMIS : 1;
			BOOL RIMMIS : 1;
		};
	};
}__attribute__((__packed__)) UARTMaskedInterrupt;

typedef struct UARTInterruptClear
{
	union
	{
		UINT32 Raw;
		struct
		{
			UINT32 Invalid1 : 21;
			BOOL OEIC : 1;
			BOOL BEIC : 1;
			BOOL PEIC : 1;
			BOOL FEIC : 1;
			BOOL RTIC : 1;
			BOOL TXIC : 1;
			BOOL RXIC : 1;
			BOOL DSRMIC : 1;
			BOOL DCDMIC : 1;
			BOOL CTSMIC : 1;
			BOOL RIMIC : 1;
		};
	};
}__attribute__((__packed__)) UARTInterruptClear;

typedef struct UARTDMAControl
{
	union
	{
		UINT32 Raw;
		struct
		{
			UINT32 Invalid1 : 29;
			BOOL DMAONERR : 1;
			BOOL TXDMAE : 1;
			BOOL RXDMAE : 1;
		};
	};
}__attribute__((__packed__)) UARTDMAControl;

typedef struct UARTTestControl
{
	union
	{
		UINT32 Raw;
		struct
		{
			UINT32 Invalid1 : 30;
			BOOL ITCR1 : 1;
			BOOL ITCR0 : 1;
		};
	};
}__attribute__((__packed__)) UARTTestControl;

typedef struct UARTITIP
{
	union
	{
		UINT32 Raw;
		struct
		{
			UINT32 Invalid1 : 30;
			BOOL ITIP3 : 1;
			UINT8 Invalid2 : 2;
			BOOL ITIP0 : 1;
		};
	};
}__attribute__((__packed__)) UARTITIP;

typedef struct UARTITOP
{
	union
	{
		UINT32 Raw;
		struct
		{
			UINT32 Invalid1 : 24;
			BOOL ITOP11 : 1;
			BOOL ITOP10 : 1;
			BOOL ITOP9 : 1;
			BOOL ITOP8 : 1;
			BOOL ITOP7 : 1;
			BOOL ITOP6 : 1;
			BOOL ITOP5 : 1;
			BOOL ITOP4 : 1;
			BOOL ITOP3 : 1;
			UINT8 Invalid2 : 2;
			BOOL ITOP0 : 1;
		};
	};
}__attribute__((__packed__)) UARTITOP;

typedef struct UARTDR
{
	union
	{
		UINT32 Raw;
		struct
		{
			UINT32 Invalid1 : 21;
			UINT16 TDR100 : 11;
		};
	};
}__attribute__((__packed__)) UARTTDR;

void BCM_InitUART(VOID);
void BCM2711_WriteUART(const char *Msg);

#endif