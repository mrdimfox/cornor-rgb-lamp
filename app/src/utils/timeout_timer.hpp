#pragma once

#include <zephyr.h>

namespace utils {

namespace detail {

/** Additional timeout timer params */
struct TimeoutTimerParams
{
    bool is_periodic = false;
    bool start_on_creation = false;
};

}  // namespace detail

/**
 * @brief Timeout counting timer, simplified wrapped over Zephyr timers
 */
class TimeoutTimer
{
 public:
    using Params = detail::TimeoutTimerParams;

    TimeoutTimer(k_timeout_t period = K_MSEC(100), Params params = Params());

    /**
     * Returns true if timeout reached at least once from the last period start
     *
     * Calling this methos resets the timer’s timeouts expired count to zero.
     */
    bool is_timeout();

    /**
     * Returns the number of times it has expired since its status was last read
     *
     * Calling this methos resets the timer’s timeouts expired count to zero.
     */
    uint32_t timeouts_expired_count();

    /** Start a timer */
    void start();

    /** Start a timer with new period */
    void start(k_timeout_t period);

    /** Same as `start()` but with another name */
    void restart();

    /** Stop a timer */
    void stop();

 private:
    const Params _params;

    k_timeout_t _period;
    k_timer _timer;
};

}  // namespace utils
