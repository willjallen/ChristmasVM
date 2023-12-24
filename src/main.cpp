
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
 * :IDEA: Santa VS the grinch. Basically simplified corewars in christmas flavor
 *
 * Registers:
 * REG_A
 * REG_B
 * REG_C
 * REG_PC
 * REG_ACCUM
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
 *
 *
	<program> ::= <statement> | <statement> <program>

	<statement> ::= <operation> | <operation> <argument> | <operation> <argument> <argument>

	<operation> ::= "AddressOf" | "Load" | "Store" | "Jump" | "JumpC" | "Add" | "Subtract" | "Multiply" | "Divide"

	<argument> ::= <register> | <type>

	<register> ::= "REG_A" | "REG_B" | "REG_PC"

	<type> ::= <place> | <pointer> | <bool> | <int> | <uint>

	<place> ::= "PLACE(" <number> ")"
	<pointer> ::= "POINTER(" <number> ")"
	<bool> ::= "TRUE" | "FALSE"
	<int> ::= <signed_number>
	<uint> ::= <number>

	<number> ::= <digit> | <digit> <number>
	<signed_number> ::= <number> | "-" <number>
	<digit> ::= "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9"
 *
 */


#include <iostream>

#include "CVM.h"




int main(int argc, char** argv){
	/* Default 8 MB of memory */
	size_t MEMORY_SIZE_MB = 8; 

	/* Parse arguments */
	if(argc < 1){
		std::cout << "Usage: CVM [program_file] <memory (MB)>" << std::endl;
	}else if(argc == 1){
	}
	
	std::cout << std::endl;                         
	std::cout << std::endl;                         
	std::cout << " ██████╗██╗   ██╗███╗   ███╗" << std::endl;
	std::cout << "██╔════╝██║   ██║████╗ ████║" << std::endl;
	std::cout << "██║     ██║   ██║██╔████╔██║" << std::endl;
	std::cout << "██║     ╚██╗ ██╔╝██║╚██╔╝██║" << std::endl;
	std::cout << "╚██████╗ ╚████╔╝ ██║ ╚═╝ ██║" << std::endl;
	std::cout << " ╚═════╝  ╚═══╝  ╚═╝     ╚═╝" << std::endl;
	std::cout << std::endl;                         
	std::cout << std::endl;                         
	std::cout << "Christmas VM by William Allen" << std::endl;
	std::cout << "Version 0.0.1" << std::endl;	



	size_t MEMORY_SIZE =  MEMORY_SIZE_MB * 1024 * 1024 / sizeof(uint16_t);
	
	/** Initialize the VM */
	CVM cvm = CVM(MEMORY_SIZE);
	cvm.init();	

}



