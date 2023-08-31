# Attempt to implement Single Pair Ethernet in ESPHome

This is an entry for the [Sparkfun SPE competition](https://www.sparkfun.com/spe_challenge). Unfortunately I never received the form to submit this project, so I was unable to formally submit it.

I was unsuccessful in getting a version working due to issues with newer versions of the Arduino framework and the Sparkfun ADIN1110 library.

## Setup

This project uses the (retired before the competition finished) [Sparkfun MicroMod Single Pair Ethernet Kit](https://www.sparkfun.com/products/retired/19628) and an [Adafruit BME680 sensor](https://www.adafruit.com/product/3660).

The remote sensor side uses the Artemis processor and one SPE board and has the BME680 sensor attached via a StemmaQT/Qwiic connector.

The ESPHome side uses the ESP32 processor and the other SPE board.

### Issues

I had initial issues with getting the examples to run, but eventually found a partially working setup.

The kit came with only a single carrier board, which was later rectified by Sparkfun.

One of the SPE function boards I received was not working with the ESP32, and [only worked with the Artemis](https://forum.sparkfun.com/viewtopic.php?f=182&t=60070). When using the ESP32, having that SPE function board plugged in resulted in an error on boot. The other SPE function board worked with both processors.

```
rst:0x10 (RTCWDT_RTC_RESET),boot:0x33 (SPI_FAST_FLASH_BOOT)
invalid header: 0xffffffff
```

The Sparkfun ADIN1110 library also [does not work with the latest Arduino versions and the ESP32](https://github.com/sparkfun/SparkFun_ADIN1110_Arduino_Library/issues/1), even with the basic examples, which prevented me from getting a functional version of this project.

## Remote side

The sensor side of the connection used the Artemis processor with the SPE function board that did not work with the ESP32.

This side is a modified version of [Example ??] from the ADIN1110 library, but using an Adafruit BME680 instead of the BME280 since that is what I had available.

TransmitStrBME680.ino is the Arduino sketch for the remote side.

## ESPHome integration

The ESPHome integration used the example and documentation for ESPHome custom components.

spe.h and spe.yaml contain the ESPHome custom component.

Since ESPHome uses PlatformIO, I was unable to get a version that worked with the correct version of the Arduino framework and the ADIN1110 library. This version starts correctly with no link, but crashes any time a link is established.

```
[D][SPETEST:046]: Link
Guru Meditation Error: Core  1 panic'ed (IllegalInstruction). Exception was unhandled.
```

This crash appears to be the [known issue with the ESP32 and the ADIN1110 library](https://github.com/sparkfun/SparkFun_ADIN1110_Arduino_Library/issues/1).
