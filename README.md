# ESP8266 Smart Home Automation

A smart home automation project built around the ESP8266, with the long-term goal of bringing together **Google Assistant voice control, connected microphones, mobile/app control, sensors, and appliance automation** in one system.

The current repository contains an early ESP8266 web-server and relay-control prototype. It is the starting point for a larger smart-home system.

## Project Vision

The goal is to build a flexible smart-home system that can control and automate devices around the home using:

- Google Assistant voice control
- Connected real-time microphones around the home
- Mobile / app control
- Motion detection
- Light-level detection
- Temperature monitoring
- Humidity monitoring
- Automatic rules and schedules
- Relay, IR, Wi-Fi, and Bluetooth-based appliance control

The voice-control concept is centered around **Google Assistant with microphones connected around the home**, so users can give voice commands from different rooms.

## Planned Features

### Voice Control

The system is intended to integrate with Google Assistant and connected microphones placed around the home.

Example commands:

```text
"Turn on the bedroom light."
"Turn off all the lights."
"Set the fan to medium."
"Turn on the air purifier."
"Set the AC to 24 degrees."
```

The exact communication architecture between Google Assistant, the microphones, and the smart-home controller will be determined during development.

### Mobile / App Control

A mobile or web-based interface is planned for:

- Light and relay control
- Fan control
- AC control
- Air purifier control
- Air humidifier control
- Sensor monitoring
- Schedules
- Automation rules
- Device status

### Sensor Integration

The system is intended to support:

- Motion sensors
- Light sensors
- Temperature sensors
- Humidity sensors

Sensor data can be used both for monitoring and automatic actions.

Example:

```text
Motion detected
        +
Low light level
        ↓
Turn on the light
```

Another example:

```text
High temperature
        ↓
Turn on / adjust the fan
```

## Appliance Control

Different appliances may use different control methods depending on the device.

### Lights

Relay-based control can be used for supported ON/OFF loads.

### Fans

The system is intended to support fan control, including ON/OFF and potentially speed control depending on the fan hardware.

### Air Conditioners

AC control is planned through one or more of:

- IR signals
- Wi-Fi
- Bluetooth

The final method will depend on the AC model and its available interface.

### Air Purifiers

The system is intended to control supported air purifiers using the control interface available on the device, such as IR, Wi-Fi, or Bluetooth.

### Air Humidifiers

Supported humidifiers can similarly be integrated through their available control interface.

## Current Prototype

The current repository contains an **ESP8266 web-server and 4-channel relay-control prototype**.

The current prototype demonstrates:

- ESP8266 Wi-Fi connectivity
- Embedded web server
- Browser-based relay control
- 4 relay channels
- Individual relay timers
- Relay status display
- EEPROM-based relay state storage

This prototype is an early building block for the larger smart-home system described above.

## System Concept

```text
                ┌─────────────────────────────┐
                │      Google Assistant       │
                │   + Connected Microphones   │
                │       Around the Home       │
                └──────────────┬──────────────┘
                               │
                               │ Voice Commands
                               ▼
                ┌─────────────────────────────┐
                │       Smart Home Core       │
                │    ESP8266 / Future MCU     │
                │      Controller Platform    │
                └──────────────┬──────────────┘
                               │
          ┌────────────────────┼────────────────────┐
          │                    │                    │
          ▼                    ▼                    ▼
    ┌───────────┐       ┌────────────┐      ┌──────────────┐
    │  Sensors  │       │ App / Web  │      │ Automation   │
    │  Motion   │       │  Control   │      │ Rules        │
    │  Light    │       │            │      │ Schedules    │
    │  Temp     │       │            │      │              │
    │  Humidity │       │            │      │              │
    └─────┬─────┘       └──────┬─────┘      └──────┬───────┘
          │                    │                     │
          └────────────────────┼─────────────────────┘
                               │
                     ┌─────────▼─────────┐
                     │ Appliance Control │
                     └─────────┬─────────┘
                               │
       ┌──────────────┬────────┼────────┬──────────────┐
       ▼              ▼        ▼        ▼              ▼
    Lights           Fans      AC    Air Purifier   Humidifier
    Relay         Relay /     IR /      IR / Wi-Fi / Bluetooth
                 Other       Wi-Fi /
                            Bluetooth
```

## Planned Architecture

The existing ESP8266 prototype is only the first stage of the project.

Future development may include:

- Custom PCB
- Dedicated enclosure
- Distributed sensor nodes around the home
- Central smart-home controller
- Google Assistant integration
- Connected microphones for room-to-room voice commands
- Secure device communication
- User authentication
- OTA firmware updates
- Local/offline automation
- Mobile application
- Appliance-specific control modules
- Additional communication protocols
- More advanced automation rules

## Hardware

### Current Prototype

- ESP8266 / NodeMCU
- 4-channel relay module
- Suitable power supply
- Connected loads

### Planned Hardware

Depending on the final architecture:

- Motion sensors
- Light sensors
- Temperature sensors
- Humidity sensors
- Microphones / audio input
- Relay modules
- IR transmitters / receivers
- Wi-Fi interfaces
- Bluetooth interfaces
- Appliance-specific control hardware

## Software & Technologies

### Current Prototype

- Arduino IDE
- ESP8266
- NodeMCU
- C/C++ (Arduino framework)
- Wi-Fi
- HTTP web server
- EEPROM

### Planned

- Google Assistant integration
- Mobile / web application
- Voice-command processing
- Sensor and automation logic
- Additional communication protocols
- Production-ready firmware

## Relay Pin Configuration

| Relay | GPIO | NodeMCU |
|------:|-----:|:-------:|
| Relay 1 | GPIO 5 | D1 |
| Relay 2 | GPIO 4 | D2 |
| Relay 3 | GPIO 0 | D3 |
| Relay 4 | GPIO 2 | D4 |

> Pin labels may vary depending on the ESP8266 / NodeMCU board being used.

## Setup

1. Install the ESP8266 board support package in Arduino IDE.
2. Open `ESP8266_Home_Automation_Server.ino`.
3. Enter your own Wi-Fi SSID and password in the code.
4. Upload the firmware to the ESP8266.
5. Open the Serial Monitor at `115200` baud.
6. Find the IP address printed after the ESP8266 connects to Wi-Fi.
7. Open that IP address in a browser connected to the same network.

## Project Status

**Stage: Early prototype / experimentation**

The current implementation is only a small part of the larger smart-home concept.

The existing code focuses on ESP8266 networking, web-server control, relay switching, timers, and basic automation. The long-term goal is to expand this into a complete smart-home platform with voice control, microphones, sensors, mobile control, and control of a wide range of appliances.

## Roadmap

- [x] ESP8266 Wi-Fi communication
- [x] Web server
- [x] Browser-based relay control
- [x] 4-channel relay control
- [x] Individual relay timers
- [x] EEPROM state storage
- [ ] Motion sensor integration
- [ ] Light sensor integration
- [ ] Temperature and humidity monitoring
- [ ] Fan control
- [ ] AC control
- [ ] IR appliance control
- [ ] Wi-Fi / Bluetooth appliance integration
- [ ] Air purifier control
- [ ] Air humidifier control
- [ ] Mobile application
- [ ] Google Assistant integration
- [ ] Connected real-time microphones
- [ ] Room-to-room voice commands
- [ ] Custom PCB
- [ ] Dedicated enclosure
- [ ] Production-ready hardware and firmware

## Author

**Md. Mahinul Kabir**

[GitHub](https://github.com/Mahinul-Kabir)
