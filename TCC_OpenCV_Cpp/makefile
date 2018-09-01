# Makefile

dptcc : dptcc.o image_processing.o gladeGUI.o
	g++ -g -Wall -o dptcc dptcc.o image_processing.o gladeGUI.o `pkg-config gtkmm-3.0 --cflags --libs`

dptcc.o : dptcc.cpp image_processing.hpp gladeGUI.hpp
	g++ -g -Wall -c dptcc.cpp `pkg-config gtkmm-3.0 --cflags --libs`

gladeGUI.o : gladeGUI.cpp gladeGUI.hpp image_processing.hpp
	g++ -g -Wall -c gladeGUI.cpp `pkg-config gtkmm-3.0 --cflags --libs`

image_processing.o: image_processing.cpp image_processing.hpp
	g++ -g -Wall -c image_processing.cpp

clean:
	rm -f dptcc dptcc.o image_processing.o gladeGUI.o