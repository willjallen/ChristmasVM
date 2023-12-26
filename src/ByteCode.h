#ifndef BYTECODE_H
#define BYTECODE_H

#include <stdint.h>


enum class BYTECODE : uint8_t {

/* INSTRUCTIONS */
	
	// HALT -> []
    // Stops the execution
    HALT = 0x00,

    /* Binary Ops */
	// COMPARE <regA> <regB> -> [REG_FLAGS]
	// Sets the REG_FLAGS with a bitmask corresponding to <, >, <=, >= and = 
	COMPARE,
	
	// JUMP <addr> -> []
	// Sets the PC to a particular address in memory
	JUMP,

	// JUMPE <addr> -> []
	// Sets the PC to a particular address in memory if EQ flag is set
	JUMPE,

	// JUMPLT <addr> -> []
	// Sets the PC to a particular address in memory if LT flag is set
	JUMPLT,

	// JUMPGT <addr> -> []
	// Sets the PC to a particular address in memory if GT flag is set
	JUMPGT,

	// JUMPLTE <addr> -> []
	// Sets the PC to a particular address in memory if LTE flag is set
	JUMPLTE,

	// JUMPGTE <addr> -> []
	// Sets the PC to a particular address in memory if GTE flag is set
	JUMPGTE,

	/* MOVING */


    // MOVERR <regA> <regB> -> []
    // Moves the contents of register A into register B
    MOVRR,  

    // MOVERM <regA> <addr> -> []
    // Moves the contents of register A into memory
    MOVRM,

    // MOVEMR <addr> <regA> -> []
    // Moves the contents of memory into register A
    MOVEMR,

    // MMOVERR <regA> <regB> -> []
    // Moves the contents of memory at the address inside register A to register B 
    IMOVRR,  

    // MMOVERM <regA> <addr> -> []
    // Moves the contents of memory at the address inside register A to memory
    IMOVRM,

    // MMOVEMR <addr> <regA> -> []
    // Moves contents of memory at the address inside memory to register A
    IMOVEMR,

	/* ARITHMETIC */

    // ADD <regA> <regB> -> [regB]
    // RegisterA + RegisterB -> RegisterB
    ADD,
    
    // SUBTRACT <regA> <regB> -> [regB]
    // RegisterA - RegisterB -> RegisterB
    SUBTRACT,

    // MULTIPLY <regA> <regB> -> [regB]
    // RegisterA * RegisterB -> RegisterB
    MULTIPLY,

    // DIVIDE <regA> <regB> -> [regB]
    // RegisterA / RegisterB -> RegisterB
    DIVIDE,

    // INCREMENT <regA> -> [regA]
    // RegisterA + 1 -> RegisterA
    INCREMENT,

    // DECREMENT <regA> -> [regA]
    // RegisterA - 1 -> RegisterA
    DECREMENT,

	/* BITWISE */

    // AND <regA> <regB> -> [regB]
    // RegisterA AND RegisterB -> RegisterB
	AND,

    // OR <regA> <regB> -> [regB]
    // RegisterA OR RegisterB -> RegisterB
	OR,

    // XOR <regA> <regB> -> [regB]
    // RegisterA XOR RegisterB -> RegisterB
	XOR,
   
   	// NOT <regA> -> [regA]
    // RegisterA -> !RegisterA
    NOT,

    // SHIFTLEFT <regA> <literal> -> [regA]
    // RegisterA << literal -> RegisterA
	SHIFTLEFT,

    // SHIFTRIGHT <regA> <literal> -> [regA]
    // RegisterA >> literal  -> RegisterA
	SHIFTRIGHT,

	/* REGISTERS */	

	REG_0,
	REG_1,
	REG_2,
	REG_3,
	REG_4,
	REG_5,
	REG_6,
	REG_7,
	REG_PC,
	REG_FLAGS

};

#endif
