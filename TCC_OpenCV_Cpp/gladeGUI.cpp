#include "gladeGUI.hpp"
#include "image_processing.hpp"

// GUI - interface Gráfica
GUI::GUI(): window(nullptr), button_clean(nullptr)
{
    auto app = Gtk::Application::create("dptccGUI");

    // carregue o arquivo Glade
    auto refBuilder = Gtk::Builder::create();
    try  {
      refBuilder->add_from_file("gladeGUI.glade");
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
    refBuilder->get_widget("btnClean", button_clean);
    if (button_clean) {
    	button_clean->signal_clicked().connect( sigc::mem_fun(*this,
    	&GUI::clean_on_btn_clicked));
    }

    // instanciar GtkWindow
    refBuilder->get_widget("gladeWindowMain", window);
    if(window) { app->run(*window); }

    delete window;
    delete button_clean;
}

void GUI::clean_on_btn_clicked() {
	cout << "clicked\n";
	ImageProcessing::test();
}