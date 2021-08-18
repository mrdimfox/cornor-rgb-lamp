# RGB cornor lamp

## RGB LEDs control

RGBs is controlled by SPI1 (MOSI line only) configured to 2.5 MHz frequency.
So, according to WS2812B protocol:

* 0b1000 — zero bit;
* 0b1100 — one bit.

Button (B1 USER) is using for a switching the lamp blinking mode.

## Board connections list

* LED = D13 = PA5 — LED indicator.
* MOSI = D11 = PA7 — RGB LEDs control.
* Button = PC13 — modes control button.

## Debug

Start OpenOCD with:

```bash
openocd  -f "board/st_nucleo_l4.cfg" -c "telnet_port 5555" -c "tpiu config internal - uart off 80000000" -c "itm ports on"
```

Connect to debuger by launching "Docker Host (OpenOCD) launch" debug
configuration in VS Code.
