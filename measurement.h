#ifndef MEASUREMENT_H
#define MEASUREMENT_H

#include <string>

struct Measurement {
    std::string sensorName;
    std::string unit;
    double value;
    
    Measurement(const std::string& name, const std::string& unit, double value);
};

#endif
