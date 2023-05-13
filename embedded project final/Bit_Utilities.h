#ifndef Bit_Utilies
#define Bit_Utilies

#define GET_BIT(reg1,bit)   ((reg1>>bit)&1)		// returns a specified bit 
#define GET_REG(reg)        (reg&0xff)				// returns all data from a register

#define SET(reg,val)        reg = val					// sets a value in a register
#define SET_BIT(reg,val)    reg |= (1<<val)		// sets a specified bit in a register
#define SET_BITS(reg,val)   reg|= val					// sets multiple specified bits in a register
#define CLR(reg,val)        reg &=~val				// clears multiple specified bits in a register
#define CLR_BIT(reg,val)    reg &=~(1<<val)		// clears	a specified bit in a register

#endif