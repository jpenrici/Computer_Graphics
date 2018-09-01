#ifndef GLADE_GUI_HPP
#define GLADE_GUI_HPP

#include <gtkmm.h>
#include <iostream>

using std::cerr;

class GUI {
public:
	GUI();
	virtual ~GUI(){};

protected:
	// eventos
	void clean_on_btn_clicked();

	Gtk::Window* window;
	Gtk::Button* button_clean;
};

#endif // GLADE_GUI_HPP