/*
  TCC
*/

#include "gladeGUI.hpp"
#include "image_processing.hpp"

#include <iostream>
using std::string;
using std::cout;
using std::cin;

#include <cstring>

void terminal(int, char**);

int main (int argc, char **argv)
{
  bool openGUI = false;
  if (argc > 1) {
    if (std::strcmp(argv[1], "--gui") == 0) openGUI = true;
  }

  if (openGUI) { GUI win; } 
  else { terminal(argc, argv); }

  return (EXIT_SUCCESS);
}

// opções no terminal
int menu() {
  string msg(
    "option.....\n"
    "***********\n");

  int op(0);
  while (true) {
    cout << msg << "\n";
    cin >> op;
    if (op > 0 && op < 10) break;
    cout << "option error!\n";
  }

  return op;
}

// usar aplicação em Linha de Comando
void terminal(int argc, char** argv)
{
  if (argc <= 2) {
    int option = menu();
    switch (option) {
      case 1:
        ImageProcessing::processing(argv[1]);
        break;
      default:
        cout << ":(\n";
    }
  } else {
    cout << "use:\n"
    << argv[0] << " <folder>  # images in the folder\n"
    << argv[0] << " <image>   # specific image\n"
    << argv[0] << "           # images in the current folder\n"
    << argv[0] << " --gui     # graphical user interface\n\n";
  }
}