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
	Gtk::ComboBox* combobox_image;
	Gtk::Image* image_1;
	Gtk::Image* image_2;
    Gtk::TextView* infoTextView;
    Gtk::Statusbar* statusbar;
    Gtk::MenuItem* menu_main;
    Gtk::MenuItem* menu_help;
};

// GUI - interface Gráfica
GUI::GUI(): 
window(nullptr),
button_clean(nullptr),
combobox_image(nullptr),
image_1(nullptr),
image_2(nullptr),
infoTextView(nullptr),
statusbar(nullptr),
menu_main(nullptr),
menu_help(nullptr)
{
    auto app = Gtk::Application::create("GUI");

    // carregue o arquivo Glade
    auto refBuilder = Gtk::Builder::create();
    try  {
      refBuilder->add_from_file("resources/gladeGUI.glade");
    } catch(const Glib::FileError& ex) {
      cerr << "FileError: " << ex.what() << "\n";
      exit(0);
    } catch(const Glib::MarkupError& ex) {
      cerr << "MarkupError: " << ex.what() << "\n";
      exit(0);
    } catch(const Gtk::BuilderError& ex) {
      cerr << "BuilderError: " << ex.what() << "\n";
      exit(0);
    }

    // instanciar GtkButton
    refBuilder->get_widget("button_clean", button_clean);
    if (button_clean) {
    	button_clean->signal_clicked().connect( sigc::mem_fun(*this,
    	&GUI::clean_on_btn_clicked));
    }

    // instanciar GtkComboBox
    refBuilder->get_widget("combobox_image", combobox_image);

    // instanciar GtkImage
    refBuilder->get_widget("image_1", image_1);
    refBuilder->get_widget("image_2", image_2);

    // instanciar GtkTextView
    refBuilder->get_widget("infoTextView", infoTextView);

    // instanciar GtkStatusbar
    refBuilder->get_widget("statusbar", statusbar);

    // instanciar GtkMenuBar
	refBuilder->get_widget("menu_main", menu_main);
	refBuilder->get_widget("menu_help", menu_help);

    // instanciar GtkWindow
    refBuilder->get_widget("glade_window_main", window);

    if(window) { app->run(*window); }

    delete window;
    delete button_clean;
    delete image_1;
    delete image_2;
    delete statusbar;
    delete infoTextView;
    delete menu_main;
    delete menu_help;
}

void GUI::clean_on_btn_clicked() {
	// cout << "clicked\n";
	// ImageProcessing::test();
}

#endif // GLADE_GUI_HPP