CXX=g++
CXX_FLAGS=-Wall -Wextra -pedantic -Weffc++ -std=c++17
OPENCV = `pkg-config --cflags --libs /usr/local/Cellar/opencv/4.1.0_3/lib/pkgconfig/opencv4.pc`
LIBS = $(OPENCV)
TARGET   := program


all: $(TARGET)

$(TARGET) : main.o motionDetection.o
	$(CXX) -o $@ $^ $(LIBS) $(CXX_FLAGS) 

main.o : main.cpp motionDetection.o
	$(CXX) $(LIBS) -std=c++17 -c $< -o$@

motionDetection.o : motionDetection.cpp motionDetection.h
	$(CXX) $(LIBS) -std=c++17 -c $< -o$@

clean: 
	$(RM) *.o $(TARGET)