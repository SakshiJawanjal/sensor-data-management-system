# sensor-data-management-system
C-based Sensor Data Management System using file handling, structures, and alert logic for real-time sensor monitoring simulation.

## 📊 Sensor Data Management System
The Sensor Data Management System is a C-based console application designed to simulate real-time monitoring and management of sensor data in an embedded system environment.

This project helps in understanding how sensor data is collected, stored, processed, and analyzed using file handling and structured programming in C.
---
## 🎯 Purpose of the Project
In real-world embedded systems like home safety systems, industrial monitoring, and IoT devices, sensors continuously generate data such as temperature, gas levels, and smoke levels. This project simulates that behavior in software form without using actual hardware.

It demonstrates how data from sensors can be managed efficiently and how alerts can be generated when abnormal conditions are detected.
---
## ⚙️ How the System Works
1. The user inputs sensor data such as sensor ID, sensor type, and sensor value.
2. The data is stored permanently using file handling.
3. The system reads stored data whenever required.
4. Based on predefined conditions, the system analyzes sensor values.
5. If values exceed safe limits, the system generates alerts like "Warning", "Danger", or "Critical".
6. Users can also search, update, delete, and sort sensor records.
---
## 📡 Sensor Types Simulated
- Temperature Sensor
- Gas Sensor (MQ-2)
- Smoke Sensor
Each sensor type has its own threshold values for normal, warning, and critical conditions.
---
## 🚨 Alert System
The system automatically checks sensor values and generates alerts:
- Safe / Normal → Normal operating condition
- Warning → Slightly high values
- Danger / Critical → Emergency condition requiring attention
---
## 🧠 Key Concepts Used

- C Programming Language
- File Handling (fopen, fread, fwrite)
- Structures
- String Handling
- Conditional Logic
- Sorting Algorithms
---
## 🏭 Real-World Applications

This project is a simulation of real-world systems used in:
- Home safety systems (gas leakage detection)
- Industrial automation
- Environmental monitoring systems
- IoT-based smart systems
---
## 👨‍💻 Learning Outcome
This project helps in understanding:
- How embedded systems handle sensor data
- How real-time decision-making works in software
- How data persistence is achieved using file handling
