
CXX = g++

CXXFLAGS = -std=c++17 -Wall

TARGET = 1
SOURCE = 1.cpp

TARGET2 = 2
SOURCE2 = 2.cpp

TARGET3 = 3
SOURCE3 = 3.cpp

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCE)
	$(CXX) $(CXXFLAGS) -o $(TARGET2) $(SOURCE2)
	$(CXX) $(CXXFLAGS) -o $(TARGET3) $(SOURCE3)

clean:
	rm -f $(TARGET)
