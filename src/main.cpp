
/**
  ██████╗██╗  ██╗██████╗ ██╗███████╗████████╗███╗   ███╗ █████╗ ███████╗    ██╗   ██╗███╗   ███╗
██╔════╝██║  ██║██╔══██╗██║██╔════╝╚══██╔══╝████╗ ████║██╔══██╗██╔════╝    ██║   ██║████╗ ████║
██║     ███████║██████╔╝██║███████╗   ██║   ██╔████╔██║███████║███████╗    ██║   ██║██╔████╔██║
██║     ██╔══██║██╔══██╗██║╚════██║   ██║   ██║╚██╔╝██║██╔══██║╚════██║    ╚██╗ ██╔╝██║╚██╔╝██║
╚██████╗██║  ██║██║  ██║██║███████║   ██║   ██║ ╚═╝ ██║██║  ██║███████║     ╚████╔╝ ██║ ╚═╝ ██║
 ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝╚══════╝   ╚═╝   ╚═╝     ╚═╝╚═╝  ╚═╝╚══════╝      ╚═══╝  ╚═╝     ╚═╝
*/

/**
 * This is a toy VM to emulate a 16 bit machine. It is equipped to compile cmas-lang (.cmas) to CVM bytecode (.cbc) and running that. 
 * 
 * (+) Denotes implemented
 * 
 * VM MODEL:
 * Registers:
 * REG_A
 * REG_B
 * REG_C
 * REG_RESULT
 * REG_PC
 *
 * Memory:
 * MEMORY[addr]
 *
 * CMAS LANGUAGE:
 *
 * Types (they're all uint16_t under the hood):
 * POINTER
 * BOOL
 * INT
 * UINT
 *
 * Functions:
 * LABEL() -> POINTER
 * VAR(TYPE, NAME) -> POINTER
 * ADDRESSOF(NAME) -> POINTER
 * LOAD(ADDR) -> POINTER | BOOL | INT | UINT
 * STORE(NAME, ADDR)
 * JUMP(ADDR)
 * JUMPC(COND, ADDR)
 *
 * Unary Operations:
 * !
 * ++
 * -- 
 *
 * Binary Operations
 * =
 * +
 * -
 * /
 * * 
 * >>
 * <<
 *
 */


#include <iostream>
#include <filesystem>

#include "spdlog/spdlog.h"

#include "CVM.h"
#include "Lexer.h"
#include "ResultCode.h"



RESULT run(int argc, char** argv){
	/* Default 8 MB of memory */
	size_t MEMORY_SIZE_MB = 8; 
	std::filesystem::path programPath;

	bool compile = false;
	bool execute = false;

	/* Parse arguments */
	if(argc == 1){
		std::cout << "Usage: CVM [program_file] <memory (MB)>" << std::endl;
		return RESULT_CODE::CLI_ERROR;
	}else if(argc == 2){
		programPath = std::filesystem::path(argv[1]);
		
		// Check if the file exists and is not a directory
		if (std::filesystem::exists(programPath) && !std::filesystem::is_directory(programPath)) {
            // Extract the file extension
            std::string extension = programPath.extension().string();

            // Check for .cmas extension
            if (extension == ".cmas") {
            	compile = true;
			}
            // Check for .cbc extension
            else if (extension == ".cbc") {
            	execute = true;
			}
            else {
                std::cout << "Unsupported file extension." << std::endl;
				return RESULT_CODE::CLI_ERROR;
            }
        } else {
            std::cout << "Invalid file path or directory provided." << std::endl;
            return RESULT_CODE::CLI_ERROR;
        }
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
	

	if(compile){
		spdlog::info("Compiling file: " + programPath.filename().string());	
		Lexer lexer = Lexer(programPath);
		lexer.tokenize();	
	}

	if(execute){
		/** Initialize the VM */
		CVM cvm = CVM(MEMORY_SIZE);
		cvm.init();	
	}

	return RESULT_CODE::SUCCESS;
}


int main(int argc, char** argv){
	RESULT result = run(argc, argv);
	if(result.value == 1){
		return 0;
	}else if(result.name != "CLI_ERROR"){
		spdlog::error("Error: " + result.name);
		return 0;
	}else{
		// Don't print an error message on a CLI failure
		return 0;
	}
}

