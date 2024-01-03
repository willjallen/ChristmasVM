#include <filesystem>

#include "../ResultCode.h"

class Compiler{
	public:
		Compiler() {}
		RESULT compileFunasmToBytecode(std::filesystem::path filePath);
	private:

		std::filesystem::path filePath;

};



