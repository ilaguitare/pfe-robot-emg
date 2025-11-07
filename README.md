# Build your own mini robot and control it with your arm using muscle contractions (EMG sensor)

| ![Image 1](mini_voiture/images/DSC_2789.JPG) | ![Image 2](mini_voiture/images/DSC_2790.JPG) |
|----------------------------------------------|----------------------------------------------|
| ![Image 3](mini_voiture/images/DSC_2791.JPG) | ![Image 4](mini_voiture/images/DSC_2793.JPG) |

## Materials
- XIAO ESP32C3  
- L9110S motor driver  
- Two Micro Metal DC Gear Motors 6V 150RPM N20  
- 18650 battery 3.7V 3300mAh  
- TP4056 charger module  
- Power switch  

## 3D Printing
Chassis (round design) by: [Thingiverse - thing:2848238](https://www.thingiverse.com/thing:2848238)

## Code
*(to be added)*

## BLE (Bluetooth Low Energy) Communication

The robot communicates with the control interface via **Bluetooth Low Energy (BLE)** using an **XIAO ESP32C3** microcontroller.  
The ESP32 acts as a **BLE server**, exposing a **GATT characteristic** that receives simple control commands (`F`, `B`, `L`, `R`, `S`) to drive the motors.

| Command | Action      |
|----------|-------------|
| `F`      | Forward     |
| `B`      | Backward    |
| `L`      | Turn Left   |
| `R`      | Turn Right  |
| `S`      | Stop        |

On the computer side, a **Python script** handles communication through the **[Bleak](https://github.com/hbldh/bleak)** library.  
It connects asynchronously to the robot and sends commands via a simple **Tkinter-based GUI**.

For mobile testing or manual communication, the robot can also be controlled using the **nRF Connect** app (available on Android and iOS).  
This allows direct BLE communication without needing a computer.

**Advantages:**
- Fully **wireless** connection (no USB or Wi-Fi required)  
- **Low power** and reliable BLE protocol  
- **Cross-platform compatibility**: works on Linux, Windows, and Android  

---
