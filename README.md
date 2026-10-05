# ESP8266 Smart Home Automation

A smart home automation system built around Wi-Fi-connected devices, appliance control, sensors, automation, voice interaction, and intelligent behavior learning.

The project started as a simple ESP8266-based web server and relay controller and is being developed toward a complete smart-home system capable of controlling appliances, monitoring the environment, understanding user behavior, and performing automated actions based on context and preferences.

---

## Project Vision

The long-term goal is to build a flexible smart-home system that can:

- Control lights, fans, ACs, purifiers, humidifiers, and other appliances
- Provide control through a mobile/web app
- Support voice-based control
- Work with Wi-Fi, IR, Bluetooth, and physical controls
- Monitor sensors and device states
- Detect human presence
- Automate appliances based on schedules, rules, presence, and context
- Learn user habits and preferences
- Predict likely actions and suggest or perform them automatically
- Continue essential automation locally even when the internet is unavailable
- Provide clear notifications whenever the system performs an automatic action

The system is intended to be flexible, user-configurable, and capable of evolving as new devices and automation features are added.

---

## Appliance Control

The system should support multiple ways of communicating with appliances depending on what each appliance supports.

Possible control methods include:

- Wi-Fi
- IR
- Bluetooth
- Relay
- Fan speed control
- Other device-specific interfaces

The system should prioritize the most capable/native communication method available.

For example:

```text
Wi-Fi AC
   ↓
Use Wi-Fi control
   ↓
If Wi-Fi control is unavailable
   ↓
Fall back to IR
```

For appliances that do not support smart communication, the system can use relay or IR-based control where appropriate.

---

## Multi-Protocol Appliance Architecture

Different appliances may use different communication methods.

| Appliance | Primary Control | Possible Fallback |
|---|---|---|
| Smart AC | Wi-Fi | IR |
| Smart Light | Wi-Fi | Relay |
| Normal Light | Relay | Physical Switch |
| Smart Fan | Wi-Fi | Relay |
| Normal Fan | Relay / Speed Controller | Physical Switch |
| Remote AC | IR | Physical Remote |
| Purifier | Wi-Fi / IR | Device Remote |
| Humidifier | Wi-Fi / IR / Relay | Physical Control |

The exact control method depends on the appliance.

The system should be designed so that additional protocols and appliance types can be added later.

---

## Device State & Feedback

The system should distinguish between a device state that is actually confirmed and a state that represents only the last command sent.

### Confirmed State

Used when the controller can receive actual feedback from the appliance.

Example:

```text
AC
Status: ON
Temperature: 24°C
Source: Wi-Fi feedback
```

### Last Command State

Used when the appliance does not provide feedback, such as many IR-controlled devices.

Example:

```text
AC
Status: ON (last command)
Temperature: 24°C
Source: IR
```

The system should not falsely report a device as confirmed when it cannot actually verify the state.

---

## Current Prototype

The current prototype is based on an ESP8266/NodeMCU and a 4-channel relay module.

### Current capabilities

- ESP8266 Wi-Fi connectivity
- Embedded web server
- Browser-based relay control
- Four relay channels
- Individual channel timers
- Relay status display
- EEPROM-based relay state storage

### Current hardware

- ESP8266 / NodeMCU
- 4-channel relay module
- Power supply
- Connected electrical loads

### Current firmware

- Arduino IDE
- ESP8266
- C/C++
- Wi-Fi
- HTTP
- EEPROM

---

## Smart Home App

A dedicated app is planned as the main user interface for the system.

The app should provide control and configuration for:

- Lights
- Relays
- Fans
- ACs
- Purifiers
- Humidifiers
- Sensors
- Device status
- Schedules
- Automation rules
- User preferences
- Notifications
- System settings

The app should also allow users to configure how the system behaves instead of forcing fixed behavior.

---

## User-Configurable System

System behavior should be configurable by the user through the app.

Settings should not be unnecessarily hardcoded into the firmware.

Users should be able to configure things such as:

- Automation rules
- Schedules
- Device preferences
- Notification preferences
- Power recovery behavior
- Human-presence checks
- Router failure timeout
- AP-mode behavior
- Automatic actions
- Recovery actions
- Timing-related parameters
- Appliance-specific behavior

For example, after a power outage the user may choose whether the system should:

```text
Restore previous states
```

or:

```text
Keep everything OFF
```

or:

```text
Check for human presence first
        ↓
Presence detected → restore relevant states
No presence → keep appliances OFF
```

The exact behavior should be configurable from the app.

---

## Local-First Operation

Essential smart-home functionality should not depend entirely on an internet connection.

If the internet goes down but the local router/network is still available:

- Local device control should continue
- Local automation should continue
- Sensors should continue working
- Previously configured rules should continue working
- Voice control may become unavailable
- The app should clearly indicate that internet connectivity is unavailable

The goal is to keep the core smart-home system functional locally whenever possible.

---

## Router Failure & AP Mode

If the local router/network becomes unavailable, the controller should be able to detect the failure.

After a user-configurable period of network failure:

```text
Router unavailable
       ↓
Wait for configured timeout
       ↓
Controller switches to AP mode
       ↓
User is notified
       ↓
User can connect directly to the controller
```

The timeout and related behavior should be configurable from the app.

---

## Power Failure & Recovery

The controller should have battery backup so that it can remain operational during a power outage.

The battery is intended to keep the controller and smart-home logic running rather than powering high-power household appliances.

During a power outage:

- The controller remains active while battery power is available
- Mains-powered appliances may remain unavailable
- Sensors and controller logic can continue operating
- Device states can continue to be monitored where possible

### Power Restoration

When mains power returns, the system should follow the user's configured recovery behavior.

One possible recovery flow is:

```text
Power restored
      ↓
Ensure controllable appliances are OFF
      ↓
Monitor for human presence
      ↓
Person detected?
   ┌───────┴───────┐
  YES              NO
   ↓                ↓
Restore relevant   Keep appliances
previous states    OFF
```

For relay-controlled devices, the controller can directly switch the relay OFF.

For IR-controlled devices, the controller can send an OFF command, but actual reception cannot always be guaranteed.

The user should be able to configure whether presence detection is used and how power recovery should behave.

---

## Physical Control

Smart-home automation should not completely eliminate traditional physical control.

For relay-controlled appliances:

- Physical switches should remain usable
- The controller and physical control should be designed to avoid conflicting behavior
- Appliances should remain controllable even if the smart controller becomes unavailable

For remote-controlled appliances:

- The original physical remote can still be used when the controller is unavailable

The intended behavior is based on physical user actions rather than requiring a fixed ON/OFF switch position to always represent the current logical state.

---

## Sensors

Planned sensor support includes:

- Motion sensors
- Human-presence detection
- Light sensors
- Temperature sensors
- Humidity sensors

Sensor data can be used for:

- Automation
- Presence detection
- Environmental monitoring
- Energy-related decisions
- User behavior learning
- Predictive automation

---

## Camera & Presence Detection

A camera may be used for more advanced presence and activity detection.

Potential capabilities include:

- Detecting human presence
- Detecting arrival
- Detecting departure
- Occupancy detection
- Understanding basic activity/context

Camera-based detection may work together with motion and other sensors rather than relying on a single source.

The exact detection architecture is still evolving.

---

## Voice Control

Voice interaction is a major part of the planned system.

Example commands:

```text
Turn on the bedroom light.

Turn off all lights.

Set the fan to speed 2.

Turn on the purifier.

Set the AC to 24°C.
```

Potential voice interfaces include:

- Google Assistant
- Microphones
- Other supported voice interfaces

Voice control may require internet connectivity depending on the voice-processing system being used.

---

## Automation

The system should support different types of automation.

### Schedule-Based

```text
Turn on the bedroom light at 7:00 PM.
```

### Presence-Based

```text
When someone enters the room,
turn on the light.
```

### Sensor-Based

```text
If temperature becomes too high,
turn on the fan.
```

### Context-Based

```text
If someone arrives home
and it is hot,
prepare the AC.
```

### User Behavior-Based

```text
The user usually turns on the AC
around this time.

Suggest:
"Turn on the AC?"
```

Automation behavior should be configurable from the app.

---

## Automatic Action Notifications

Whenever the system performs an action automatically, the user should be notified when configured to do so.

For example:

```text
The system turned on the AC automatically.
```

Depending on the action, the notification may allow the user to:

- Cancel the action
- Perform the action immediately
- Delay the action
- Schedule the action
- Change the automation behavior

The goal is to make automatic actions transparent, controllable, and user-configurable.

---

## Behavior Learning & Machine Learning

A long-term goal is to allow the system to learn user behavior and preferences.

Potential data points include:

- Arrival and departure patterns
- Appliance usage
- AC temperature preferences
- Fan usage
- Lighting habits
- Purifier usage
- Humidifier usage
- Time-based routines
- Presence patterns
- User responses to automated suggestions

The system may initially use simple statistical or rule-based learning before introducing more advanced machine-learning models.

---

## Predictive Automation

Based on learned behavior, the system may predict actions the user is likely to take.

Example:

```text
You usually turn on the AC around this time.

Turn it on?
```

Possible user preferences:

```text
Always Yes
Yes
No
```

The system can learn from these responses and gradually improve its automation decisions.

Predictive automation should remain user-configurable and should not silently override user preferences.

---

## Arrival & Nearby Detection

The system may use available signals to detect when a user is approaching or arriving home.

Possible inputs include:

- Phone presence
- Wi-Fi presence
- Bluetooth
- Camera
- Motion sensors
- Other presence-detection methods

This can be used together with environmental conditions and learned behavior to prepare the home automatically.

---

## Device Communication

The system is intended to support multiple communication technologies depending on the appliance.

Potential technologies include:

- Wi-Fi
- Bluetooth
- IR
- GPIO
- Relay control
- Other appliance-specific protocols

The architecture should allow additional communication methods to be added without redesigning the entire automation system.

---

## Hardware Direction

The current prototype uses an ESP8266.

As the system expands, the controller architecture may need additional capabilities for:

- Camera processing
- Audio
- More sensors
- Multiple communication protocols
- More complex automation
- Local data processing
- Machine learning
- User interfaces
- Reliable production firmware

The final controller architecture will depend on the requirements of the complete system.

---

## Current Pin Configuration

| Relay | GPIO | NodeMCU Pin |
|---|---:|---|
| Relay 1 | GPIO5 | D1 |
| Relay 2 | GPIO4 | D2 |
| Relay 3 | GPIO0 | D3 |
| Relay 4 | GPIO2 | D4 |

---

## Technology Stack

### Current

- Arduino IDE
- ESP8266
- NodeMCU
- C/C++
- Wi-Fi
- HTTP
- EEPROM

### Planned

- Mobile/Web App
- Voice Control
- Sensors
- Camera
- Presence Detection
- IR
- Bluetooth
- Wi-Fi Appliance Control
- Automation Engine
- Notifications
- Usage History
- Behavior Learning
- Machine Learning
- OTA Firmware Updates
- Custom Hardware

---

## Project Status

**Early prototype / long-term development**

### Completed

- ESP8266 Wi-Fi connectivity
- Embedded web server
- Browser-based relay control
- 4-channel relay control
- Individual timers
- Relay status
- EEPROM relay-state storage

### Planned

- Mobile/Web application
- User-configurable automation
- Sensors
- Human-presence detection
- Camera integration
- Fan control
- Fan speed control
- AC control
- IR control
- Wi-Fi appliance control
- Bluetooth appliance control
- Purifier control
- Humidifier control
- Voice control
- Microphone integration
- Notifications
- Arrival detection
- Local-first operation
- Router-failure AP mode
- Battery-backed controller
- Power recovery automation
- Physical switch integration
- Usage history
- Behavior learning
- Predictive automation
- Machine learning
- Expanded hardware
- Custom PCB
- Enclosure
- Production-ready firmware

---

## Roadmap

### Phase 1 — Core Controller

- [x] Wi-Fi connectivity
- [x] Web server
- [x] Browser relay control
- [x] Four-channel relay
- [x] Timers
- [x] EEPROM state storage

### Phase 2 — Smart Devices

- [ ] Sensors
- [ ] Fan control
- [ ] Fan speed control
- [ ] AC control
- [ ] IR control
- [ ] Wi-Fi appliance control
- [ ] Bluetooth appliance control
- [ ] Purifier
- [ ] Humidifier

### Phase 3 — Smart Home Interface

- [ ] Mobile/Web app
- [ ] Device dashboard
- [ ] User-configurable settings
- [ ] Schedules
- [ ] Automation rules
- [ ] Notifications
- [ ] Voice control

### Phase 4 — Presence & Context

- [ ] Motion detection
- [ ] Human-presence detection
- [ ] Camera integration
- [ ] Arrival detection
- [ ] Occupancy detection
- [ ] Context-aware automation

### Phase 5 — Reliability

- [ ] Local-first automation
- [ ] Router failure detection
- [ ] Configurable AP-mode timeout
- [ ] Direct controller access
- [ ] Battery backup
- [ ] Power recovery logic
- [ ] Physical control fallback

### Phase 6 — Intelligence

- [ ] Usage history
- [ ] User preference learning
- [ ] Behavior learning
- [ ] Predictive automation
- [ ] Machine learning
- [ ] Context-aware suggestions

### Phase 7 — Hardware

- [ ] Expanded controller architecture
- [ ] Custom PCB
- [ ] Integrated power management
- [ ] Appliance interfaces
- [ ] Enclosure
- [ ] Production-ready firmware

---

## Goal

The goal is to evolve the current ESP8266 relay prototype into a flexible smart-home platform that combines:

**Control + Sensors + Presence + Automation + Voice + Learning**

while keeping the system:

- User-configurable
- Reliable
- Extensible
- Locally functional where possible
- Transparent about automatic actions
- Compatible with different types of appliances and communication methods
