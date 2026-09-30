# ESP8266 Smart Home Automation

A smart home automation project that started with an ESP8266-based web server and relay controller.

The long-term goal is to build a more intelligent smart-home system that can combine **voice control, app control, sensors, cameras, appliance control, and machine learning** to learn the user's habits and automate the home around them.

## Project Vision

The planned system is intended to control and automate different parts of a home through:

- Google Assistant voice control
- Real-time microphones connected to the Google Assistant setup
- Mobile / web app control
- Motion detection
- Light-level detection
- Temperature monitoring
- Humidity monitoring
- Camera-based presence / activity detection
- Automatic schedules and rules
- Machine-learning-based behavior learning

The system should not only respond to direct commands, but gradually learn how the user normally uses appliances and use that information to make useful suggestions or automate actions.

## Voice Control

Google Assistant will be one of the main ways to interact with the system.

The planned setup also includes microphones around the home so the user can give voice commands from different rooms.

Example commands:

```text
"Turn on the bedroom light."
"Turn off all the lights."
"Set the fan to speed 2."
"Turn on the air purifier."
"Set the AC to 24 degrees."
```

## App Control

A mobile / web application is planned for:

- Controlling lights and relays
- Controlling fans
- Controlling AC
- Controlling air purifiers
- Controlling air humidifiers
- Viewing sensor data
- Viewing device status
- Setting schedules
- Configuring automation preferences
- Receiving notifications

## Sensors

The system is planned to use multiple sensors, including:

- Motion sensor
- Light sensor
- Temperature sensor
- Humidity sensor

Sensor data can be used for both monitoring and automation.

Example:

```text
Motion detected
       +
Low light level
       ↓
Suggest / turn on the light
```

Another example:

```text
Room temperature rises
       +
User is present
       ↓
Suggest / adjust fan or AC
```

## Camera Integration

A camera connected to the smart-home hardware is planned as another source of information.

Possible uses include:

- Detecting whether someone is present
- Detecting when the user arrives or leaves
- Supporting room occupancy information
- Providing additional context for automation and behavior learning

The exact camera hardware and processing method will be decided during later development.

## Machine Learning & Behavior Learning

One of the main long-term goals is to add machine learning or other lightweight data-driven methods so the system can learn the user's habits instead of relying only on fixed rules.

The system may learn patterns such as:

- When the user normally arrives home
- When the user normally leaves
- Which days and times the user uses specific appliances
- How the user uses the AC, fan, air purifier, and humidifier
- Preferred appliance settings under different room conditions
- Repeated daily or weekly routines

### Example: Learning Fan / AC Preferences

Suppose the user repeatedly uses:

```text
Room temperature: 27°C
Humidity: 65%
Time: 8:00 PM
Fan speed: 2
```

After collecting enough history, the system could learn that the user commonly prefers that setting under similar conditions.

The same concept could be applied to:

- AC temperature / mode
- Fan speed
- Air purifier settings
- Humidifier settings

The exact ML model is not decided yet. The system may start with simple statistical or rule-based learning and become more advanced as more data is collected.

## Predictive Automation

The system may also learn the user's normal arrival and departure patterns using factors such as:

- Day of the week
- Time of day
- Previous activity
- Presence information
- Camera information
- Other available signals

This could allow the system to prepare the home before the user arrives.

Example:

```text
User usually arrives around 6:30 PM on weekdays
                     ↓
            Approaching usual time
                     ↓
             Check room conditions
                     ↓
       Notify user about an appliance
```

For example, the system could notify the user:

> "You usually turn on the AC around this time. Turn it on?"

The user could choose a preference such as:

- **Always Yes** — automatically perform the action
- **Yes** — ask for confirmation
- **No** — do not suggest this action

The same notification and preference system could be used for:

- AC
- Fan
- Air purifier
- Air humidifier
- Lights
- Other supported appliances

## Nearby / Arrival Detection

Another planned feature is to notify the user when they are getting close to home.

Depending on the final design, the system could combine available presence or location-related signals with learned routines.

Example:

```text
User is nearby
      +
Normal arrival time
      +
Room needs cooling / air treatment
      ↓
Send notification
```

The user can then decide whether to turn on the relevant appliance.

## Appliance Control

Different appliances may use different control methods.

### Lights

Relay-based ON/OFF control for supported electrical loads.

### Fans

Possible control methods include:

- Relay-based ON/OFF
- Hardware-specific speed control

### Air Conditioners

Possible control methods:

- IR
- Wi-Fi
- Bluetooth

The final method will depend on the AC model and available interface.

### Air Purifiers

Possible control methods:

- IR
- Wi-Fi
- Bluetooth

### Air Humidifiers

Possible control methods:

- IR
- Wi-Fi
- Bluetooth

## Current Prototype

The current repository contains an early **ESP8266 4-channel relay and web-server prototype**.

The current implementation demonstrates:

- ESP8266 Wi-Fi connectivity
- Embedded web server
- Browser-based relay control
- 4 relay channels
- Individual relay timers
- Relay status display
- EEPROM-based relay state storage

This prototype is the starting point for the larger smart-home concept described above.

## Current Hardware

The existing prototype uses:

- ESP8266 / NodeMCU
- 4-channel relay module
- Suitable power supply
- Connected loads

## Planned Hardware Direction

As the project grows, the development board may be upgraded to a more capable platform to support the additional requirements such as:

- Camera processing
- Microphone / audio processing
- Machine learning
- More sensors
- More communication interfaces
- More complex automation logic

The final controller and hardware architecture have not been decided yet.

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
- Voice interaction
- Sensor processing
- Camera-based detection
- Machine learning / behavior learning
- Automation and scheduling
- IR / Wi-Fi / Bluetooth appliance control
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

**Stage: Early prototype / long-term development**

The current code is only the first stage of the project. The larger goal is to develop a smart-home platform that can combine:

**Voice + App + Sensors + Camera + Appliance Control + Machine Learning**

The system is expected to evolve significantly as the hardware and software architecture are developed.

## Roadmap

### Completed

- [x] ESP8266 Wi-Fi communication
- [x] Web server
- [x] Browser-based relay control
- [x] 4-channel relay control
- [x] Individual relay timers
- [x] EEPROM state storage

### Planned

- [ ] Motion sensor integration
- [ ] Light sensor integration
- [ ] Temperature and humidity monitoring
- [ ] Fan control
- [ ] AC control
- [ ] IR appliance control
- [ ] Wi-Fi / Bluetooth appliance integration
- [ ] Air purifier control
- [ ] Air humidifier control
- [ ] Camera integration
- [ ] Presence / occupancy detection
- [ ] Google Assistant integration
- [ ] Connected microphones
- [ ] Mobile application
- [ ] Smart notifications
- [ ] Arrival / nearby-user detection
- [ ] User preference system
- [ ] Appliance usage history
- [ ] Behavior learning
- [ ] Predictive automation
- [ ] Machine learning
- [ ] Custom PCB
- [ ] Dedicated enclosure
- [ ] Upgrade development board
- [ ] Production-ready hardware and firmware

## Author

**Md. Mahinul Kabir**

[GitHub](https://github.com/Mahinul-Kabir)
