#include "info_indicator.hpp"

#include <assert.h>
#include <device.h>
#include <devicetree.h>
#include <drivers/gpio.h>
#include <zephyr.h>

#define INFO_INDICATOR_LED_NODE DT_ALIAS(info_indicator_led)

static constexpr auto LED_PORT = DT_GPIO_LABEL(INFO_INDICATOR_LED_NODE, gpios);
static constexpr auto LED_PIN = DT_GPIO_PIN(INFO_INDICATOR_LED_NODE, gpios);
static constexpr auto LED_GPIO_FLAGS =
  DT_GPIO_FLAGS(INFO_INDICATOR_LED_NODE, gpios);

namespace indication {

InfoIndicator::InfoIndicator(k_timeout_t indication_period) :
  _gpio_port{device_get_binding(LED_PORT)}
{
    assert(device_is_ready(_gpio_port));

    gpio_pin_configure(_gpio_port, LED_PIN,
                       GPIO_OUTPUT_ACTIVE | LED_GPIO_FLAGS);

    k_timer_init(&_indication_timer, NULL, NULL);
    k_timer_start(&_indication_timer, indication_period, indication_period);
}

void InfoIndicator::indicate()
{
    if (k_timer_status_get(&_indication_timer) == 0) {
        return;
    }

    gpio_pin_toggle(_gpio_port, LED_PIN);
}

}  // namespace indication
