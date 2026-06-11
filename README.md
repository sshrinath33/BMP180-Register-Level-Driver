# BMP180 Register-Level Driver for AVR (Without Wire.h)

A BMP180 temperature and pressure sensor driver implemented using AVR TWI (I²C) registers without using Arduino's Wire.h library or any third-party BMP180 libraries.

---

## Project Objective

The objective of this project was to understand the I²C protocol and AVR TWI peripheral at a low level by implementing a complete BMP180 sensor driver from scratch. This project focuses on direct register manipulation, protocol-level communication, calibration coefficient handling, and Bosch's compensation algorithms for accurate temperature and pressure measurements.

---

## Features

* Register-level TWI (I²C) implementation
* No Wire.h library used
* No third-party BMP180 libraries used
* Temperature measurement
* Pressure measurement
* Calibration coefficient retrieval
* START, STOP, and Repeated START generation
* ACK/NACK handling
* Serial Monitor diagnostics and debugging

---

## Hardware Used

* Arduino Uno (ATmega328P)
* BMP180 Barometric Pressure Sensor
* 2 × 2.2kΩ Pull-up Resistors

---

## Circuit Connections

| BMP180 | Arduino Uno |
| ------ | ----------- |
| VCC    | 5V          |
| GND    | GND         |
| SDA    | A4          |
| SCL    | A5          |

---

## TWI Registers Used

### TWBR (TWI Bit Rate Register)

Used to configure the SCL clock frequency.

### TWCR (TWI Control Register)

Used for:

* START generation
* STOP generation
* ACK/NACK control
* Clearing TWINT
* Enabling TWI

### TWDR (TWI Data Register)

Used to:

* Transmit slave addresses
* Transmit register addresses
* Receive sensor data

### TWSR (TWI Status Register)

Used to verify:

* START condition
* Address transmission
* Data transmission
* Data reception
* ACK/NACK status

---

## BMP180 Communication Sequence

### Temperature Measurement

```text
START
SLA+W
ACK
0xF4
ACK
0x2E
ACK
STOP

Wait 4.5 ms

START
SLA+W
ACK
0xF6
ACK
REPEATED START
SLA+R
ACK

Read MSB (ACK)
Read LSB (NACK)

STOP
```

### Pressure Measurement

```text
START
SLA+W
ACK
0xF4
ACK
Pressure Command
ACK
STOP

Wait according to OSS

START
SLA+W
ACK
0xF6
ACK
REPEATED START
SLA+R
ACK

Read MSB (ACK)
Read LSB (ACK)
Read XLSB (NACK)

STOP
```

---

## Important TWI Status Codes

| Status Code | Meaning                         |
| ----------- | ------------------------------- |
| 0x08        | START transmitted               |
| 0x10        | Repeated START transmitted      |
| 0x18        | SLA+W transmitted, ACK received |
| 0x28        | Data transmitted, ACK received  |
| 0x40        | SLA+R transmitted, ACK received |
| 0x50        | Data received, ACK returned     |
| 0x58        | Data received, NACK returned    |

---

## Temperature Compensation

The raw temperature value (UT) is obtained from the BMP180 and compensated using the factory calibration coefficients stored inside the sensor.

The implementation follows the procedure described in the BMP180 datasheet.

### Example

```text
Raw Temperature = 27620
Temperature = 25.60 °C
```

---

## Pressure Compensation

The raw pressure value (UP) is obtained from the BMP180.

The compensation algorithm uses:

* Calibration coefficients
* Oversampling Setting (OSS)
* B5 value obtained from the temperature calculation

The implementation follows Bosch's official compensation equations from the BMP180 datasheet.

### Example

```text
Pressure = 981.00 hPa
```

---

## Example Output

### Temperature Measurement

```text
Communication started!
SLA_W begins!
Control register address written!
Temperature command written!
Process stopped!

Communication re-started!
SLA_W_repeated begins!
Control register address written!
Repeated START status = 0x10

SLA_R begins!
MSB received!
LSB received!

Raw Temperature = 27728
Temperature = 26.20 °C

Process stopped!
```

### Pressure Measurement

```text
Communication started!
SLA_W begins!
Control register address written!
Pressure command written!
Process stopped!

Communication re-started!
SLA_W_repeated begins!
Control register address written!
Repeated START status = 0x10

SLA_R begins!
MSB received!
LSB received!
XLSB received!

Raw Pressure (UP) = 167792
Final Pressure (Pa) = 98116
Pressure (hPa) = 981.16

Process stopped!
```

---

## Learning Outcomes

Through this project, the following concepts were explored and implemented:

* AVR register-level programming
* TWI peripheral operation
* I²C protocol internals
* START, STOP, and Repeated START conditions
* ACK/NACK handling
* Sensor register access
* Datasheet-driven development
* Embedded debugging techniques
* Sensor driver development
* Temperature compensation algorithms
* Pressure compensation algorithms

---

## Challenges Faced

* Understanding AVR TWI status codes
* Implementing correct ACK/NACK sequencing
* Debugging Repeated START conditions
* Reading and combining multi-byte sensor data
* Retrieving calibration coefficients correctly
* Implementing Bosch's compensation formulas from the datasheet
* Debugging register-level communication issues

One of the biggest lessons from this project was learning that persistence is often more important than initial understanding. The protocol and datasheet were difficult to grasp at first, but became significantly easier once the communication flow and status codes started making sense.

---

## Future Improvements

* Convert the driver into a reusable AVR library
* Add altitude calculation


---

## References

### BMP180 Datasheet

https://cdn-shop.adafruit.com/datasheets/BST-BMP180-DS000-09.pdf

### ATmega328P Datasheet

https://ww1.microchip.com/downloads/en/DeviceDoc/ATmega328P-Data-Sheet-DS40002061B.pdf

These two documents were the primary references used throughout the development of this project.

---

## Author

**Shrinath Raj Subramanian**

Interests:

* Embedded Systems
* Space Technology
* Satellite Systems
* Rocketry

This project was developed as a learning exercise to gain a deeper understanding of I²C communication, sensor interfacing, and embedded driver development at the register level.
