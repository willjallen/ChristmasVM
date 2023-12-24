#include <memory>
#include<iostream>


class CVM {

	private:

		/** MEMORY & REGISTERS */

		const size_t MEMORY_SIZE =  MEMORY_SIZE_MB * 1024 * 1024 / sizeof(uint16_t);

		std::unique_ptr<uint16_t[]> memory;

		std::unique_ptr<uint16_t> REG_A;
		std::unique_ptr<uint16_t> REG_B;
		std::unique_ptr<uint16_t> REG_PC;
	public:
		int init();	

}
