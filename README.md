https://github.com/SomaDilshad/Inlamningsuppgift-1-del-2.git
- Multi-Sensor System with Inheritance and Polymorphism
- Inlämningsuppgift 2 - Fortsättning på IoT-sensorsystem

-  Overview
This project extends the multi-sensor system from Assignment 1 with object-oriented design principles, specifically inheritance and polymorphism. The system now features a more modular architecture with specialized sensor classes and additional functionality for threshold monitoring.

-  New Features in Version 2

-  1. Inheritance Hierarchy
- Base Class: `Sensor` (abstract)
- Derived Classes: 
  - `TemperatureSensor`
  - `HumiditySensor` 
  - `PressureSensor`

-  2. Polymorphic Behavior
- Virtual method `readValue()` for sensor-specific implementations
- Factory pattern for sensor creation
- Runtime polymorphism through base class pointers

-  3. New Manager Class
- `SensorManager` handles all sensor operations
- Centralized control and data management
- Clean separation of concerns

-  4. Threshold Analysis (VG Feature)
- Set upper/lower limits for sensors
- Automatic violation detection
- Real-time monitoring capabilities

-  Updated Architecture

```
Main Program
    ↓
SensorManager → MeasurementStorage
    ↓
[TemperatureSensor, HumiditySensor, PressureSensor]
    ↓
Measurement
```

-  File Structure
```
project/
├── main.cpp              - Updated main program with new menu
├── sensor.h/cpp          - Inheritance hierarchy (UPDATED)
├── measurement.h/cpp     - Measurement struct
├── storage.h/cpp         - Data storage and analysis  
├── utils.h/cpp           - Utility functions
├── sensormanager.h/cpp   - NEW: Central management class
└── Makefile              - Build configuration
```

-  Compilation & Execution

```bash
- Compile
make

- Run
./sensorsystem_v2

- Or compile manually
g++ -std=c++17 -o sensorsystem_v2 .cpp
```

-  New User Interface

```
=== MAIN MENU ===
1. List all sensors (NEW - shows polymorphic types)
2. Take new measurements
3. Show all measurements  
4. Show statistics
5. File operations
6. Clear all data
7. Set thresholds (NEW)
8. Check thresholds (NEW)
0. Exit
```

-  Inheritance Implementation Details

-  Base Class: Sensor
```cpp
class Sensor {
    // Common properties
    virtual double readValue() const = 0;  // Pure virtual
    virtual std::string getSensorInfo() const;
};
```

-  Derived Class Example: TemperatureSensor
```cpp
class TemperatureSensor : public Sensor {
public:
    TemperatureSensor(const std::string& name);
    double readValue() const override;  // Polymorphic override
    std::string getSensorInfo() const override;
};
```

-  Factory Pattern
```cpp
std::unique_ptr<Sensor> createSensor("Temperature", "TempSensor1");
// Returns TemperatureSensor instance as Sensor pointer
```

-  Threshold Analysis Feature

-  Setting Thresholds
```cpp
// Set upper limit for temperature
manager.setThreshold("TempSensor1", 25.0, true);

// Set lower limit for humidity  
manager.setThreshold("HumiditySensor1", 40.0, false);
```

-  Checking Violations
```cpp
manager.checkThresholds();
// Output: TempSensor1: 3 violations of upper limit 25.0
```

-  Testing the New Features

1. Test Inheritance:
   ```bash
   ./sensorsystem_v2
   Choose: 1  # Lists sensors with their specific types
   ```

2. Test Thresholds:
   ```bash
   Choose: 7  # Set threshold
   Choose: 8  # Check violations
   ```

3. Test File Operations:
   ```bash
   Choose: 5 → Save data
   Restart program → Choose: 5 → Load data
   ```

-  Requirements Met

-  From Assignment 1 (Still Valid)
-  Multiple sensor types
-  Measurement storage in `std::vector<Measurement>`
-  Statistical analysis (mean, min, max, stddev)
-  File I/O with CSV format
-  Menu-based interface

-  New Requirements (Assignment 2)
-  Inheritance hierarchy with base and derived classes
-  Polymorphic method calls
-  At least one new functional improvement (Threshold Analysis)
-  Better code organization with Manager class
-  Proper separation in .h/.cpp files

-  Future Extensions

Potential improvements for next version:
- Multiple inheritance for complex sensors
- Template-based measurements for different data types
- Observer pattern for real-time notifications
- Database integration for persistent storage


