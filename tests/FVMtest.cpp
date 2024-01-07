#include <gtest/gtest.h>
#include "FVM.h" // Make sure this path is correct based on your project structure

std::vector<uint8_t>& operator<<(std::vector<uint8_t>& vec, BYTECODE code) {
    vec.push_back(static_cast<uint8_t>(code));
    return vec;
}


// Test Fixture for FVM Tests
class FVMTest : public ::testing::Test {
protected:
    std::unique_ptr<FVM> fvm;

    virtual void SetUp() {
        fvm = std::make_unique<FVM>(64);
        fvm->init();
    }

    virtual void TearDown() {
    }

};

TEST_F(FVMTest, CompareInstructionEqual) {
    fvm->REG_0 = 10; 
    fvm->REG_1 = 10;

    std::vector<uint8_t> bytecode;
    bytecode << BYTECODE::COMPARE << BYTECODE::REG_0 << BYTECODE::REG_1;

    fvm->run(bytecode);

    EXPECT_EQ(fvm->REG_FLAGS, FVM::FLAG::EQ);
}

TEST_F(FVMTest, CompareInstructionLessThan) {
    fvm->REG_0 = 5; 
    fvm->REG_1 = 10;

    std::vector<uint8_t> bytecode;
    bytecode << BYTECODE::COMPARE << BYTECODE::REG_0 << BYTECODE::REG_1;

    fvm->run(bytecode);

    EXPECT_EQ(fvm->REG_FLAGS, FVM::FLAG::LT);
}

TEST_F(FVMTest, AddInstruction) {
    std::vector<uint8_t> bytecode;

    fvm->REG_0 = 2; 
    fvm->REG_1 = 2;

    bytecode << BYTECODE::ADD << BYTECODE::REG_0 << BYTECODE::REG_1;    

    fvm->run(bytecode);

    EXPECT_EQ(fvm->REG_1, 4);
}

