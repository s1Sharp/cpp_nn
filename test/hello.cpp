#include "hello/hello.hpp"

#include <gtest/gtest.h>

#include "torch/torch.h"

using namespace project;

TEST(Hello, demo) {
	torch::Tensor tensor = torch::rand({2, 3});
	std::cout << tensor << std::endl;
	ASSERT_EQ(hello(), "Hello project");
}
