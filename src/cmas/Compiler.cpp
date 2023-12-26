#include <filesystem>
#include <fstream>
#include <sstream>
#include <vector>

#include "../ResultCode.h"
#include "../ByteCode.h"
#include "Compiler.h"

RESULT Compiler::compileCmasIRToBytecode(std::filesystem::path filePath) {
    std::ifstream fileStream(filePath);

    if (!fileStream.is_open()) {
        return RESULT_CODE::FILE_NOT_FOUND; // Assuming you have this result code for file errors
    }

    std::string line;
    while (std::getline(fileStream, line)) {
        std::istringstream lineStream(line);
        std::vector<std::string> tokens;
        std::string token;

        // Split the line into tokens (instruction and arguments)
        while(std::getline(lineStream, token, ' ')) {
            if(!token.empty()) {
                tokens.push_back(token);
            }
        }

        // Now you have tokens[0] as the instruction, and tokens[1], tokens[2] (if present) as arguments
        // You can process each instruction here, e.g., translate it into bytecode

        // Example:
        if(tokens.empty()) {
            continue; // Skip empty lines
        }

        if(tokens[0] == "HALT") {
        	// Write 
			BYTECODE bytecode = BYTECODE_STR.at("HALT");
		}
    }

    fileStream.close();
    return RESULT_CODE::SUCCESS; // Assuming SUCCESS is a result code
}


