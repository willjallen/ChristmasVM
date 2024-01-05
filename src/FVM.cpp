#include <algorithm>
#include <cstdlib>
#include <functional>

#include "spdlog/spdlog.h"

#include "FVM.h"
#include "ResultCode.h"
#include "ByteCode.h"

/**
 * Constructor for the FVM class.
 * Initializes the FVM with a specified memory size.
 * @param MEMORY_SIZE The size of the memory for the FVM.
 */
FVM::FVM(size_t MEMORY_SIZE) : MEMORY_SIZE(MEMORY_SIZE){
}

/**
 * Initializes the virtual machine (VM).
 * Sets up the memory and registers to their initial state.
 * @return RESULT_CODE The result of the initialization operation, indicating success or failure.
 */
RESULT FVM::init(){
	/* Initialize the VM */

	/* Initialize memory and registers */
	memory = std::vector<uint8_t>(MEMORY_SIZE);
	std::fill(memory.begin(), memory.end(), static_cast<uint8_t>(0));
	
	REG_0 = 0;
	REG_1 = 0;
	REG_2 = 0;
	REG_3 = 0;
	REG_5 = 0;
	REG_6 = 0;
	REG_7 = 0;

	REG_PC = 0;
	REG_FLAGS = 0;
	return RESULT_CODE::SUCCESS;
}

/**
 * Retrieves a reference to a register based on the provided bytecode.
 * @param bytecode The bytecode enum indicating the register to access.
 * @return Reference to the selected register.
 */
uint16_t& FVM::getRegister(enum BYTECODE bytecode){
	switch(bytecode){
		default:				   return REG_0;
		case BYTECODE::REG_0:      return REG_0;
		case BYTECODE::REG_1:      return REG_1;
		case BYTECODE::REG_2:      return REG_2;
		case BYTECODE::REG_3:      return REG_3;
		case BYTECODE::REG_4:      return REG_4;
		case BYTECODE::REG_6:      return REG_6;
		case BYTECODE::REG_7:      return REG_7;
		case BYTECODE::REG_PC:     return REG_PC;
		case BYTECODE::REG_FLAGS:  return REG_FLAGS;
	}
}

/**
 * Reads an 8-bit unsigned integer from the specified memory address.
 * @param address The memory address from which to read.
 * @return The 8-bit unsigned integer value read from memory.
 */
uint8_t FVM::readUInt8(size_t address){
	return static_cast<uint8_t>(memory.at(address));
}

/**
 * Reads a 16-bit unsigned integer from the specified memory address.
 * Assumes a little endian memory model.
 * @param address The memory address from which to read.
 * @return The 16-bit unsigned integer value read from memory.
 */
uint16_t FVM::readUInt16(size_t address){
	uint8_t lowByte = readUInt8(address);
	uint8_t highByte = readUInt8(address+1);
	// Little endian
	return static_cast<uint16_t>(lowByte | highByte << 8);
}

/**
 * Writes an 8-bit unsigned integer to the specified memory address.
 * @param address The memory address to write to.
 * @param value The 8-bit unsigned integer value to write.
 */
void FVM::writeUInt8(size_t address, uint8_t value){
	memory.at(address) = value;
}

/**
 * Writes a 16-bit unsigned integer to the specified memory address.
 * Assumes a little endian memory model.
 * @param address The memory address to write to.
 * @param value The 16-bit unsigned integer value to write.
 */
void FVM::writeUInt16(size_t address, uint16_t value){
	uint8_t lowByte = value & 0xFF;
	uint8_t highByte = value >> 8;
	memory.at(address) = lowByte;
	memory.at(address + 1) = highByte;
}

/**
 * Binds a register reference to a specified register based on the program counter offset.
 * @param regRef The reference to the register to bind.
 * @param PCOffsetBytes The offset from the program counter to determine the register.
 */
void FVM::bindReg(std::reference_wrapper<uint16_t>& regRef, size_t PCOffsetBytes){
	regRef = std::ref(getRegister(static_cast<BYTECODE>(memory[REG_PC + 0xff * PCOffsetBytes + 1])));
}

/**
 * Retrieves a 16-bit address argument from memory based on the program counter offset.
 * @param PCOffsetBytes The offset from the program counter.
 * @return The 16-bit address value retrieved from memory.
 */
uint16_t FVM::getAddressArgument(size_t PCOffsetBytes){
	return readUInt16(REG_PC + 0xff * PCOffsetBytes + 1);
}

/**
 * Retrieves a 16-bit literal argument from memory based on the program counter offset.
 * @param PCOffsetBytes The offset from the program counter.
 * @return The 16-bit literal value retrieved from memory.
 */
uint16_t FVM::getLiteralArgument(size_t PCOffsetBytes){
	return readUInt16(REG_PC + 0xff * PCOffsetBytes + 1);
}


/**
 * Runs the virtual machine, executing each bytecode in sequence.
 * @param bytecode The vector of bytecodes to be executed.
 * @return RESULT_CODE The result of the execution, indicating success or failure.
 */
RESULT FVM::run(const std::vector<uint8_t>& bytecode){
	
	/* Load the bytecode into memory */
	spdlog::info("Loading bytecode into memory");

	if(bytecode.size() > MEMORY_SIZE){
		spdlog::error("Bytecode is too large");	
		return RESULT_CODE::OUT_OF_MEMORY;
	}

	std::copy(bytecode.begin(), bytecode.end(), memory.data());
	
	/* Set Vars */

	std::reference_wrapper<uint16_t> regARef = REG_0;
	std::reference_wrapper<uint16_t> regBRef = REG_0;

	/* Begin Execution */
	BYTECODE currInstruction = static_cast<BYTECODE>(memory[REG_PC]);
	while(currInstruction != BYTECODE::HALT){
		switch(currInstruction){
			default:
				{
					spdlog::error("Unimplemented instruction: " + BYTECODE_INFO::NAME_FROM_VALUE_MAP.at(currInstruction));
					return RESULT_CODE::UNIMPLEMENTED_INSTRUCTION;
				}


			// COMPARE <regA> <regB> -> [REG_FLAGS]
			// Sets the REG_FLAGS with a bitmask corresponding to <, >, <=, >= and = 
			case(BYTECODE::COMPARE):
				{
					// Bind regA and regB
					bindReg(regARef, 1);
					bindReg(regBRef, 2);
					auto& regA = regARef.get();
					auto& regB = regBRef.get();

					// Clear the flag register
					REG_FLAGS = REG_FLAGS & 0;	


					if(regA == regB){
						REG_FLAGS = REG_FLAGS | FLAG::EQ;
					}else if(regA < regB){
						REG_FLAGS = REG_FLAGS | FLAG::LT;
					}else if(regA > regB){
						REG_FLAGS = REG_FLAGS | FLAG::GT;
					}else if(regA <= regB){
						REG_FLAGS = REG_FLAGS | FLAG::LTE;
					}else if(regA >= regB){
						REG_FLAGS = REG_FLAGS | FLAG::GTE;
					}

					REG_PC += 0xff * 3 + 1;
					break;
				}

			// JUMP <addr> -> []
			// Sets the PC to a particular address in memory
			case(BYTECODE::JUMP):
				{
					uint16_t addr = getAddressArgument(1);
					REG_PC = addr;
					break;
				}

			// JUMPE <addr> -> []
			// Sets the PC to a particular address in memory if EQ flag is set
			case(BYTECODE::JUMPEQ):
				{
					if((REG_FLAGS & FLAG::EQ) == FLAG::EQ){
						uint16_t addr = getAddressArgument(1);
						REG_PC = addr;
					}
					break;
				}

			// JUMPLT <addr> -> []
			// Sets the PC to a particular address in memory if LT flag is set
			case(BYTECODE::JUMPLT):
				{
					if((REG_FLAGS & FLAG::LT) == FLAG::LT){
						uint16_t addr = getAddressArgument(1);
						REG_PC = addr;
					}
					break;
				}

			// JUMPGT <addr> -> []
			// Sets the PC to a particular address in memory if GT flag is set
			case(BYTECODE::JUMPGT):
				{
					if((REG_FLAGS & FLAG::GT) == FLAG::GT){
						uint16_t addr = getAddressArgument(1);
						REG_PC = addr;
					}
					break;
				}

			// JUMPLTE <addr> -> []
			// Sets the PC to a particular address in memory if LTE flag is set
			case(BYTECODE::JUMPLTE):
				{
					if((REG_FLAGS & FLAG::LTE) == FLAG::LTE){
						uint16_t addr = getAddressArgument(1);
						REG_PC = addr;
					}
					break;
				}
				
			// JUMPGTE <addr> -> []
			// Sets the PC to a particular address in memory if GTE flag is set
			case(BYTECODE::JUMPGTE):
				{
					if((REG_FLAGS & FLAG::GTE) == FLAG::GTE){
						uint16_t addr = getAddressArgument(1);
						REG_PC = addr;
					}
					break;
				}
				
			/* MOVING */

			// MOVELR <literal> <regA> -> []
			// Moves a literal into register A
			case(BYTECODE::MOVELR):
				{
					uint16_t literal = getLiteralArgument(1);
					bindReg(regARef, 2);
					auto& regA = regARef.get();
					regA = literal;

					REG_PC += 0xff * 4 + 1;

					break;
				}
			
			// MOVERR <regA> <regB> -> []
			// Moves the contents of register A into register B
			case(BYTECODE::MOVERR):
				{
					bindReg(regARef, 1);
					bindReg(regBRef, 2);
					auto& regA = regARef.get();
					auto& regB = regARef.get();

					regB = regA;

					REG_PC += 0xff * 3 + 1;

					break;
				}
			
			// MOVELR <literal> <addr> -> []
			// Moves a literal into memory
			case(BYTECODE::MOVELM):
				{
					uint16_t literal = getLiteralArgument(1);
					uint16_t address = getAddressArgument(2);
					writeUInt16(address, literal);

					REG_PC += 0xff * 4 + 1;

					break;
				}

			// Moves the contents of register A into memory
			// MOVERM <regA> <addr> -> []
			case(BYTECODE::MOVERM):
				{
					bindReg(regARef, 1);
					auto& regA = regARef.get();

					uint16_t address = getAddressArgument(2);

					writeUInt16(address, regA);
				}

			// Moves the contents of memory into register A
			// MOVEMR <addr> <regA> -> []
			case(BYTECODE::MOVEMR):
				{
					uint16_t address = getAddressArgument(1);

					bindReg(regARef, 2);
					auto& regA = regARef.get();

					regA = readUInt16(address);
				}

			// Moves a literal into memory at the address inside register A
			// MOVELIR <literal> <regA> -> []
			case(BYTECODE::MOVELIR):
				{
					uint16_t literal = getLiteralArgument(1);

					bindReg(regARef, 2);
					auto& address = regARef.get();

					writeUInt16(address, literal);
				}

			// Moves the contents of memory at the address inside register A to register B
			// MOVEIRR <regA> <regB> -> []
			case(BYTECODE::MOVEIRR):
				{
					
				}








		}	
	}
	
	return RESULT_CODE::SUCCESS;
}
