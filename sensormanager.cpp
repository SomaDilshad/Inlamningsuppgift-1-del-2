#include "sensormanager.h"
#include "utils.h"
#include <iostream>
#include <algorithm>

SensorManager::SensorManager() {
    createDefaultSensors();
}

void SensorManager::addSensor(std::unique_ptr<Sensor> sensor) {
    sensors.push_back(std::move(sensor));
}

void SensorManager::createDefaultSensors() {
    sensors.push_back(std::make_unique<TemperatureSensor>("TempSensor1"));
    sensors.push_back(std::make_unique<HumiditySensor>("HumiditySensor1"));
    sensors.push_back(std::make_unique<PressureSensor>("PressureSensor1"));
}

void SensorManager::listAllSensors() const {
    std::cout << "\n=== REGISTERED SENSORS ===\n";
    for (const auto& sensor : sensors) {
        std::cout << "- " << sensor->getSensorInfo() << "\n";
    }
}

std::vector<std::string> SensorManager::getSensorNames() const {
    std::vector<std::string> names;
    for (const auto& sensor : sensors) {
        names.push_back(sensor->getName());
    }
    return names;
}

void SensorManager::takeMeasurements(int measurementsPerSensor) {
    std::cout << "\nTaking " << measurementsPerSensor << " measurements per sensor...\n";
    
    for (int i = 0; i < measurementsPerSensor; i++) {
        for (const auto& sensor : sensors) {
            Measurement m = sensor->createMeasurement();
            storage.läggTillMätning(m);
            std::cout << "  " << sensor->getName() << ": " 
                      << Utils::formateraDouble(m.value) << " " 
                      << sensor->getUnit() << "\n";
        }
    }
    std::cout << "Completed! Added " << (measurementsPerSensor * sensors.size()) 
              << " measurements.\n";
}

void SensorManager::takeSingleMeasurement(const std::string& sensorName) {
    for (const auto& sensor : sensors) {
        if (sensor->getName() == sensorName) {
            Measurement m = sensor->createMeasurement();
            storage.läggTillMätning(m);
            std::cout << "Measurement taken: " << sensor->getName() << ": " 
                      << Utils::formateraDouble(m.value) << " " 
                      << sensor->getUnit() << "\n";
            return;
        }
    }
    std::cout << "Sensor " << sensorName << " not found.\n";
}

void SensorManager::showAllMeasurements() const {
    storage.visaAllaMätningar();
}

void SensorManager::showStatistics() const {
    storage.visaStatistikPerSensor();
}

void SensorManager::showSensorStatistics(const std::string& sensorName) const {
    storage.visaStatistikFörSensor(sensorName);
}

bool SensorManager::saveToFile(const std::string& filename) {
    return storage.sparaTillFil(filename);
}

bool SensorManager::loadFromFile(const std::string& filename) {
    return storage.laddaFrånFil(filename);
}

void SensorManager::clearAllData() {
    storage.rensAllaMätningar();
    std::cout << "All measurement data cleared.\n";
}

//=== NY FUNKTIONALITET: Threshold Analysis ===

void SensorManager::setThreshold(const std::string& sensorName, double threshold, bool isUpperLimit) {
    thresholds.push_back({sensorName, threshold, isUpperLimit});
    std::cout << "Threshold set for " << sensorName << ": " 
              << (isUpperLimit ? "Max " : "Min ") << threshold << "\n";
}

void SensorManager::checkThresholds() const {
    if (thresholds.empty()) {
        std::cout << "No thresholds configured.\n";
        return;
    }
    
    std::cout << "\n=== THRESHOLD ANALYSIS ===\n";
    for (const auto& th : thresholds) {
        int violations = getViolationsCount(th.sensorName, th.value, th.isUpperLimit);
        std::cout << th.sensorName << ": " << violations << " violations of "
                  << (th.isUpperLimit ? "upper" : "lower") << " limit " 
                  << Utils::formateraDouble(th.value) << "\n";
    }
}

int SensorManager::getViolationsCount(const std::string& sensorName, double threshold, bool isUpperLimit) const {
    int count = 0;
    // Hämta mätningar och räkna överträdelser
    auto measurements = storage.hämtaMätningarFörSensor(sensorName);
    
    for (const auto& m : measurements) {
        if (isUpperLimit && m.value > threshold) {
            count++;
        } else if (!isUpperLimit && m.value < threshold) {
            count++;
        }
    }
    return count;
}
