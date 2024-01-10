#include <algorithm>
#include <cstdlib>
#include <functional>
#include <iomanip>  // for std::setw and std::setfill
#include <sstream> 
#include <format>

#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_DEBUG
#include "spdlog/spdlog.h"
#include "FVM.h"
#include "ResultCode.h"
#include "ByteCode.h"

/**
 * Constructor for the FVM class.
 * Initializes the FVM with a specified memory size.
 * @param MEMORY_SIZE The size of the memory for the FVM.
 */
FVM::FVM(size_t MEMORY_SIZE) : MEMORY_SIZE(MEMORY_SIZE){
}

/**
 * Initializes the virtual machine (VM).
 * Sets up the memory and registers to their initial state.
 * @return RESULT_CODE The result of the initialization operation, indicating success or failure.
 */
RESULT FVM::init(){
	/* Initialize the VM */

	/* Initialize memory and registers */
	memory = std::vector<uint8_t>(MEMORY_SIZE);
	std::fill(memory.begin(), memory.end(), static_cast<uint8_t>(0));
	
	REG_0 = 0;
	REG_1 = 0;
	REG_2 = 0;
	REG_3 = 0;
	REG_5 = 0;
	REG_6 = 0;
	REG_7 = 0;

	REG_PC = 0;
	REG_FLAGS = 0;
	return RESULT_CODE::SUCCESS;
}

std::string FVM::memoryToHexString() const {
    std::stringstream hexStream;
    hexStream << std::hex; // Set stream to output in hex

    for (const auto& elem : memory) {
        hexStream << std::setw(2) << std::setfill('0') << static_cast<unsigned>(elem) << " ";
    }

    return hexStream.str();
}

std::string FVM::dumpState() const {
	std::stringstream state;
	
	// Dump registers
	state << "Registers:\n";
	state << "REG_0: 0x" << std::hex << REG_0 << "\n";
	state << "REG_1: 0x" << std::hex << REG_1 << "\n";
	state << "REG_2: 0x" << std::hex << REG_2 << "\n";
	state << "REG_3: 0x" << std::hex << REG_3 << "\n";
	state << "REG_4: 0x" << std::hex << REG_4 << "\n";
	state << "REG_5: 0x" << std::hex << REG_5 << "\n";
	state << "REG_6: 0x" << std::hex << REG_6 << "\n";
	state << "REG_7: 0x" << std::hex << REG_7 << "\n";
	
	// Dump program counter and flags
	state << "Program Counter (PC): 0x" << std::hex << REG_PC << "\n";
	state << "Flags: 0x" << std::hex << REG_FLAGS << "\n";

	// Dump memory state
	state << "Memory:\n" << memoryToHexString();

	return state.str();
}

/**
 * Retrieves a reference to a register based on the provided bytecode.
 * @param bytecode The bytecode enum indicating the register to access.
 * @return Reference to the selected register.
 */
uint16_t& FVM::getRegister(const enum BYTECODE bytecode) {
	switch(bytecode){
		default:
			{
				SPDLOG_ERROR("Expected Register, got: " + BYTECODE_INFO::NAME_FROM_VALUE_MAP.at(bytecode));
			}
		case BYTECODE::REG_0:      return REG_0;
		case BYTECODE::REG_1:      return REG_1;
		case BYTECODE::REG_2:      return REG_2;
		case BYTECODE::REG_3:      return REG_3;
		case BYTECODE::REG_4:      return REG_4;
		case BYTECODE::REG_6:      return REG_6;
		case BYTECODE::REG_7:      return REG_7;
		case BYTECODE::REG_PC:     return REG_PC;
		case BYTECODE::REG_FLAGS:  return REG_FLAGS;
	}
}

/**
 * Reads an 8-bit unsigned integer from the specified memory address.
 * @param address The memory address from which to read.
 * @return The 8-bit unsigned integer value read from memory.
 */
uint8_t FVM::readUInt8(const size_t address) const {
	return static_cast<uint8_t>(memory[address]);
}

/**
 * Reads a 16-bit unsigned integer from the specified memory address.
 * Assumes a little endian memory model.
 * @param address The memory address from which to read.
 * @return The 16-bit unsigned integer value read from memory.
 */
uint16_t FVM::readUInt16(const size_t address) const {
	uint8_t lowByte = readUInt8(address);
	uint8_t highByte = readUInt8(address+1);
	// Little endian
	return static_cast<uint16_t>(lowByte | highByte << 8);
}

/**
 * Writes an 8-bit unsigned integer to the specified memory address.
 * @param address The memory address to write to.
 * @param value The 8-bit unsigned integer value to write.
 */
void FVM::writeUInt8(const size_t address, const uint8_t value){
	memory[address] = value;
}

/**
 * Writes a 16-bit unsigned integer to the specified memory address.
 * Assumes a little endian memory model.
 * @param address The memory address to write to.
 * @param value The 16-bit unsigned integer value to write.
 */
void FVM::writeUInt16(const size_t address, const uint16_t value){
	uint8_t lowByte = value & 0xFF;
	uint8_t highByte = value >> 8;
	memory[address] = lowByte;
	memory[address + 1] = highByte;
}

/**
 * Binds a register reference to a specified register based on the program counter offset.
 * @param regRef The reference to the register to bind.
 * @param PCOffset The offset from the program counter to determine the register.
 */
void FVM::bindReg(std::reference_wrapper<uint16_t>& regRef, const size_t PCOffset){
	regRef = std::ref(getRegister(static_cast<BYTECODE>(memory[REG_PC + PCOffset])));
}

/**
 * Retrieves a 16-bit address argument from memory based on the program counter offset.
 * @param PCOffset The offset from the program counter.
 * @return The 16-bit address value retrieved from memory.
 */
uint16_t FVM::getAddressArgument(const size_t PCOffset) const {
	return readUInt16(REG_PC + PCOffset);
}

/**
 * Retrieves a 16-bit literal argument from memory based on the program counter offset.
 * @param PCOffset The offset from the program counter.
 * @return The 16-bit literal value retrieved from memory.
 */
uint16_t FVM::getLiteralArgument(const size_t PCOffset) const {
	return readUInt16(REG_PC + PCOffset);
}

/**
 * Loads a vector of bytecode into memory.
 * @param Offset The offset from position 0 to load the memory into
 * @param bytecode The vector of bytecodes to be loaded.
 * @return RESULT_CODE The result of the execution, indicating success or failure.
 */
RESULT FVM::loadBytecode(const size_t offset, const std::vector<uint8_t>& bytecode){
	SPDLOG_INFO("Loading bytecode into memory");

	if(bytecode.size() > MEMORY_SIZE){
		SPDLOG_ERROR("Bytecode is too large");	
		return RESULT_CODE::OUT_OF_MEMORY;
	}

	if(offset >= MEMORY_SIZE - bytecode.size()){
		SPDLOG_ERROR("Offset is too large");
		return RESULT_CODE::BAD_OFFSET;
	}

	std::copy(bytecode.begin(), bytecode.end(), memory.data() + offset);
	
	SPDLOG_DEBUG("Loaded memory: {}", memoryToHexString());

	return RESULT_CODE::SUCCESS;
}

/**
 * Runs the virtual machine, executing each bytecode in sequence.
 * @param bytecode The vector of bytecodes to be executed.
 * @return RESULT_CODE The result of the execution, indicating success or failure.
 */
RESULT FVM::step(){
	
	/* Set Vars */

	regARef = REG_0;
	regBRef = REG_0;

	/* Begin Execution */
	BYTECODE currInstruction = static_cast<BYTECODE>(memory[REG_PC]);
	SPDLOG_DEBUG("Current instruction: " + BYTECODE_INFO::NAME_FROM_VALUE_MAP.at(currInstruction));
	switch(currInstruction){
		default:
			{
				SPDLOG_ERROR("Unimplemented instruction: " + BYTECODE_INFO::NAME_FROM_VALUE_MAP.at(currInstruction));
				return RESULT_CODE::UNIMPLEMENTED_INSTRUCTION;
			}

		// HALT -> [REG_FLAGS]
		// Sets the REG_FLAGS with a bit corresponding to HLT
		case(BYTECODE::HALT):
			{
				REG_FLAGS = REG_FLAGS | FLAG::HLT;

				return RESULT_CODE::SUCCESS;
			}

		// COMPARE <regA> <regB> -> [REG_FLAGS]
		// Sets the REG_FLAGS with a bit corresponding to <, >, <=, >= and = 
		case(BYTECODE::COMPARE):
			{
				// Bind regA and regB
				bindReg(regARef, 1);
				bindReg(regBRef, 2);
				auto& regA = regARef.get();
				auto& regB = regBRef.get();

				// Clear the flag register
				REG_FLAGS = REG_FLAGS & 0;	


				if(regA == regB){
					REG_FLAGS = REG_FLAGS | FLAG::EQ;
				}
				
				if(regA < regB){
					REG_FLAGS = REG_FLAGS | FLAG::LT;
				}
				
				if(regA > regB){
					REG_FLAGS = REG_FLAGS | FLAG::GT;
				}
				
				if(regA <= regB){
					REG_FLAGS = REG_FLAGS | FLAG::LTE;
				} 
				
				if(regA >= regB){
					REG_FLAGS = REG_FLAGS | FLAG::GTE;
				}

				REG_PC += 3;
				break;
			}

		// JUMP <addr> -> []
		// Sets the PC to a particular address in memory
		case(BYTECODE::JUMP):
			{
				uint16_t addr = getAddressArgument(1);
				REG_PC = addr;
				break;
			}

		// JUMPE <addr> -> []
		// Sets the PC to a particular address in memory if EQ flag is set
		case(BYTECODE::JUMPEQ):
			{
				if((REG_FLAGS & FLAG::EQ) == FLAG::EQ){
					uint16_t addr = getAddressArgument(1);
					REG_PC = addr;
				}
				break;
			}

		// JUMPLT <addr> -> []
		// Sets the PC to a particular address in memory if LT flag is set
		case(BYTECODE::JUMPLT):
			{
				if((REG_FLAGS & FLAG::LT) == FLAG::LT){
					uint16_t addr = getAddressArgument(1);
					REG_PC = addr;
				}
				break;
			}

		// JUMPGT <addr> -> []
		// Sets the PC to a particular address in memory if GT flag is set
		case(BYTECODE::JUMPGT):
			{
				if((REG_FLAGS & FLAG::GT) == FLAG::GT){
					uint16_t addr = getAddressArgument(1);
					REG_PC = addr;
				}
				break;
			}

		// JUMPLTE <addr> -> []
		// Sets the PC to a particular address in memory if LTE flag is set
		case(BYTECODE::JUMPLTE):
			{
				if((REG_FLAGS & FLAG::LTE) == FLAG::LTE){
					uint16_t addr = getAddressArgument(1);
					REG_PC = addr;
				}
				break;
			}
			
		// JUMPGTE <addr> -> []
		// Sets the PC to a particular address in memory if GTE flag is set
		case(BYTECODE::JUMPGTE):
			{
				if((REG_FLAGS & FLAG::GTE) == FLAG::GTE){
					uint16_t addr = getAddressArgument(1);
					REG_PC = addr;
				}
				break;
			}
			
		/* MOVING */

		// MOVELR <literal> <regA> -> []
		// Moves a literal into register A
		case(BYTECODE::MOVELR):
			{
				uint16_t literal = getLiteralArgument(1);
				bindReg(regARef, 3);
				auto& regA = regARef.get();
				regA = literal;

				REG_PC += 4;

				break;
			}
		
		// MOVERR <regA> <regB> -> []
		// Moves the contents of register A into register B
		case(BYTECODE::MOVERR):
			{
				bindReg(regARef, 1);
				bindReg(regBRef, 2);
				auto& regA = regARef.get();
				auto& regB = regARef.get();

				regB = regA;

				REG_PC += 3;

				break;
			}
		
		// MOVELR <literal> <addr> -> []
		// Moves a literal into memory
		case(BYTECODE::MOVELM):
			{
				uint16_t literal = getLiteralArgument(1);
				uint16_t address = getAddressArgument(3);
				writeUInt16(address, literal);

				REG_PC += 4;

				break;
			}

		// Moves the contents of register A into memory
		// MOVERM <regA> <addr> -> []
		case(BYTECODE::MOVERM):
			{
				bindReg(regARef, 1);
				auto& regA = regARef.get();

				uint16_t address = getAddressArgument(2);

				writeUInt16(address, regA);

				REG_PC += 4;

				break;

			}

		// Moves the contents of memory into register A
		// MOVEMR <addr> <regA> -> []
		case(BYTECODE::MOVEMR):
			{
				uint16_t address = getAddressArgument(1);

				bindReg(regARef, 3);
				auto& regA = regARef.get();

				regA = readUInt16(address);

				REG_PC += 4;
				
				break;
			}

		// Moves a literal into memory at the address inside register A
		// MOVELIR <literal> <regA> -> []
		case(BYTECODE::MOVELIR):
			{
				uint16_t literal = getLiteralArgument(1);

				bindReg(regARef, 3);
				auto& address = regARef.get();

				writeUInt16(address, literal);

				REG_PC += 4;
				
				break;

			}

		// Moves the contents of memory at the address inside register A to register B
		// MOVEIRR <regA> <regB> -> []
		case(BYTECODE::MOVEIRR):
			{
				bindReg(regARef, 1);
				bindReg(regBRef, 2);

				auto& address = regARef.get();
				auto& regB = regBRef.get();	

				uint16_t contents = readUInt16(address);
				regB = contents;

				REG_PC += 3;
				
				break;
			}

		// Moves the contents of memory at the address inside register A to memory
		// MOVEIRM <regA> <addr> -> []
		case(BYTECODE::MOVEIRM):
			{
				bindReg(regARef, 1);
				auto& address = regARef.get();

				uint16_t contents = readUInt16(address);
				writeUInt16(address, contents);

				REG_PC += 4;
				
				break;
			}


		// Moves contents of memory at the address inside memory to register A
		// MOVEIMR <addr> <regA> -> []
		case(BYTECODE::MOVEIMR):
			{
				uint16_t address = getAddressArgument(1);

				bindReg(regARef, 3);
				auto& regA = regARef.get();

				uint16_t contents = readUInt16(address);

				regA = contents;

				REG_PC += 4;
				
				break;

			}

		// RegisterA + RegisterB -> RegisterB
		// ADD <regA> <regB> -> [regB]
		case(BYTECODE::ADD):
			{
				bindReg(regARef, 1);
				bindReg(regBRef, 2);

				auto& regA = regARef.get();
				auto& regB = regBRef.get();

				regB = regA + regB;

				REG_PC += 3;

				break;
			}

		// RegisterA - RegisterB -> RegisterB
		// SUBTRACT <regA> <regB> -> [regB]
		case(BYTECODE::SUBTRACT):
			{
				bindReg(regARef, 1);
				bindReg(regBRef, 2);

				auto& regA = regARef.get();
				auto& regB = regBRef.get();

				regB = regA - regB;

				REG_PC += 3;

				break;
			}

		// RegisterA * RegisterB -> RegisterB
		// MULTIPLY <regA> <regB> -> [regB]
		case(BYTECODE::MULTIPLY):
			{
				bindReg(regARef, 1);
				bindReg(regBRef, 2);

				auto& regA = regARef.get();
				auto& regB = regBRef.get();

				regB = regA * regB;

				REG_PC += 3;

				break;
			}

		// RegisterA / RegisterB -> RegisterB
		// DIVIDE <regA> <regB> -> [regB]
		case(BYTECODE::DIVIDE):
			{
				bindReg(regARef, 1);
				bindReg(regBRef, 2);

				auto& regA = regARef.get();
				auto& regB = regBRef.get();

				regB = regA / regB;

				REG_PC += 3;

				break;
			}

		// RegisterA + 1 -> RegisterA
		// INCREMENT <regA> -> [regA]
		case(BYTECODE::INCREMENT):
			{
				bindReg(regARef, 1);

				auto& regA = regARef.get();

				regA += 1;

				REG_PC += 2;

				break;
			}

		// RegisterA - 1 -> RegisterA
		// DECREMENT <regA> -> [regA]
		case(BYTECODE::DECREMENT):
			{
				bindReg(regARef, 1);

				auto& regA = regARef.get();

				regA -= 1;

				REG_PC += 2;

				break;
			}

		// RegisterA AND RegisterB -> RegisterB
		// AND <regA> <regB> -> [regB]
		case(BYTECODE::AND):
			{
				bindReg(regARef, 1);
				bindReg(regBRef, 2);

				auto& regA = regARef.get();
				auto& regB = regBRef.get();

				regB = regA & regB;

				REG_PC += 3;

				break;
			}

		// RegisterA OR RegisterB -> RegisterB
		// OR <regA> <regB> -> [regB]
		case(BYTECODE::OR):
			{
				bindReg(regARef, 1);
				bindReg(regBRef, 2);

				auto& regA = regARef.get();
				auto& regB = regBRef.get();

				regB = regA | regB;

				REG_PC += 3;

				break;
			}

		// RegisterA XOR RegisterB -> RegisterB
		// XOR <regA> <regB> -> [regB]
		case(BYTECODE::XOR):
			{
				bindReg(regARef, 1);
				bindReg(regBRef, 2);

				auto& regA = regARef.get();
				auto& regB = regBRef.get();

				regB = regA ^ regB;

				REG_PC += 3;

				break;
			}

		// RegisterA -> !RegisterA
		// NOT <regA> -> [regA]
		case(BYTECODE::NOT):
			{
				bindReg(regARef, 1);

				auto& regA = regARef.get();

				regA = ~regA;

				REG_PC += 2;

				break;
			}

		// RegisterA << literal -> RegisterA
		// SHIFTLEFT <regA> <literal> -> [regA]
		case(BYTECODE::SHIFTLEFT):
			{
				bindReg(regARef, 1);

				uint16_t literal = getLiteralArgument(2);

				auto& regA = regARef.get();

				regA = regA << literal;

				REG_PC += 4;

				break;
			}

		// RegisterA >> literal  -> RegisterA
		// SHIFTRIGHT <regA> <literal> -> [regA]
		case(BYTECODE::SHIFTRIGHT):
			{
				bindReg(regARef, 1);

				uint16_t literal = getLiteralArgument(2);

				auto& regA = regARef.get();

				regA = regA >> literal;

				REG_PC += 4;

				break;
			}
	}	
	
	return RESULT_CODE::SUCCESS;
}

RESULT FVM::run(){
	while(!((REG_FLAGS & FLAG::HLT) == FLAG::HLT)){
		RESULT result = step();
		if(result != RESULT_CODE::SUCCESS){
			return result;
		}
	}

	return RESULT_CODE::SUCCESS;
}
