# Cow Pi Mark 3a PCB Assembly Notes

- I2C or SPI
  - There is a pair of solder jumpers on the left side of the board. Creating a
    solder bridge from each center pad to its top pad will connect the
    slide-switches to Arduino pins `D10` and `D11`, freeing the pins used for
    I2C. Creating a bridge from each center pad to its bottom pad will connect
    the slide-switches to pins `D18/A4` and `D19/A5`, freeing the pins used
    for SPI.
  - For I2C, the display module will be driven by a [common I2C interface board
    for LCD character displays](https://www.google.com/search?q=i2c+adapter+for+lcd+1602).
    Before soldering the interface module to the PCB, solder short wires to the
    `GND`, `5V`, `SDA`, and `SCL` solder pads near the located between the
    Arduino's footprint and the mini-breadboard's footprint. After soldering the
    interface module to the PCB, solder the other ends of those wires to the
    interface module's I2C headers.
  - For SPI, you'll need a 10kΩ trim potentiometer (the files in the repo are
    set up for 3 inline pins since that's what's in my junk drawer; you'll
    need to change the footprint if you want a different pin arrangement), a
    10kΩ fixed resistor, an NPN transistor (I'm using 2N2222), and a 74HC595
    shift register. If you want to have the option to disable the display
    module, then you'll also need a 3-pin male header and a shunt jumper;
    otherwise, you can create a solder bridge from the center `SPI-LCD1602
    Disable/Enable` hole to the `Enable` hole.
- Common [2-row, 16-column LCD character display](https://www.google.com/search?q=lcd+1602+display+module)
  ("LCD1602") driven by Hitachi HD44780 LCD controller.
- Slide-switches: two (2) common 3-pin, 2.54mm (0.1in) pitch, breadboard-mountable
  switches
- Tactile switches (buttons): nineteen (19) 6mm, 4-prong tactile switches
  (you could use only 18 if you omit the `RESET` button and just use the one
  on the Arduino)
- Diodes: sixteen (16) diodes; I originally planned to use 1N4001 but got a good
  deal on 1N4448. These are to permit safe and accurate reading of multiple
  keypad buttons simultaneously (not yet supported in the library a/o v0.3.0).
  If you'll only ever press one keypad button at a time, then you can create
  solder bridges across the diode holes instead of inserting diodes.
- LEDs: two (2) common LEDs. I like to use red for left and green for right, to
  match navigation lights, but that's not necessary. You can omit the left LED
  since it duplicate's the Arduino's build-in LED. For that matter, the left
  LED is nigh-useless when using SPI.
- Current-limiting resistors: two (2) common resistors. I spec'd 470Ω, but
  the value isn't critical as long as your choice sufficiently limits the current
  into the LEDs and leaves the LED bright enough to see.
- External power jack (optional): 2.1mm barrel connector
- 4-input NAND -- because of the limited number of external interrupts on the
  ATmega328P (and, by exension, the Arduino Nano), we use NANDs to generate
  the interrupt signals for the keypad and for the left/right buttons. (Early
  testing confirms that the NANDs won't be needed when using an Arduino Nano
  Every due to the ample external interrupts, but the CowPi library doesn't yet
  support that (a/o v0.3.0).) We originally used 74LS20, but *any* 74x20 should
  do (we're currently using 74HC20 because they're a little cheaper and also
  have a broader Vcc range). If you want to selectively break the connection
  from the 74x20 to the Arduino, then add two (2) 2-pin male headers to the
  appropriate location near the Arduino and close the circuit with shunt jumpers;
  if you think you'll never break that circuit, then you can create solder
  bridges where the male headers would otherwise go.
- Breakout header (optional): 2x8-pin, 2.54 (0.1in) pitch, female header. It
  doesn't break out all of the Arduino pins, only those that might be available
  for use by external components
- Mini-breadboard (optional): a convenient place to mount external components,
  also a convenient way to hide the order number printed on the PCB. Note that
  the mini-breadboard I used to measure the space needed didn't have interlocking
  tabs, and the mini-breadboards I ordered to place on the PCBs do -- those tabs
  make for a tight squeeze, so place the mini-breadboard on last.
