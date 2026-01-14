#include "measurement.h"

Measurement::Measurement(const std::string& name, const std::string& unit, double value)
    : sensorName(name), unit(unit), value(value) {}
