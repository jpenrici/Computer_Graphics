# Requirements
   
    cmake
    pkg-config
    opencv library

### cmake and run

    use: ./run <filename.cpp>

### g++

    use: g++ -std=c++17 -g -Wall <filename.cpp> -o <filenameRun> `pkg-config --cflags --libs opencv4`
	 ./<filenameRun>

	
# Reference source

    https://docs.opencv.org
