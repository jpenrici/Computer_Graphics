/*
  TCC
*/

#include "gladeGUI.hpp"
#include "image_processing.hpp"
#include <iostream>
#include <cstring>

using std::cout;

void terminal(int, char**);

int main (int argc, char **argv)
{
  bool openGUI = false;
  if (argc > 1) {
    if (std::strcmp(argv[1], "--gui") == 0) { openGUI = true; }
  }

  if (!openGUI) { terminal(argc, argv); }
  else {

    // GUI - interface Gráfica
    int argc_ = 1; // não usar os argumentos no Gtk::Application.
    auto app = Gtk::Application::create(argc_, argv, "org.gtkmm.example");

    // carregue o arquivo Glade
    auto refBuilder = Gtk::Builder::create();
    try  {
      refBuilder->add_from_file("gladeGUI.glade");
    } catch(const Glib::FileError& ex) {
      std::cerr << "FileError: " << ex.what() << "\n";
      return 1;
    } catch(const Glib::MarkupError& ex) {
      std::cerr << "MarkupError: " << ex.what() << "\n";
      return 1;
    } catch(const Gtk::BuilderError& ex) {
      std::cerr << "BuilderError: " << ex.what() << "\n";
      return 1;
    }

    // instanciar GtkWindow
    Gtk::Window* pWindow = nullptr;
    refBuilder->get_widget("gladeWindowMain", pWindow);

    // iniciar
    if(pWindow) { app->run(*pWindow); }

    delete pWindow;
  } 

  return (EXIT_SUCCESS);
}

// usar aplicação em Linha de Comando
void terminal(int argc, char** argv) {
  if (argc <= 2) {
    ImageProcessing::processing(argv[1]);
  } else {
    cout << "use:\n"
    << argv[0] << " <folder>  # images in the folder\n"
    << argv[0] << " <image>   # specific image\n"
    << argv[0] << "           # images in the current folder\n"
    << argv[0] << " --gui     # graphical user interface\n\n";
  }
}