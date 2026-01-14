#include "sensor.h"
#include "utils.h"
#include <chrono>
#include <iostream>

//=== Base Sensor Implementation ===
Sensor::Sensor(const std::string& name, const std::string& unit, 
               double minValue, double maxValue, const std::string& type)
    : name(name), unit(unit), type(type) {
    
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    generator.seed(seed);
    distribution = std::uniform_real_distribution<double>(minValue, maxValue);
}

Measurement Sensor::createMeasurement() const {
    double value = readValue();  // Polymorfiskt anrop!
    return Measurement(name, unit, value);
}

std::string Sensor::getSensorInfo() const {
    return name + " (" + type + ")";
}

//=== TemperatureSensor Implementation ===
TemperatureSensor::TemperatureSensor(const std::string& name)
    : Sensor(name, "°C", 15.0, 30.0, "Temperature") {}

double TemperatureSensor::readValue() const {
    // Kan ha sensor-specifik logik här
    return distribution(generator);
}

std::string TemperatureSensor::getSensorInfo() const {
    return Sensor::getSensorInfo() + " - Measures ambient temperature";
}

//=== HumiditySensor Implementation ===
HumiditySensor::HumiditySensor(const std::string& name)
    : Sensor(name, "%", 30.0, 80.0, "Humidity") {}

double HumiditySensor::readValue() const {
    // Eventuellt annan distributionslogik
    return distribution(generator);
}

std::string HumiditySensor::getSensorInfo() const {
    return Sensor::getSensorInfo() + " - Measures relative humidity";
}

//=== PressureSensor Implementation ===
PressureSensor::PressureSensor(const std::string& name)
    : Sensor(name, "hPa", 980.0, 1050.0, "Pressure") {}

double PressureSensor::readValue() const {
    return distribution(generator);
}

std::string PressureSensor::getSensorInfo() const {
    return Sensor::getSensorInfo() + " - Measures atmospheric pressure";
}

//=== Factory Function ===
std::unique_ptr<Sensor> createSensor(const std::string& type, const std::string& name) {
    if (type == "Temperature") {
        return std::make_unique<TemperatureSensor>(name);
    } else if (type == "Humidity") {
        return std::make_unique<HumiditySensor>(name);
    } else if (type == "Pressure") {
        return std::make_unique<PressureSensor>(name);
    }
    return nullptr;
}
