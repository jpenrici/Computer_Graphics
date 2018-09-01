#include "gladeGUI.hpp"
#include "image_processing.hpp"

// GUI - interface Gráfica
int GUI::open(int argc, char **argv) {

    int argc_ = 1; // não usar os argumentos no Gtk::Application.
    auto app = Gtk::Application::create(argc_, argv, "org.gtkmm.example");

    // carregue o arquivo Glade
    auto refBuilder = Gtk::Builder::create();
    try  {
      refBuilder->add_from_file("gladeGUI.glade");
    } catch(const Glib::FileError& ex) {
      std::cerr << "FileError: " << ex.what() << "\n";
      return (EXIT_FAILURE);
    } catch(const Glib::MarkupError& ex) {
      std::cerr << "MarkupError: " << ex.what() << "\n";
      return (EXIT_FAILURE);
    } catch(const Gtk::BuilderError& ex) {
      std::cerr << "BuilderError: " << ex.what() << "\n";
      return (EXIT_FAILURE);
    }

    // instanciar GtkWindow
    Gtk::Window* pWindow = nullptr;
    refBuilder->get_widget("gladeWindowMain", pWindow);

    // iniciar
    if(pWindow) { app->run(*pWindow); }

    delete pWindow;

    return (EXIT_SUCCESS);
}