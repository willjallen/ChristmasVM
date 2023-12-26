#ifndef BYTECODE_H
#define BYTECODE_H

#include <stdint.h>
#include <string>
#include <unordered_map>
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

namespace BYTECODE_INFO {


	enum class ARGUMENT_TYPE : uint8_t {
		REGISTER,
		ADDRESS,
		INDIRECT_ADDRESS
	};

	struct OBJECT {
		BYTECODE_INFO(BYTECODE bytecode,
				bool isInstruction,
				bool isRegister,
				std::vector<ARGUMENT_TYPE> args) : 
			bytecode(bytecode) 
			isInstruction(isInstruction)
			isRegister(isRegister)
			args(args);
		BYTECODE bytecode;
		bool isInstruction;
		bool isRegister;
		std::vector<ARGUMENT_TYPE> args;
	};
	
	// This should be a map to OBJECTs, also idk if this should be in the namespace
	const std::unordered_map<std::string, BYTECODE> STR_MAP = {
		{"HALT", BYTECODE::HALT},
		{"COMPARE", BYTECODE::COMPARE},
		{"JUMP", BYTECODE::JUMP},
		{"JUMPE", BYTECODE::JUMPE},
		{"JUMPLT", BYTECODE::JUMPLT},
		{"JUMPGT", BYTECODE::JUMPGT},
		{"JUMPLTE", BYTECODE::JUMPLTE},
		{"JUMPGTE", BYTECODE::JUMPGTE},
		{"MOVRR", BYTECODE::MOVRR},
		{"MOVRM", BYTECODE::MOVRM},
		{"MOVEMR", BYTECODE::MOVEMR},
		{"IMOVRR", BYTECODE::IMOVRR},
		{"IMOVRM", BYTECODE::IMOVRM},
		{"IMOVEMR", BYTECODE::IMOVEMR},
		{"ADD", BYTECODE::ADD},
		{"SUBTRACT", BYTECODE::SUBTRACT},
		{"MULTIPLY", BYTECODE::MULTIPLY},
		{"DIVIDE", BYTECODE::DIVIDE},
		{"INCREMENT", BYTECODE::INCREMENT},
		{"DECREMENT", BYTECODE::DECREMENT},
		{"AND", BYTECODE::AND},
		{"OR", BYTECODE::OR},
		{"XOR", BYTECODE::XOR},
		{"NOT", BYTECODE::NOT},
		{"SHIFTLEFT", BYTECODE::SHIFTLEFT},
		{"SHIFTRIGHT", BYTECODE::SHIFTRIGHT},
		{"REG_0", BYTECODE::REG_0},
		{"REG_1", BYTECODE::REG_1},
		{"REG_2", BYTECODE::REG_2},
		{"REG_3", BYTECODE::REG_3},
		{"REG_4", BYTECODE::REG_4},
		{"REG_5", BYTECODE::REG_5},
		{"REG_6", BYTECODE::REG_6},
		{"REG_7", BYTECODE::REG_7},
		{"REG_PC", BYTECODE::REG_PC},
		{"REG_FLAGS", BYTECODE::REG_FLAGS}
	};
}

#endif
