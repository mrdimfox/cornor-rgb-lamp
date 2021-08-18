#include "timeout_timer.hpp"

#include <zephyr.h>

namespace utils {

TimeoutTimer::TimeoutTimer(k_timeout_t period, Params params) :
  _params{params}, _period(period)
{
    k_timer_init(&_timer, nullptr, nullptr);
    if (params.start_on_creation) {
        this->start(period);
    }
}

void TimeoutTimer::start()
{
    k_timer_start(&_timer, _period, _params.is_periodic ? _period : K_NO_WAIT);
}

void TimeoutTimer::start(k_timeout_t period)
{
    _period = period;
    this->start();
}

void TimeoutTimer::restart()
{
    this->start();
}

void TimeoutTimer::stop()
{
    k_timer_stop(&_timer);
}

bool TimeoutTimer::is_timeout()
{
    return k_timer_status_get(&_timer) > 0;
}

uint32_t TimeoutTimer::timeouts_expired_count()
{
    return k_timer_status_get(&_timer);
}

}  // namespace utils
