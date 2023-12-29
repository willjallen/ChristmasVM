#include <filesystem>

#include "../ResultCode.h"

class Compiler{
	public:
		Compiler() {}
		RESULT compileCmasIRToBytecode(std::filesystem::path filePath);
	private:

		std::filesystem::path filePath;

};



