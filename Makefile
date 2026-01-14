CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
TARGET = sensorsystem_v2
SOURCES = main.cpp sensor.cpp measurement.cpp storage.cpp utils.cpp sensormanager.cpp

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)
