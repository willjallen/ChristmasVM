#ifndef BYTECODE_H
#define BYTECODE_H
#include <stdint.h>
#include <string>
#include <unordered_map>
enum class BYTECODE : uint8_t
{

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

    // JUMPEQ <addr> -> []
    // Sets the PC to a particular address in memory if EQ flag is set
    JUMPEQ,

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

    // MOVELR <literal> <regA> -> []
    // Moves a literal into register A
    MOVELR,

    // MOVERR <regA> <regB> -> []
    // Moves the contents of register A into register B
    MOVERR,

    // MOVELR <literal> <addr> -> []
    // Moves a literal into memory
    MOVELM,

    // MOVERM <regA> <addr> -> []
    // Moves the contents of register A into memory
    MOVERM,

    // MOVEMR <addr> <regA> -> []
    // Moves the contents of memory into register A
    MOVEEMR,

    /* INDIRECT MOVING */

    // MOVERR <regA> <regB> -> []
    // Moves the contents of memory at the address inside register A to register B
    MOVELIR,

    // MOVERR <regA> <regB> -> []
    // Moves the contents of memory at the address inside register A to register B
    MOVEIRR,

    // MOVERM <regA> <addr> -> []
    // Moves the contents of memory at the address inside register A to memory
    MOVEIRM,

    // MOVEMR <addr> <regA> -> []
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

namespace BYTECODE_INFO
{

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
                                                           args(args)
        {
        }
        BYTECODE bytecode;
        std::vector<ARGUMENT_TYPE> args;
    };

    const std::unordered_map<std::string, BYTECODE_OBJECT> OBJECT_FROM_NAME_MAP = {
        {"HALT", {BYTECODE::HALT, "HALT", true, false, {}}},
        {"COMPARE", {BYTECODE::COMPARE, "COMPARE", true, false, {ARGUMENT_TYPE::REGISTER, ARGUMENT_TYPE::REGISTER}}},
        {"JUMP", {BYTECODE::JUMP, "JUMP", true, false, {ARGUMENT_TYPE::ADDRESS}}},
        {"JUMPEQ", {BYTECODE::JUMPEQ, "JUMPEQ", true, false, {ARGUMENT_TYPE::ADDRESS}}},
        {"JUMPLT", {BYTECODE::JUMPLT, "JUMPLT", true, false, {ARGUMENT_TYPE::ADDRESS}}},
        {"JUMPGT", {BYTECODE::JUMPGT, "JUMPGT", true, false, {ARGUMENT_TYPE::ADDRESS}}},
        {"JUMPLTE", {BYTECODE::JUMPLTE, "JUMPLTE", true, false, {ARGUMENT_TYPE::ADDRESS}}},
        {"JUMPGTE", {BYTECODE::JUMPGTE, "JUMPGTE", true, false, {ARGUMENT_TYPE::ADDRESS}}},
        {"MOVERR", {BYTECODE::MOVERR, "MOVERR", true, false, {ARGUMENT_TYPE::REGISTER, ARGUMENT_TYPE::REGISTER}}},
        {"MOVERM", {BYTECODE::MOVERM, "MOVERM", true, false, {ARGUMENT_TYPE::REGISTER, ARGUMENT_TYPE::ADDRESS}}},
        {"MOVEEMR", {BYTECODE::MOVEEMR, "MOVEEMR", true, false, {ARGUMENT_TYPE::ADDRESS, ARGUMENT_TYPE::REGISTER}}},
        {"MOVELR", {BYTECODE::MOVELR, "MOVELR", true, false, {ARGUMENT_TYPE::LITERAL, ARGUMENT_TYPE::REGISTER}}},
        {"MOVELM", {BYTECODE::MOVELM, "MOVELM", true, false, {ARGUMENT_TYPE::LITERAL, ARGUMENT_TYPE::ADDRESS}}},
        {"MOVELIR", {BYTECODE::MOVELIR, "MOVELIR", true, false, {ARGUMENT_TYPE::REGISTER, ARGUMENT_TYPE::REGISTER}}},
        {"MOVEIRR", {BYTECODE::MOVEIRR, "MOVEIRR", true, false, {ARGUMENT_TYPE::REGISTER, ARGUMENT_TYPE::REGISTER}}},
        {"MOVEIRM", {BYTECODE::MOVEIRM, "MOVEIRM", true, false, {ARGUMENT_TYPE::REGISTER, ARGUMENT_TYPE::ADDRESS}}},
        {"MOVEIMR", {BYTECODE::MOVEIMR, "MOVEEIMR", true, false, {ARGUMENT_TYPE::ADDRESS, ARGUMENT_TYPE::REGISTER}}},
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
        {"REG_FLAGS", {BYTECODE::REG_FLAGS, "REG_FLAGS", false, true, {}}}};

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
        {BYTECODE::REG_FLAGS, "REG_FLAGS"}};
}

#endif
