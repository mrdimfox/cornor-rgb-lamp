#pragma once

#include <algorithm>
#include <array>
#include <device.h>
#include <drivers/led_strip.h>
#include <stdint.h>
#include <zephyr.h>

#include "utils/timeout_timer.hpp"

namespace patterns {

inline static constexpr std::array<led_rgb, 3> COLORS = {
  led_rgb{.r = 0x0f, .g = 0x00, .b = 0x00},
  led_rgb{.r = 0x00, .g = 0x0f, .b = 0x00},
  led_rgb{.r = 0x00, .g = 0x00, .b = 0x0f}};

inline static constexpr led_rgb NO_COLOR = {.r = 0x00, .g = 0x00, .b = 0x00};

struct RunningLedsParams
{
    int64_t speed = 1;  //!< speed of pattern in LED per sec (1..1000)
};

/**
 * @brief Straightforward realization of a simple "Running LED" strip pattern
 *
 * Switch on/off LEDs of strip one by one. LEDs color is changed after
 * reaching the end of the strip.
 *
 * @todo Make a Zephyr driver for controlling strip light modes
 */
template<size_t STRIP_NUM_PIXELS>
class RunningLeds
{
    static constexpr size_t NUM_PIXELS = STRIP_NUM_PIXELS;
    static constexpr int64_t MAX_SPEED = 1000;

 public:
    /**
     * @brief Construct a new Running Leds object
     *
     * If `speed` is not in 1..1000 interval it will be bounded.
     *
     * @param strip led strip driver complied device
     * @param params configurable paramters of LED switching pattern
     */
    RunningLeds(const device* strip, RunningLedsParams param);

    /**
     * @brief Switch LED strip state to a new one according to the pattern
     */
    void run();

 private:
    const device* _strip_dev;

    std::array<led_rgb, NUM_PIXELS> _pixels = {};

    led_rgb* _cursor = _pixels.begin();
    const led_rgb* _current_color = COLORS.begin();

    utils::TimeoutTimer _running_timer;

    void _move_cursor();
    void _update_strip();
};


template<size_t N>
RunningLeds<N>::RunningLeds(const device* strip, RunningLedsParams param) :
  _strip_dev(strip),
  _running_timer{K_MSEC(100), utils::TimeoutTimer::Params{.is_periodic = true}}
{
    const int64_t switch_state_period =
      1000 / std::clamp(param.speed, int64_t{1}, MAX_SPEED);

    _running_timer.start(K_MSEC(switch_state_period));
}

template<size_t N>
void RunningLeds<N>::run()
{
    if (not _running_timer.is_timeout()) {
        return;
    }

    _update_strip();
    _move_cursor();
}

template<size_t N>
void RunningLeds<N>::_move_cursor()
{
    _cursor = std::next(_cursor);

    if (_cursor == _pixels.end()) {
        _cursor = _pixels.begin();

        _current_color = std::next(_current_color);
        if (_current_color == COLORS.end()) {
            _current_color = COLORS.begin();
        }
    }
}

template<size_t N>
void RunningLeds<N>::_update_strip()
{
    *_cursor = *_current_color;
    led_strip_update_rgb(_strip_dev, _pixels.data(), _pixels.size());
    *_cursor = NO_COLOR;
}

}  // namespace patterns
