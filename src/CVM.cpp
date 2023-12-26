#include <algorithm>
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

uint8_t readUInt8(std::vector<char>& memory, size_t address){
	return *reinterpret_cast<uint8_t*>(memory.at(address));
}

void CVM::bindReg(std::reference_wrapper<uint16_t>& regRef, size_t PCOffsetBytes){
	regRef = std::ref(getRegister(static_cast<BYTECODE>(memory[REG_PC + 0xff * PCOffsetBytes + 1])));
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
		return RESULT_CODE::OUT_OF_MEMORY_ERROR;
	}

	std::copy(bytecode.begin(), bytecode.end(), memory.data());
	
	/* Set Vars */

	std::reference_wrapper<uint16_t> regARef = REG_0;
	std::reference_wrapper<uint16_t> regBRef = REG_0;

	/* Begin Execution */
	BYTECODE currInstruction = static_cast<BYTECODE>(memory[REG_PC]);
	while(currInstruction != BYTECODE::HALT){
		switch(currInstruction){
			default: break;

			/* COMPARE <regA> <regB> -> [REG_FLAGS] */
			case(BYTECODE::COMPARE):

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
	}
	
	return RESULT_CODE::SUCCESS;
}
