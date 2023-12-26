
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
*/

#include <iostream>
#include <filesystem>

#include "spdlog/spdlog.h"

#include "CVM.h"
#include "cmas/Lexer.h"
#include "ResultCode.h"



RESULT run(int argc, char** argv){
	/* Default 8 MB of memory */
	size_t MEMORY_SIZE_MB = 8; 
	std::filesystem::path programPath;

	bool compile_cmas = false;
	bool compile_cmasir = false;
	bool execute_cbc = false;

	/* Parse arguments */
	if(argc == 1){
		std::cout << "Usage: CVM [program_file] <memory (MB)>" << std::endl;
		return RESULT_CODE::CLI_ERROR;
	}else if(argc == 2){
		programPath = std::filesystem::path(argv[1]);
		
		// Check if the file exists and is not a directory
		if (std::filesystem::exists(programPath) && !std::filesystem::is_directory(programPath)) {
            std::string extension = programPath.extension().string();

            if (extension == ".cmas") {
            	compile_cmas = true;
			}
			else if(extension == ".cmasir"){
				compile_cmasir = true;
			}
            else if (extension == ".cbc") {
            	execute_cbc = true;
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
	

	if(compile_cmas){
		spdlog::info("Compiling cmas file: " + programPath.filename().string());	
		Lexer lexer = Lexer(programPath);
		lexer.tokenize();	
	}

	if(compile_cmasir){
		spdlog::info("Compiling cmasir file: " + programPath.filename().string());	
	
	}

	if(execute_cbc){
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

