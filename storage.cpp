#include "storage.h"
#include "utils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <iomanip>

void MeasurementStorage::läggTillMätning(const Measurement& m) {
    measurements.push_back(m);
}

void MeasurementStorage::visaAllaMätningar() const {
    if (measurements.empty()) {
        std::cout << "No measurements available.\n";
        return;
    }
    
    std::cout << "\n=== ALL MEASUREMENTS ===\n";
    for (const auto& m : measurements) {
        std::cout << m.sensorName << ": " 
                  << Utils::formateraDouble(m.value) << " " 
                  << m.unit << "\n";
    }
}

void MeasurementStorage::visaStatistikPerSensor() const {
    if (measurements.empty()) {
        std::cout << "No measurements available.\n";
        return;
    }
    
    std::cout << "\n=== STATISTICS PER SENSOR ===\n";
    
    // Hämta unika sensornamn
    std::vector<std::string> sensorNames;
    for (const auto& m : measurements) {
        if (std::find(sensorNames.begin(), sensorNames.end(), m.sensorName) == sensorNames.end()) {
            sensorNames.push_back(m.sensorName);
        }
    }
    
    // Beräkna statistik för varje sensor
    for (const auto& name : sensorNames) {
        visaStatistikFörSensor(name);
    }
}

void MeasurementStorage::visaStatistikFörSensor(const std::string& sensorName) const {
    std::vector<double> values;
    std::string unit;
    
    for (const auto& m : measurements) {
        if (m.sensorName == sensorName) {
            values.push_back(m.value);
            unit = m.unit;
        }
    }
    
    if (values.empty()) {
        std::cout << "No measurements found for " << sensorName << ".\n";
        return;
    }
    
    // Beräkna statistik
    double sum = 0.0;
    double min = values[0];
    double max = values[0];
    
    for (double v : values) {
        sum += v;
        if (v < min) min = v;
        if (v > max) max = v;
    }
    
    double mean = sum / values.size();
    
    // Standardavvikelse
    double variance = 0.0;
    for (double v : values) {
        variance += (v - mean) * (v - mean);
    }
    double stddev = std::sqrt(variance / values.size());
    
    std::cout << "\n--- " << sensorName << " ---\n";
    std::cout << "Count: " << values.size() << "\n";
    std::cout << "Mean: " << Utils::formateraDouble(mean) << " " << unit << "\n";
    std::cout << "Min: " << Utils::formateraDouble(min) << " " << unit << "\n";
    std::cout << "Max: " << Utils::formateraDouble(max) << " " << unit << "\n";
    std::cout << "Std Dev: " << Utils::formateraDouble(stddev) << " " << unit << "\n";
}

bool MeasurementStorage::sparaTillFil(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error: Could not open file " << filename << " for writing.\n";
        return false;
    }
    
    // Skriv CSV-header
    file << "SensorName,Unit,Value\n";
    
    // Skriv alla mätningar
    for (const auto& m : measurements) {
        file << m.sensorName << "," << m.unit << "," 
             << Utils::formateraDouble(m.value) << "\n";
    }
    
    file.close();
    std::cout << "Saved " << measurements.size() << " measurements to " << filename << ".\n";
    return true;
}

bool MeasurementStorage::laddaFrånFil(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error: Could not open file " << filename << " for reading.\n";
        return false;
    }
    
    measurements.clear();
    std::string line;
    bool firstLine = true;
    
    while (std::getline(file, line)) {
        if (firstLine) {
            firstLine = false;
            continue; // Skip header
        }
        
        if (line.empty()) continue;
        
        std::istringstream iss(line);
        std::string name, unit, valueStr;
        
        if (std::getline(iss, name, ',') &&
            std::getline(iss, unit, ',') &&
            std::getline(iss, valueStr)) {
            try {
                double value = std::stod(valueStr);
                measurements.push_back(Measurement(name, unit, value));
            } catch (...) {
                std::cout << "Warning: Could not parse line: " << line << "\n";
            }
        }
    }
    
    file.close();
    std::cout << "Loaded " << measurements.size() << " measurements from " << filename << ".\n";
    return true;
}

void MeasurementStorage::rensAllaMätningar() {
    measurements.clear();
}

std::vector<Measurement> MeasurementStorage::hämtaMätningarFörSensor(const std::string& sensorName) const {
    std::vector<Measurement> result;
    for (const auto& m : measurements) {
        if (m.sensorName == sensorName) {
            result.push_back(m);
        }
    }
    return result;
}
