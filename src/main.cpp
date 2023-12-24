
/**
  ██████╗██╗  ██╗██████╗ ██╗███████╗████████╗███╗   ███╗ █████╗ ███████╗    ██╗   ██╗███╗   ███╗
██╔════╝██║  ██║██╔══██╗██║██╔════╝╚══██╔══╝████╗ ████║██╔══██╗██╔════╝    ██║   ██║████╗ ████║
██║     ███████║██████╔╝██║███████╗   ██║   ██╔████╔██║███████║███████╗    ██║   ██║██╔████╔██║
██║     ██╔══██║██╔══██╗██║╚════██║   ██║   ██║╚██╔╝██║██╔══██║╚════██║    ╚██╗ ██╔╝██║╚██╔╝██║
╚██████╗██║  ██║██║  ██║██║███████║   ██║   ██║ ╚═╝ ██║██║  ██║███████║     ╚████╔╝ ██║ ╚═╝ ██║
 ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝╚══════╝   ╚═╝   ╚═╝     ╚═╝╚═╝  ╚═╝╚══════╝      ╚═══╝  ╚═╝     ╚═╝
                                                                                              
 */

/**
 * This is a toy VM to emulate an 16 bit machine. It has
 *
 * Registers:
 * REG_A
 * REG_B
 * REG_PC
 *
 * Types:
 * PLACE
 * POINTER
 * BOOL
 * INT
 * UINT
 *
 * Operations:
 * AddressOf
 * Load 
 * Store
 * Jump
 * JumpC
 * Add/Subtract/Multiply/Divide
 */

#include <memory>
#include <algorithm>
#include<iostream>


/** MEMORY & REGISTERS */


const size_t MEMORY_SIZE_MB = 8; 
const size_t MEMORY_SIZE =  MEMORY_SIZE_MB * 1024 * 1024 / sizeof(uint16_t);

std::unique_ptr<uint16_t[]> memory;

std::unique_ptr<uint16_t> REG_A;
std::unique_ptr<uint16_t> REG_B;
std::unique_ptr<uint16_t> REG_PC;





int main(int argc, char** argv){
	/* Initialize the vm */

	/* Initialize memory and registers */
	memory = std::make_unique<uint16_t[]>(MEMORY_SIZE);
	std::fill(memory.get(), memory.get() + MEMORY_SIZE, 0);
	
	REG_A = std::make_unique<uint16_t>(0);
	REG_B = std::make_unique<uint16_t>(0);


}


