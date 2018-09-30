#include "../image_tools.hpp"
#include <iostream>

inline void test(int line)
{
	std::cout << "\n[ Line: " << line << "]\n";
}

// Testes gerais
void test_1();	
void test_2();

int main()
{
	test_1();
	test_2();

	return 0;
}

void test_1()
{
	test(__LINE__);
	img_tools::create_workspace();

	test(__LINE__);
	img_tools::create_workspace("Workspace_1");

	test(__LINE__);
	img_tools::save_imgp("Images/images_test/leaf_diseases.jpg", "Workspace_2");

	test(__LINE__);
	std::cout << "load_imgp(\"Workspace_2/imgp/M0_leaf_diseases.imgp\")\n";
	std::vector<std::vector<std::string> > v_test;
	v_test = img_tools::load_imgp("Workspace_2/imgp/M0_leaf_diseases.imgp");

	test(__LINE__);
	tools::view_vector_2D(v_test);

	test(__LINE__);
	for (auto value: v_test) {
		if (value.front() == "#WORKSPACE" ||
			value.front() == "ORIGINAL")
			continue;

		std::cout << value.front() << ":\nsave: " << value.back() << '\n';
	}
}

void test_2()
{
	const std::unordered_map<std::string, std::string> map_lab = {
		{"ORIGINAL"  , "/original"},
		{"GRAYSCALE" , "/grayscale"},
		{"BINARY"    , "/binary"},
		{"BINARY_INV", "/binary_inv"},
		{"LAB_02"   , "/lab_02"},
		{"LAB_03"   , "/lab_03"},
		{"LAB_04"   , "/lab_04"}
	};

	test(__LINE__);
	img_tools::save_imgp("Images/images_test/leaf_diseases.jpg", "Work_LAB1",
		map_lab);

	test(__LINE__);
	img_tools::save_imgp("Images/images_test/leafs/f3.png", "Work_LAB1",
		map_lab);

	// irá escrever no .imgp somente o mapa padrão
	test(__LINE__);
	img_tools::save_imgp("Images/images_test/leafs/f4.png", "Work_LAB1");	
}