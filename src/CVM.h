

#include <functional>
#include <memory>
#include "ResultCode.h"
#include "ByteCode.h"

enum FLAG : uint16_t  {
	EQ = 0x0,
	LT,
	LTE,
	GT,
	GTE
};


class CVM{
	public:

		CVM(size_t MEMORY_SIZE);
		RESULT init();
		RESULT run(const std::vector<uint16_t>& bytecode);
	private:
		size_t MEMORY_SIZE;

		std::vector<char> memory;
		uint8_t readUInt8(size_t address);
		uint16_t readUInt16(size_t address);

		uint16_t getAddressArgument(size_t PCOffsetBytes);
		uint16_t getLiteralArgument(size_t PCOffsetBytes);

		uint16_t REG_0;
		uint16_t REG_1;
		uint16_t REG_2;
		uint16_t REG_3;
		uint16_t REG_4;
		uint16_t REG_5;
		uint16_t REG_6;
		uint16_t REG_7;

		uint16_t REG_PC;
		uint16_t REG_FLAGS;

		uint16_t& getRegister(enum BYTECODE bytecode);
		void bindReg(std::reference_wrapper<uint16_t>& regRef, size_t PCOffsetBytes);

};
