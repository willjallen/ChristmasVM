#include <gtest/gtest.h>
#include "FVM.h" 

std::vector<uint8_t>& operator<<(std::vector<uint8_t>& vec, BYTECODE code) {
    vec.push_back(static_cast<uint8_t>(code));
    return vec;
}


class FVMTest : public ::testing::Test{
protected:
    std::unique_ptr<FVM> fvm;

    virtual void SetUp() {
        fvm = std::make_unique<FVM>(64);
        fvm->init();
    }

    virtual void TearDown() {
    }

};

/** COMPARE */

TEST_F(FVMTest, CompareInstructionLessThan){
    fvm->REG_0 = 5; 
    fvm->REG_1 = 10;

    std::vector<uint8_t> bytecode;
    bytecode << BYTECODE::COMPARE << BYTECODE::REG_0 << BYTECODE::REG_1;
    
    fvm->loadBytecode(0, bytecode);

    fvm->run();

    EXPECT_EQ(fvm->REG_FLAGS & FVM::FLAG::LT, FVM::FLAG::LT);
}

TEST_F(FVMTest, CompareInstructionGreaterThan){
    fvm->REG_0 = 10;
    fvm->REG_1 = 5; 
    
    std::vector<uint8_t> bytecode;
    bytecode << BYTECODE::COMPARE << BYTECODE::REG_0 << BYTECODE::REG_1;

    fvm->loadBytecode(0, bytecode);

    fvm->run();

    EXPECT_EQ(fvm->REG_FLAGS & FVM::FLAG::GT, FVM::FLAG::GT);
}

TEST_F(FVMTest, CompareInstructionLessThanOrEqual_LT){
    fvm->REG_0 = 5; 
    fvm->REG_1 = 10;

    std::vector<uint8_t> bytecode;
    bytecode << BYTECODE::COMPARE << BYTECODE::REG_0 << BYTECODE::REG_1;

    fvm->loadBytecode(0, bytecode);

    fvm->run();

    EXPECT_EQ(fvm->REG_FLAGS & FVM::FLAG::LTE, FVM::FLAG::LTE);
}

TEST_F(FVMTest, CompareInstructionLessThanOrEqual_EQ){
    fvm->REG_0 = 10; 
    fvm->REG_1 = 10;

    std::vector<uint8_t> bytecode;
    bytecode << BYTECODE::COMPARE << BYTECODE::REG_0 << BYTECODE::REG_1;

    fvm->loadBytecode(0, bytecode);

    fvm->run();

    EXPECT_EQ(fvm->REG_FLAGS & FVM::FLAG::LTE, FVM::FLAG::LTE);
}

TEST_F(FVMTest, CompareInstructionGreaterThanOrEqual_GT){
    fvm->REG_0 = 15; 
    fvm->REG_1 = 10;

    std::vector<uint8_t> bytecode;
    bytecode << BYTECODE::COMPARE << BYTECODE::REG_0 << BYTECODE::REG_1;

    fvm->loadBytecode(0, bytecode);

    fvm->run();

    EXPECT_EQ(fvm->REG_FLAGS & FVM::FLAG::GTE, FVM::FLAG::GTE);
}

TEST_F(FVMTest, CompareInstructionGreaterThanOrEqual_EQ){
    fvm->REG_0 = 10; 
    fvm->REG_1 = 10;

    std::vector<uint8_t> bytecode;
    bytecode << BYTECODE::COMPARE << BYTECODE::REG_0 << BYTECODE::REG_1;

    fvm->loadBytecode(0, bytecode);

    fvm->run();

    EXPECT_EQ(fvm->REG_FLAGS & FVM::FLAG::GTE, FVM::FLAG::GTE);
}


TEST_F(FVMTest, CompareInstructionEqual){
    fvm->REG_0 = 10; 
    fvm->REG_1 = 10;

    std::vector<uint8_t> bytecode;
    bytecode << BYTECODE::COMPARE << BYTECODE::REG_0 << BYTECODE::REG_1;

    fvm->loadBytecode(0, bytecode);

    fvm->run();

    EXPECT_EQ(fvm->REG_FLAGS & FVM::FLAG::EQ, FVM::FLAG::EQ);
}


/** JUMP */


TEST_F(FVMTest, AddInstruction){
    std::vector<uint8_t> bytecode;

    fvm->REG_0 = 2; 
    fvm->REG_1 = 2;

    bytecode << BYTECODE::ADD << BYTECODE::REG_0 << BYTECODE::REG_1;    

    fvm->loadBytecode(0, bytecode);

    fvm->run();

    EXPECT_EQ(fvm->REG_1, 4);
}

