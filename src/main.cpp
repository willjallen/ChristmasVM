
/**
███████╗██╗   ██╗███╗   ██╗    ██╗   ██╗███╗   ███╗
██╔════╝██║   ██║████╗  ██║    ██║   ██║████╗ ████║
█████╗  ██║   ██║██╔██╗ ██║    ██║   ██║██╔████╔██║
██╔══╝  ██║   ██║██║╚██╗██║    ╚██╗ ██╔╝██║╚██╔╝██║
██║     ╚██████╔╝██║ ╚████║     ╚████╔╝ ██║ ╚═╝ ██║
╚═╝      ╚═════╝ ╚═╝  ╚═══╝      ╚═══╝  ╚═╝     ╚═╝
*/

/**
* This is a toy VM to emulate a 16 bit machine. It is equipped to compile cmas-lang (.cmas) to CVM bytecode (.cbc) and running that. 
*/

#ifdef _WIN32 
	#include <Windows.h>
#endif

#include <iostream>
#include <filesystem>

#include "spdlog/spdlog.h"

#include "FVM.h"
#include "lang/Lexer.h"
#include "lang/Compiler.h"
#include "ResultCode.h"



RESULT run(int argc, char** argv){
	/* Default 8 MB of memory */
	size_t MEMORY_SIZE_MB = 8; 
	std::filesystem::path programPath;

	bool compile_funlang = false;
	bool compile_funasm = false;
	bool execute_fbc = false;

	/* Parse arguments */
	if(argc == 1){
		std::cout << "Usage: FVM [program_file] <memory (MB)>" << std::endl;
		return RESULT_CODE::CLI_ERROR;
	}else if(argc == 2){
		programPath = std::filesystem::path(argv[1]);
		
		// Check if the file exists and is not a directory
		if (std::filesystem::exists(programPath) && !std::filesystem::is_directory(programPath)) {
            std::string extension = programPath.extension().string();

            if (extension == ".funlang") {
            	compile_funlang = true;
			}
			else if(extension == ".funasm"){
				compile_funasm = true;
			}
            else if (extension == ".fbc") {
            	execute_fbc = true;
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
	std::cout << "███████╗██╗   ██╗███╗   ███╗" << std::endl;
	std::cout << "██╔════╝██║   ██║████╗ ████║" << std::endl;
	std::cout << "█████╗  ██║   ██║██╔████╔██║" << std::endl;
	std::cout << "██╔══╝  ╚██╗ ██╔╝██║╚██╔╝██║" << std::endl;
	std::cout << "██║      ╚████╔╝ ██║ ╚═╝ ██║" << std::endl;
	std::cout << "╚═╝       ╚═══╝  ╚═╝     ╚═╝" << std::endl;
	std::cout << std::endl;                         
	std::cout << std::endl;                         
	std::cout << "Fun VM by William Allen" << std::endl;
	std::cout << "Version 0.0.1" << std::endl;	



	size_t MEMORY_SIZE =  MEMORY_SIZE_MB * 1024 * 1024 / sizeof(uint16_t);
	

	if(compile_funlang){
		spdlog::info("Compiling funlang file: " + programPath.filename().string());	
		Lexer lexer = Lexer(programPath);
		lexer.tokenize();	
	}

	if(compile_funasm){
		spdlog::info("Compiling funasm file: " + programPath.filename().string());	
		Compiler compiler;
		compiler.compileFunasmToBytecode(programPath);
	
	}

	if(execute_fbc){
		/** Initialize the VM */
		FVM cvm = FVM(MEMORY_SIZE);
		cvm.init();	
	}

	return RESULT_CODE::SUCCESS;
}


int main(int argc, char** argv){
	#ifdef _WIN32
		SetConsoleOutputCP(CP_UTF8);
	#endif

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

