#ifndef UTILS_H
#define UTILS_H

#include <string>

class Utils {
public:
    static int hämtaIntegerInput(const std::string& prompt);
    static double hämtaDoubleInput(const std::string& prompt);
    static std::string formateraDouble(double value, int decimals = 2);
};

#endif
