/**
 * @file hello.hpp
 * @author Maksim Tsarkov (s1sharp.it@gmail.com)
 * @brief test file easy hello
 * @version 0.1
 * @date 2023-10-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <string>
#include <boost/asio.hpp>
#include <ctime>
#include <chrono>
#include <iostream>

namespace project {

/**
	 * @brief A function
	 * 
	 * @return std::string 
	 */
std::string hello();

}  // namespace project

int test_main();

// A custom implementation of the Clock concept from the standard C++ library.
struct time_t_clock
{
  // The duration type.
  typedef std::chrono::steady_clock::duration duration;

  // The duration's underlying arithmetic representation.
  typedef duration::rep rep;

  // The ratio representing the duration's tick period.
  typedef duration::period period;

  // An absolute time point represented using the clock.
  typedef std::chrono::time_point<time_t_clock> time_point;

  // The clock is not monotonically increasing.
  static constexpr bool is_steady = false;

  // Get the current time.
  static time_point now() noexcept
  {
    return time_point() + std::chrono::seconds(std::time(0));
  }
};

// The boost::asio::basic_waitable_timer template accepts an optional WaitTraits
// template parameter. The underlying time_t clock has one-second granularity,
// so these traits may be customised to reduce the latency between the clock
// ticking over and a wait operation's completion. When the timeout is near
// (less than one second away) we poll the clock more frequently to detect the
// time change closer to when it occurs. The user can select the appropriate
// trade off between accuracy and the increased CPU cost of polling. In extreme
// cases, a zero duration may be returned to make the timers as accurate as
// possible, albeit with 100% CPU usage.
struct time_t_wait_traits
{
  // Determine how long until the clock should be next polled to determine
  // whether the duration has elapsed.
  static time_t_clock::duration to_wait_duration(
      const time_t_clock::duration& d)
  {
    if (d > std::chrono::seconds(1))
      return d - std::chrono::seconds(1);
    else if (d > std::chrono::seconds(0))
      return std::chrono::milliseconds(10);
    else
      return std::chrono::seconds(0);
  }

  // Determine how long until the clock should be next polled to determine
  // whether the absoluate time has been reached.
  static time_t_clock::duration to_wait_duration(
      const time_t_clock::time_point& t)
  {
    return to_wait_duration(t - time_t_clock::now());
  }
};

typedef boost::asio::basic_waitable_timer<
  time_t_clock, time_t_wait_traits> time_t_timer;