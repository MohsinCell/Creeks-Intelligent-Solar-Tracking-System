# Creeks - Intelligent Solar Tracking System (using Arduino)

This repository contains the Arduino code for a simple dual-axis solar tracker.  
The system controls two servos — **azimuth** and **elevation** — and supports both **automatic tracking** and **manual angle control** through serial commands.

The tracker is compatible with the dashboard - **[https://creeks.netlify.app/](https://creeks.netlify.app/)**.

---

## 📌 Features

- Dual-axis control using hobby servos  
- **AUTO mode:** smooth simulated sun-tracking  
- **MANUAL mode:** user-defined angles  
- Calibration routine  
- Center reset  
- Live position reporting via Serial  
- Clean command-based interface  
- **Web dashboard control** via serial-over-USB or wireless modules

---

## 🛠 Hardware Requirements

- Arduino Uno / Nano / Mega  
- 2 × SG90 / MG995 / MG996R or similar servos  
- 5V external power for servos (recommended)  
- Jumper wires  
- Mechanical mount for dual-axis movement  

**Pins used:**
- **Azimuth Servo:** D9  
- **Elevation Servo:** D8  

---

## 🔌 Serial Commands

Send commands through the Serial Monitor (9600 baud) or any external GUI/dashboard.

`MODE AUTO` - Enables automatic tracking 
`MODE MANUAL` - Allows manual angle control 
`SET <AZ> <EL>` - Sets angles manually (0–180°) 
`STATUS` - Returns current servo positions 
`RESET` - Moves both servos to center (90°, 90°) 
`CALIBRATE` - Tests 0° → 180° → center 

### Examples

```
> MODE AUTO
AUTO mode enabled. Starting sun tracking...

> MODE MANUAL
MANUAL mode enabled. Use SET command.

> SET 45 60
Azimuth: 45° | Elevation: 60°

> STATUS
Current Position - Azimuth: 45° | Elevation: 60°

> RESET
Resetting to center position (90°, 90°)

> CALIBRATE
Calibration starting...
Testing Azimuth: 0° → 180° → 90°
Testing Elevation: 0° → 180° → 90°
Calibration complete.
```

---

## 🌐 Web Dashboard Control

You can control the tracker using the web dashboard at **[https://creeks.netlify.app/](https://creeks.netlify.app/)**.

### Dashboard Features:
- 🎮 **Real-time servo control** with sliders
- 📊 **Live position monitoring** 
- 🤖 **Auto/Manual mode switching**
- 📍 **Visual sun path display**
- 🔄 **One-click calibration and reset**
- 📡 **Serial communication interface**

### How to Connect:
1. Upload the Arduino code to your board
2. Connect Arduino to your computer via USB
3. Open the dashboard: [https://creeks.netlify.app/](https://creeks.netlify.app/)
4. Click **"Connect"** and select your Arduino's serial port
5. Control the tracker directly from your browser!

> **Note:** The dashboard uses the [Web Serial API](https://developer.mozilla.org/en-US/docs/Web/API/Web_Serial_API) — works in Chrome, Edge, and Opera browsers.

---

## 📥 Installation

### 1. Clone the Repository
```bash
git clone https://github.com/yourusername/dual-axis-solar-tracker.git
cd dual-axis-solar-tracker
```

### 2. Hardware Setup
1. Connect **azimuth servo** signal wire to Arduino pin **D9**
2. Connect **elevation servo** signal wire to Arduino pin **D8**
3. Connect servo **power (VCC)** to external **5-6V supply**
4. Connect all **grounds together** (Arduino + servos + power supply)
5. Mount servos to your mechanical frame

### 3. Upload Code
1. Open `solar_tracker.ino` in Arduino IDE
2. Select your board: **Tools → Board → Arduino Uno** (or your model)
3. Select COM port: **Tools → Port → COM#**
4. Click **Upload** (→)
5. Open **Serial Monitor** (Ctrl+Shift+M) and set baud rate to **9600**

### 4. Test the System
```
> STATUS
Current Position - Azimuth: 90° | Elevation: 90°

> CALIBRATE
(Servos should move through full range)

> MODE AUTO
(System starts automatic tracking simulation)
```

---

## 🎯 Auto Tracking Algorithm

The automatic mode simulates a full day sun path cycle:

**Example: Ahmedabad, Gujarat (23.0225°N, 72.5714°E) — December 15, 2024**

The tracker moves smoothly between these positions with configurable delays.

---

## 📄 License

This project is licensed under the **MIT License** — see [LICENSE](LICENSE) file for details.

---

⭐ **If you find this project useful, give it a star!**

*Built for renewable energy education and practical IoT applications*
