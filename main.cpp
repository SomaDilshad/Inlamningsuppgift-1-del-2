#include <iostream>
#include <memory>
#include "sensormanager.h"
#include "utils.h"

void displayMainMenu();
void handleFileOperations(SensorManager& manager);
void handleThresholdOperations(SensorManager& manager);

int main() {
    std::cout << "=== MULTI-SENSOR SYSTEM WITH INHERITANCE ===\n";
    std::cout << "Now with polymorphism and threshold analysis!\n\n";
    
    SensorManager manager;
    
    int choice;
    do {
        displayMainMenu();
        choice = Utils::hämtaIntegerInput("Enter your choice: ");
        
        switch (choice) {
            case 1:
                manager.listAllSensors();
                break;
            case 2: {
                int count = Utils::hämtaIntegerInput("Measurements per sensor: ");
                manager.takeMeasurements(count);
                break;
            }
            case 3:
                manager.showAllMeasurements();
                break;
            case 4:
                manager.showStatistics();
                break;
            case 5:
                handleFileOperations(manager);
                break;
            case 6:
                manager.clearAllData();
                break;
            case 7:
                handleThresholdOperations(manager);
                break;
            case 8:
                manager.checkThresholds();
                break;
            case 0:
                std::cout << "Exiting program...\n";
                break;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
        
        if (choice != 0) {
            std::cout << "\nPress Enter to continue...";
            std::cin.get();
        }
        
    } while (choice != 0);
    
    return 0;
}

void displayMainMenu() {
    std::cout << "\n=== MAIN MENU ===\n";
    std::cout << "1. List all sensors\n";
    std::cout << "2. Take new measurements\n";
    std::cout << "3. Show all measurements\n";
    std::cout << "4. Show statistics\n";
    std::cout << "5. File operations\n";
    std::cout << "6. Clear all data\n";
    std::cout << "7. Set thresholds (NEW)\n";
    std::cout << "8. Check thresholds (NEW)\n";
    std::cout << "0. Exit\n";
}

void handleFileOperations(SensorManager& manager) {
    std::cout << "\n1. Save to file\n";
    std::cout << "2. Load from file\n";
    
    int choice = Utils::hämtaIntegerInput("Choose: ");
    std::string filename;
    
    std::cout << "Enter filename: ";
    std::getline(std::cin, filename);
    
    if (choice == 1) {
        manager.saveToFile(filename);
    } else if (choice == 2) {
        manager.loadFromFile(filename);
    }
}

void handleThresholdOperations(SensorManager& manager) {
    std::string sensorName;
    double threshold;
    
    std::cout << "Enter sensor name: ";
    std::getline(std::cin, sensorName);
    
    threshold = Utils::hämtaDoubleInput("Enter threshold value: ");
    
    std::cout << "1. Upper limit (alerts when above)\n";
    std::cout << "2. Lower limit (alerts when below)\n";
    int type = Utils::hämtaIntegerInput("Choose limit type: ");
    
    manager.setThreshold(sensorName, threshold, type == 1);
}
