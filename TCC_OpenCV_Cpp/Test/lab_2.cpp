/*
 * Laboratório 2
 *
 * Workspace LAB2
 *
 * Objetivo: Trabalhar com lote de imagens.
 *
 */

#include "../image_tools.hpp"
using namespace img_tools;

using namespace std;
using namespace cv;

int main()
{
	string new_workspace(tools::current_dir() + "/LAB2");
	string new_method_name = "lab2_";
	string new_folder = "../Images/images_test/leaf_disease";
	string new_extension = "jpg";

	// Processar diretório com imagens
	bath(new_workspace, new_method_name, new_folder, new_extension);

	cout << '\n';
	vector<string> imgps = list_imgp(new_workspace);
	tools::view_vector_line(imgps, "\n");	

	return 0;
}