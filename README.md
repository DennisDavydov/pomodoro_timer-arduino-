
# Arduino Pomodoro Timer

This project is an Arduino-based Pomodoro timer using an OLED display and two buttons to control the timer settings and functionality. The Pomodoro Technique is a time management method developed by Francesco Cirillo in the late 1980s, and it is designed to improve productivity by breaking work into intervals, traditionally 25 minutes in length, separated by short breaks.

## Features

- Countdown timer for work and break periods.
- Adjustable work and break durations.
- Pause and resume functionality.
- Settings are saved in EEPROM memory.

## Components

- Arduino board (e.g., Arduino Uno)
- OLED display (128x64 pixels)
- Two push buttons (Change and Select)
- Breadboard and jumper wires

## Wiring Diagram

Provide a wiring diagram or a brief explanation of how the components are connected to the Arduino.

## Getting Started

1. Upload the provided Arduino code to your Arduino board.
2. Connect the OLED display and buttons to the Arduino following the wiring diagram.
3. Power on the Arduino board.

## Usage

- The Pomodoro timer starts with the default work and break durations stored in EEPROM.
- Use the "Change" button to navigate through the settings.
- Use the "Select" button to start/stop the timer or apply changes in the settings.
- The timer will automatically switch between work and break periods.
- To pause the timer, press the "Select" button when the timer is running.
- To resume, press the "Select" button again.

## Changing Work and Break Durations

1. Navigate to the settings screen by pressing the "Change" button.
2. Use the "Change" button to select work minutes, work seconds, break minutes, break seconds, or apply changes.
3. Use the "Select" button to increase the selected value.
4. Once the desired values are set, press the "Select" button on "Apply" to save the changes.

## Acknowledgments

- Thanks to Adafruit for their Adafruit_SSD1306 library for the OLED display.

## Contributing

Contributions are welcome! Feel free to open an issue or submit a pull request.

