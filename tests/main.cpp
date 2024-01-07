#include <gtest/gtest.h>
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_DEBUG
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

class Environment : public ::testing::Environment {
 public:
  ~Environment() override {}

  // Override this to define how to set up the environment.
  void SetUp() override {
    spdlog::set_pattern("[%^%l%$] [%s:%#%$] [func: %!%$] %v");
    spdlog::set_level(spdlog::level::debug);
  }

  // Override this to define how to tear down the environment.
  void TearDown() override {}
};

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::AddGlobalTestEnvironment(new Environment());
    return RUN_ALL_TESTS();
}
