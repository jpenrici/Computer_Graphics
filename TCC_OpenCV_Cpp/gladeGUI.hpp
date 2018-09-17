#ifndef GLADE_GUI_HPP
#define GLADE_GUI_HPP

#include <gtkmm.h>
#include <iostream>

class GUI {
public:
	GUI();
	virtual ~GUI(){};

protected:
	// eventos
    void on_menu_file_open();
    void on_menu_file_save();
    void on_menu_file_save_as();
    void on_menu_file_quit();
    void on_menu_file_about();
    void on_button_1_clicked(); 
    void on_combobox_image_changed();  

    // janela principal
	Gtk::Window* window;
    Gtk::ImageMenuItem* menu_open;
    Gtk::ImageMenuItem* menu_save;
    Gtk::ImageMenuItem* menu_save_as;
    Gtk::ImageMenuItem* menu_quit;
    Gtk::ImageMenuItem* menu_about;    
    Gtk::Image* image_1;
    Gtk::Image* image_2;    
    Gtk::Button* button_1;
    Gtk::ComboBox* combobox_image;    
    Gtk::Statusbar* statusbar;
};

// GUI - interface Gráfica do usuário
GUI::GUI(): 
window(nullptr),
menu_open(nullptr),
menu_save(nullptr),
menu_save_as(nullptr),
menu_quit(nullptr),
menu_about(nullptr),
image_1(nullptr),
image_2(nullptr),
button_1(nullptr),
combobox_image(nullptr),
statusbar(nullptr)
{
    auto app = Gtk::Application::create("GUI");

    // carregue o arquivo Glade
    auto refBuilder = Gtk::Builder::create();
    try  {
      refBuilder->add_from_file("resources/gladeGUI.glade");
    } catch(const Glib::FileError& ex) {
      std::cerr << "FileError: " << ex.what() << "\n";
      exit(0);
    } catch(const Glib::MarkupError& ex) {
      std::cerr << "MarkupError: " << ex.what() << "\n";
      exit(0);
    } catch(const Gtk::BuilderError& ex) {
      std::cerr << "BuilderError: " << ex.what() << "\n";
      exit(0);
    }

    // instanciar GtkMenuBar
    refBuilder->get_widget("menu_open", menu_open);
    if (menu_open) {
        menu_open->signal_activate().connect(sigc::mem_fun(*this,
            &GUI::on_menu_file_open));
    }

    refBuilder->get_widget("menu_save", menu_save);
    if (menu_save) {
        menu_save->signal_activate().connect(sigc::mem_fun(*this,
            &GUI::on_menu_file_save));
    }

    refBuilder->get_widget("menu_save_as", menu_save_as);
    if (menu_save_as) {
        menu_save_as->signal_activate().connect(sigc::mem_fun(*this,
            &GUI::on_menu_file_save_as));
    }

    refBuilder->get_widget("menu_quit", menu_quit);
    if (menu_quit) {
        menu_quit->signal_activate().connect(sigc::mem_fun(*this,
            &GUI::on_menu_file_quit));
    }    

    refBuilder->get_widget("menu_about", menu_about);
    if (menu_about) {
        menu_about->signal_activate().connect(sigc::mem_fun(*this,
            &GUI::on_menu_file_about));
    }

    // instanciar GtkImage
    refBuilder->get_widget("image_1", image_1);
    refBuilder->get_widget("image_2", image_2);   
    
    // instanciar GtkButton
    refBuilder->get_widget("button_1", button_1);
    if (button_1) {
    	button_1->signal_clicked().connect(sigc::mem_fun(*this,
    	   &GUI::on_button_1_clicked));
    }

    // instanciar GtkComboBox
    refBuilder->get_widget("combobox_image", combobox_image);
    if (combobox_image) {
        combobox_image->signal_changed().connect(sigc::mem_fun(*this,
           &GUI::on_combobox_image_changed));
    }    

    // instanciar GtkStatusbar
    refBuilder->get_widget("statusbar", statusbar);

    // instanciar GtkWindow
    refBuilder->get_widget("glade_window_main", window);

    // configurações iniciais  

    if(window) {
        app->run(*window);
    }

    delete menu_open;
    delete menu_save;
    delete menu_save_as;
    delete menu_quit;
    delete menu_about;
    delete image_1;
    delete image_2;
    delete button_1;
    delete combobox_image;
    delete statusbar;
    delete window;
}

void GUI::on_menu_file_open()
{
    std::cout << "OPEN\n";
}

void GUI::on_menu_file_save()
{
    std::cout << "SAVE\n";
}

void GUI::on_menu_file_save_as()
{
    std::cout << "SAVE AS\n";
}

void GUI::on_menu_file_quit()
{
    std::cout << "QUIT\n";
}

void GUI::on_menu_file_about()
{
    std::cout << "ABOUT\n";
}

void GUI::on_button_1_clicked()
{
	std::cout << "BUTTON\n";
}

void GUI::on_combobox_image_changed()
{
    std::cout << "COMBO BOX\n";
}

#endif // GLADE_GUI_HPP