#include "info_indicator.hpp"
void main(void)
{
    indication::InfoIndicator info_indicator;

    while (true) {
        info_indicator.indicate();
    }
}
