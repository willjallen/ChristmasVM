#include <algorithm>
#include <cstdlib>
#include <functional>

#include "spdlog/spdlog.h"

#include "CVM.h"
#include "ResultCode.h"
#include "ByteCode.h"

CVM::CVM(size_t MEMORY_SIZE) : MEMORY_SIZE(MEMORY_SIZE){


}

/**
 * Initializes the VM. Sets up memory and registers
 * @returns RESULT_CODE The result of the operation.
 */
RESULT CVM::init(){
	/* Initialize the VM */

	/* Initialize memory and registers */
	memory = std::vector<char>(MEMORY_SIZE);
	std::fill(memory.begin(), memory.end(), 0);
	
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


uint16_t& CVM::getRegister(enum BYTECODE bytecode){
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

uint8_t CVM::readUInt8(size_t address){
	return static_cast<uint8_t>(memory.at(address));
}

uint16_t CVM::readUInt16(size_t address){
	uint8_t lowByte = readUInt8(address);
	uint8_t highByte = readUInt8(address+1);
	// Little endian
	return static_cast<uint16_t>(lowByte | highByte << 8);
}

void CVM::bindReg(std::reference_wrapper<uint16_t>& regRef, size_t PCOffsetBytes){
	regRef = std::ref(getRegister(static_cast<BYTECODE>(memory[REG_PC + 0xff * PCOffsetBytes + 1])));
}

uint16_t CVM::getAddressArgument(size_t PCOffsetBytes){
	return readUInt16(REG_PC + 0xff * PCOffsetBytes + 1);
}

uint16_t CVM::getLiteralArgument(size_t PCOffsetBytes){
	return readUInt16(REG_PC + 0xff * PCOffsetBytes + 1);
}

/*
 * Runs the VM. Executes each bytecode in sequence.
 * @returns RESULT_CODE The result of the operation.
 */
RESULT CVM::run(const std::vector<uint16_t>& bytecode){
	
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
				

			// MOVELR <literal> <regA> -> []
			// Moves a literal into register A
				case(BYTECODE::MOVLR):
					{
						uint16_t literal = getLiteralArgument(1);
						bindReg(regARef, 2);
						auto& regA = regARef.get();
						regA = literal;
						break;
					}
		}	
	}
	
	return RESULT_CODE::SUCCESS;
}
