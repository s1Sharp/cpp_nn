#include "hello.hpp"

namespace project {
std::string hello() {
	return "Hello project";
}
}  // namespace project

int test_main() {
	try {
		boost::asio::io_context io_context;

		time_t_timer timer(io_context);

		timer.expires_after(std::chrono::seconds(5));
		std::cout << "Starting synchronous wait\n";
		timer.wait();
		std::cout << "Finished synchronous wait\n";

		timer.expires_after(std::chrono::seconds(5));
		std::cout << "Starting asynchronous wait\n";
		timer.async_wait(
			[](const boost::system::error_code& /*error*/)
			{
			std::cout << "timeout\n";
			});
		io_context.run();
		std::cout << "Finished asynchronous wait\n";
	} catch (std::exception& e) {
		std::cout << "Exception: " << e.what() << "\n";
	}

	return 0;
}