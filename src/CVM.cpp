#include <algorithm>

#include "spdlog/spdlog.h"

#include "CVM.h"
#include "ResultCode.h"

enum BYTECODE  {
	BC_LOAD = 0x00,
	BC_STORE = 0x01
};

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
	
	REG_A = std::make_unique<uint16_t>(0);
	REG_B = std::make_unique<uint16_t>(0);
	REG_C = std::make_unique<uint16_t>(0);
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


	/* uint16_t currInstruction = *REG_PC; */
	
	return RESULT_CODE::SUCCESS;
}
