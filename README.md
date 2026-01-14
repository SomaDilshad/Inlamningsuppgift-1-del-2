- Multi-Sensor System with Inheritance and Polymorphism
- Inlämningsuppgift 2 - Fortsättning på IoT-sensorsystem

- Overview
This project extends the multi-sensor system from Assignment 1 with object-oriented design principles, specifically inheritance and **polymorphism. The system now features a more modular architecture with specialized sensor classes and additional functionality for threshold monitoring.

-  New Features in Version 2

-  1. Inheritance Hierarchy
Implemented a clear class hierarchy:
- Abstract Base Class: `Sensor` - defines common interface with virtual methods
- Concrete Derived Classes: 
  - `TemperatureSensor` - specialized for temperature readings
  - `HumiditySensor` - specialized for humidity measurements  
  - `PressureSensor` - specialized for pressure data

-  2. Polymorphic Behavior
- Virtual Methods: `readValue()` is overridden in each derived class
- Factory Pattern: `createSensor()` function returns appropriate sensor type
- Runtime Binding: Methods are called through base class pointers

-  3. New Manager Class
- `SensorManager` centralizes all sensor operations
- Handles sensor lifecycle and data collection
- Provides clean API for main program

-  4. Threshold Analysis (VG Feature)
- Configurable upper/lower limits per sensor
- Automatic violation counting
- Real-time monitoring support

-  Class Design

-  Inheritance Structure
```
Sensor (Abstract Base Class)
├── TemperatureSensor
├── HumiditySensor
└── PressureSensor
```

-  Key Design Patterns
1. Factory Pattern: For creating sensor instances
2. Strategy Pattern: Each sensor implements its own reading logic
3. Manager Pattern: Centralized control through SensorManager

-  Key Methods
- `Sensor::readValue()` - Pure virtual method for sensor-specific readings
- `Sensor::createMeasurement()` - Template method using readValue()
- `SensorManager::setThreshold()` - Configures monitoring limits
- `SensorManager::checkThresholds()` - Analyzes data against limits

-  File Structure
```
project/
├── main.cpp                 - Main program with enhanced menu
├── sensor.h/cpp             - Inheritance hierarchy implementation
├── measurement.h/cpp        - Data structure for measurements
├── storage.h/cpp            - Data persistence and analysis  
├── utils.h/cpp              - Utility functions
├── sensormanager.h/cpp      - Central management system
└── Makefile                 - Build configuration
```

-  Compilation & Execution

```bash
-  Compile the project
make

-  Run the program
./sensorsystem_v2

-  Alternative manual compilation
g++ -std=c++17 -Wall -Wextra -o sensorsystem_v2 *.cpp
```

-  Program Features Menu

```
=== MAIN MENU ===
1. List all sensors (shows polymorphic types)
2. Take new measurements from all sensors
3. Display all stored measurements  
4. Show statistical analysis
5. File operations (save/load data)
6. Clear all measurement data
7. Configure threshold limits (NEW)
8. Check for threshold violations (NEW)
0. Exit program
```

-  Testing the Implementation

-  Test 1: Verify Inheritance
1. Run program and select option 1
2. Verify that different sensor types are listed correctly
3. Each sensor should show its specific type information

-  Test 2: Test Threshold System
1. Set a threshold for a sensor (option 7)
2. Take some measurements (option 2)
3. Check for violations (option 8)
4. Verify that violations are correctly detected

-  Test 3: Verify Polymorphism
1. Sensors are stored as base class pointers
2. Each sensor type produces values in its specific range
3. Factory function creates correct sensor types

-  Implementation Details

-  Code Organization Principles
- Separation of Concerns: Each class has a single responsibility
- Encapsulation: Internal details are hidden behind public interfaces
- Dependency Injection: SensorManager works with any Sensor-derived class
- Resource Management: Smart pointers prevent memory leaks

-  File Format for Data Storage
```
timestamp,sensor_name,value,unit
2024-11-20 10:30:25,TempSensor1,22.5,°C
2024-11-20 10:30:25,HumiditySensor1,45.2,%
```

-  Statistical Analysis Includes
- Mean value calculation
- Minimum and maximum detection
- Standard deviation computation
- Per-sensor and system-wide statistics

-  Requirements Fulfillment

-  Core Requirements (All Passed)
-  Inheritance hierarchy with base and derived classes
-  Polymorphic method implementations
-  At least one new functional improvement
-  Proper code organization in .h/.cpp files
-  Maintains all functionality from Assignment 1

-  Extended Features (VG Level)
-  Threshold monitoring system
-  Configurable upper/lower limits
-  Violation detection and reporting
-  Enhanced user interface


-  Learning Outcomes

This implementation demonstrates:
1. Effective use of inheritance to create specialized sensor types
2. Polymorphism for flexible method calls
3. Design patterns for clean architecture
4. C++ best practices for memory and resource management
5. Extensible design that can accommodate new sensor types

-  Future Enhancement Possibilities

1. Additional Sensor Types: Light sensors, motion detectors, etc.
2. Network Integration: Remote sensor data collection
3. Real-time Alerts: Email/SMS notifications for threshold violations
4. Data Visualization: Graphical representation of sensor data
5. Multi-threading: Concurrent data collection from multiple sensors

