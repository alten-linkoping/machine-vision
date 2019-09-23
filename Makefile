CXX=g++
CXX_FLAGS=-Wall -Wextra -pedantic -Weffc++ -std=c++14
#OPENCV = `pkg-config --cflags --libs /usr/local/Cellar/opencv/4.1.0_3/lib/pkgconfig/opencv4.pc`
OPENCV = `pkg-config --cflags --libs opencv`
LIBS = $(OPENCV)
TARGET   := program

#export LDFLAGS="-L/usr/local/opt/opencv@3/lib"
#export CPPFLAGS="-I/usr/local/opt/opencv@3/include"

#For pkg-config to find opencv@3 you may need to set:


all: $(TARGET)

$(TARGET) : main_test.o HOGDetection.o
	$(CXX) -o $@ $^ $(LIBS) $(CXX_FLAGS) 

main_test.o : main_test.cpp HOGDetection.o
	$(CXX) $(LIBS) -std=c++14 -c $< -o$@

HOGDetection.o : HOGDetection.cpp HOGDetection.h
	$(CXX) $(LIBS) -std=c++14 -c $< -o$@

clean: 
	$(RM) *.o $(TARGET)