#include <algorithm>

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
	memory = std::make_unique<uint16_t[]>(MEMORY_SIZE);
	std::fill(memory.get(), memory.get() + MEMORY_SIZE, 0);
	
	REG_1 = std::make_unique<uint16_t>(0);
	REG_2 = std::make_unique<uint16_t>(0);
	REG_3 = std::make_unique<uint16_t>(0);
	REG_4 = std::make_unique<uint16_t>(0);
	REG_PC = std::make_unique<uint16_t>(0);

	return RESULT_CODE::SUCCESS;
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

	std::copy(bytecode.begin(), bytecode.end(), memory.get());
	
	/* Begin Execution */
	uint16_t currInstruction = *REG_PC;
	while(currInstruction != BYTECODE::HALT){
		/* switch(currInstruction){ */
		/* 		break; */
		/* } */	
	}
	
	return RESULT_CODE::SUCCESS;
}
