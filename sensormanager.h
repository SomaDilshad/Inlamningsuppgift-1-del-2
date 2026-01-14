#ifndef SENSORMANAGER_H
#define SENSORMANAGER_H

#include <vector>
#include <memory>
#include <string>
#include "sensor.h"
#include "storage.h"

struct Threshold {
    std::string sensorName;
    double value;
    bool isUpperLimit;  // true = övre gräns, false = nedre gräns
};

class SensorManager {
private:
    std::vector<std::unique_ptr<Sensor>> sensors;
    MeasurementStorage storage;
    std::vector<Threshold> thresholds;
    
public:
    SensorManager();
    
    // Sensor management
    void addSensor(std::unique_ptr<Sensor> sensor);
    void createDefaultSensors();
    void listAllSensors() const;
    std::vector<std::string> getSensorNames() const;
    
    // Measurement operations
    void takeMeasurements(int measurementsPerSensor);
    void takeSingleMeasurement(const std::string& sensorName);
    
    // Data operations
    void showAllMeasurements() const;
    void showStatistics() const;
    void showSensorStatistics(const std::string& sensorName) const;
    
    // File operations
    bool saveToFile(const std::string& filename);
    bool loadFromFile(const std::string& filename);
    void clearAllData();
    
    // Threshold analysis (ny funktionalitet)
    void setThreshold(const std::string& sensorName, double threshold, bool isUpperLimit);
    void checkThresholds() const;
    int getViolationsCount(const std::string& sensorName, double threshold, bool isUpperLimit) const;
};

#endif
