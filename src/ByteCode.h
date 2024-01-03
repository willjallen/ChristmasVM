
#ifndef BYTECODE_H
#define BYTECODE_H


#include <stdint.h>
#include <string>
#include <unordered_map>


enum class BYTECODE : uint8_t {

	// Stops the execution
	// HALT -> []
	HALT = 0x00,

	// Sets the REG_FLAGS with a bitmask corresponding to <, >, <=, >= and =
	// COMPARE <regA> <regB> -> [REG_FLAGS]
	COMPARE,

	// Sets the PC to a particular address in memory
	// JUMP <addr> -> []
	JUMP,

	// Sets the PC to a particular address in memory if EQ flag is set
	// JUMPEQ <addr> -> []
	JUMPEQ,

	// Sets the PC to a particular address in memory if LT flag is set
	// JUMPLT <addr> -> []
	JUMPLT,

	// Sets the PC to a particular address in memory if GT flag is set
	// JUMPGT <addr> -> []
	JUMPGT,

	// Sets the PC to a particular address in memory if LTE flag is set
	// JUMPLTE <addr> -> []
	JUMPLTE,

	// Sets the PC to a particular address in memory if GTE flag is set
	// JUMPGTE <addr> -> []
	JUMPGTE,

	// Moves a literal into register A
	// MOVELR <literal> <regA> -> []
	MOVELR,

	// Moves the contents of register A into register B
	// MOVERR <regA> <regB> -> []
	MOVERR,

	// Moves a literal into memory
	// MOVELM <literal> <addr> -> []
	MOVELM,

	// Moves the contents of register A into memory
	// MOVERM <regA> <addr> -> []
	MOVERM,

	// Moves the contents of memory into register A
	// MOVEEMR <addr> <regA> -> []
	MOVEEMR,

	// Moves the contents of memory at the address inside register A to register B
	// MOVELIR <regA> <regB> -> []
	MOVELIR,

	// Moves the contents of memory at the address inside register A to register B
	// MOVEIRR <regA> <regB> -> []
	MOVEIRR,

	// Moves the contents of memory at the address inside register A to memory
	// MOVEIRM <regA> <addr> -> []
	MOVEIRM,

	// Moves contents of memory at the address inside memory to register A
	// MOVEIMR <addr> <regA> -> []
	MOVEIMR,

	// RegisterA + RegisterB -> RegisterB
	// ADD <regA> <regB> -> [regB]
	ADD,

	// RegisterA - RegisterB -> RegisterB
	// SUBTRACT <regA> <regB> -> [regB]
	SUBTRACT,

	// RegisterA * RegisterB -> RegisterB
	// MULTIPLY <regA> <regB> -> [regB]
	MULTIPLY,

	// RegisterA / RegisterB -> RegisterB
	// DIVIDE <regA> <regB> -> [regB]
	DIVIDE,

	// RegisterA + 1 -> RegisterA
	// INCREMENT <regA> -> [regA]
	INCREMENT,

	// RegisterA - 1 -> RegisterA
	// DECREMENT <regA> -> [regA]
	DECREMENT,

	// RegisterA AND RegisterB -> RegisterB
	// AND <regA> <regB> -> [regB]
	AND,

	// RegisterA OR RegisterB -> RegisterB
	// OR <regA> <regB> -> [regB]
	OR,

	// RegisterA XOR RegisterB -> RegisterB
	// XOR <regA> <regB> -> [regB]
	XOR,

	// RegisterA -> !RegisterA
	// NOT <regA> -> [regA]
	NOT,

	// RegisterA << literal -> RegisterA
	// SHIFTLEFT <regA> <literal> -> [regA]
	SHIFTLEFT,

	// RegisterA >> literal  -> RegisterA
	// SHIFTRIGHT <regA> <literal> -> [regA]
	SHIFTRIGHT,


	REG_0,


	REG_1,


	REG_2,


	REG_3,


	REG_4,


	REG_5,


	REG_6,


	REG_7,


	REG_PC,


	REG_FLAGS,

};

namespace BYTECODE_INFO {

	enum class ARGUMENT_TYPE : uint8_t
	{
		REGISTER,
		LITERAL,
		ADDRESS,
	};



	struct BYTECODE_OBJECT
	{
		BYTECODE_OBJECT(BYTECODE bytecode,
						std::string name,
						std::vector<ARGUMENT_TYPE> args) : bytecode(bytecode),
														   name(name),
														   args(args)
		{
		}
		BYTECODE bytecode;
		std::string name;
		std::vector<ARGUMENT_TYPE> args;
	};


	const std::unordered_map<std::string, BYTECODE_OBJECT> OBJECT_FROM_NAME_MAP = {
		{"HALT", {BYTECODE::HALT, "HALT", {}}},
		{"COMPARE", {BYTECODE::COMPARE, "COMPARE", {ARGUMENT_TYPE::REGISTER, ARGUMENT_TYPE::REGISTER}}},
		{"JUMP", {BYTECODE::JUMP, "JUMP", {ARGUMENT_TYPE::ADDRESS}}},
		{"JUMPEQ", {BYTECODE::JUMPEQ, "JUMPEQ", {ARGUMENT_TYPE::ADDRESS}}},
		{"JUMPLT", {BYTECODE::JUMPLT, "JUMPLT", {ARGUMENT_TYPE::ADDRESS}}},
		{"JUMPGT", {BYTECODE::JUMPGT, "JUMPGT", {ARGUMENT_TYPE::ADDRESS}}},
		{"JUMPLTE", {BYTECODE::JUMPLTE, "JUMPLTE", {ARGUMENT_TYPE::ADDRESS}}},
		{"JUMPGTE", {BYTECODE::JUMPGTE, "JUMPGTE", {ARGUMENT_TYPE::ADDRESS}}},
		{"MOVELR", {BYTECODE::MOVELR, "MOVELR", {ARGUMENT_TYPE::LITERAL, ARGUMENT_TYPE::REGISTER}}},
		{"MOVERR", {BYTECODE::MOVERR, "MOVERR", {ARGUMENT_TYPE::REGISTER, ARGUMENT_TYPE::REGISTER}}},
		{"MOVELM", {BYTECODE::MOVELM, "MOVELM", {ARGUMENT_TYPE::LITERAL, ARGUMENT_TYPE::ADDRESS}}},
		{"MOVERM", {BYTECODE::MOVERM, "MOVERM", {ARGUMENT_TYPE::REGISTER, ARGUMENT_TYPE::ADDRESS}}},
		{"MOVEEMR", {BYTECODE::MOVEEMR, "MOVEEMR", {ARGUMENT_TYPE::ADDRESS, ARGUMENT_TYPE::REGISTER}}},
		{"MOVELIR", {BYTECODE::MOVELIR, "MOVELIR", {ARGUMENT_TYPE::REGISTER, ARGUMENT_TYPE::REGISTER}}},
		{"MOVEIRR", {BYTECODE::MOVEIRR, "MOVEIRR", {ARGUMENT_TYPE::REGISTER, ARGUMENT_TYPE::REGISTER}}},
		{"MOVEIRM", {BYTECODE::MOVEIRM, "MOVEIRM", {ARGUMENT_TYPE::REGISTER, ARGUMENT_TYPE::ADDRESS}}},
		{"MOVEIMR", {BYTECODE::MOVEIMR, "MOVEIMR", {ARGUMENT_TYPE::ADDRESS, ARGUMENT_TYPE::REGISTER}}},
		{"ADD", {BYTECODE::ADD, "ADD", {ARGUMENT_TYPE::REGISTER, ARGUMENT_TYPE::REGISTER}}},
		{"SUBTRACT", {BYTECODE::SUBTRACT, "SUBTRACT", {ARGUMENT_TYPE::REGISTER, ARGUMENT_TYPE::REGISTER}}},
		{"MULTIPLY", {BYTECODE::MULTIPLY, "MULTIPLY", {ARGUMENT_TYPE::REGISTER, ARGUMENT_TYPE::REGISTER}}},
		{"DIVIDE", {BYTECODE::DIVIDE, "DIVIDE", {ARGUMENT_TYPE::REGISTER, ARGUMENT_TYPE::REGISTER}}},
		{"INCREMENT", {BYTECODE::INCREMENT, "INCREMENT", {ARGUMENT_TYPE::REGISTER}}},
		{"DECREMENT", {BYTECODE::DECREMENT, "DECREMENT", {ARGUMENT_TYPE::REGISTER}}},
		{"AND", {BYTECODE::AND, "AND", {ARGUMENT_TYPE::REGISTER, ARGUMENT_TYPE::REGISTER}}},
		{"OR", {BYTECODE::OR, "OR", {ARGUMENT_TYPE::REGISTER, ARGUMENT_TYPE::REGISTER}}},
		{"XOR", {BYTECODE::XOR, "XOR", {ARGUMENT_TYPE::REGISTER, ARGUMENT_TYPE::REGISTER}}},
		{"NOT", {BYTECODE::NOT, "NOT", {ARGUMENT_TYPE::REGISTER}}},
		{"SHIFTLEFT", {BYTECODE::SHIFTLEFT, "SHIFTLEFT", {ARGUMENT_TYPE::REGISTER, ARGUMENT_TYPE::LITERAL}}},
		{"SHIFTRIGHT", {BYTECODE::SHIFTRIGHT, "SHIFTRIGHT", {ARGUMENT_TYPE::REGISTER, ARGUMENT_TYPE::LITERAL}}},
		{"REG_0", {BYTECODE::REG_0, "REG_0", {}}},
		{"REG_1", {BYTECODE::REG_1, "REG_1", {}}},
		{"REG_2", {BYTECODE::REG_2, "REG_2", {}}},
		{"REG_3", {BYTECODE::REG_3, "REG_3", {}}},
		{"REG_4", {BYTECODE::REG_4, "REG_4", {}}},
		{"REG_5", {BYTECODE::REG_5, "REG_5", {}}},
		{"REG_6", {BYTECODE::REG_6, "REG_6", {}}},
		{"REG_7", {BYTECODE::REG_7, "REG_7", {}}},
		{"REG_PC", {BYTECODE::REG_PC, "REG_PC", {}}},
		{"REG_FLAGS", {BYTECODE::REG_FLAGS, "REG_FLAGS", {}}},
	};

	const std::unordered_map<BYTECODE, std::string> NAME_FROM_VALUE_MAP = {
		{BYTECODE::HALT, "HALT"},
		{BYTECODE::COMPARE, "COMPARE"},
		{BYTECODE::JUMP, "JUMP"},
		{BYTECODE::JUMPEQ, "JUMPEQ"},
		{BYTECODE::JUMPLT, "JUMPLT"},
		{BYTECODE::JUMPGT, "JUMPGT"},
		{BYTECODE::JUMPLTE, "JUMPLTE"},
		{BYTECODE::JUMPGTE, "JUMPGTE"},
		{BYTECODE::MOVELR, "MOVELR"},
		{BYTECODE::MOVERR, "MOVERR"},
		{BYTECODE::MOVELM, "MOVELM"},
		{BYTECODE::MOVERM, "MOVERM"},
		{BYTECODE::MOVEEMR, "MOVEEMR"},
		{BYTECODE::MOVELIR, "MOVELIR"},
		{BYTECODE::MOVEIRR, "MOVEIRR"},
		{BYTECODE::MOVEIRM, "MOVEIRM"},
		{BYTECODE::MOVEIMR, "MOVEIMR"},
		{BYTECODE::ADD, "ADD"},
		{BYTECODE::SUBTRACT, "SUBTRACT"},
		{BYTECODE::MULTIPLY, "MULTIPLY"},
		{BYTECODE::DIVIDE, "DIVIDE"},
		{BYTECODE::INCREMENT, "INCREMENT"},
		{BYTECODE::DECREMENT, "DECREMENT"},
		{BYTECODE::AND, "AND"},
		{BYTECODE::OR, "OR"},
		{BYTECODE::XOR, "XOR"},
		{BYTECODE::NOT, "NOT"},
		{BYTECODE::SHIFTLEFT, "SHIFTLEFT"},
		{BYTECODE::SHIFTRIGHT, "SHIFTRIGHT"},
		{BYTECODE::REG_0, "REG_0"},
		{BYTECODE::REG_1, "REG_1"},
		{BYTECODE::REG_2, "REG_2"},
		{BYTECODE::REG_3, "REG_3"},
		{BYTECODE::REG_4, "REG_4"},
		{BYTECODE::REG_5, "REG_5"},
		{BYTECODE::REG_6, "REG_6"},
		{BYTECODE::REG_7, "REG_7"},
		{BYTECODE::REG_PC, "REG_PC"},
		{BYTECODE::REG_FLAGS, "REG_FLAGS"},
	};
};
#endif
