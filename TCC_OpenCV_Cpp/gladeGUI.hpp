#ifndef GLADE_GUI_HPP
#define GLADE_GUI_HPP

#include <gtkmm.h>

class GUI {
public:
	GUI(){};
	~GUI(){};
	static int open(int, char**);
};

#endif // GLADE_GUI_HPP