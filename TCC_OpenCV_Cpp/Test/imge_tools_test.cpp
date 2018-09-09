#include "../image_tools.hpp"
#include <iostream>

inline void test(int line)
{
	std::cout << "\n[ Line: " << line << "]\n";
}

int main()
{
	test(__LINE__);
	img_tools::workspace = "../Workspace/";
	img_tools::workspace_imgp = "../Workspace/imgp/";
	img_tools::initialize_imgp("Workspace/images/diseases/f1.png");

	test(__LINE__);
	img_tools::method_name = "method_basic_";
	img_tools::initialize_imgp("Workspace/images/diseases/f2.png");
	tools::write("MASK:" + img_tools::workspace +"output/mask/mask-"
		+ img_tools::name + ".png\n", img_tools::imgp_path);

	img_tools::method_name = "dpp-";
	img_tools::map_imgp = {
		{"ORIGINAL"  , "output/original/"},
		{"GRAYSCALE" , "output/grayscale/gray-"},
		{"BINARY"    , "output/binary/bin-"},
		{"MASK", "output/mask/mask-"},
		{"MASK_02", "output/mask/mask_02-"},
		{"MASK_03", "output/mask/mask_03-"},
		{"MASK_04", "output/mask/mask_04-"}
	};

	test(__LINE__);
	img_tools::create_imgp("Workspace/images/diseases/f1.png");
	test(__LINE__);
	img_tools::status_map();

	test(__LINE__);
	img_tools::recover_imgp("../Workspace/imgp/dpp-f1.imgp");
	img_tools::status_map();

	test(__LINE__);
	std::string directory = tools::get_directory(img_tools::get_path_map("MASK"));
	std::string filename = tools::get_filename(img_tools::get_path_map("MASK"));
	std::string name = tools::get_name(filename);
	std::string new_path = directory + name + ".txt";
	std::cout << new_path << '\n';
	tools::write(new_path, new_path);

	return 0;
}