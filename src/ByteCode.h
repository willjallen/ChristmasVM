
/**
 * Bytecode Schema:
 * - No packing, arguments (addr, literals, etc.) follow sequentially in memory
 * INSTRUCTION | arg1 | arg2
 */

enum BYTECODE  {
    // HALT -> []
    // Stops the execution
    HALT = 0x0000,

    /* Binary Ops */

    // MOVERR <regA> <regB> -> []
    // Moves the contents of register A into register B
    MOVRR,  

    // MOVERM <regA> <addr> -> []
    // Moves the contents of register A into memory
    MOVRM,

    // MOVEMR <addr> <regA> -> []
    // Moves the contents of memory into register A
    MOVEMR,

    // IMOVERR <regA> <regB> -> []
    // Moves the contents of memory at the address inside register A to register B 
    IMOVRR,  

    // IMOVERM <regA> <addr> -> []
    // Moves the contents of memory at the address inside register A to memory
    IMOVRM,

    // IMOVEMR <addr> <regA> -> []
    // Moves contents of memory into the memory at the address inside register A
    IMOVEMR,

    // ADD <regA> <regB> -> [regB]
    // Adds the contents of register A and register B then places the result in register B
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

    /* Unary Ops */

    // NOT <regA> -> [regA]
    // RegisterA -> !RegisterA
    NOT,

    // INCREMENT <regA> -> [regA]
    // RegisterA + 1 -> RegisterA
    INCREMENT,

    // DECREMENT <regA> -> [regA]
    // RegisterA - 1 -> RegisterA
    DECREMENT
};
