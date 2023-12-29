#include <filesystem>
#include <fstream>
#include <sstream>
#include <vector>

#include "spdlog/spdlog.h"

#include "../ResultCode.h"
#include "../ByteCode.h"
#include "Compiler.h"

RESULT Compiler::compileCmasIRToBytecode(std::filesystem::path filePath) {
	spdlog::info("Compiling ir cmas file");
    std::ifstream fileStream(filePath);

    if (!fileStream.is_open()) {
        return RESULT_CODE::FILE_NOT_FOUND;
    }

	std::ostringstream bytecodeStream(std::ostringstream::ate);

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

        if(tokens.empty()) {
            continue; // Skip empty lines
        }
			
		BYTECODE_INFO::BYTECODE_OBJECT bytecodeObj = BYTECODE_INFO::OBJECT_FROM_NAME_MAP.at(tokens[0]);
		
		// Emit instruction bytecode
		bytecodeStream << static_cast<uint8_t>(bytecodeObj.bytecode);

		// Retrieve arguments
		if(tokens.size() - 1 != bytecodeObj.args.size()){
			return RESULT_CODE::INCORRECT_NUM_ARGS;	
		}

		// Emit arguments bytecode
		for(int i = 1; i < tokens.size(); i++){
			auto token = tokens[i];
			auto argType = bytecodeObj.args[i - 1];
			switch(argType){
				case BYTECODE_INFO::ARGUMENT_TYPE::REGISTER:
					// Emit register
					bytecodeStream << static_cast<uint8_t>(BYTECODE_INFO::OBJECT_FROM_NAME_MAP.at(token).bytecode);
					break;
				case BYTECODE_INFO::ARGUMENT_TYPE::ADDRESS:
				case BYTECODE_INFO::ARGUMENT_TYPE::LITERAL:
					// Convert the hexadecimal string to an unsigned integer
					uint16_t value = std::stoul(token, nullptr, 16);

					// Convert to bytes
					uint8_t highByte = (value >> 8) & 0xFF; 
					uint8_t lowByte = value & 0xFF;
					
					// Emit address or literal, little endian
					bytecodeStream << lowByte << highByte;
					break;
			}
		}
		


	}

    fileStream.close();

	// Write bytecode to a file
	std::filesystem::path bcFilePath = filePath;
	bcFilePath.replace_extension(".cbc");

    std::ofstream outFileStream(bcFilePath);
	std::string bytecodeString = bytecodeStream.str(); 
    outFileStream.write(bytecodeString.data(), bytecodeString.size());


    return RESULT_CODE::SUCCESS; // Assuming SUCCESS is a result code
}


