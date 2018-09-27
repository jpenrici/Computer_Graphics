#include "../image_view.hpp"
#include <gtkmm/application.h>
#include <iostream>

int main(int argc, char** argv)
{
	auto app = Gtk::Application::create(argc, argv, "imageView.example");

	Image_view window;

	int status = app->run(window);

	if(status){
		return (EXIT_FAILURE);
	}

	return (EXIT_SUCCESS);
}