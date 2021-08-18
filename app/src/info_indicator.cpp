#include "info_indicator.hpp"

#include <assert.h>
#include <device.h>
#include <devicetree.h>
#include <drivers/gpio.h>
#include <zephyr.h>

#include "utils/timeout_timer.hpp"


#define INFO_INDICATOR_LED_NODE DT_ALIAS(info_indicator_led)

static constexpr auto LED_PORT = DT_GPIO_LABEL(INFO_INDICATOR_LED_NODE, gpios);
static constexpr auto LED_PIN = DT_GPIO_PIN(INFO_INDICATOR_LED_NODE, gpios);
static constexpr auto LED_GPIO_FLAGS =
  DT_GPIO_FLAGS(INFO_INDICATOR_LED_NODE, gpios);

namespace indication {

using utils::TimeoutTimer;

InfoIndicator::InfoIndicator(k_timeout_t indication_period) :
  _gpio_port{device_get_binding(LED_PORT)},
  _indication_timer(
    indication_period,
    TimeoutTimer::Params{.is_periodic = true, .start_on_creation = true})
{
    assert(device_is_ready(_gpio_port));

    gpio_pin_configure(_gpio_port, LED_PIN,
                       GPIO_OUTPUT_ACTIVE | LED_GPIO_FLAGS);
}

void InfoIndicator::indicate()
{
    if (not _indication_timer.is_timeout()) {
        return;
    }

    gpio_pin_toggle(_gpio_port, LED_PIN);
}

}  // namespace indication
