
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


#include <stdout>

#include <CVM.h>




int main(int argc, char** argv){
	/* Default 8 MB of memory */
	size_t MEMORY_SIZE_MB = 8; 

	/* Parse arguments */
	if(argc < 1){
		std::cout << "Usage: CVM [program_file] <memory (MB)>" << std::endl;
	}else if(argc == 1){
			
	}

	size_t MEMORY_SIZE =  MEMORY_SIZE_MB * 1024 * 1024 / sizeof(uint16_t);

}



