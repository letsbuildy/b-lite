#ifndef BLITE_H
#define BLITE_H

// Motor pins(2 X 2-pin connector) connected to DRR8833
#define m1_pin1 0
#define m1_pin2 2
#define m2_pin1 14
#define m2_pin2 15

// programmable I/O (2 X 3-pin connector) 5v bi-directional level shifted driving at BAT level
#define io2 12
#define io1 13

// Analog input pin (1 X 3-pin connector) driving at 5v
#define analog_sensor A0

// I2C/HC-SR04 pin (1X 4-pin connector) driving at 3.3 level
#define i2c_tx 4
#define i2c_rx 5

// pre-soldered components in board  
#define thermistor 16

#endif