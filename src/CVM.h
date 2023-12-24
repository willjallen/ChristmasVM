

#include <memory>
class CVM{
	public:
		CVM(size_t MEMORY_SIZE);
		int init();
	private:
		size_t MEMORY_SIZE;

		std::unique_ptr<uint16_t[]> memory;
		std::unique_ptr<uint16_t> REG_A;
		std::unique_ptr<uint16_t> REG_B;
		std::unique_ptr<uint16_t> REG_C;
		std::unique_ptr<uint16_t> REG_PC;

};
