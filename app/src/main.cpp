#include <assert.h>
#include <zephyr.h>
#include <device.h>

#include "info_indicator.hpp"
#include "patterns.hpp"


#define STRIP_NODE DT_ALIAS(led_strip)

static constexpr int STRIP_NUM_PIXELS = DT_PROP(STRIP_NODE, chain_length);

void main(void)
{
    const device* led_strip = DEVICE_DT_GET(STRIP_NODE);
    assert(device_is_ready(led_strip));

    patterns::RunningLeds<STRIP_NUM_PIXELS> running_leds(
      led_strip, patterns::RunningLedsParams{.speed = 10});

    indication::InfoIndicator info_indicator;

    while (true) {
        info_indicator.indicate();
        running_leds.run();
    }
}
