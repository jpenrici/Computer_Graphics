#include "image_view.hpp"
#include <gtkmm/application.h>
#include <iostream>

int main(int argc, char** argv)
{
	auto app = Gtk::Application::create(argc, argv, "Image View");

	ImageView window;

	app->run(window);

	std::cout << "GUI fineshed!" << '\n';

	return (EXIT_SUCCESS);
}