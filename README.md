## CAN Transmission System (STM32F103C8T6)

### Project Overview
This project implements a CAN master setup using an STM32F103C8T6 microcontroller and the SN65HVD230 CAN transceiver. The system is designed to transmit data to another CAN node at a baud rate of 250kbps. This is a bare-metal project developed with CMSIS, using a 72MHz system clock via PLL.

Currently, the code is a crude implementation to get the CAN transmission working. The system will be refactored to use structures and other methods to improve organization and maintainability in future versions.

### Key Features
CAN Master Setup using STM32F103C8T6

CAN Transceiver: SN65HVD230

Baud Rate: 250 kbps

Clock: 72 MHz (using PLL)

Bare Metal Code using CMSIS

USART & Timer4 for custom delays

Build System: make (Makefile used for building)

### Hardware Requirements
Microcontroller: STM32F103C8T6

CAN Transceiver: SN65HVD230

ST-Link: For flashing the firmware

Linux Machine: Ubuntu 22.04 (tested on this OS)

### Building the Project
To build the project, simply use the make command:
make
This will generate the necessary files, including the main.bin binary file.

### Flashing the Project to STM32
Locate the Build folder where the main.bin file is created.

### Use the following command to flash the firmware to your STM32F103C8T6 using ST-Link:

st-flash write main.bin 0x8000000

Ensure your ST-Link is set up correctly and connected to your target device.

### Project Setup on Linux (Ubuntu 22.04)
This project has been tested on a Linux machine running Ubuntu 22.04. Ensure that you have ST-Link tools installed, as well as dependencies for flashing the STM32.

### Notes
The system operates at 72 MHz using the PLL configuration.

The USART and Timer4 modules are used to manage communication and custom delays in the code.

This setup currently focuses on CAN data transmission only. The system transmits data to the other CAN node, which you can extend for other functionalities.

This is a crude implementation. In the future, structures will be used to better organize the code and improve maintainability.

### Future Enhancements
CAN reception functionality

Error handling and retries

Adding filtering mechanisms for specific CAN messages

Implementing CAN node communication for more complex systems

Code refactor to use structures and improve organization
