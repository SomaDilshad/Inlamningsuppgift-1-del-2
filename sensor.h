#ifndef SENSOR_H
#define SENSOR_H

#include <string>
#include <random>
#include <memory>
#include "measurement.h"

// Abstrakt basklass för alla sensorer
class Sensor {
protected:
    std::string name;
    std::string unit;
    std::string type;
    
    mutable std::mt19937 generator;
    mutable std::uniform_real_distribution<double> distribution;

public:
    Sensor(const std::string& name, const std::string& unit, 
           double minValue, double maxValue, const std::string& type);
    
    virtual ~Sensor() = default;
    
    // Ren virtuell metod - måste implementeras i underklasser
    virtual double readValue() const = 0;
    
    // Konkret metod som använder den virtuella
    Measurement createMeasurement() const;
    
    // Get-metoder
    std::string getName() const { return name; }
    std::string getUnit() const { return unit; }
    std::string getType() const { return type; }
    
    // Virtual metod för sensor-specifik information
    virtual std::string getSensorInfo() const;
};

// Temperatursensor - specifik implementation
class TemperatureSensor : public Sensor {
public:
    TemperatureSensor(const std::string& name);
    double readValue() const override;
    std::string getSensorInfo() const override;
};

// Humidity sensor - specifik implementation  
class HumiditySensor : public Sensor {
public:
    HumiditySensor(const std::string& name);
    double readValue() const override;
    std::string getSensorInfo() const override;
};

// Pressure sensor - specifik implementation
class PressureSensor : public Sensor {
public:
    PressureSensor(const std::string& name);
    double readValue() const override;
    std::string getSensorInfo() const override;
};

// Factory funktion för att skapa sensorer
std::unique_ptr<Sensor> createSensor(const std::string& type, const std::string& name);

#endif
