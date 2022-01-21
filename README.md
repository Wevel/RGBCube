# RGBCube
Project aiming to create a small led cube similar to that of [Greg Davill](https://gregdavill.com/blog/2020/6/13/miniature-3456x-led-cube). This will likely use the same [LED panels](https://github.com/gregdavill/GlassUnicorn/tree/master/hardware/panel_r0.1), but will require a new control board to account for what components are available.

## Control Board
* Change MCU to ESP32 module so as to add wifi connectivity and simplify PCB
* Change FPGA to use one of the following:
	* [Teensy 4.0](https://www.pjrc.com/store/teensy40.html): Not an FPGA, but probably still powerful enough
	* [iCEBreaker Bitsy](https://1bitsquared.com/products/icebreaker-bitsy): Not currently available, but uses the same footprint as the Teensy 4.0, so could be a future upgrade
	* [UPduino v3.1](https://tinyvision.ai/products/upduino-v3-0): May be too long
* Change IMU (Hopefully to the BNO055 if it is ever available again)

## Led Panel
This will likely use the same [LED panels](https://github.com/gregdavill/GlassUnicorn/tree/master/hardware/panel_r0.1) as Greg Davill.

## Frame
May try to 3d print something.
