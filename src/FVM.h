

#include <functional>
#include <memory>
#include "ResultCode.h"
#include "ByteCode.h"



class FVM{
	public:
		enum FLAG : uint16_t  {
			EQ = 0x0,
			LT,
			LTE,
			GT,
			GTE
		};

		FVM(const size_t MEMORY_SIZE);
		RESULT init();
		RESULT run(const std::vector<uint8_t>& bytecode);

	protected:
		size_t MEMORY_SIZE;

		std::vector<uint8_t> memory;
		uint8_t readUInt8(const size_t address) const;
		uint16_t readUInt16(const size_t address) const;

		void writeUInt8(const size_t address, const uint8_t value);
		void writeUInt16(const size_t address, const uint16_t value);

		uint16_t getAddressArgument(const size_t PCOffsetBytes) const;
		uint16_t getLiteralArgument(const size_t PCOffsetBytes) const;

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

		uint16_t& getRegister(const enum BYTECODE bytecode);
		void bindReg(std::reference_wrapper<uint16_t>& regRef, const size_t PCOffsetBytes);

};
