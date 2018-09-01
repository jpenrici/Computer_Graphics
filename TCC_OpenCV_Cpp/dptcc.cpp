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
    if (std::strcmp(argv[1], "--gui") == 0) openGUI = true;
  }

  if (openGUI) {
    GUI win;
    return (win.open(argc, argv));
  } else {
    terminal(argc, argv);
  }

  return (EXIT_SUCCESS);
}

// usar aplicação em Linha de Comando
void terminal(int argc, char** argv)
{
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