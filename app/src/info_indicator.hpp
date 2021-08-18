#pragma once

#include <zephyr.h>
#include <device.h>

#include "utils/timeout_timer.hpp"

namespace indication {

/**
 * @brief Simple indication pattern for the onboard LED
 * @todo Make a Zephyr driver for controlling the onboard LED
 */
class InfoIndicator
{
 public:
    InfoIndicator(k_timeout_t indication_period = K_MSEC(1000));

    /**
     * @brief Indicate with indication period of time using the indication LED
     */
    void indicate();

 private:
    const device* _gpio_port;

    utils::TimeoutTimer _indication_timer;
};

}  // namespace indication
