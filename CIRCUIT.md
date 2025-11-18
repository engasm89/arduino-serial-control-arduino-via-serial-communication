# ESP32 Serial Control — Circuit Schematic

- Course: Arduino Serial: Control Arduino via Serial Communication
- Author: Ashraf S A AlMadhoun
- Link: https://www.udemy.com/course/arduino-serial-control-arduino-via-serial-communication/?couponCode=JULYMAXDICOUNT

## Connections

- Onboard LED at `GPIO2`.
- USB to PC for UART.
- Optional external LED via resistor to another GPIO.

## Diagram (ASCII)

```
 ESP32 ---- USB ---- PC (Serial Terminal)
 GPIO2 -> LED
 GPIO4 ->[220Ω]-> LED -> GND
```

## Notes

- Baud rate typically 115200; ensure terminal settings match.
- Avoid powering external loads directly from GPIO; use drivers.

