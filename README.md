# 8051 Development Board Project

This project involved building a custom **8051 development board** using the **AT89C51RC2 chip** with **32KB NVSRAM** for external storage. The project included driver development for various peripherals and rigorous testing with measurement tools.

## Key Components and Features

### Hardware
- **8051 Microcontroller**: Built the development board around the **AT89C51RC2** microcontroller.
- **External Storage**: Added **32KB NVSRAM** to expand storage capacity.

### Driver Development
- **UART Setup**: Developed driver codes for **UART** communication using circular buffers for efficient data handling.
- **I2C Interface**: Interfaced an **EEPROM** via **I2C** using bit-banging for manual clock and data line control.
- **SPI-based DAC Module**: Integrated an **SPI-based DAC module** for digital-to-analog conversions.
- **LCD Display**: Interfaced an **LCD** for real-time data display and user interaction.

### Testing and Analysis
- **Bus Cycle Analysis**: Used a **logic analyzer** and **oscilloscope** to capture and analyze bus cycles.
- **Power Measurements**: Measured **average and instantaneous current and voltage** to ensure optimal performance and efficiency.

## Tools and Equipment
- **Logic Analyzer** and **Oscilloscope** for signal and bus cycle analysis
- **Multimeter** for current and voltage measurements
- **8051-compatible development tools** for coding and debugging

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.
