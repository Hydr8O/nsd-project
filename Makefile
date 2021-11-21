SOURCE = source

.PHONY: clean

main: main.o ImagePreprocessor.o EdgeDetector.o ContourDetector.o
	g++ main.o ImagePreprocessor.o EdgeDetector.o ContourDetector.o -L./lib/opencv/lib -lopencv_core -lopencv_imgcodecs -lopencv_imgproc -o main


main.o: main.cpp
	g++ -std=c++11 -c main.cpp -I./lib/opencv/include/opencv4 -o main.o

ImagePreprocessor.o: ${SOURCE}/ImagePreprocessor.cpp
	g++ -c ${SOURCE}/ImagePreprocessor.cpp -I./lib/opencv/include/opencv4 -o ImagePreprocessor.o

EdgeDetector.o: ${SOURCE}/EdgeDetector.cpp
	g++ -c ${SOURCE}/EdgeDetector.cpp -I./lib/opencv/include/opencv4 -o EdgeDetector.o

ContourDetector.o: ${SOURCE}/ContourDetector.cpp
	g++ -c ${SOURCE}/ContourDetector.cpp -I./lib/opencv/include/opencv4 -o ContourDetector.o

clean:
	rm -rf *.o *.so