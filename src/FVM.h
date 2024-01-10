

#include <functional>
#include <memory>
#include "ResultCode.h"
#include "ByteCode.h"



class FVM{


	public:
		enum FLAG : uint16_t  {
			EQ = 0x01,
			LT = 0x02,
			LTE = 0x04,
			GT = 0x08,
			GTE = 0x10,
			HLT = 0x20,
		};

		FVM(const size_t MEMORY_SIZE);
		RESULT init();
		RESULT loadBytecode(const size_t offset, const std::vector<uint8_t>& bytecode);
		RESULT step();
		RESULT run();


		size_t MEMORY_SIZE;
		
		std::vector<uint8_t> memory;
		
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

		uint8_t readUInt8(const size_t address) const;
		uint16_t readUInt16(const size_t address) const;
		
		uint16_t getAddressArgument(const size_t PCOffset) const;
		uint16_t getLiteralArgument(const size_t PCOffset) const;
	
		void writeUInt8(const size_t address, const uint8_t value);
		void writeUInt16(const size_t address, const uint16_t value);
		
		uint16_t& getRegister(const enum BYTECODE bytecode);
	

		std::string memoryToHexString() const;
		std::string dumpState() const;

	private:
		void bindReg(std::reference_wrapper<uint16_t>& regRef, const size_t PCOffset);

		std::reference_wrapper<uint16_t> regARef = REG_0;
		std::reference_wrapper<uint16_t> regBRef = REG_0;

};

