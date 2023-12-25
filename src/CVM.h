

#include <memory>
#include "ResultCode.h"

class CVM{
	public:
		CVM(size_t MEMORY_SIZE);
		RESULT init();
		RESULT run(const std::vector<uint16_t>& bytecode);
	private:
		size_t MEMORY_SIZE;

		std::unique_ptr<uint16_t[]> memory;
		std::unique_ptr<uint16_t> REG_1;
		std::unique_ptr<uint16_t> REG_2;
		std::unique_ptr<uint16_t> REG_3;
		std::unique_ptr<uint16_t> REG_4;
		std::unique_ptr<uint16_t> REG_PC;

};
