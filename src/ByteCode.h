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

    // MOVELR <literal> <regB> -> []
    // Moves a literal into register B
    MOVLR,  

    // MOVERR <regA> <regB> -> []
    // Moves the contents of register A into register B
    MOVRR,  

    // MOVELR <literal> <addr> -> []
    // Moves a literal into memory
    MOVLM,  

    // MOVERM <regA> <addr> -> []
    // Moves the contents of register A into memory
    MOVRM,

    // MOVEMR <addr> <regA> -> []
    // Moves the contents of memory into register A
    MOVEMR,
	
	/* INDIRECT MOVING */
    
	// MMOVERR <regA> <regB> -> []
    // Moves the contents of memory at the address inside register A to register B 
    MOVLIR,  

    // MMOVERR <regA> <regB> -> []
    // Moves the contents of memory at the address inside register A to register B 
    MOVIRR,  

    // MMOVERM <regA> <addr> -> []
    // Moves the contents of memory at the address inside register A to memory
    MOVIRM,

    // MMOVEMR <addr> <regA> -> []
    // Moves contents of memory at the address inside memory to register A
    MOVEIMR,

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
		LITERAL,
		ADDRESS,
	};

	struct OBJECT {
		OBJECT(BYTECODE bytecode,
				std::string name,
				bool isInstruction,
				bool isRegister,
				std::vector<ARGUMENT_TYPE> args) : 
			bytecode(bytecode),
			isInstruction(isInstruction),
			isRegister(isRegister),
			args(args)
			{}
		BYTECODE bytecode;
		bool isInstruction;
		bool isRegister;
		std::vector<ARGUMENT_TYPE> args;
	};
	
const std::unordered_map<std::string, OBJECT> OBJECT_MAP = {
        {"HALT", {BYTECODE::HALT, "HALT", true, false, {}}},
        {"COMPARE", {BYTECODE::COMPARE, "COMPARE", true, false, {ARGUMENT_TYPE::REGISTER, ARGUMENT_TYPE::REGISTER}}},
        {"JUMP", {BYTECODE::JUMP, "JUMP", true, false, {ARGUMENT_TYPE::ADDRESS}}},
        {"JUMPE", {BYTECODE::JUMPE, "JUMPE", true, false, {ARGUMENT_TYPE::ADDRESS}}},
        {"JUMPLT", {BYTECODE::JUMPLT, "JUMPLT", true, false, {ARGUMENT_TYPE::ADDRESS}}},
        {"JUMPGT", {BYTECODE::JUMPGT, "JUMPGT", true, false, {ARGUMENT_TYPE::ADDRESS}}},
        {"JUMPLTE", {BYTECODE::JUMPLTE, "JUMPLTE", true, false, {ARGUMENT_TYPE::ADDRESS}}},
        {"JUMPGTE", {BYTECODE::JUMPGTE, "JUMPGTE", true, false, {ARGUMENT_TYPE::ADDRESS}}},
		{"MOVRR", {BYTECODE::MOVRR, "MOVRR", true, false, {ARGUMENT_TYPE::REGISTER, ARGUMENT_TYPE::REGISTER}}},
        {"MOVRM", {BYTECODE::MOVRM, "MOVRM", true, false, {ARGUMENT_TYPE::REGISTER, ARGUMENT_TYPE::ADDRESS}}},
        {"MOVEMR", {BYTECODE::MOVEMR, "MOVEMR", true, false, {ARGUMENT_TYPE::ADDRESS, ARGUMENT_TYPE::REGISTER}}},
		{"MOVLR", {BYTECODE::MOVLR, "MOVLR", true, false, {ARGUMENT_TYPE::LITERAL, ARGUMENT_TYPE::REGISTER}}},
        {"MOVLM", {BYTECODE::MOVLM, "MOVLM", true, false, {ARGUMENT_TYPE::LITERAL, ARGUMENT_TYPE::ADDRESS}}},
        {"MOVLIR", {BYTECODE::MOVLIR, "MOVLIR", true, false, {ARGUMENT_TYPE::REGISTER, ARGUMENT_TYPE::REGISTER}}},
        {"MOVIRR", {BYTECODE::MOVIRR, "MOVIRR", true, false, {ARGUMENT_TYPE::REGISTER, ARGUMENT_TYPE::REGISTER}}},
        {"MOVIRM", {BYTECODE::MOVIRM, "MOVIRM", true, false, {ARGUMENT_TYPE::REGISTER, ARGUMENT_TYPE::ADDRESS}}},
        {"MOVEIMR", {BYTECODE::MOVEIMR, "MOVEIMR", true, false, {ARGUMENT_TYPE::ADDRESS, ARGUMENT_TYPE::REGISTER}}},
        {"ADD", {BYTECODE::ADD, "ADD", true, false, {ARGUMENT_TYPE::REGISTER, ARGUMENT_TYPE::REGISTER}}},
        {"SUBTRACT", {BYTECODE::SUBTRACT, "SUBTRACT", true, false, {ARGUMENT_TYPE::REGISTER, ARGUMENT_TYPE::REGISTER}}},
        {"MULTIPLY", {BYTECODE::MULTIPLY, "MULTIPLY", true, false, {ARGUMENT_TYPE::REGISTER, ARGUMENT_TYPE::REGISTER}}},
        {"DIVIDE", {BYTECODE::DIVIDE, "DIVIDE", true, false, {ARGUMENT_TYPE::REGISTER, ARGUMENT_TYPE::REGISTER}}},
        {"INCREMENT", {BYTECODE::INCREMENT, "INCREMENT", true, false, {ARGUMENT_TYPE::REGISTER}}},
        {"DECREMENT", {BYTECODE::DECREMENT, "DECREMENT", true, false, {ARGUMENT_TYPE::REGISTER}}},
        {"AND", {BYTECODE::AND, "AND", true, false, {ARGUMENT_TYPE::REGISTER, ARGUMENT_TYPE::REGISTER}}},
        {"OR", {BYTECODE::OR, "OR", true, false, {ARGUMENT_TYPE::REGISTER, ARGUMENT_TYPE::REGISTER}}},
        {"XOR", {BYTECODE::XOR, "XOR", true, false, {ARGUMENT_TYPE::REGISTER, ARGUMENT_TYPE::REGISTER}}},
        {"NOT", {BYTECODE::NOT, "NOT", true, false, {ARGUMENT_TYPE::REGISTER}}},
        {"SHIFTLEFT", {BYTECODE::SHIFTLEFT, "SHIFTLEFT", true, false, {ARGUMENT_TYPE::REGISTER, ARGUMENT_TYPE::LITERAL}}},
        {"SHIFTRIGHT", {BYTECODE::SHIFTRIGHT, "SHIFTRIGHT", true, false, {ARGUMENT_TYPE::REGISTER, ARGUMENT_TYPE::LITERAL}}},
        {"REG_0", {BYTECODE::REG_0, "REG_0", false, true, {}}},
        {"REG_1", {BYTECODE::REG_1, "REG_1", false, true, {}}},
        {"REG_2", {BYTECODE::REG_2, "REG_2", false, true, {}}},
        {"REG_3", {BYTECODE::REG_3, "REG_3", false, true, {}}},
        {"REG_4", {BYTECODE::REG_4, "REG_4", false, true, {}}},
        {"REG_5", {BYTECODE::REG_5, "REG_5", false, true, {}}},
        {"REG_6", {BYTECODE::REG_6, "REG_6", false, true, {}}},
        {"REG_7", {BYTECODE::REG_7, "REG_7", false, true, {}}},
        {"REG_PC", {BYTECODE::REG_PC, "REG_PC", false, true, {}}},
        {"REG_FLAGS", {BYTECODE::REG_FLAGS, "REG_FLAGS", false, true, {}}}
    };
}

#endif
