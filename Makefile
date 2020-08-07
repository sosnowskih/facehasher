TARGET = facehasher
SOURCES = $(wildcard src/*.cpp)
HEADERS = $(wildcard src/*.h*)
OBJECTS = $(SOURCES:%.cpp=%.o)
LD = g++
CXX = g++
CXXFLAGS = -std=c++14 -g -Wall -Iinclude -DGL_SILENCE_DEPRECATION 
LDFLAGS = -ljsoncpp -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_videoio -lopencv_videostab -lopencv_objdetect -lopencv_imgcodecs

.PHONY: all clean

all: $(TARGET)

clean:
	$(RM) src/*.o
	$(RM) $(TARGET)

$(TARGET): $(OBJECTS)
	$(LD) -o $@ $(OBJECTS) $(LDFLAGS)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

