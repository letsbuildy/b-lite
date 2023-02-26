Buildy B-lite will get you stared with IoT projects: mobile control,sensor driven actions, advanced automation ,smart devices to solve a real life problems.

B-lite kit provides:
1. 2 X servo motor (max: 2 Amp per channel)
2. 2 X I/O pins to connect to any digital sensors and motors.
3. 1 X analog sensors input port
4. 1 X I2C port for industry standard communication protocol.
5. 1 X Serial port for flashing and serial monitoring.

B-lite can be programmed using Arduino IDE.
To enable the kit add the below code on top:

```
#define m1_pin1 2;
#define m1_pin2 10;
#define m2_pin1 0;
#define m2_pin2 14;

#define io1 12;
#define io2 13;

#define analog_sensor A0;

#define i2c_tx 4;
#define i2c_rx 5;

```